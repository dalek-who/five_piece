//AI执黑先下时，在中间的六个位置随机落子，以防止每一局结果完全相同
#include"five_piece.h"

extern int  current_x,current_y;

void firstpiece(void){
    int first=30;
    srand((unsigned)time(NULL));
//生成随机数，几个随机数为一组，摇到该组的随机数，就落在这一组的那个棋子位置
//落在靠中间的位置概率会大一点
    while(!(first>=0 && first<=11)){
            first=rand()%12;
            switch(first){
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    current_x=7;
                    current_y=7;
                    return;
                case 5:
                case 6:
                    current_x=6;
                    current_y=7;
                    return;
                case 7:
                case 8:
                    current_x=5;
                    current_y=7;
                    return;
                case 9:
                    current_x=6;
                    current_y=8;
                    return;
                case 10:
                    current_x=5;
                    current_y=8;
                    return;
                case 11:
                    current_x=5;
                    current_y=9;
                    return;

                default:
                    break;
            }
    }
}

