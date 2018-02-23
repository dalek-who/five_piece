//五子棋自定义的头文件
#ifndef _FIVE_PIECE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define SIZE 15//棋盘尺寸

//两个玩家
#define PLAYER1 1
#define PLAYER2 2

//用于判断输赢的JudgeWin函数的参数
#define CONTINUE 0//棋局继续
#define WIN 1//有一方获胜
#define EQUAL 5//平局
#define FORBIDPIECE 8//禁手

//用于AI给棋盘打分的参数
#define DIE 3//两头被堵死.为了与禁手区别开，这里标为3，是非0的最低分数。标0的是已经被占的位置，以及禁手位置
#define SLEEP 10//一头是活的，一头被堵死
#define LIVE 5//端点每个活空位的权值
#define LINE 10//每一个连子的权值
                //此LINE是当乘方的底数用的。非禁手位非死位，返回的成绩power(LINE,line)+LIVE
#define FIVE 80000000//如果形成五连子
#define DL3 60008//双活三（double live 3)棋型较为特殊，对于非禁手方，比单个冲四还有价值（形成双活三后必胜）,要专门标出比冲四更高成绩。冲4是10^4+5=10005

#define FORBID 0//禁手
#define UNFORBID 1//非禁手
#define OUT -1//标记端点越界

int judge_winer(int player);
int getaddress(int player);
void display2dl(long long int array[SIZE][SIZE]);
void display2d(int array[SIZE][SIZE]);

//记录一点的棋型结构（只对某一方向记录。总共要使用四个这样的结构）
typedef struct piece{
    //左左端点，左跳连子，左端点，连子，右端点，右跳连子，右端点
    int LL;
    int Ljump;
    int L;
    int line;
    int R;
    int Rjump;
    int RR;
    
    //可用空间
    int space;

    //两端是否被堵住
    int live;
    int block;
    
    //各种棋型的数量
    int l5;
    int r4;
    int l4;
    int r3;
    int l3;
    int r2;
    int l2;
    int r1;
    int l1;
    int longline;
    int die;

    //打分
    long long int score;
}piece;


#endif
