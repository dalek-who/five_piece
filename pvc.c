////////////////////////////////////////
////////人机模式pvc
////////////////////////////////////////
#include"five_piece.h"
#include <string.h>
#include <stdio.h>
#define SIZE 15
#define PLAYER1 1
#define PLAYER2 2
#define WIN 1
#define EQUAL 5
#define CONTINUE 0

//棋手最近一次落子时的坐标
int current_x;//行号
int current_y;//列号


void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
void set_piece(int x,int y, int player);

int getaddress(int player);
void ChangePlayer(int *player);
int judge_winer(int player);//判断是否有人胜利

//不同难度的AI
void AI_easy    (int computer,int people);
void AI_middle  (int computer,int people);

//参数：空。返回值：空
void pvc(void)
{   int player=PLAYER1;
    int result=CONTINUE;//是否有人胜利	
    int level=-1;//游戏难度
    int first=-1;//选择谁先下棋
    int computer,people;//选择电脑/人谁先谁后
    void (*pAI)(int,int)=NULL;//选择不同难度AI的函数指针

    char stop[10];

    //选择人先还是电脑先
    while(first!=1){
        printf("people   first:input 1\ncomputer first:input 2\n");
        scanf("%d",&first);
        switch(first){
            case 1:
                people=PLAYER1;
                computer=PLAYER2;
                first=1;
                break;
            
            case 2:
                people=PLAYER2;
                computer=PLAYER1;
                first=1;
                break;
            
            default:
                printf("worng input,choose again\n");
                break;
        }
    }

    //选择难度
    while(  level!=1    //难度系数待定，后面继续完善
          &&level!=2
       /*   &&level!=3 */ ){
        printf("easy   level:input 1\n");//后续再次添加难度系数
        printf("middle level:input 2\n");//后续再次添加难度系数
        scanf("%d",&level);
        switch(level){
            case 1:
                pAI=AI_easy;
                break;
            case 2:
                pAI=AI_middle;
                break;

        /*  case 3:
              pAI=AI_difficult
        */
            default:
                printf("worng input,choose again\n");
                break;
        }
    }

    //清空棋盘
    initRecordBorard();
    recordtoDisplayArray();  //在下棋前，先显示一个空棋盘
	displayBoard();

    //下棋回合部分
    while(result==CONTINUE){
        if(player==computer)
            (*pAI)(computer,people);//电脑下棋
        else
            getaddress(people);//人下
        
        recordtoDisplayArray();
        displayBoard();
        result=judge_winer(player);
        
        switch(result){
         //一方获胜
            case WIN:
                if(player==computer){//电脑获胜
                printf("//////////////////////////////////\n//////////////////////////////////\n ///      *  Wang Yuanzheng 2.4  *      //\n///          WIN!!!             //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                }
                else{//人获胜
                printf("//////////////////////////////////\n//////////////////////////////////\n///          *  You  *          //\n///          WIN!!!             //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                }
                break;
        
        //平局
            case EQUAL:
                printf("//////////////////////////////////\n//////////////////////////////////\n ///          Nobody Win         //\n///      --  Game Over --       //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                break;

        //尚未决出胜负，另一方继续
            case CONTINUE:
                ChangePlayer(&player);
                break;
            
            case FORBIDPIECE:
                printf("///////////forbid//////////////\n");
                printf("please input whatever to continue\n");
                scanf("%s",stop);
                result=CONTINUE;
                ChangePlayer(&player);
                break;
           
            default:
                break;
        };
    }
        return;
}


