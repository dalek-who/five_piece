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

////////////////////////////////////////////////
////////////
////////////人人对战的总函数
////////////
////////////////////////////////////////////////
//参数：空。返回值：空
void pvp(void)
{   int player=PLAYER1;
    int result=CONTINUE;//是否有人胜利	
    
    initRecordBorard();
    recordtoDisplayArray();  //在下棋前，先显示一个空棋盘
	displayBoard();
  
    char stop[10];

    while(result==CONTINUE){
        getaddress(player);
        recordtoDisplayArray();
        displayBoard();
        result=judge_winer(player);
        
        switch(result){
         //一方获胜
            case WIN:
                printf("//////////////////////////////////\n//////////////////////////////////\n ///      *  player[%d]  *      //\n///          WIN!!!             //\n//////////////////////////////////\n//////////////////////////////////\n",player);
                return;
                break;
        
        //平局
            case EQUAL:
                printf("//////////////////////////////////\n//////////////////////////////////\n ///          Nobody Win         //\n///      --  Game Over --       //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                break;

        //尚未决出胜负，换人，继续
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
