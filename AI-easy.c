//最简单的AI，用来把五子棋程序整体的架构先搭好
//AI-easy通过生成随机数落子
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 15

extern int aRecordBoard[SIZE][SIZE];
extern int current_x,current_y;

void AI_easy(int computer,int people){
    int i,j;
    srand((unsigned)time(NULL));
    
    for(i=rand()%15,j=rand()%15;
        aRecordBoard[i][j]!=0;
        i=rand()%15,j=rand()%15)
        ;
    aRecordBoard[i][j]=computer;
    current_x=i;
    current_y=j;
}
