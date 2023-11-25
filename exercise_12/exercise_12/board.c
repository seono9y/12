//
//  board.c
//  exercise_12
//
//  Created by 추서연 on 2023/11/25.
//

#include "board.h"

// board.h

#ifndef BOARD_H
#define BOARD_H

#define N_BOARD 20
#define BOARDSTATUS_OK 1
#define BOARDSTATUS_BROKEN 0

void board_initBoard(void);
int board_getBoardStatus(int pos);
int board_getBoardCoin(int pos);
void board_stepShark(void);

#endif /* BOARD_H */

#include "board.h"
#include <stdio.h>
#include <stdlib.h>

static int board_status[N_BOARD];
static int board_coin[N_BOARD];
static int shark_position;

void board_initBoard(void) {
    for (int i = 0; i < N_BOARD; ++i) {
        board_status[i] = BOARDSTATUS_OK;
        board_coin[i] = rand() % 3; // 임의로 동전 할당 (0, 1, 2 중 하나)
    }
    shark_position = N_BOARD - 1; // 상어 초기 위치 설정
}

int board_getBoardStatus(int pos) {
    return board_status[pos];
}

int board_getBoardCoin(int pos) {
    int coin = board_coin[pos];
    board_coin[pos] = 0; // 동전을 주우면 해당 칸의 동전을 없앰
    return coin;
}

void board_stepShark(void) {
    int steps = rand() % 5 + 1; // 1부터 5까지 랜덤한 칸 이동
    for (int i = 0; i < steps; ++i) {
        if (shark_position > 0) {
            board_status[shark_position] = BOARDSTATUS_OK; // 상어 이동 전 칸을 복구
            --shark_position;
            board_status[shark_position] = BOARDSTATUS_BROKEN; // 상어 이동 후 칸을 파손
        }
    }
}
