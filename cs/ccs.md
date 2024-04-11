# C言語チートシート

### 暗黙の型変換
異なる方での比較・計算・代入を行う場合は明示的にキャストを行うこと。
int と uintを比較の場合暗黙的にuintにキャストされてしまうので注意。
gccのコンパイルオプションで-Wを付けることでコンパイル時に暗黙の型変換について警告を出せる。

### 除算の小数点以下 切り捨て、四捨五入、切り上げ
ans = (x + y - 1) / y;  // 切り上げ

include <math.h>
double floor(double);  //切り捨て
double round(double);  //四捨五入
double cell(double);   //切り上げ

### intの最大値
limits.h のINT_MAXで定義されている。

### bitmap表現マクロ
#define X_SIZE 40
#define Y_SIZE 60
char graphics[X_SIZE / 8][Y_SIZE];
#define set_bit(x,y) graphics[(x)/8][y] |= (0x80 >> ((x)%8))

### ビットフィールドまたは構造体の圧縮 (使用非推奨）
struct item{
    uint16_t list:1;
    uint16_t seen:1;
    uint16_t number:14;
}

### ポインタ望ましくない使用方法だが覚書
int array[10];
int main(){
    int *data_ptr;
    int value;
    data_ptr = &array[0];   //1番目の要素を指すポインタ
    value = *data_ptr++;    //要素＃０を取得、data_ptrは要素＃１を指す
    value = *++data_ptr;    //要素＃２を取得、data_ptrは要素＃２を指す
    value = ++*data_ptr;    //要素＃２を１増加し、その値を返す



