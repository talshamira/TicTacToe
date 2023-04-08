#include "TicTacToe.h"

ERROR getChar(char *choice)
{
    if(!scanf(" %c",choice))
    {
        printf(ERROR2);
        return DATA_FAIL;
    }
    return SUCCESS;
}

bool checkDown(const Game *game, const char choice, const Character playerCharacter)
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

bool checkLeft(const Game *game, const char choice, const Character playerCharacter)
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
bool checkPrimaryDiaganal(const Game *game, const Character playerCahracter)
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
bool checkSecondaryDiaganal(const Game *game, const Character playerCahracter)
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
    int counter = 0;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(game->board[i][j] == X || game->board[i][j] == O)
            {
                counter++;
            }
        }
    }
    return (counter == M*M);
}
void getWinner(Game *game ,const int choice)
{
    Character playerCharacter;
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
    if((!(choice%M)) || ((choice%M) == 1))
    {
        if(choice%M == 1)
        {
            if(!choice/M)
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
        else
        {
            if(!(choice%M))
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


ERROR turn(Game *game)
{
    int choice;
    Character playerCharacter;
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
            return DATA_FAIL;
        }
    while(flag)
    {
        if(choice == PRINT)
        {
            printBoard(game);
            printf("Please enter your choice \n");
            if(!scanf("%d", &choice))
            {
                printf(ERROR2);
                return DATA_FAIL;
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
                return DATA_FAIL;
            }
        }
    }
    getWinner(game, choice);
    if(game->turn == PLAYER1)
    {
        game->turn = PLAYER2;
    }
    else
    {
        game->turn = PLAYER1;
    }
    printBoard(game);
    return SUCCESS;
}
bool isValidChoice(const Game *game, const int choice)
{
    if(!(choice%M))
    {
        return ( ((game->board[(choice/M) -1][M-1] != X) && (game->board[(choice/M) -1][M-1] != O)) &&  ((choice <= 9) && (choice > 0)) );
    }
    return ( ((game->board[choice/M][(choice%M)-1] != X) && (game->board[choice/M][(choice%M)-1] != O)) &&  ((choice <= 9) && (choice > 0)) );
}
void enterChoice(Game *game, const int choice, const Character playerCharacter)
{
    
    if(!(choice%M))
    {
        game->board[(choice/M)-1][M-1] = playerCharacter;
    }
    else
    {
        game->board[choice/M][(choice%M) -1] = playerCharacter; 
    }
}

ERROR getParamaters(Game *game)
{
    char choice;
    char buffer[BUFFER_Size]="";
    printf("Player1 please enter your name: \n");
    if(!scanf(" %s", buffer))
    {
        printf(ERROR1);
        return DATA_FAIL;
    }
    if(!strlen(buffer))
    {
        printf(ERROR3);
        return EMPTY_STRING;
    }
    game->player1.name = (char*) malloc(strlen(buffer) + 1);
    if(!game->player1.name)
    {
        printf(ERROR3);
        free(game->player1.name);
        return EMPTY_STRING;
    }
    strcpy(game->player1.name , buffer);
    printf("Please enter your prefered character %s.\nChoose X or O\n", game->player1.name);
   do
   {
        if(getChar(&choice) != SUCCESS)
        {
            return DATA_FAIL;
        }
        if(choice != 'X' && choice != 'O')
        {
            printf("Invalid Choice!\nPlease enter a valid option\n");
        }
   } while(choice != 'X' && choice != 'O');
    printf("Player2 please enter your name: \n");
    if(!scanf(" %s", buffer))
    {
        printf(ERROR1);
        return DATA_FAIL;
    }
    if(!strlen(buffer))
    {
        printf(ERROR3);
        return EMPTY_STRING;
    }
    game->player2.name = (char*) malloc(strlen(buffer) + 1);
    if(!game->player2.name)
    {
        printf(ERROR3);
        free(game->player1.name);
        free(game->player2.name);
        return EMPTY_STRING;
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
    return SUCCESS;
}

void printBoard(const Game *game)
{
    for(int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if(game->board[i][j] == X)
            {
                printf("X");
            }
            else if(game->board[i][j] == O)
            {
                printf("O");
            }
            else
            {
                printf(" ");
            }
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
