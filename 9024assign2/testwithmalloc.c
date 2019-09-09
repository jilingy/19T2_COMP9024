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

#define WHITESPACE 100
#define MAXVERTICES 1000
#define MAXSTRINGLENGTH 21

bool differByOne(char *preword, char *currword);
int getLength(char *word);
Quack dfs(Graph, Vertex, int);
void dfsR(Graph, Vertex, int, int *, int *, int *, int *, Quack, Quack);
int* mallocArray(int);       // malloc an array of length int * sizeof(int)
//void printArray(char *, int *, int); // print an int array of length int
int maxNum =0;

int main(int argc, char *argv[]){
    char **strArray;
    char *charArray;
    char *each;
    char c;
    char *p;
    char delimiters[]=" \n\t\r";
    int numV=0;
    int length=0;
    Quack result = createQuack();
    Quack lengthQuack = createQuack();
    
    //二维数组，把每个单词d放到每一行
    strArray = malloc(MAXVERTICES * sizeof(char*));
    charArray=malloc(MAXVERTICES*MAXSTRINGLENGTH * sizeof(char));
    each=charArray;
    if (strArray==NULL||charArray==NULL||each==NULL)
    {
        fprintf(stderr, "Can't get memory for that many values.\n");
        return EXIT_FAILURE;
    }
    
    //每一个单词分配21个位置
    for(int i=0; i<MAXVERTICES ;i++){
        strArray[i] = malloc(MAXSTRINGLENGTH * sizeof(char));
    }
    
    //分割单词
    while((c=getchar()) != '\n') {
        *charArray=c;
        charArray++;
        length++;
    }
    *charArray = '\0';
    printf("%s\n",each);

    p = strtok(each,delimiters);
    //printf("第一个单词：%s\n",p);
    
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
        int pos=0;
        
        while(*(p+pos)!='\0') {
            strArray[numV][pos]=*(p+pos);
            pos++;
        }
        strArray[numV][pos]='\0';
        numV++;
        p= strtok(NULL,delimiters);
    }

    //可以写一个showDictionary的function
    //参照printArray("Visited: ", visited, numV);的写法～～～
    for (int i=0; i<numV; i++) {
        printf("%d: %s\n",i,strArray[i]);
    }
    printf("Ordered Word Ladder Graph\n");
    if (numV >= 0) {
        Graph g = newGraph(numV);
        for (int i = 0; i < numV-1; i++) { // 外循环取出一维数组
            for (int j = i+1; j < numV; j++) { // 外循环取出一维数组
                if (strcmp(strArray[i],strArray[j])==0) {
                    continue;
                }else {
                    if (differByOne(strArray[i], strArray[j])) {
                        insertEdge(newEdge(i, j), g);
                    }
                }
            }
        }
        showGraph(g);
        
        //an bn cn ig it iz试试(因为是disconnected的graph）
        //calculate the maxlenghth of the input
        for (int i = 0; i < numV; i++) {
            dfs(g, i, numV);
        }
        printf("Longest ladder length: %d\n", maxNum);
        printf("Longest ladders:\n");
        int lengthQ=0;
        
        //each one word should be the start vertice
        for (int i = 0; i < numV; i++) {
            dfs(g, i, numV);
            result=dfs(g, i, numV);
            lengthQuack=dfs(g, i, numV);
            int eachresult=0;
            while (!isEmptyQuack(result)) {
                pop(lengthQuack);
                lengthQ++;
                printf("%d: ",lengthQ);
                for(int i=0;i<maxNum;i++){
                    eachresult=pop(result);
                    if(i==(maxNum-1)){
                        printf("%s\n",strArray[eachresult]);
                        break;
                    }
                    printf("%s -> ",strArray[eachresult]);
                }
            }
        }
        
        //free graph
        g = freeGraph(g);
        g = NULL;
    }else {
        return EXIT_FAILURE;
    }

    //可以写一个free二维数组的function
    for(int j=0;j<10;j++){
        if(strArray[j]!=NULL){
            free(strArray[j]);
        }
    }
    
    //free quack and array
    destroyQuack(result);
    destroyQuack(lengthQuack);
    free(strArray);
    free(each);
    return EXIT_SUCCESS;
}

//check differbyone rules
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

Quack dfs(Graph g, Vertex rootv, int numV) {//'wrapper' for recursive dfs
    int *visited = mallocArray(numV);  // ... handles disconnected graphs
    int depth =1;
    int order = 0;
    Quack store = createQuack();
    Quack resultQuack = createQuack();
    Vertex startv = rootv;             // this is the starting vertex
    int allVis = 0;                    // assume not all visited
    while (!allVis) {                  // as long as there are vertices
        dfsR(g, startv, numV, &order, visited, &maxNum, &depth, store, resultQuack);
        allVis = 1;
    }
    free(visited);
    return resultQuack;
}

void dfsR(Graph g, Vertex v, int numV, int *order, int *visited, int *maxNum, int *depth, Quack store, Quack resultQuack) {
    Quack midstack = createQuack();
    visited[v] = *order;                // records the order of visit
    *order = *order+1;
    *depth = *depth+1;
    int midtemp;
    int middle;
    push(v, store);
    for (Vertex w = 0; w < numV; w++) {
        if (isEdge(newEdge(v,w), g) && visited[w]==UNVISITED) {
            if (v<w) {
                dfsR(g, w, numV, order, visited, maxNum, depth, store, resultQuack);
            }
        }
    }
    *depth = *depth-1;
    visited[v]=UNVISITED;
    if ((*depth)>=(*maxNum)) {
        if((*depth)>(*maxNum)){
            makeEmptyQuack(resultQuack);
        }
        while (!isEmptyQuack(store)) {
            midtemp=pop(store);
            push(midtemp,midstack);
        }
        while (!isEmptyQuack(midstack)) {
            middle=pop(midstack);
            push(middle,store);
            qush(middle,resultQuack);
        }
        *maxNum=*depth;
    }
    pop(store);
    return;
}

int *mallocArray(int numV){
    int *visitedList;
    int *p;
    int *show;
    visitedList = malloc(numV * sizeof(int));
    p=visitedList;
    show=visitedList;
    if (visitedList==NULL) {
        fprintf(stderr, "Can't get memory for that many values.\n");
        return NULL;
    }
    for (int i=0; i<numV; i++) {
        *p=-1;
        p++;
    }
    return visitedList;
}
