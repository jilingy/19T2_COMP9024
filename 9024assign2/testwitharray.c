//
//  main.c
//  assign2
//
//  Created by jilingy on 2019/7/24.
//  Copyright © 2019 jilingy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Quack.h"
#include "Graph.h"

#define INITIAL 1024
#define WHITESPACE 100
#define MAXVERTICES 1000
#define MAXLENGTH 21
bool differByOne(char *preword, char *currword);
int getLength(char *word);
int readNumV(void);
int readGraph(int numV, Graph g);

int main(int argc, char *argv[]){
    char *str;
    char *p;
    char delimiters[]=" \n\t\r";
    int numV=0;
    
    //建立了二维数组，把每个单词d放到每一行
    char strArray[MAXVERTICES][MAXLENGTH];
    
    str= malloc(INITIAL * sizeof(char));

    if (str==NULL)
    {
        fprintf(stderr, "Can't get memory for that many values.\n");
        return EXIT_FAILURE;
    }
    
    str=fgets(str, INITIAL, stdin);
    //p：the first word
    p = strtok(str,delimiters);
    
    //如果没有任何输入,算失败还是成功？
    if (p==NULL) {
        printf("Dictionary\n");
        printf("Ordered Word Ladder Graph\n");
        printf("V=0, E=0\n");
        printf("Longest ladder length: 0\n");
        return EXIT_SUCCESS;
    }

    //To breaks string str into a series of p using delimiters.
    while(p){
        if (numV==0) {
            printf("Dictionary\n");
        }
        printf("%d: %s\n",numV,p);
        strcpy(strArray[numV], p);
        numV++;
        p= strtok(NULL,delimiters);
    }
/*
    printf("分隔分隔分隔分隔分隔分隔分隔分隔分隔分隔\n");
    for (int i = 0; i < numV; i++) { // 外循环取出一维数组
        printf("%s", strArray[i]);
        printf("\n");
    }
*/
    
    if (numV >= 0) {
        Graph g = newGraph(numV);
        for (int i = 0; i < numV-1; i++) { // 外循环取出一维数组
            for (int j = i+1; j < numV; j++) { // 外循环取出一维数组
                if (differByOne(strArray[i], strArray[j])) {
                    insertEdge(newEdge(i, j), g);
                }
            }
        }
        showGraph(g);
        g = freeGraph(g);
        
    }
    else {
        return EXIT_FAILURE;
    }

    free(str);
    return EXIT_SUCCESS;
}



//check differbyone rules
//int getLength(char *word);
bool differByOne(char *preword, char *currword){
    bool result=true;
    char *pp = preword;
    char *cp = currword;
    char *startpp = preword;
    char *startcp= currword;
    int count =0;
    int prelength=0;
    int currlength=0;
    prelength=getLength(preword);
    currlength=getLength(currword);
    
    //判断长度， 只要大于2
    if (abs((int)(prelength-currlength)) > 1)
    {
        return false;
    }
    
    //长度相等，数有多少不同的 大d于两位就不行
    if(prelength==currlength)
    {
        while(*pp!='\0'){
            if(*pp != *cp){
                count++;
            }
            if(count==2)
            {
                return false;
            }
            pp++;
            cp++;
        }
    }else{
        if (prelength > currlength) {
            while (*startcp!='\0') {
                if(*startpp!=*startcp){
                    startpp=startpp+1;
                }
                if(*startpp!=*startcp){
                    return false;
                }
                startpp++;
                startcp++;
            }
        }else{
            while (*startpp!='\0') {
                if(*startpp!=*startcp){
                    startcp=startcp+1;
                }
                if(*startpp!=*startcp){
                    return false;
                }
                startpp++;
                startcp++;
            }
        }
        
        /*
        char str_large[20], str_small[20];
        if (prelength > currlength){
            strcpy(str_large, preword);
            strcpy(str_small, currword);
        }
        else if (prelength < currlength){
            strcpy(str_large, currword);
            strcpy(str_small, preword);
        }
        for (int i = 0; i < strlen(str_small); i++){
            if (str_small[i] != str_large[i]){
                int pos = i;
                for (int j = pos; j < strlen(str_small); j++){
                    if (str_small[j] != str_large[j + 1]){
                        return false;
                    }
                }
                break;
            }
        }
         */
    }
    return result;
}

int getLength(char *word){
    int length=strlen(word);
    return length;
}
