#include "TicTacToe.h"

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
            printf("%s is the winner!\n", game.player1.name);
            break;
        case SECONDPLAYER:
            printf("%s is the winner!\n", game.player2.name);
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
    printf("Thanks for playing!!!");
    free(game.player1.name);
    free(game.player2.name);
    return 0;
}
