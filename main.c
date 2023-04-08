#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define M 3
#define ALL_OK 0
#define ERROR1 "Error getting the name inputed goodbye"
#define ERROR_CODE1 1
#define ERROR2 "Error getting the character inputed goodbye"
#define ERROR_CODE2 2
#define BUFFER_Size 256
#define ERROR3 "Empty String"
#define ERROR_CODE3 3
#define PLAYER1 1
#define PLAYER2 2

typedef enum Winner {FIRSTPLAYER, SECONDPLAYER, TIE, NOWINNER} Winner;
typedef enum Character {X, O} Character; 
typedef struct {
   Character character;
   char *name; 
} Player;

typedef struct {
    Player player1;
    Player player2;
    char board[M][M];
    int turn;
    Winner winner;
} Game;
int getParamaters(Game *game);
void printBoard(const Game *game);
int getChar(char *choice);
bool checkDown(const Game *game, const char choice, const char playerCharacter);
bool checkLeft(const Game *game, const char choice, const char playerCharacter);
void whoIsWinner(Game *game);
bool checkPrimaryDiaganal(const Game *game, const char playerCahracter);
bool checkSecondaryDiaganal(const Game *game, const char playerCahracter);
bool isFull(const Game *game);
void getWinner(Game *game ,const char choice);
int turn(Game *game);
bool isValidChoice(const Game *game, const int choice);
void enterChoice(Game *game, const int choice, const char playerCharacter);

int main()
{
    char choice;
    Game game;
    do
    {
        if(getParamaters(&game))
        {
            return -1;
        }
        while(game.winner == NOWINNER)
        {
            turn(&game);
        }
        switch (game.winner)
        {
        case TIE:
            printf("It is a tie! \n");
            break;
        case FIRSTPLAYER:
            printf("%s is the winner!", game.player1.name);
            break;
        case SECONDPLAYER:
            printf("%s is the winner!", game.player2.name);
            break;
        default:
            break;
        }
        printf("Would you like to play again?\nPress y for yes and n for no\n");
        if(getChar(&choice))
        {
            return -1;
        }
        while(choice != 'n' && choice != 'y')
        {
            printf("Invalid character please enter your selection again");
            if(getChar(&choice))
            {
                return -1;
            }
        }
    }while(choice != 'n');
    
    free(game.player1.name);
    free(game.player2.name);
    return 0;
}
int getChar(char *choice)
{
    if(!scanf(" %c",choice))
    {
        printf(ERROR2);
        return ERROR_CODE2;
    }
    return ALL_OK;
}

bool checkDown(const Game *game, const char choice, const char playerCharacter)
{
    int counter = 0;
    for(int i = 0; i < M; i++)
    {
        if(game->board[(int) ((choice-1)/M)][i] == playerCharacter)
        {
           counter++;
        }
    }
        if(counter == M)
        {
            return true;
        }
    return false;
}

