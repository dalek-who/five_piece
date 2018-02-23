////////////////////////////////////////
////////�˻�ģʽpvc
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

//��ͬ�Ѷȵ�AI
void AI_easy    (int computer,int people);
void AI_middle  (int computer,int people);

//�������ա�����ֵ����
void pvc(void)
{   int player=PLAYER1;
    int result=CONTINUE;//�Ƿ�����ʤ��	
    int level=-1;//��Ϸ�Ѷ�
    int first=-1;//ѡ��˭������
    int computer,people;//ѡ�����/��˭��˭��
    void (*pAI)(int,int)=NULL;//ѡ��ͬ�Ѷ�AI�ĺ���ָ��

    char stop[10];

    //ѡ�����Ȼ��ǵ�����
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

    //ѡ���Ѷ�
    while(  level!=1    //�Ѷ�ϵ�������������������
          &&level!=2
       /*   &&level!=3 */ ){
        printf("easy   level:input 1\n");//�����ٴ�����Ѷ�ϵ��
        printf("middle level:input 2\n");//�����ٴ�����Ѷ�ϵ��
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

    //�������
    initRecordBorard();
    recordtoDisplayArray();  //������ǰ������ʾһ��������
	displayBoard();

    //����غϲ���
    while(result==CONTINUE){
        if(player==computer)
            (*pAI)(computer,people);//��������
        else
            getaddress(people);//����
        
        recordtoDisplayArray();
        displayBoard();
        result=judge_winer(player);
        
        switch(result){
         //һ����ʤ
            case WIN:
                if(player==computer){//���Ի�ʤ
                printf("//////////////////////////////////\n//////////////////////////////////\n ///      *  Wang Yuanzheng 2.4  *      //\n///          WIN!!!             //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                }
                else{//�˻�ʤ
                printf("//////////////////////////////////\n//////////////////////////////////\n///          *  You  *          //\n///          WIN!!!             //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                }
                break;
        
        //ƽ��
            case EQUAL:
                printf("//////////////////////////////////\n//////////////////////////////////\n ///          Nobody Win         //\n///      --  Game Over --       //\n//////////////////////////////////\n//////////////////////////////////\n");
                return;
                break;

        //��δ����ʤ������һ������
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


