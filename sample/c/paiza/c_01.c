#include <stdio.h>
#include <string.h>

int donuts_search(char in[100][100], int height, int width) {
    char donuts[3][3] = {
        {'#', '#', '#'},
        {'#', '.', '#'},
        {'#', '#', '#'}
    };
    for (int h = 0; h < 3; h++) {
        for (int w = 0; w < 3; w++) {
            if (in[height + h][width + w] != donuts[h][w]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {
    int raw = 0, len = 0, cnt = 0;
    char str[10];
    char in[100][100];

    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d %d\n", &raw, &len);

    for (int i = 0; i < raw; i++) {
        fgets(str, len, stdin);
        str[strcspn(str, "\n")] = '\0'; // 改行文字の削除

        for (int l = 0; l < len; l++) {
            in[i][l] = str[l];
        }
    }

    for (int h = 0; h < raw - 2; h++) {
        for (int w = 0; w < len - 2; w++) {
            cnt += donuts_search(in, h, w);
        }
    }

    printf("%d\n", cnt);
    return 0;
}

//#include <stdio.h>
//#include <string.h>
//
//int donuts_search(char in[100][100], int height, int width){
//	char donuts[3][3] = {
//	                    {'#','#','#'},
//	                    {'#','.','#'},
//	                    {'#','#','#'}};
//	for(int h = 0; h < 3; h++){
//		for(int w = 0; w < 3; w++){
//			if(strcmp(&in[height+h][width+w], &donuts[h][w]) != 0){
//				return 0;
//			}
//		}
//	}
//	return 1;
//}	
//
//int main(void){
//    int raw=0, len=0, cnt=0;
//    char str[10];
//    char in[100][100];
//    fgets(str, sizeof(str), stdin);
//    sscanf(str, "%d %d¥n", &raw, &len);
//    for(int i = 0; i < raw; i++){
//        fgets(str, len, stdin);
//		for (int l = 0; l < len; l++) {
//			strcpy(&in[i][l], &str[l]);
//		}
//	}
//    for(int h = 0; h < raw; h++){
//        for(int w = 0; w < len; w++){
//        	cnt += donuts_search(in, h, w);
//		}
//    }
//    printf("%d", cnt);
//    return 0;
//}
