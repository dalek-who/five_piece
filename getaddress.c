//////////////////////////////////////////////////////////////////////////////////
//类型：void
//作用：读取棋子位置，并存入记录棋局的矩阵。如果输入棋子位置出错，会要求重新输入
//传入参数：player 当前玩家
//记入全局变量：current_x,current_y  当前落子行号、列号
//return：无
////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#define SIZE 15
#include<stdlib.h>
#include<string.h>

int myatoi(char s[]);

void getaddress(int player){
    extern int current_x,current_y;
    extern int aRecordBoard[SIZE][SIZE];
    int x,y;
    char cy;//x行号，y列号，cy是辅助y的参量
    char cx[100];
    do{
        do{
            printf("player %d please input x(number,0~14)\n",player);
            scanf("%s",cx);
            x=myatoi(cx);
        }
        while((x<0||x>14)&&printf("error:x out of the Board,or illegal input\n"))//输入x，若错误，重新输入{
        ;
        
        do{
            printf("player %d please input y(character,A~O)\n",player);
            scanf("%c",&cy);
            y=(int)(cy-'A');
        }
        while((y<0||y>14)&&printf("error:y out of the Board,or illegal input\n"))//输入y，若错误，重新输入
        ;
    }
    while(aRecordBoard[x][y]!=0 && printf("error:have been piece in this point\n"))
    ;
    
    current_x=x;
    current_y=y;
    aRecordBoard[x][y]=player;
}

//标准库的atoi，若不能转为数字则返回0，我自定义的myatoi是返回-1
int myatoi(char s[]){
    int n=0,i=0;
    for(i=0;i<strlen(s);++i){
        if((!(isdigit(s[i]))&&s[i]!='\n'))
            return -1;
    }
    
    for(i=0;s[i]>='0'&&s[i]<='9';++i){
        n=n*10+s[i]-'0';   //s[i]-'0'即为s[i]的数字
    }
    return n;
}
