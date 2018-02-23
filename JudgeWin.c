//判断当前局面是否有人胜出，或者平局，或者继续游戏
//这个里面不含禁手判负的功能。另一个文件JudgeWin02.c是升级版，追加了禁手判断，程序中使用的是JudgeWin02.c
#include<stdio.h>
#define WIN 1//有人胜利，游戏结束
#define EQUAL 5//平局，游戏结束
#define CONTINUE 0//游戏继续
#define SIZE 15

int hang5(int player);
int lie5(int player);
int xiel5(int player);
int xier5(int player);

extern int current_x,current_y;//声明主函数中的全局变量
extern int aRecordBoard[SIZE][SIZE];

int judge_winer(int player){//player：当前玩家代表的棋子（黑PLAYER1或白PLAYER2）
    int result,empty=0;//result输赢平结果,empty棋盘是否有空位
    int i,j;
    
    //判断为一方胜利的条件：任一方向有五连子
    result=hang5(player)|lie5(player)|xiel5(player)|xier5(player);
    if(result==WIN)
        return WIN;
    
    //判断为平局的条件：未返回胜利，且棋盘上已无空位
    for(i=0;i<15;++i){
        for(j=0;j<15;++j){
            if(aRecordBoard[i][j]==0){
                empty=1;
                break;
            }
        }
        if(empty==1)
            break;
    }
    if(empty==0)
        return EQUAL;

    //判断游戏继续：不赢不平
    return CONTINUE;
}


//1
int hang5(int player){//判断一行是否有五连子
    int line_five=0;//标记连子个数
    int i,j;
    for(line_five=0,i=current_x,j=current_y;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        ++j,++line_five)
    ;
/*    if(line_five==5)
        return WIN;
*/

    for(i=current_x,j=current_y-1;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        --j,++line_five)
    ;
    if(line_five==5)
        return WIN;

    return CONTINUE;
}

//2
int lie5(int player){//判断一列是否有五连子
    int line_five=0;//标记连子个数
    int i,j;
    for(line_five=0,i=current_x,j=current_y;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        ++i,++line_five)
    ;
//    if(line_five==5)
  //      return WIN;


    for(i=current_x-1,j=current_y;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        --i,++line_five)
    ;
    if(line_five==5)
        return WIN;

    return CONTINUE;
}

//3
int xiel5(int player){//判断斜右下方向是否有五连子
    int line_five=0;//标记连子个数
    int i,j;
    for(line_five=0,i=current_x,j=current_y;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        ++i,++j,++line_five)
    ;
//    if(line_five==5)
  //      return WIN;


    for(i=current_x-1,j=current_y-1;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        --i,--j,++line_five)
    ;
    if(line_five==5)
        return WIN;

    return CONTINUE;
}

//4
int xier5(int player){//判断斜右上方向是否有五连子
    int line_five=0;//标记连子个数
    int i,j;
    for(line_five=0,i=current_x,j=current_y;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        ++i,--j,++line_five)
    ;
//    if(line_five==5)
  //      return WIN;


    for(i=current_x-1,j=current_y+1;
        line_five!=5&&aRecordBoard[i][j]==player&&i<=14&&i>=0&&j<=14&&j>=0;
        --i,++j,++line_five)
    ;
    if(line_five==5)
        return WIN;

    return CONTINUE;
}
