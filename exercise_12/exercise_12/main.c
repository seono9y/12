//
//  main.c
//  board.h
//  exercise_12
//
//  Created by 추서연 on 2023/11/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// board.h

#ifndef BOARD_H
#define BOARD_H

#define N_BOARD 20
#define BOARDSTATUS_OK 1
#define BOARDSTATUS_BROKEN 0

void board_initBoard();
int board_getBoardStatus(int pos);
int board_getBoardCoin(int pos);
void board_stepShark();
void board_printBoardStatus();

#endif

int main(int argc, const char * argv[]) {
   
    srand((unsigned)time(NULL));
    
    printf("=====================================================\n");
    printf("*****************************************************\n");
    printf("                     BINGO GAME                      \n");
    printf("*****************************************************\n");
    printf("*****************************************************\n\n\n");
    
    
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("=====================================================\n");
    printf("*****************************************************\n");
    printf("                 CONGRATULATION!!!!                  \n");
    printf("$$$$$$$$$$$$$$$$(    BINGO!!!!!   )$$$$$$$$$$$$$$$$$ \n");
    printf("                 CONGRATULATION!!!!                  \n");
    printf("*****************************************************\n");
    printf("=====================================================\n\n");
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define N_PLAYER 3
#define PLAYERSTATUS_LIVE 1
#define PLAYERSTATUS_DIE 0

typedef struct {
    char name[20];
    int position;
    int coins;
    int status;
} Player;

void initializePlayers(Player players[], int numPlayers);
void printGameStatus(Player players[], int numPlayers);
int rollDice();
void movePlayer(Player *player, int steps);
void sharkAttack(Player players[], int numPlayers);
int checkDie(Player players[], int numPlayers);
int game_end(Player players[], int numPlayers);
int getAlivePlayer(Player players[], int numPlayers);
int getWinner(Player players[], int numPlayers);

int main () {
    srand(time(NULL));

    Player players[N_PLAYER];
    initializePlayers(players, N_PLAYER);

    board_initBoard();

    int turn = 0;

    do {
        printf("\n%s 플레이어의 차례\n", players[turn].name);
        printGameStatus(players, N_PLAYER);

        int diceResult = rollDice();
        printf("주사위 결과: %d\n", diceResult);

        movePlayer(&players[turn], diceResult);
        int coin = board_getBoardCoin(players[turn].position);
        players[turn].coins += coin;

        if (players[turn].position >= N_BOARD - 1) {
            players[turn].status = PLAYERSTATUS_DIE;
        }

        sharkAttack(players, N_PLAYER);
        ++turn;
        turn %= N_PLAYER;

    } while (game_end(players, N_PLAYER));

    printf("\n게임 종료!\n");
    printf("생존 플레이어 수: %d\n", getAlivePlayer(players, N_PLAYER));
    printf("승자: %s\n", players[getWinner(players, N_PLAYER)].name);

    return 0;
}


