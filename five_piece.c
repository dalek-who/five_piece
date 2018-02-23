//五子棋总函数，进入人人/人机模式的入口
#include<stdio.h>

void pvp(void);
void pvc(void);

int main(){
    int module=-1;//模式选择
    printf("welocme to my five_piece program!\n");
    while(module!=1&&module!=2){
        printf("people vs people  : input 1\n");
        printf("people vs computer: input 2\n");
        scanf("%d",&module);
        
//选择并进入人人/人机模式
        switch(module){
            case 1:
                pvp();
                break;
            case 2:
                pvc();
                break;
            default:
                printf("wrong input, please choose again\n");
                break;
        }
    }
    int i; scanf("%d",&i);
    return 0;
}

