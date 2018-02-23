//这里面是所有与显示棋盘/储存棋局矩阵有关的函数
//关于棋盘/棋局矩阵的数组等也在此定义
//用来切换玩家的函数change也在这里

#include <string.h>
#include <stdio.h>
#define SIZE 15
#define PLAYER1 1
#define PLAYER2 2
#define WIN 1
#define EQUAL 5
#define CONTINUE 0
//棋盘使用Unicode画的，一个符号占两个char，所以要*2，+1是为了末尾的'\0'
char aInitDisplayBoardArray[SIZE+1][SIZE*2+3] = 
{
	" 0┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
	" 1┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 2┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 3┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 4┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 5┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 6┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 7┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 8┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	" 9┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"10┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"11┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"12┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"13┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
	"14┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛",
	"   A B C D E F G H I J K L M N O" 
};
//此数组用于显示
char aDisplayBoardArray[SIZE+1][SIZE*2+3];
//此数组用于算法计算使用
int aRecordBoard[SIZE][SIZE];//
char play1Pic[]="●";
char play2Pic[]="◎";
char _play1Pic[]="▲";
char _play2Pic[]="△";
//棋手最近一次落子时的坐标
int current_x;//行号
int current_y;//列号

//改变当前player的函数
void ChangePlayer(int *player){//改变当前player的函数
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
// 函数名称： set_piece 
// 作用：将棋手player的棋子落在x行y列

//  参数：无 
// 返回值：无 
/////////////////////////////////////////////////////////////
void set_piece(int x,int y, int player){
	aRecordBoard[x][y]=player;
	current_x=x;
	current_y=y;
}



/////////////////////////////////////////////////////////////
// 函数名称：initRecordBorard
// 作用：初始化二维数组aRecordBoard
//  参数：无
// 返回值：无
/////////////////////////////////////////////////////////////
void initRecordBorard(void){
	//通过双重循环，将aRecordBoard清0
    int x,y;
    for(x=0;x<SIZE;++x)
        for(y=0;y<SIZE;++y)
            aRecordBoard[x][y]=0;
}



/////////////////////////////////////////////////////////////
// 函数名称：recordtoDisplayArray
// 作用：将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
//  参数：无
// 返回值：无
/////////////////////////////////////////////////////////////
void recordtoDisplayArray(void){
	int i,j;
    static int round=1;//round是我自己家的一个变量，用来记录回合数，只有第一回合需要拷贝空棋盘，后面的回合只要在前一句棋盘的基础上改变就可以了
	int x,y;//用来标示记录棋局的矩阵的元素坐标
    //第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
    if(round==1){
        for(i=0;i<=SIZE+1;++i)
            for(j=0;j<=2*SIZE+3;++j)
                aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j]; 
        ++round;
        return;
    }

	//第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上

	for(x=0;x<SIZE;++x)
        for(y=0;y<SIZE;++y)
            switch(aRecordBoard[x][y]){
                    case PLAYER1:
                                if(aDisplayBoardArray[x][2*y+2]!=play1Pic[0]      //若此位置不是圆形或三角棋子，则填上三角棋子
                                    &&aDisplayBoardArray[x][2*y+2]!=_play1Pic[0]){
                                    aDisplayBoardArray[x][2*y+2]=_play1Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=_play1Pic[1];
                                }
                                else if(aDisplayBoardArray[x][2*y+2]==_play1Pic[0]){ //若是三角棋子，则换成圆棋子
                                    aDisplayBoardArray[x][2*y+2]=play1Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=play1Pic[1];
                                }
                                break;
                    
                    
                    case PLAYER2:
                                if(aDisplayBoardArray[x][2*y+2]!=play2Pic[0]      //若此位置不是圆形或三角棋子，则填上三角棋子
                                    &&aDisplayBoardArray[x][2*y+2]!=_play2Pic[0]){
                                    aDisplayBoardArray[x][2*y+2]=_play2Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=_play2Pic[1];
                                }
                                else if(aDisplayBoardArray[x][2*y+2]==_play2Pic[0]){ //若是三角棋子，则换成圆棋子
                                    aDisplayBoardArray[x][2*y+2]=play2Pic[0];
                                    aDisplayBoardArray[x][2*y+3]=play2Pic[1];
                                }
                                break;
                    
            }   

    //注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
}



/////////////////////////////////////////////////////////////
// 函数名称：displayBoard
// 作用：将aDisplayBoardArray中记录的棋盘，显式到屏幕上
//  参数：无
// 返回值：无
/////////////////////////////////////////////////////////////
void displayBoard(void){
	int i,j;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将aDisplayBoardArray输出到屏幕上
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
//在gdb调试时用来打印二维数组的函数
void displayRecordBoard(void){//用来在gdb测试时显示棋局矩阵
	int i,j;
    printf("\n");
    for(i=0;i<SIZE;++i){
        for(j=0;j<SIZE;++j)
            printf("%d,",aRecordBoard[i][j]);
        printf("\n");
    }
} 
///////////////////////////////////
///gdb打印其他二维数组
/////////////////////////////
/*void display2d(long long int array[SIZE][SIZE]){//用来在gdb测试时显示棋局矩阵
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
