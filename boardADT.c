//  COMP9024 Assignment 1 - Sliding-Tile Puzzle
//  boardADT.c
//  puzzle
//
//  Created by jilingy on 2019/6/22.
//  Copyright © 2019 jilingy. All rights reserved.
//

#include "boardADT.h"

/**
 * initialize the board
 */
struct boardStructure {
    //length of board
    int length;
    // each numbers and blank
    int *numbers;
};

/**
 * create a new board
 * return board
 */
Board newBoard(char *values) {
    Board board = malloc(sizeof(struct boardStructure));
    int compValue=0;
    char *eachNumber;
    unsigned long len = strlen(values);
    for (int i=0;i<len;i++) {
        if (*(values+i)=='b') {
            continue;
            //if a-z, A-Z,continue
        }else if ((*(values+i)>='a'&& *(values+i)<='z') || (*(values+i)>='A' && *(values+i)<='Z')) {
            //*(values+i)='b';
            //continue;
            return NULL;
        }
        //eliminate tab
        if (!isdigit(*(values+i))) {
            *(values+i)=' ';
        }
    }
    
    //check board is null or not
    if (board == NULL) {
        return board;
    }else if (board!=NULL){
        // initialize the board
        board->length = 0;
        board->numbers = NULL;
        if (values!=NULL) {
            //To get eachnumber, split空格
            eachNumber = strtok(values, " ");
            //to get head pointer
            board->numbers = malloc(INITIAL * sizeof(int));
            //continue to get number
            while( eachNumber != NULL ) {
                //whether "b"
                compValue = strcmp(eachNumber, "b");
                //if the element is not b
                if(compValue < 0 || compValue>0 ){
                    *(board->length + board->numbers) = atoi(eachNumber);
                }else{
                    *(board->length + board->numbers) = 0;
                }
                eachNumber = strtok(NULL, " ");
                //count length
                board->length++;
            }
        }
    }
    return board;
}


/**
 * display the board
 * print the board
 */
void displayBoard(Board board){
    int length=0;
    length = board->length;
    
    for (int i=0; i<length; i++) {
        //if the value is b, print "b"
        if (*(board->numbers + i)==0) {
            printf("b ");
        //else print the value
        }else{
            printf("%d ", *(board->numbers + i));
        }
    }
    printf("\n");
}

/**
 * get board size
 * return size
 */
int getSize(Board board){
    int size = 0;
    // set board size
    if (board != NULL) {
        size = (int) sqrt(board->length);
    }
    return size;
}

/**
 * get blank position
 * return blank position
 */
int blankPos(Board board){
    int blankPos=0;
    int size =0;
    size = getSize(board);
    if (board != NULL) {
        //如果size是偶数
        for (int i = 0; i < 10; i++) {
            blankPos+= i / size + 1;
        }
    }
    return blankPos;
}

/**
 * check the each number exist or not
 * return true: each number is existed; false: each number is not existed
 */
bool isExisted(Board board){
    int length = 0;
    int sum = 0;
    int sumNumbers = 0;
    length = board->length;
    for (int i=0; i<length; i++) {
        sum+=i;
    }
    
    //if number is greater than length, return false
    for (int i=0; i<length; i++) {
        sumNumbers+=*(board->numbers + i);
        if (*(board->numbers + i)>=length) {
            return false;
        }
    }
    
    //if numbers's sum is not equal to sum(1+2+...+length)
    if (sumNumbers!=sum) {
        return false;
    }
    
    //check whether number repeated or not
    for (int i = 0; i < length; i++) {
        bool temp =false;
        for (int k = 0; k < length; k++) {
            if (i==*(board->numbers + k)) {
                temp = true;
                break;
            }
        }
        if(!temp){
            return temp;
        }
    }
    return true;
}


/**
 * check how many "b" in the board
 * return "b"'s number
 */
int bCheck(Board board) {
    int length = 0;
    int count =0;
    int zero = 0;
    length = board->length;
    
    for (int a = 0; a<length; a++) {
        if (*(board->numbers + a)==zero) {
            count++;
        }
    }
    return count;
}


/**
 * check board is valid or not
 * return true: valid; false: is not valid
 */
bool isValid(Board origin, Board target) {
    int oLength=0;
    int oSize =0;
    int tLength=0;
    int tSize =0;
    oSize = getSize(origin);
    oLength = origin->length;
    tSize = getSize(target);
    tLength = target->length;
    
    //printf("oSize: %d\n",oSize);
    //printf("tSize: %d\n",tSize);
    //printf("oLength: %d\n",oLength);
    //printf("tLength: %d\n",tLength);
    
    //check two boards are null or not
    if (origin == NULL || target == NULL || origin->numbers == NULL || target->numbers == NULL) {
        printf("Board Error.\n");
        return false;
    }
    //check origin's length is smaller than 2 or (size)^2 != length
    if (oLength==0 || oSize < 2 || oSize * oSize != oLength) {
        printf("Start's size Error.\n");
        return false;
    }
    //check target's length is smaller than 2 or (size)^2 != length
    if (tLength==0 || tSize < 2 || tSize * tSize != tLength) {
        printf("Goal's si1ze Error.\n");
        return false;
    }
    
    //check b's number
    if (bCheck(origin)!=1 || bCheck(target)!=1 ) {
        printf("There should be one blank space.\n");
        return false;
    }
    //check each number existed or not
    if (isExisted(origin)==0 || isExisted(target)==0 ) {
        printf("Input Error.\n");
        return false;
    }
    
    return true;
}

/**
 * get disorder numbers
 * return disorder numbers of board
 */
int countDisorder(Board board) {
    // check size
    int blank = 0;
    int disNum = 0;
    int length=0;
    int size =0;
    blank = blankPos(board);
    size = getSize(board);
    length = board->length;
    //check board
    if (board != NULL) {
        //if the board size is even
        if (size % 2 == 0){
            for (int i = 0; i < length; i++) {
                for (int j = i + 1; j < length; j++) {
                    if (*(board->numbers + j) != 0) {
                        disNum += *(board->numbers + i) > *(board->numbers + j);
                    }
                }
                disNum += blank;
            }
        //if the board size is odd
        }else{
            for (int i = 0; i < length; i++) {
                for (int j = i + 1; j < length; j++) {
                    if (*(board->numbers + j) != 0) {
                        disNum += *(board->numbers + i) > *(board->numbers + j);
                    }
                }
            }
        }
    }
    return disNum;
}

/**
 * free board
 */
void freeBoard(Board board) {
    //check board is null or not 
    if (board != NULL) {
        if (board->numbers != NULL) {
            free(board->numbers);
        }
        free(board);
    }
}

