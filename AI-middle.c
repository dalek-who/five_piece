//中等难度的AI，仅考虑当前棋局（人/机都考虑），不进行多步推演,考虑禁手

#include"five_piece.h"

typedef struct score_index{//记录一个点的坐标与成绩
        int x;
        int y;
        long long int score;
        } score_index;

extern int current_x,current_y;
extern int aRecordBoard[SIZE][SIZE];
void PlusScore(int player,int think_x,int think_y,\
                long long int ThinkScore[SIZE][SIZE],int ThinkBoard[SIZE][SIZE]);//单局的对每个点局部打分函数
void FindMax(long long int ThinkScore[SIZE][SIZE],score_index best[],long long int *pmax,int *pnmax);//打完分，提取相应指标
void c_decide(long long int cmax,long long int pmax,int num_cmax,int num_pmax,\
              int *cdecide_x,int *cdecide_y,\
              struct score_index c_best[],struct score_index p_best[],\
              long long int c_ThinkScore[SIZE][SIZE],long long int p_ThinkScore[SIZE][SIZE]);
void display2dl(long long int array[SIZE][SIZE]);
void firstpiece(void);

//参数：computer：电脑是player1还是player2，people：人是player1还是player2
void AI_middle(int computer,int people){
    int think_x,think_y,//用来思考的坐标
        i,j,//用来扫描的坐标
        num_cmax,num_pmax,//机/人的分值最大的点的个数
//        state,maxer,more,//用状态机的方法，权衡最终选择打还是防，maxer，more是状态机state的两位
        cdecide_x,cdecide_y,//电脑最终决定的落子位置
        pdecide_x,pdecide_y;//人最终决定的落子位置。不做推演的AI用不到，但改为多步推演后会用到
    
    long long int cmax,pmax;//机/人的最大分值
    
         static int round=1;//只调用一次，ai开局第一个子随机落在中间的一个位置

//    int *pnum_cmax=&num_cmax,*pnum_pmax=&num_pmax,
  //      *pcmax=&cmax,*ppmax=&pmax;

    struct score_index c_best[SIZE*SIZE],p_best[SIZE*SIZE];//记录对于电脑和人的最好成绩成绩与坐标的结构数组
    int ThinkBoard[SIZE][SIZE];//拷贝棋局矩阵，用来思考
    long long int   c_ThinkScore[SIZE][SIZE],//对电脑的打分矩阵
                    p_ThinkScore[SIZE][SIZE];//对人的打分矩阵

//初始化ThinkBoard[][]
    for(i=0;i<SIZE;++i){
        for(j=0;j<SIZE;++j)
            ThinkBoard[i][j]=aRecordBoard[i][j];
    }

//调用一个模块：如果电脑执黑先行，第一局在中间六个位置中随机落在一个位置，以防止每局完全相同的结果。该模块只调用一次，只做这一件事
//
  if(round==1 && computer==PLAYER1){
        firstpiece();
        ++round;
        aRecordBoard[current_x][current_y]=computer;
        return;
    }

////////////////////////////////////
//打分后，相同成绩落子落在第中位数个格子里，这样的话暂时不用写这个模块了

//棋局打分部分
    for(think_x=0;think_x<SIZE;++think_x){
        for(think_y=0;think_y<SIZE;++think_y){

            if(ThinkBoard[think_x][think_y]!=0){//某位置非空,双方成绩都标为0
                c_ThinkScore[think_x][think_y]=p_ThinkScore[think_x][think_y]=0;
                continue;
            }
            
            //禁手模块。如果computer==PLAYER1才调用
            //////////////////////////////////////
            //////////////////////////////////////
            //禁手判断模块合在了打分模块里。禁手种类做了简化，活3，冲4，活4仅数连子。中间有空格的情况不算

            //打分模块.禁手模块合在了打分模块里。对于黑子，会在禁手标0（只有禁手和已有棋子的位置被标0.标0代表不能落子）
            //只有黑方遇到禁手会被标0，白子没有禁手
            PlusScore(computer,think_x,think_y,c_ThinkScore,ThinkBoard);
            PlusScore(people  ,think_x,think_y,p_ThinkScore,ThinkBoard);
        }
    }

            //查找相应参数
            /////////////
            FindMax(c_ThinkScore,c_best,&cmax,&num_cmax);            
            FindMax(p_ThinkScore,p_best,&pmax,&num_pmax);
            //决定攻防，以及落子位置
            ////////////    
            c_decide(cmax,pmax,num_cmax,num_pmax,&cdecide_x,&cdecide_y,c_best,p_best,c_ThinkScore,p_ThinkScore);

            //落子。把落子从决定攻防位置中单提了出来，为了方便在后续的多局推演评估中，可以让人更方便的调用决定攻防的模块
            ///////////
            aRecordBoard[cdecide_x][cdecide_y]=computer;
	        current_x=cdecide_x;
        	current_y=cdecide_y;

  //      display2dl(c_ThinkScore);
    //    display2dl(p_ThinkScore);
}



