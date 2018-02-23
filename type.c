//由棋型信息判断是什么棋型

#include"five_piece.h"
//返回值：空
//参数：player：角色的棋子颜色。*piece：指向记录棋型数据信息的结构的指针
void type(int player,piece *piece){
    //初始化各种棋型的数量
    piece->l5=0;
    piece->r4=0;
    piece->l4=0;
    piece->r3=0;
    piece->l3=0;
    piece->r2=0;
    piece->l2=0;
    piece->r1=0;
    piece->l1=0;
    piece->longline=0;
    piece->die=0;
    
    //为了写起来方便，做一些初始化
    int LL      =piece->LL,
        Ljump   =piece->Ljump,
        L       =piece->L,
        line    =piece->line,
        R       =piece->R,
        Rjump   =piece->Rjump,
        RR      =piece->RR,

        live    =piece->live,
        block   =piece->block;

    //连五
    if(piece->line==5){
        ++piece->l5;
        return;
    }
    
    //空位不足
    if(piece->space<5){
        ++piece->die;
        return;
    }
    
    //长连
    if(piece->line>=6){
        ++piece->longline;
        return;
    }
    
    //以下为对称的棋型
    ////////////////////////////////////////////
    //活四（只有对称的一种）
    if(L==0 && line ==4 && R==0){
        ++piece->l4;
        return;
    }
   
    //对称的活三
    if(LL==0 && L==0 && line ==3 && R==0 && RR==0){
        ++piece->l3;
        return;
    }

    //对称冲三1
    if(Ljump==-1 && L==0 && line==3 && R==0 && Rjump==-1){
        ++piece->r3;
        return;
    }
    
    //对称冲三2
    if(Ljump==1 && L==0 && line==1 && R==0 && Rjump==1){
        ++piece->r3;
        return;
    }
    //以下为不对称棋型
    //////////////////////////////////////////
    
    //向右
    /////////
    //冲四，两种类型
    if(R==0){
        if(     ( ( (L!=0 && L!=player) || L==OUT ) && line==4)//1_2220
//            ||  ( L==0 && line==4 && ( (R!=0 && R!=player) || R=OUT ) )//0_2221与上面一个是同一个棋型，只不过一个在左边堵着，一个在右边堵着
            ||  ( Rjump!=-1 && line+Rjump==4 )//2_202
          )
            ++piece->r4;

    //活三，两种类型
        else if(     ( L==0 && Rjump!=-1 && line==3 && Rjump==0)//022_00
            ||  ( L==0 && Rjump!=-1 && line+Rjump==3 && RR==0)//02_020
          )
            ++piece->l3;
    
    //冲三，三种类型
    //可以识别2_002
    //但不能识别_0022
        else if(     ( ( (L!=player && L!=0)|| L==OUT ) && Rjump!=-1 && line==3 && Rjump==0)//122_00
            ||  ( ( (L!=player && L!=0)|| L==OUT ) && Rjump!=-1 && line+Rjump==3 && RR==0)//12_020
            ||  ( L==0 && Rjump!=-1 && line+Rjump==3 && ( (RR!=0 && RR!=player) || RR==OUT ) )//02_021,前一个是堵在左面的，这个是堵在右面的。前一种通过向左扫扫不出这一类型，必须单开一个
            ||  ( line==2 && Rjump!=-1 && Rjump==0 && RR==player )//2_002
          )
            ++piece->r3;
    }
    
    //向左
    //与向右判断条件相同，把代码中的R，L互换
    //每个特殊棋型++后面都跟着return。右边的已经扫完了，扫左边的只要找到特殊棋型，就算完成任务了，就可以return了
    /////////
    //冲四，两种类型
    if(L==0){
        if(     ( ( (R!=0 && R!=player) || R==OUT ) && line==4)
            ||  ( Ljump!=-1 && line+Ljump==4 )
          ){
            ++piece->r4;
            return;
        }

    //活三，两种类型
        else if(     ( R==0 && Ljump!=-1 && line==3 && Ljump==0)
            ||  ( R==0 && Ljump!=-1 && line+Ljump==3 && LL==0)
          ){
            ++piece->l3;
            return;
        }
    
    //冲三，三种类型
        else if(     ( ( (R!=player && R!=0)|| R==OUT ) && Ljump!=-1 && line==3 && Ljump==0)
            ||  ( ( (R!=player && R!=0)|| R==OUT ) && Ljump!=-1 && line+Ljump==3 && LL==0)
            ||  ( R==0 && Ljump!=-1 && line+Ljump==3 && ( (LL!=0 && LL!=player) || LL==OUT ) )//02_021,前一个是堵在左面的，这个是堵在右面的。前一种通过向左扫扫不出这一类型，必须单开一个
            ||  ( line==2 && Ljump!=-1 && Ljump==0 && LL==player )
          ){
            ++piece->r3;
            return;
        }
    }
        
        
    //"其他"
    //所有不满足前面条件的棋型，只按line归类（r3，r2,l2,r1,l1)
    //之前寻找每种棋型，找到后都有return；如果能执行到这一步，说明之前所有的if条件，以及return都没有达成，所以可以全部归入“其他”
    if( piece->l5==0 && piece->l4==0 && piece->r4 ==0 && piece->l3 ==0 && piece->r3 ==0 && piece->die ==0){
        if( live==2 && line==3 )
            ++piece->l3;
        else if( live==1 && line==3 )
            ++piece->r3;
        else if( live==2 && line==2 )
            ++piece->l2;
        else if( live==1 && line==2 )
            ++piece->r2;
        else if( live==2 && line==1 )
            ++piece->l1;
        else if( live==1 && line==1 )
            ++piece->r1;
        
    //为防止遗漏，再补充一个else
        else ;
    }
    //所有的都找完了
        return;
} 
