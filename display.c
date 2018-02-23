//����������������ʾ����/������־����йصĺ���
//��������/��־���������Ҳ�ڴ˶���
//�����л���ҵĺ���changeҲ������

#include <string.h>
#include <stdio.h>
#define SIZE 15
#define PLAYER1 1
#define PLAYER2 2
#define WIN 1
#define EQUAL 5
#define CONTINUE 0
//����ʹ��Unicode���ģ�һ������ռ����char������Ҫ*2��+1��Ϊ��ĩβ��'\0'
char aInitDisplayBoardArray[SIZE+1][SIZE*2+3] = 
{
	" 0���өөөөөөөөөөөөө�",
	" 1�ĩ��������������",
	" 2�ĩ��������������",
	" 3�ĩ��������������",
	" 4�ĩ��������������",
	" 5�ĩ��������������",
	" 6�ĩ��������������",
	" 7�ĩ��������������",
	" 8�ĩ��������������",
	" 9�ĩ��������������",
	"10�ĩ��������������",
	"11�ĩ��������������",
	"12�ĩ��������������",
	"13�ĩ��������������",
	"14���۩۩۩۩۩۩۩۩۩۩۩۩۩�",
	"   A B C D E F G H I J K L M N O" 
};
//������������ʾ
char aDisplayBoardArray[SIZE+1][SIZE*2+3];
//�����������㷨����ʹ��
int aRecordBoard[SIZE][SIZE];//
char play1Pic[]="��";
char play2Pic[]="��";
char _play1Pic[]="��";
char _play2Pic[]="��";
//�������һ������ʱ������
int current_x;//�к�
int current_y;//�к�

//�ı䵱ǰplayer�ĺ���
void ChangePlayer(int *player){//�ı䵱ǰplayer�ĺ���
    switch(*player){
            case PLAYER1:
                    *player=PLAYER2;
                    break;
            case PLAYER2:
                    *player=PLAYER1;
                    break;
    }
}




///////////////////////////////////////////////////////////// 
// �������ƣ� set_piece 
// ���ã�������player����������x��y��

//  �������� 
// ����ֵ���� 
/////////////////////////////////////////////////////////////
void set_piece(int x,int y, int player){
	aRecordBoard[x][y]=player;
	current_x=x;
	current_y=y;
}



/////////////////////////////////////////////////////////////
// �������ƣ�initRecordBorard
// ���ã���ʼ����ά����aRecordBoard
//  ��������
// ����ֵ����
/////////////////////////////////////////////////////////////
void initRecordBorard(void){
	//ͨ��˫��ѭ������aRecordBoard��0
    int x,y;
    for(x=0;x<SIZE;++x)
        for(y=0;y<SIZE;++y)
            aRecordBoard[x][y]=0;
}



/////////////////////////////////////////////////////////////
// �������ƣ�recordtoDisplayArray
// ���ã���aRecordBoard�м�¼������λ�ã�ת����aDisplayBoardArray��
//  ��������
// ����ֵ����
/////////////////////////////////////////////////////////////
void recordtoDisplayArray(void){
	int i,j;
    static int round=1;//round�����Լ��ҵ�һ��������������¼�غ�����ֻ�е�һ�غ���Ҫ���������̣�����Ļغ�ֻҪ��ǰһ�����̵Ļ����ϸı�Ϳ�����
	int x,y;//������ʾ��¼��ֵľ����Ԫ������
    //��һ������aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��
    if(round==1){
        for(i=0;i<=SIZE+1;++i)
            for(j=0;j<=2*SIZE+3;++j)
                aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j]; 
        ++round;
        return;
    }

	//�ڶ�����ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����

	for(x=0;x<SIZE;++x)
        for(y=0;y<SIZE;++y)
            switch(aRecordBoard[x][y]){
                    case PLAYER1:
                                if(aDisplayBoardArray[x][2*y+2]!=play1Pic[0]      //����λ�ò���Բ�λ��������ӣ���������������
                                    &&aDisplayBoardArray[x][2*y+2]!=_play1Pic[0]){
                                    aDisplayBoardArray[x][2*y+2]=_play1Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=_play1Pic[1];
                                }
                                else if(aDisplayBoardArray[x][2*y+2]==_play1Pic[0]){ //�����������ӣ��򻻳�Բ����
                                    aDisplayBoardArray[x][2*y+2]=play1Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=play1Pic[1];
                                }
                                break;
                    
                    
                    case PLAYER2:
                                if(aDisplayBoardArray[x][2*y+2]!=play2Pic[0]      //����λ�ò���Բ�λ��������ӣ���������������
                                    &&aDisplayBoardArray[x][2*y+2]!=_play2Pic[0]){
                                    aDisplayBoardArray[x][2*y+2]=_play2Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=_play2Pic[1];
                                }
                                else if(aDisplayBoardArray[x][2*y+2]==_play2Pic[0]){ //�����������ӣ��򻻳�Բ����
                                    aDisplayBoardArray[x][2*y+2]=play2Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=play2Pic[1];
                                }
                                break;
                    
            }   

    //ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
}



/////////////////////////////////////////////////////////////
// �������ƣ�displayBoard
// ���ã���aDisplayBoardArray�м�¼�����̣���ʽ����Ļ��
//  ��������
// ����ֵ����
/////////////////////////////////////////////////////////////
void displayBoard(void){
	int i,j;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������aDisplayBoardArray�������Ļ��
    for(i=0;i<SIZE+1;++i){
        for(j=0;j<2*SIZE+3;++j)
            printf("%c",aDisplayBoardArray[i][j]);
        printf("\n");
    }
    printf("\n");
    //printf("my x : %3d,     other x: %3d,\n",current_x,15-current_x);
    printf("my x : %3d,     other x: %3d,\n",current_x,current_x+1);
    printf("my y : %3c,     other y: %3c,\n",'A'+current_y,'A'+current_y);
    //printf("my y : %3d,     other y: %3d,\n",current_y,current_y);
    printf("\n");
    printf("******  ****** ****** ******  ******\n");
    printf("****** made by Wang Yuanzheng ******\n");
    printf("******  ****** ****** ******  ******\n");
    printf("\n");
} 

/////////////////////////////////////////////////////////////
//��gdb����ʱ������ӡ��ά����ĺ���
void displayRecordBoard(void){//������gdb����ʱ��ʾ��־���
	int i,j;
    printf("\n");
    for(i=0;i<SIZE;++i){
        for(j=0;j<SIZE;++j)
            printf("%d,",aRecordBoard[i][j]);
        printf("\n");
    }
} 
///////////////////////////////////
///gdb��ӡ������ά����
/////////////////////////////
/*void display2d(long long int array[SIZE][SIZE]){//������gdb����ʱ��ʾ��־���
	int i,j;
    printf("\n");
    for(i=0;i<SIZE;++i){
        printf("%4d",i);
        for(j=0;j<SIZE;++j)
            printf("%lld,",array[i][j]);
        printf("\n");
    }
    printf("    ");
    for(j=0;j<SIZE;++j)
        printf("%6c,",'A'+j);
    printf("\n");
}
*/
