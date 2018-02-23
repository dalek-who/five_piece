#include"five_piece.h"
#include <string.h>
#include <stdio.h>
#define SIZE 15
#define PLAYER1 1
#define PLAYER2 2
#define WIN 1
#define EQUAL 5
#define CONTINUE 0


//�������һ������ʱ������
int current_x;//�к�
int current_y;//�к�


void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
void set_piece(int x,int y, int player);

int getaddress(int player);
void ChangePlayer(int *player);
int judge_winer(int player);//�ж��Ƿ�����ʤ��

////////////////////////////////////////////////
////////////
////////////���˶�ս���ܺ���
////////////
////////////////////////////////////////////////
//�������ա�����ֵ����
void pvp(void)
{   int player=PLAYER1;
    int result=CONTINUE;//�Ƿ�����ʤ��	
    
    initRecordBorard();
    recordtoDisplayArray();  //������ǰ������ʾһ��������
	displayBoard();
  
    char stop[10];

    while(result==CONTINUE){
        getaddress(player);
        recordtoDisplayArray();
        displayBoard();
        result=judge_winer(player);
        
        switch(result){
         //һ����ʤ
            case WIN:
                printf("//////////////////////////////////\n//////////////////////////////////\n ///      *  player[%d]  *      //\n///          WIN!!!             //\n//////////////////////////////////\n//////////////////////////////////\n",player);
                return;
                break;
        
        //ƽ��
            case EQUAL:
                printf("//////////////////////////////////\n//////////////////////////////////\n ///          Nobody Win         //\n///      --  Game Over --       //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                break;

        //��δ����ʤ�������ˣ�����
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
