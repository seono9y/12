//
//  main.c
//  exercise_12
//
//  Created by 추서연 on 2023/11/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.c"
#include "board.h"
#define N_BOARD             20
#define MAX_CHARNAME        200
#define N_PLAYER            3
#define MAX_DIE             6
#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2
#define BOARDSTATUS_NOK     0
int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME]={"LIVE","DIE","END"};

int getAlivePlayer(void)
{
    int i;
    int cnt=0;

    for(i=0;i<=N_PLAYER;i++)
    {
        if(player_status[i]==PLAYERSTATUS_END)
            cnt++;
    }
    return cnt;
}

int getWinner(void)
{
    int i;
    int winner=0;
    int max_coin=-1;

    for(i=0;i<N_PLAYER;i++)
    {
        if(player_status[i]==PLAYERSTATUS_END && player_coin[i]>max_coin)
        {
            max_coin=player_coin[i];
            winner=i;
        }
    }
    return winner;
}

int getDieWinner(void)
{
    int i;
    int Diewinner=0;
    int max_coin=-1;

    for(i=0;i<N_PLAYER;i++)
    {
        if(player_status[i]==PLAYERSTATUS_DIE && player_coin[i]>max_coin)
        {
            max_coin=player_coin[i];
            Diewinner=i;
        }
    }
    return Diewinner;
}

int game_end(void)
{
    int i;
    int flag_end = 0;

    for (i=0;i<N_PLAYER;i++)
    {
        if(player_status[i]==PLAYERSTATUS_LIVE)
        {
            return 0;
        }
    }
    flag_end=1;

    if(flag_end){
        int AlivePlayers = getAlivePlayer();
        int winner = getWinner();
        int Diewinner = getDieWinner();

        printf("GAME END!!\n");

        if(AlivePlayers>0)
        {
            printf("%d players are alive! Winner is %s\n", AlivePlayers, player_name[winner]);
        }
        else
        {
            printf("All the players have died! Winner is %s\n", player_name[Diewinner]);
        }
        return 1;
    }
    return 0;
}
void opening(void){
    printf("====================================================\n");
    printf("                !!!!![SHARK GAME]!!!!!              \n");
    printf("====================================================\n");
}

int rolldie(void)
{
    return rand()%MAX_DIE+1;
}

void printPlayerStatus(int player)
{
    printf("%s : pos %i, coin %i, status %s\n", player_name[player],player_position[player],player_coin[player],player_statusString[player_status[player]]);
}


void printPlayerPosition(int player)
{
    int i;

        for (i=0;i<N_BOARD;i++)
        {
            printf("|");
            if(player_position[player]==i)
                printf("%c",player_name[player][0]);
            else
            {
                if(board_getBoardStatus(i) == BOARDSTATUS_NOK)
                    printf("X");
                else
                    printf(" ");
            }
        }
        printf("|\n");
    }


void checkDie(void)
{
    int i;
    
    for (i = 0; i < N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_LIVE)
        {
            if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
            {
                player_status[i] = PLAYERSTATUS_DIE;

                if (player_status[i] == PLAYERSTATUS_DIE)
                {
                    printf("%s in pos %i has died!! (coin %i)\n", player_name[i], player_position[i], player_coin[i]);
                }
            }
        }
    }
}


int main(int argc, char *argv[]) {
    int pos=0;
    int i;
    int turn=0;
    int flag_end = 0;

    srand((unsigned)time(NULL));

    opening();

    board_initBoard();
    
    for(i=0;i<N_PLAYER;i++)
    {
        player_position[i]=0;
        player_coin[i]=0;
        player_status[i]=PLAYERSTATUS_LIVE;
        //player_name
        printf("Player %i's name: ",i);
        scanf("%s",player_name[i]);
    }


    
    do {
        int step;
        char c;

        if(player_status[turn] !=PLAYERSTATUS_LIVE){
            turn=(turn+1)%N_PLAYER;
            continue;
        }

    
        int board_getBoardStatus(int pos);


        printf("----------------Player status ---------------\n");
        for (i=0;i<N_PLAYER;i++)
        {
            printPlayerStatus(i);
            printPlayerPosition(i);
        }
        printf("---------------------------------------------\n");


        
        printf("%s turn!! ",player_name[turn]);
        printf("Press any key to roll a die!\n");

        scanf("%s",&c);
        fflush(stdin);

        step=rolldie();

        
        player_position[turn] += step;
        if(player_position[turn]>=N_BOARD)
            player_position[turn] = N_BOARD-1;
            printf("Die result : %i, %s moved to %i!\n",step,player_name[turn],player_position[turn]);

        if (player_position[turn]==N_BOARD-1)
        {
            player_status[turn] = PLAYERSTATUS_END;

            if((player_status[turn] = PLAYERSTATUS_END))
                {
                    printf("%s reached the end!! (coin : %i)\n",player_name[turn],player_coin[turn]);
                }
        }

    
        int coinResult = board_getBoardStatus(player_position[turn]);
        player_coin[turn] += coinResult;
            if (coinResult>=1)
                printf("    -> Lucky! %s got %d coins\n", player_name[turn],coinResult);


       
        turn=(turn+1)%N_PLAYER;//wrap around
        
        if (turn==0)
        {
            int shark_pos = board_stepShark();
            printf("Shark moved to %i\n", shark_pos);
            checkDie();

            game_end();
        }

    } while(1);
    
    return 0;
}
