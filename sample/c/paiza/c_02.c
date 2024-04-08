#include <stdio.h>
int main(void){
    char str[1000];
    int N=0, K=0, cnt=0;
    int A[100];
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d %d\n", &N, &K );
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }
    
    for(int i = 0; i < N; i++){
        if(A[i] == K){
            cnt++;
        }
    }
    printf("%d\n ", cnt);
    return 0;
}
