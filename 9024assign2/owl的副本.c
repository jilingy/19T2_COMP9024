//  COMP9024 Assignment 2 - Ordered Word Ladder
//  owl.c
//
//  Created by jilingy on 2019/8/8.
//  Copyright © 2019 jilingy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Quack.h"
#include "Graph.h"
#define MAXVERTICES 1000
#define MAXSTRINGLENGTH 21

void dfsR(Graph, Vertex, int, int *, int *, int *, int *, Quack, Quack);
bool differByOne(char *preword, char *currword);
Quack dfs(Graph, Vertex, int,Quack);
int getLength(char *word);
int* mallocArray(int);       // malloc an array of length int * sizeof(int)
int maxNum =0;

int main(int argc, char *argv[]){
    char delimiters[]=" \n\t\r";
    char **strArray;
    char *charArray;
    char *move;
    char *p;
    char c;
    int length=0;
    int numV=0;
    
    //To create a result Quack
    Quack result = createQuack();
    
    //To create two-dimensional array
    strArray = malloc(MAXVERTICES * sizeof(char*));
    charArray=malloc(MAXVERTICES*MAXSTRINGLENGTH * sizeof(char));
    
    //move point to the front of charArray
    move=charArray;
    
    //To handle malloc failure
    if (strArray==NULL||charArray==NULL)
    {
        fprintf(stderr, "Can't get memory for that many values.\n");
        return EXIT_FAILURE;
    }
    
    //To assign 21 positions for each word
    for(int i=0; i<MAXVERTICES ;i++){
        strArray[i] = malloc(MAXSTRINGLENGTH * sizeof(char));
    }
    
    //To read stdin
    while((c=getchar()) != EOF) {
        *move=c;
        move++;
        length++;
    }
    *move = '\0';
    
    //To split the first word
    p = strtok(charArray,delimiters);
    
    //To deal with no input
    if (p==NULL) {
        printf("Dictionary\n");
        printf("Ordered Word Ladder Graph\n");
        printf("V=0, E=0\n");
        printf("Longest ladder length: 0\n");
        return EXIT_SUCCESS;
    }
    
    //To breaks string str into a series of p using delimiters
    //To delete repeated words
    while(p){
        int pos=0;
        if (numV==0) {
            printf("Dictionary\n");
            while(*(p+pos)!='\0') {
                strArray[numV][pos]=*(p+pos);
                pos++;
            }
            strArray[numV][pos]='\0';
            numV++;
        }else{
            if (strcmp(p,strArray[numV-1])==0) {
                p= strtok(NULL,delimiters);
                continue;
            }else{
                while(*(p+pos)!='\0') {
                    strArray[numV][pos]=*(p+pos);
                    pos++;
                }
                strArray[numV][pos]='\0';
                numV++;
            }
        }
        p= strtok(NULL,delimiters);
    }
    
    //To print dictionary
    for (int i=0; i<numV; i++) {
        printf("%d: %s\n", i, strArray[i]);
    }
    printf("Ordered Word Ladder Graph\n");
    
    //To insert new edges by using differByOne to create a graph
    if (numV >= 0) {
        Graph g = newGraph(numV);
        for (int i = 0; i < numV; i++) {
            for (int j = i+1; j < numV; j++) {
                if(differByOne(strArray[i], strArray[j])) {
                    insertEdge(newEdge(i, j), g);
                }
            }
        }
        showGraph(g);
        
        //To calculate the maxlenghth of the input
        Quack resultQuack = createQuack();
        for (int i = 0; i < numV; i++) {
            result=dfs(g, i, numV,resultQuack);
            if (maxNum==numV-i) {
                break;
            }
        }
        printf("Longest ladder length: %d\n", maxNum);
        printf("Longest ladders:\n");
        
        //each one word should be the start vertice
        int lengthQ=0;
        int eachresult=0;
        //To print final result
        while (!isEmptyQuack(result) && lengthQ<99) {
            lengthQ++;
            printf("%2d: ",lengthQ);
            for(int i=0;i<maxNum;i++){
                eachresult=pop(result);
                if(i==(maxNum-1)){
                    printf("%s\n",strArray[eachresult]);
                    break;
                }
                printf("%s -> ",strArray[eachresult]);
            }
        }
        
        //free graph
        g = freeGraph(g);
        g = NULL;
    }else {
        return EXIT_FAILURE;
    }
    
    //To free two-dimensional array
    for(int j=0;j<10;j++){
        if(strArray[j]!=NULL){
            free(strArray[j]);
        }
    }
    
    //free quacks and arrays
    destroyQuack(result);
    free(strArray);
    free(charArray);
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
    
    //To return false when length difference greater than 2
    if (abs((int)(prelength-currlength)) > 1)
    {
        return false;
    }
    
    //To return false, when the length of two words are equal and the number of different words is greater than 2.
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
    }
    return result;
}

//To get length of each word
int getLength(char *word){
    int length=strlen(word);
    return length;
}

//To return the final result which is a quack(queue) contains each little result/results
Quack dfs(Graph g, Vertex rootv, int numV,Quack resultQuack) {//'wrapper' for recursive dfs
    int *visited = mallocArray(numV);  // ... handles disconnected graphs
    int depth = 1;
    int order = 0;
    Quack store = createQuack();
    Vertex startv = rootv;             // this is the starting vertex
    int allVis = 0;                    // assume not all visited
    while (!allVis) {                  // as long as there are vertices
        dfsR(g, startv, numV, &order, visited, &maxNum, &depth, store, resultQuack);
        allVis = 1;
    }
    free(visited);
    destroyQuack(store);
    return resultQuack;
}

//Recusive dfs
void dfsR(Graph g, Vertex v, int numV, int *order, int *visited, int *maxNum, int *depth, Quack store, Quack resultQuack) {
    Quack midstack = createQuack();
    visited[v] = *order;                // records the order of visit
    *order = *order+1;
    *depth = *depth+1;
    int midtemp;
    int middle;
    push(v, store);
    
    for (Vertex w = 0; w < numV; w++) {
        if (isEdge(newEdge(v,w), g) && v<w && visited[w]==UNVISITED) {
            dfsR(g, w, numV, order, visited, maxNum, depth, store, resultQuack);
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
    destroyQuack(midstack);
    return;
}

//To allocate memory for an array of vertices that are unvisited
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
