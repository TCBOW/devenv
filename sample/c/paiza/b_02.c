#include <stdio.h>
#include <stdlib.h>
int main(void){
    // 自分の得意な言語で
    // Let's チャレンジ！！
    char str[1000];
    int N=0, H=0, W=0, P=0, Q=0; 
    int hit = 0;
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d %d %d %d %d", &N, &H, &W, &P, &Q);
    int sheet[H][W];
    for(int h = 0; h < H; h++){
        for(int w = 0; w < W; w++){
                sheet[h][w] = 0;
        }
    }
//    printf("%d %d %d %d %d\n", N,H,W,P,Q);
    int reserved_p = 0, reserved_q = 0;
    for(int i=0; i<N; i++){
        fgets(str, sizeof(str), stdin);
        scanf("%d %d", &reserved_p, &reserved_q);
        sheet[reserved_p][reserved_q] = 1;
//        printf("%d %d %d\n", reserved_p, reserved_q , sheet[reserved_p][reserved_q]);
    }
    printf("\n");
    for(int serch = 0; serch < H; serch++){
        for(int h = 0; h < H; h++){
            for(int w = 0; w < W; w++){
                if(sheet[h][w] == 0){
                    if(abs(P - h) + abs(Q - w) == serch ){
                        hit = 1;
                        printf("%d %d\n", h, w);
                    }
                }
            }
        }
        if(hit == 1)
            break;
    }

    return 0;
}
