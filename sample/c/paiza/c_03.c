#include <stdio.h>
typedef struct user{
    char nickname[21];
    int  old;
    char birth[10];
    char state[21];
}USER;
int main(void){
    char str[1000];
    int N=0;
    scanf("%d", &N);
    getchar();
    USER usr[N];
    for(int i = 0; i < N; i++){
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%20s %d %9s %20s", &usr[i].nickname[0], &usr[i].old, &usr[i].birth[0], &usr[i].state[0]);
    }
    for(int i = 0; i < N; i++){   
        printf("User{\n");
        printf("nickname : %s\n", usr[i].nickname);
        printf("old : %d\n", usr[i].old);
        printf("birth : %s\n", usr[i].birth);
        printf("state : %s\n", usr[i].state);
        printf("}\n");
    }
    return 0;
}
