//带判断禁手的输赢判断函数
#include"five_piece.h"


extern int current_x,current_y;//声明主函数中的全局变量
extern int aRecordBoard[SIZE][SIZE];
void PlusScore(int player,int think_x,int think_y,long long int ThinkScore[SIZE][SIZE],int ThinkBoard[SIZE][SIZE]);//player:当前玩家使用的棋子颜色。think_x,think_y，正在考虑的待落子位置。ThinkScore[][]是用来填写给每个位置估分的数组，ThinkBoard[][]是用来假设在某个位置落子的数组（在多步推演中会用到）

//返回值：当前局面是胜利/禁手/平局/继续游戏，每个状态用宏定义了一个值
int judge_winer(int player){//当前玩家的棋子颜色
    
    int empty=0;
    int i=0,j=0;

    //没有任何用处的一个数组。只是因为直接借用了PlusScore，必须要接入一个数组，但我只需要它打的一个点的分
    long long int score[SIZE][SIZE]; 
    int x,y;
    for(x=0;x<SIZE;++x)
        for(y=0;y<SIZE;++y)
            score[x][y]=0;
    
/*    //判断为一方胜利的条件：任一方向有五连子
    result=hang5(player)|lie5(player)|xiel5(player)|xier5(player);
    if(result==WIN)
        return WIN; 
  */

    //判断是否胜利
    PlusScore(player,current_x,current_y,score,aRecordBoard);
    
    //胜利：
    if(score[current_x][current_y]>=pow(10,9))
        return WIN;
    
    //禁手
    else if(score[current_x][current_y]==0){
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        printf("**************forbid piece******************\n");
        return FORBIDPIECE;
    }

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
