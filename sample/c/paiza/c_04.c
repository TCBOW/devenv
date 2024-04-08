#include <stdio.h>

void show(int A[], int n){
	for(int i = 0; i < n; i++){
		if(i < n - 1){
			printf("%d ", A[i]);
		} else {
			printf("%d", A[i]);
		}
		printf("\n");
	}
}
void sort(int A[], int n){
    for(int i = 0; i < n - 1 ; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(A[j] > A[j+1]){
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
				show(A, n);
            }
        }
    }
}

int main(void){
    // 自分の得意な言語で
    // Let's チャレンジ！！
    char str[1000];
    int n=0;
    scanf("%d", &n);
    int A[n];
    fgets(str, sizeof(str), stdin);
    for(int i = 0; i <= n; i++){
        sscanf(str, "%d ", &A[i]);
    }
    sort(A, n);
    return 0;
}
