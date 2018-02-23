#include"five_piece.h"
void display2dl(long long int array[SIZE][SIZE]){
int i,j;
    printf("\n");
        for(i=0;i<SIZE;++i){
                    printf("%4d ",i);
                            for(j=0;j<SIZE;++j)
                                            printf("%11d,",array[i][j]);
                                    printf("\n");
                                        }
    
    printf("    ");
        for(j=0;j<SIZE;++j)
                printf("%11c,",'A'+j);
                    printf("\n");
                        
                        printf("    ");
                            for(j=0;j<SIZE;++j)
                                    printf("%11d,",j);
                                        printf("\n");
                                        }

void display2d(int array[SIZE][SIZE]){//OAA?OUgdb?aEOE¡ÀOE 3/4 AEa 3/4 O 3/4 ?O¨®
        int i,j;
            printf("\n");
                for(i=0;i<SIZE;++i){
                            printf("%4d ",i);
                                    for(j=0;j<SIZE;++j)
                                                    printf("%d,",array[i][j]);
                                            printf("\n");
                                                }
                    
                    printf("     ");
                        for(j=0;j<SIZE;++j)
                                    printf("%c,",'A'+j);
                            printf("\n");
                                
                                printf("     ");
                                    for(j=0;j<SIZE;++j)
                                                printf("%d,",j);
                                        printf("\n");
}
