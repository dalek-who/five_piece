//给棋型打分，以及禁手判断函数
#include"five_piece.h"

//禁手判断函数
//返回值：是禁手FORBID，不是禁手返回UNFORBID，两个宏定义在头文件中
int forbid(int longline,//长连的个数
           int num_rl4,//冲（rush）/活（live）4的个数
           int num_l3){//活3的个数
    if(longline>0||num_rl4>=2||num_l3>=2)
        return FORBID;
    else return UNFORBID;
}

//一个方向的打分函数
//返回值：空
//参数：*ppiece：指向记录棋局信息的结构piece的指针
void score(piece *ppiece){
    if(ppiece->die>0){
        ppiece->score=DIE;
    return;
    }

    else if(ppiece->l5>0 || ppiece->longline>0){
        ppiece->score=pow(10,9);
    return;
    }

    else{ /* ppiece->score=   ppiece->l4*(pow(LINE,4)*10+2*pow(LINE,4));
           ppiece->score+=  ppiece->r4*(pow(LINE,4)*10+pow(LINE,4));
           ppiece->score+=  ppiece->l3*(pow(LINE,3)*10+2*pow(LINE,3));
           ppiece->score+=  ppiece->r3*(pow(LINE,3)*10+pow(LINE,3));
           ppiece->score+=  ppiece->l2*(pow(LINE,2)*10+2*pow(LINE,2));
           ppiece->score+=  ppiece->r2*(pow(LINE,2)*10+pow(LINE,2));
           ppiece->score+=  ppiece->l1*(pow(LINE,1)*10+2*pow(LINE,1));
           ppiece->score+=  ppiece->r1*(pow(LINE,1)*10+pow(LINE,1));
    */
/*
           ppiece->score=   ppiece->l4*(pow(2,5)*pow(10,5)  );
           ppiece->score+=  ppiece->r4*(pow(2,5)*pow(10,5)/2);
           ppiece->score+=  ppiece->l3*(pow(2,4)*pow(10,4)  );    
           ppiece->score+=  ppiece->r3*(pow(2,4)*pow(10,4)/2); 
           ppiece->score+=  ppiece->l2*(pow(2,3)*pow(10,3)  );    
           ppiece->score+=  ppiece->r2*(pow(2,3)*pow(10,3)/2); 
           ppiece->score+=  ppiece->l1*(pow(2,2)*pow(10,2)  );    
           ppiece->score+=  ppiece->r1*(pow(2,2)*pow(10,2)/2); 
*/
           ppiece->score=   ppiece->l4*pow(10,8);  
           ppiece->score+=  ppiece->r4*pow(10,7);  
           ppiece->score+=  ppiece->l3*pow(10,6);    
           ppiece->score+=  ppiece->r3*pow(10,5);  
           ppiece->score+=  ppiece->l2*pow(10,4);    
           ppiece->score+=  ppiece->r2*pow(10,3);  
           ppiece->score+=  ppiece->l1*pow(10,2);
           ppiece->score+=  ppiece->r1*pow(10,1); 

      /*     ppiece->score=   ppiece->l4*(pow(LINE,4)+2*LIVE)+
                            ppiece->r4*(pow(LINE,4)+LIVE)+
                            ppiece->l3*(pow(LINE,3)+2*LIVE)+
                            ppiece->r3*(pow(LINE,3)+LIVE)+
                            ppiece->l2*(pow(LINE,2)+2*LIVE)+
                            ppiece->r2*(pow(LINE,2)+LIVE)+
                            ppiece->l1*(pow(LINE,1)+2*LIVE)+
                            ppiece->r1*(pow(LINE,1)+LIVE);
    
*/
    }
    return;
}
                        