//提取出决定攻防的参数
//读取一个打分矩阵中最高的成绩及其坐标，将所有的最高成绩及坐标存入结构数组best，最后返回成绩最高点的成绩和数量,
//参数：ThinkScore[]：给棋盘上每个位置打分的矩阵，best[]记录棋盘上所有成绩最高的点的成绩以及坐标，*pmax指向最高成绩max的指针。*pnmax指向最高成绩的点的数量nmax的指针
void FindMax(long long int ThinkScore[SIZE][SIZE],struct score_index best[],long long int *pmax,int *pnmax){
    int i,j,//在二维数组里的坐标
        k,//best[]数组的坐标
        max,nmax;//最大成绩，最大成绩个数
        max=ThinkScore[0][0],nmax=0;
        
        //对best数组清零
        for(k=0;k<SIZE*SIZE;++k){
            best[k].x=-1;
            best[k].y=-1;
            best[k].score=-1;
        }
        k=0;

        //遍历找到最大成绩，并记录个数，并存入best[]
        for(i=0;i<SIZE;++i){
            for(j=0;j<SIZE;++j){
                
                //不能落子位置，跳过
                if(ThinkScore[i][j]==0)
                    continue;
                
                //找到更大的max：清空best并刷新
                else if(ThinkScore[i][j]>max){
                    max=ThinkScore[i][j];
                        
                    //对best清空刷新
                    for(k=0;k<SIZE*SIZE;++k){
                        best[k].x=-1;
                        best[k].y=-1;
                        best[k].score=-1;
                    }
                    nmax=0;
                    k=0;
                    
                    //对best的更新
                    best[k].score=max;
                    best[k].x=i;
                    best[k].y=j;
                    ++nmax;
                    ++k;
                    }
            
                
                //和max相同：存入best
                else if(ThinkScore[i][j]==max){//新增best的数据
                    best[k].score=max;
                    best[k].x=i;
                    best[k].y=j;
                    ++nmax;
                    ++k;
                }
            }
        }
        //用指针返回这两个指标
        *pmax=max;
        *pnmax=nmax;
}


//决定落子位置。这个是电脑调用版本的。如果是人调用，需要一些更改。更改已在相应位置列出
void c_decide(long long int cmax,long long int pmax,//电脑棋子最大成绩，人棋子最大成绩
              int num_cmax,int num_pmax,//电脑成绩最大旗子的数量
              int *cdecide_x,int *cdecide_y,//电脑决定的落子位置
              struct score_index c_best[],struct score_index p_best[],//电脑/人的所有最好成绩的点的成绩以及坐标
              long long int c_ThinkScore[SIZE][SIZE],long long int p_ThinkScore[SIZE][SIZE]){//电脑/人的棋盘打分矩阵
    int state,//状态机
        maxer,//谁的最大值更大
        more,//谁的最大值更多
        k;//标记数组序号的临时参数
//识别当前局面对应状态机何种状态
    if(cmax>pmax)
        maxer=3;
    else if(cmax==pmax)
        maxer=2;
    else if(cmax<pmax)
        maxer=1;

    if(num_cmax>num_pmax)
        more=3;
    else if(num_cmax==num_pmax)
        more=2;
    else if(num_cmax<num_pmax)
        more=1;
    
    state=maxer*10+more;

//状态机各种情况下的行动：
    switch(state){
        //下电脑得分最高的位置。如果有多个，取中位数位置
        case 33:
        case 32:
        case 31:
        case 23:
        case 22://如果是人调用，22人会选择进攻电脑，该状态挪到下面
            k=num_cmax/2;
            *cdecide_x=c_best[k].x;
            *cdecide_y=c_best[k].y;
            break;

        //下人得分最高的位置。取中位数位置。如果是自己的禁手位，就换下一个位置
        case 21:
        case 13:
        case 12:
        case 11:
            for(k=num_pmax/2;c_ThinkScore[p_best[k].x][p_best[k].y]==0&&k<num_pmax;++k)//如果换成人调用这个模块，则c_ThinkScore要改为p_ThinkScore
            ;//如果中位数是禁手，就往右找，只到不是禁手为止
            if(k>=num_pmax)
                for(k=num_pmax/2;c_ThinkScore[p_best[k].x][p_best[k].y]==0&&k>=0;--k)//如果换成人调用这个模块，则c_ThinkScore要改为p_ThinkScore
            ;//如果右边不行，就再往左找，直到不是禁手为止
            *cdecide_x=p_best[k].x;
            *cdecide_y=p_best[k].y;
            break;
    }
}
