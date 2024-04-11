
### 入力フォーマット指定子

```
指定子	対応する型	説明	使用例
%c	char	１文字を出力する	"%c"
%s	char *	文字列を出力する	"%8s", "%-10s"
%d	int, short	整数を10進で出力する	"%-2d","%03d"
%u	unsigned int, unsigned short	符号なし整数を10進で出力する	"%2u","%02u"
%o	int, short, 
unsigned int, unsigned short	整数を8進で出力する	"%06o","%03o"
%x	int, short, 
unsigned int, unsigned short	整数を16進で出力する	"%04x"
%f	float	実数を出力する	"%5.2f"
%e	float	実数を指数表示で出力する	"%5.3e"
%g	float	実数を最適な形式で出力する	"%g"
%ld	long	倍精度整数を10進で出力する	"%-10ld"
%lu	unsigned long	符号なし倍精度整数を10進で出力する	"%10lu"
%lo	long, unsigned long	倍精度整数を8進で出力する	"%12lo"
%lx	long, unsigned long	倍精度整数を16進で出力する	"%08lx"
%lf	double	倍精度実数を出力する	"%8.3lf"
```

### 表示桁数の指定

表示桁数は<全体の幅>.<小数点以下の幅>で指定する。どちらか片方だけの指定でも良いし、まったく指定しなくても良い。指定がなければデフォルトが使用される。 <小数点以下の幅>は、文字列の場合には最大文字数の意味になる。
```
指定例	出力結果	　
printf("[%8.3f]", 123.45678);
[ 123.456]
　
printf("[%15s]", "I am a boy.");
[    I am a boy.]
　
printf("[%.6s]", "I am a boy.");
[I am a]
　
printf("[%8.3e]", 1234.5678);
[1.234e+3]
```

表示桁数の指定よりも実際の表示文字列が長くなることがある。これはsprintf()の場合に特に注意が必要である。 文字列の格納域と同じサイズにフォーマットを指定しても、配列オーバーを引き起こす可能性のあることを意味するからである。


### リーディングゼロの指定

数値フィールドの場合に、ゼロ詰めを指定することができる。桁数の指定のまえにゼロを付加する。

指定例	出力結果	　
printf("[%08.3f]", 123.45678);
[0123.456]
　
printf("[%05d]", 1);
[00001]
　
右詰・左詰の指定

デフォルトでは右詰なので、左詰にしたいときは桁数指定のまえにマイナスをつけなければならない。

指定例	出力結果	　
printf("[%-15s]", "I am a boy.");
[I am a boy.    ]
printf("[%-8.3f]", 123.45678);
[123.456 ]
　
printf("[%-5d]", 1);
[1    ]
　
###  符号の指定

数値の表示は、デフォルトではプラス記号を出さないので、付けたいときは＋を指定する。

指定例	出力結果	　
printf("[%+5d]", 32);
[  +32]
printf("[%+5d]", -32);
[  -32]
　
printf("[%+8.3f]", 1.414);
[  +1.414]
　
### 入力フォーマット指定子

scanf(),fscanf(),sscanf()などで使用する指定子である。出力フォーマット指定子とほぼ同じだが、使えないものもある。

```
指定子	対応する型	説明
%c	char	１文字を入力する
%s	char *	文字列を入力する
%d	int	整数を10進数として入力する
%u	unsigned int	符号なし整数を10進数として入力する
%o	int, short, unsigned int	整数を8進数として入力する
%x	int, unsigned int	整数を16進数として入力する
%f	float	実数を入力する
%ｈd	short	単精度整数を10進数として入力する
%ld	long	倍精度整数を10進数として入力する
%ｈu	unsigned short	符号なし単精度整数を10進数として入力する
%lu	unsigned long	符号なし倍精度整数を10進数として入力する
%lo	long, unsigned long	倍精度整数を8進数として入力する
%lx	long, unsigned long	倍精度整数を16進数として入力する
%lf	double	倍精度実数を入力する
```

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