bool checkLeft(const Game *game, const char choice, const char playerCharacter)
{
    int counter = 0;
    for(int i = M-1; i >=0 ; i--)
    {
        if(game->board[i][(int) ((choice-1)/M)] == playerCharacter)
        {
           counter++;
        }
    }
        if(counter == M)
        {
            return true;
        }
    return false;
}
void whoIsWinner(Game *game)
{
    if(game->turn == PLAYER1)
    {
        game->winner = FIRSTPLAYER;
    }
    else
    {
        game->winner = SECONDPLAYER;
    }
}
bool checkPrimaryDiaganal(const Game *game, const char playerCahracter)
{
    int counter = 0;
    for(int i = 0; i < M ; i++)
    {
        if(game->board[i][i] == playerCahracter)
        {
            counter++;
        }
    }
    if(counter == M)
    {
        return true;
    }
    return false;
}
bool checkSecondaryDiaganal(const Game *game, const char playerCahracter)
{
    int counter = 0;
    for(int i = 0, j = M-1; i < M ; i++, j--)
    {
        if(game->board[i][j] == playerCahracter)
        {
            counter++;
        }
    }
    if(counter == M)
    {
        return true;
    }
    return false;
}
bool isFull(const Game *game)
{
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(game->board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}
void getWinner(Game *game ,const char choice)
{
    char playerCharacter;
    if(game->turn == PLAYER1)
    {
        playerCharacter = game->player1.character;
    }
    else
    {
        playerCharacter = game->player2.character;
    }
    if(isFull(game))
    {
        game->winner=TIE;
    }
    if((!((int) (choice%M))) || ((int) (choice%M) == 1))
    {
        if(choice/M == 1)
        {
            if((int)(choice%M) == 1)
            {
                if(checkPrimaryDiaganal(game, playerCharacter))
                {
                    whoIsWinner(game);
                }
            }
            else
            {
                if(checkSecondaryDiaganal(game,playerCharacter))
                {
                    whoIsWinner(game);
                } 
            }
            if(checkDown(game, choice ,playerCharacter) || checkLeft(game,choice, playerCharacter) )
            {
                whoIsWinner(game);
            }
        }
        else if((int) (choice/M) == 2)
        {
            if(checkLeft(game,choice, playerCharacter))
            {
                whoIsWinner(game);
            }
        }
        else
        {
            if(!((int)(choice%M)))
            {
                if(checkPrimaryDiaganal(game, playerCharacter))
                {
                    whoIsWinner(game);
                }
            }
            else
            {
                if(checkSecondaryDiaganal(game,playerCharacter))
                {
                    whoIsWinner(game);
                } 
            }
            if(checkLeft(game,choice, playerCharacter) || checkDown(game,choice, playerCharacter))
            {
                whoIsWinner(game);
            }
        }  
    }
    else
    {
        if(checkDown(game, choice, playerCharacter) || checkLeft(game, choice, playerCharacter))
        {
            whoIsWinner(game);
        }
    }
}


int turn(Game *game)
{
    int choice;
    char playerCharacter;
    bool flag = true;
    if(game->turn == PLAYER1)
    {
        playerCharacter = game->player1.character;
        printf("%s it is your turn.\nPlease choose your spot using the appropriate number or enter 10 to display the board\n", game->player1.name);  
    }
    else
    {
        playerCharacter = game->player2.character;
        printf("%s it is your turn.\nPlease choose your spot using the appropriate number or enter 10 to display the board\n", game->player2.name);    
    }
    if(!scanf("%d", &choice))
        {
            printf(ERROR2);
            return ERROR_CODE2;
        }
    while(flag)
    {
        if(choice == 10)
        {
            printBoard(game);
            printf("Please enter your choice \n");
            if(!scanf("%d", &choice))
            {
                printf(ERROR2);
                return ERROR_CODE2;
            }
            
        }
        else if (isValidChoice(game, choice))
        {
            enterChoice(game, choice, playerCharacter);
            flag = false;
        }
        else
        {
            printf("Invalid Option! Please choose again\n");
            if(!scanf("%d", &choice))
            {
                printf(ERROR2);
                return ERROR_CODE2;
            }
        }
    }
    if(game->turn == PLAYER1)
    {
        game->turn = PLAYER2;
    }
    else
    {
        game->turn = PLAYER1;
    }
    printBoard(game);
    return ALL_OK;
}
bool isValidChoice(const Game *game, const int choice)
{
    if(!(choice%M))
    {
        return ( (game->board[(choice-1)/M][choice%M] == ' ') &&  ((choice <= 9) && (choice > 0)) );
    }
    return ( (game->board[choice/M][choice%M] == ' ') &&  ((choice <= 9) && (choice > 0)) );
}
void enterChoice(Game *game, const int choice, const char playerCharacter)
{
    
    if(!(choice%M))
    {
        game->board[(choice-1)/M][choice%M] = playerCharacter;
    }
    else
    {
        game->board[choice/M][choice%M] = playerCharacter; 
    }
}

int getParamaters(Game *game)
{
    char choice;
    char buffer[BUFFER_Size]="";
    printf("Player1 please enter your name: \n");
    if(!scanf(" %s", buffer))
    {
        printf(ERROR1);
        return ERROR_CODE1;
    }
    if(!strlen(buffer))
    {
        printf(ERROR3);
        return ERROR_CODE3;
    }
    game->player1.name = (char*) malloc(strlen(buffer) + 1);
    if(!game->player1.name)
    {
        printf(ERROR3);
        free(game->player1.name);
        return ERROR_CODE3;
    }
    strcpy(game->player1.name , buffer);
    printf("Please enter your prefered character %s.\nChoose X or O\n", game->player1.name);
    if(getChar(&choice))
    {
        return ERROR_CODE2;
    }
    printf("Player2 please enter your name: \n");
    if(!scanf(" %s", buffer))
    {
        printf(ERROR1);
        return ERROR_CODE1;
    }
    if(!strlen(buffer))
    {
        printf(ERROR3);
        return ERROR_CODE3;
    }
    game->player2.name = (char*) malloc(strlen(buffer) + 1);
    if(!game->player2.name)
    {
        printf(ERROR3);
        free(game->player1.name);
        free(game->player2.name);
        return ERROR_CODE3;
    }
    strcpy(game->player2.name , buffer);
    switch (choice)
    {
    case 'X':
        game->player1.character = X ;
        game->player2.character = O;
        break;
    default:
        game->player1.character = O;
        game->player2.character = X;
        break;
    }
    game->turn = 1;
    game->winner = NOWINNER;
    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
        {
            game->board[i][j]= ' ';
        }
    return ALL_OK;
}

void printBoard(const Game *game)
{
    for(int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%c", game->board[i][j]);
            if(j != 2)
            {
                printf(" | ");
            }
        }
        if(i != 2)
        {
             printf("\n---------\n");
        }
       else
       {
        printf("\n");
       }
    }
}