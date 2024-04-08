#include <stdio.h>

int bubblesort(int array[], int n){
    int cnt = 0;
    int A[n];
    for(int i=0; i < n ; i++){
        A[i] = i + 1;
    }
    for(int i = 0; i < (n * 2 - 1); i++){
        for (int j = 0; j < n * 2 - i - 1; j++){
            if(array[j] > A[j]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                cnt++;
            }
        }
    }
    return cnt;
}
int main(void){
    // 自分の得意な言語で
    // Let's チャレンジ！！
    int n=0;
    scanf("%d", &n);
    
    int array[n*2];
    for (int i = 0; i < 2*n; i++){
        scanf("%d", &array[i]);
    }

    printf("%d\n", bubblesort(array, n));
    for(int i=0; i<n*2; i++){
        printf("%d\n", array[i]);
    }
    
    return 0;
}
