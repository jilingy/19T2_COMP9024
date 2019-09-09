//  COMP9024 Assignment 1 - Sliding-Tile Puzzle
//  boardADT.h
//  puzzle
//
//  Created by jilingy on 2019/6/22.
//  Copyright © 2019 jilingy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INITIAL 1024

/**
 * create type Board
 */
typedef struct boardStructure *Board;

/**
 * create board
 * return a new board
 */
Board newBoard(char*);

/**
 * display board
 */
void displayBoard(Board);

/**
 * get board's length
 * return board's length
 */
int getLength(char*);

/**
 * get "b"'s position
 * return "b"'s position
 */
int blankPos(Board);

/**
 * check how many "b" in the board
 * return "b"'s number
 */
int bCheck(Board);

/**
 * check board is valid or not
 * return true: valid; false: is not valid
 */
bool isValid(Board,Board);

/**
 * check each number is existed or not, according to length of the board
 * return true: each number is existed; false: each number is not existed.
 */
bool isExisted(Board);

/**
 * get disorder numbers
 * return disorder numbers of board
 */
int countDisorder(Board);

/**
 * free board
 */
void freeBoard(Board);

