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


#define INITIAL 1024


int main(int argc, char *argv[]){
    char *str;
    char *p;
    char delimiters[]=" \n\t\r";
    int numV=0;
    char **strArray;
    strArray = malloc(10 * sizeof(char*));
    for(int i=0; i<10 ;i++){
        strArray[i] = malloc(5 * sizeof(char));
    }
    str= malloc(INITIAL * sizeof(char));
    if (str==NULL)
    {
        printf("Can't get memory for taht many values.\n");
        return EXIT_FAILURE;
    }
    
    str=fgets(str, INITIAL, stdin);
    p = strtok(str,delimiters);
    
    //如果没有任何输入， 算失败还是成功？
    if (p==NULL) {
        printf("Dictionary\n");
        printf("Ordered Word Ladder Graph\n");
        printf("V=0, E=0\n");
        printf("Longest ladder length: 0\n");
        return EXIT_SUCCESS;
    }
    while(p){
        //strArray[numV] = malloc(5 * sizeof(char));
        int pos=0;
        printf("%s\n",p);
        while(*(p+pos)!='\0') {
            strArray[numV][pos]=*(p+pos);
            pos++;
        }
        numV++;
        p= strtok(NULL,delimiters);
    }
    printf("numV: %d\n",numV);
    
    for (int i=0; i<numV; i++) {
        printf("分割的每个单词：%s\n",strArray[i]);
    }
    
    
    for(int j=0;j<10;j++){
        if(strArray[j]!=NULL){
            free(strArray[j]);
        }
    }
    
    free(strArray);
    free(str);
    return EXIT_SUCCESS;
}


