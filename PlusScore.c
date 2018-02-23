//对BasicScore的升级，包含更多种类的活三

#include"five_piece.h"
void hang_infor  (int player,int think_x,int think_y,int ThinkBoard[SIZE][SIZE],piece *ppiece);
void lie_infor   (int player,int think_x,int think_y,int ThinkBoard[SIZE][SIZE],piece *ppiece);
void xie1_infor  (int player,int think_x,int think_y,int ThinkBoard[SIZE][SIZE],piece *ppiece);
void xie2_infor  (int player,int think_x,int think_y,int ThinkBoard[SIZE][SIZE],piece *ppiece);

void type(int player,piece *ppiece);
int forbid(int longline,int rl4,int l3);
void score(piece *ppiece);

//返回值空
void PlusScore(int player,int think_x,int think_y,long long int ThinkScore[SIZE][SIZE],int ThinkBoard[SIZE][SIZE]){//player当前玩家的棋子颜色，think_x,think_y：正在思考的位置。ThinkScore[][]是用来填写给每个位置估分的数组，ThinkBoard[][]是用来假设在某个位置落子的数组（在多步推演中会用到）
    //四个方向的棋型打分
    piece hang,
          lie,
          xie1,
          xie2;
    
    //总的活三/冲活四/长连数量
    int l3,rl4,longline,l5;

    int Forbid=UNFORBID;//是否禁手
    long long int Score=0;//不考虑禁手时的成绩
    
    //提取四个方向的数据特征
    hang_infor  (player,think_x,think_y,ThinkBoard,&hang);
    lie_infor   (player,think_x,think_y,ThinkBoard,&lie);
    xie1_infor  (player,think_x,think_y,ThinkBoard,&xie1);
    xie2_infor  (player,think_x,think_y,ThinkBoard,&xie2);

    //由四个方向的数据特征判断棋型
    type    (player,&hang);
    type    (player,&lie);
    type    (player,&xie1);
    type    (player,&xie2);

    l3= hang.l3 + 
        lie.l3 + 
        xie1.l3 + 
        xie2.l3;
    rl4=hang.l4 + hang.r4 + 
        lie .l4 + lie .r4 +
        xie1.l4 + xie1.r4 +
        xie2.l4 + xie2.r4;
    longline= hang.longline + 
        lie.longline + 
        xie1.longline + 
        xie2.longline;

    l5= hang.l5 + 
        lie.l5 + 
        xie1.l5 + 
        xie2.l5;
    
    //禁手判断
    if(player==PLAYER1)
        Forbid=forbid(longline,rl4,l3);

    //对四个方向打分
    score(&hang);
    score(&lie);
    score(&xie1);
    score(&xie2);

    //打分汇总
    Score=  hang.score+
            lie.score+
            xie1.score+
            xie2.score;
    
    //双活三打分比较特殊，进行修正
    //和活四一样的成绩，必胜棋型
    if(l3>=2 && l5==0 && longline==0)
        Score=pow(10,8);

    //最终打分
    ThinkScore[think_x][think_y]=(Forbid==FORBID)?0:Score;
    
    //结束
    return;
}
