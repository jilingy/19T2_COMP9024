//  COMP9024 Assignment 1 - Sliding-Tile Puzzle
//  puzzle.c
//  puzzle
//
//  Created by jilingy on 2019/6/22.
//  Copyright © 2019 jilingy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "boardADT.h"


int main(int argc, char **argv) {
    char *start;
    char *goal;
    char *startVal;
    char *goalVal;
    
    start= malloc(INITIAL * sizeof(char));
    goal= malloc(INITIAL * sizeof(char));
    startVal = fgets(start, INITIAL, stdin);
    goalVal = fgets(goal, INITIAL, stdin);
    
    //create origin board and target board
    Board origin = newBoard(startVal);
    Board target = newBoard(goalVal);
    
    //check malloc is null or not
    if (start==NULL||goal==NULL)
    {
        printf("Can't get memory for taht many values.\n");
        return EXIT_FAILURE;
    }
    
    //check board is null or not
    if (origin==NULL||target==NULL) {
        printf("Board is false.\n");
        return EXIT_FAILURE;
    }
    
    // check board is valid or not
    if (isValid(origin,target)==0){
        //printf("start: ");
        //displayBoard(origin);
        //printf("goal: ");
        //displayBoard(target);
        return EXIT_FAILURE;
    }else{
        // check board's  disordering numbers,and check solvalbility
        if (countDisorder(target) % 2 == countDisorder(origin) % 2) {
            printf("start: ");
            displayBoard(origin);
            printf("goal: ");
            displayBoard(target);
            printf("solvable\n");
        }else{
            printf("start: ");
            displayBoard(origin);
            printf("goal: ");
            displayBoard(target);
            printf("unsolvable\n");
        }
    }
    
    // free memories
    free(start);
    free(goal);
    freeBoard(origin);
    freeBoard(target);
    
    return EXIT_SUCCESS;
}



