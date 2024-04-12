# ゼロから学ぶC++
-----------------------------
# インストール

## コンパイラ

C++ のコンパイラは多くのベンダが開発しています。
代表的なものには次のようなものがあります。

| コンパイラ | Linux              | macOS              | Windows            |
|------------|:------------------:|:------------------:|:------------------:|
| GCC        | :white_check_mark: | :white_check_mark: | ️:white_check_mark: |
| Clang      | :white_check_mark: | :white_check_mark: | :warning:          |
| Visual C++ |                    |                    | :white_check_mark: |

GCC は Linux をメインに使用されるコンパイラですが、
Linux 以外の主要なプラットフォームでも使用することができ、
一番実績のあるコンパイラです。
Clang は近年注目されているコンパイラで、
今後は GCC に取って代わる可能性があるコンパイラです。

本書では Windows 版の GCC をインストールします。
GCC のインストールには msys2 というツールを使用します。
msys2 は Linux で使用できるコマンドの一部を Windows に移植したツールセットです。

### msys2 のインストール

下記の msys2 の公式ページにアクセスしてインストーラをダウンロードします。

```
https://www.msys2.org/
```

インストーラは `msys2-i386-yyyymmdd.exe, msys2-x86_64-yyyymmdd.exe` の
2 種類がありますが、前者が 32 ビット版で後者が 64 ビット版になります。
本書では 64 ビット版をもとに説明するので、64 ビット版をインストールしてください。

### GCC のインストール

msys2 のターミナルを起動して下記コマンドを打ってインストールします。

```bash
$ pacman -S gcc
```

## IDE

C++ 用の IDE としては Visual Studio Code が人気です。
Visual Studio Code 自体はエディタなのですが、拡張機能を入れることで
C++ 向けに使用することもできます。

下記サイトより Visual Studio Code をインストールしてください。

```
https://code.visualstudio.com/
```

Visual Studio Code の拡張機能である [C/C++] もインストールします。
Visual Studio Code を起動した後、`Ctrl+Shift+X` を押すと
拡張機能のインストール画面に切り替わるので、
[C/C++] を検索してインストールしてください。

[C/C++]: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
-----------------------------

ファイル: ./ch01-02-hello-world.md
-----------------------------
# Hello, World!

Visual Studio Code 上で `main.cc` というファイルを作成して
下記のようなソースコードを作成します。

!!! example "main.cc"
    ```cpp linenums="1"
    #include <iostream>

    int main() {
        std::cout << "Hello, World!" << std::endl;

        return 0;
    }
    ```

msys2 のターミナルを起動して下記コマンドを打ってコンパイルします。

```bash
$ g++ -std=c++11 main.cc
```

成功すると `a.exe` というファイルができていると思います。
これが実行ファイルになるので、実行すると `Hello, World!` という
メッセージが表示されます。

```bash
$ ./a.exe
Hello, World!
```
-----------------------------

ファイル: ./ch02-01-variables.md
-----------------------------
# 変数

C++ で変数を使用する方法について説明します。
整数値の変数を宣言するには次のようにします。

```cpp
int x = 5;
```

`int` は整数を表現する型です。
宣言時に初期化をせずにあとで値を代入することもできます。

```cpp
int x;
x = 5;
```

初期値を設定しないまま変数を使用すると不定な値が入るので注意して下さい。

```cpp
int x;

std::cout << x << std::endl;  // 不定な値が出力される
```

## const

`const` を付けると値の書き換えが禁止できます。

```cpp
const int x = 5;
x = 10;  // エラー
```

## constexpr

`constexpr` を付けると定数にできます。

```cpp
constexpr int x = 5;
```

`const` の値は実行時に決定しますが `constexpr` の値はコンパイル時に決定します。

## 型推論

変数の宣言時には明示的に型を指定しなくても `auto` を使うと
右辺の値から型を推論することができます。

```cpp
auto x = 5;  // x は int と推論
```
-----------------------------

ファイル: ./ch02-02-primitive-types.md
-----------------------------
# 基本型

C++ ではじめから使用できる基本型について説明します。

## bool

`bool` は真偽値を表す型で `true` または `false` が設定できます。

```cpp
bool ok = true;
```

## char

`char` はアスキー文字1文字を表現する型です。
ただし内部表現はアスキーコードの整数値として扱われ、
標準出力などに出力する際に文字に変換されて出力されます。

```cpp
char x = 'x';
```

## 数値

数値を表現する型は複数種類用意されています。

### 整数型

整数を表現するための型です。

* `char`
* `short`
* `int`
* `long`

下に行くに連れて大きな値が表現できるようになり、変数のサイズも増大します。
具体的なサイズはコンパイラによって変わってきますが
GCC では 8, 16, 32, 64 ビットで定義されています。
一般的には `int` が使用されます。

### 符号付き・符号なし整数型

各整数型に `unsigned` を付けると正の数しか表現できなくなる代わりに
大きな値が表現できるようになります。

```cpp
unsigned int x = 4000000000;
```

`signed` を付けると正負両方の値が表現できます。
明示的に付けなくてもデフォルトは `signed` になります。

!!! warning "`char` は `signed char` じゃない？"
    C++ では `char, signed char, unsigned char` はそれぞれ異なる型として定義されています（C言語も同様です）。
    プレーンな `char` 型が符号付き・符号なしのいずれになるかは、仕様上は処理系定義(implementation-defined)とされています。
    実際にはコンパイラオプションで符号有無を選択できたり、対象プロセッサアーキテクチャなどから決まるのが一般的です。
    移植性のあるコードを書く場合は十分注意して下さい。

### サイズ指定付き整数型

上述の整数型は型のサイズがコンパイラによってまちまちなので
複数のコンパイラに対応するプログラムを書くときは
移植性の面で問題が発生することがあります。
そのようなときはサイズ指定付き整数型を使用します。

* `std::int8_t`
* `std::int16_t`
* `std::int32_t`
* `std::int64_t`
* `std::uint8_t`
* `std::uint16_t`
* `std::uint32_t`
* `std::uint64_t`

数値は型のビットサイズを表しており、u は `unsigned` を表しています。
サイズ指定付き整数型を使用する場合は `#include <cstdint>` と記述する必要があります。

```cpp
#include <cstdint>

std::int32_t x = 5;
```

### 浮動小数点型

小数を表現する型は次の2つの型があります。

* `float`
* `double`

`float` は 32 ビットの大きさを持ち、`double` は 64 ビットの大きさを持ちます。
また `double` の方が `float` に比べて計算精度が高いですが数値計算の
パフォーマンスは低いです。

## 列挙型

列挙型は、名前を付けた定数（列挙子）の集合を扱う型です。

### enum

列挙型である `enum` を定義するには次のようにします。

```cpp
enum Day {
  Sun,  // 0
  Mon,  // 1
  Tue,  // 2
  Wed,  // 3
  Thu,  // 4
  Fri,  // 5
  Sat   // 6
};
```

`enum` の各列挙子は、内部では整数として扱われています。
各列挙子の定義の際に値を指定しなければ、 `0` から順に値が割り振られます。

`列挙子 = 整数` と書くことで値を指定することができます。値が指定された列挙子以降は、順に整数が割り振られます。

```cpp
enum Day {
  Sun = 1,  // 1
  Mon,      // 2
  Tue,      // 3
  Wed = 8,  // 8
  Thu,      // 9
  Fri,      // 10
  Sat       // 11
};
```

`enum` を扱うには次のようにします。

```cpp
Day day = Fri;
```

数値型に `enum` の値を代入することは可能ですが、 `enum` に数値を直接代入することは出来ません。

```cpp
int x = Fri;  // OK
Day day = 5;  // コンパイルエラー
```

列挙子の名前は被らないようにする必要があります。

```cpp
enum Day {
  Sun,
  Mon,
  Tue,
  Wed,
  Thu,
  Fri,
  Sat
};

enum SolarSystem {
  Sun,  // Sun は enum Day 内で定義済みのためコンパイルエラー
  Mercury,
  Venus,
  Earth,
  Mars,
  Jupiter,
  Saturn,
  Uranus,
  Neptune
};
```

### enum class

`enum class` で列挙型を定義することもできます。

```cpp
enum class Day {
  Sun,
  Mon,
  Tue,
  Wed,
  Thu,
  Fri,
  Sat
};
```

基本的には `enum` と同じですが、以下の点が異なります。

`enum class` を扱うには `型名::列挙子名` とします。

```cpp
Day day = Day::Fri;  // OK
Day day = Fri;       // コンパイルエラー
```

明示的に型変換をしない限り、数値型に `enum class` の値の代入はできません。

```cpp
int x = Day::Fri;  // コンパイルエラー
```

!!! tip "明示的な型変換"
    [明示的に型変換][cpp-casts] を行うことで、数値型などに `enum class` の値の代入が可能です。

    ```cpp
    int x = static_cast<int>(Day::Fri);
    ```

[cpp-casts]: ch08-01-cpp-casts.md

`enum class` の場合、列挙子の名前は型ごとに区別されるため、
他の列挙型の列挙子と名前が被っても問題ありません。

```cpp
enum class Day {
  Sun,  // Day::Sun
  Mon,
  Tue,
  Wed,
  Thu,
  Fri,
  Sat
};

enum class SolarSystem {
  Sun,  // Day::Sun と SolarSystem::Sun は区別されるためOK
  Mercury,
  Venus,
  Earth,
  Mars,
  Jupiter,
  Saturn,
  Uranus,
  Neptune
};
```
-----------------------------

ファイル: ./ch02-03-literals.md
-----------------------------
# リテラル

ソースコードの中に記述される定数値のことをリテラルといいます。

本項では整数リテラルについて紹介します。他のリテラルについては [式 - cppreference.com][cppreference_expressions] を参照してください。

## 整数リテラル

数字の先頭に特定の文字を加えることで整数の基数を変えることが出来ます。

```cpp
26   // 10進整数リテラル
032  // 先頭に0を付けると8進整数リテラル
0x1a // 先頭に0xを付けると16進整数リテラル
0x1A // 16進整数リテラル内の文字は小文字でも大文字でも区別されないので0x1aと同じ
```

数字の末尾に文字を加えることで次のような型を表現できます。

```cpp
26u    // unsigned型の26
26l    // long型の26
26ul   // unsigned long型の26
0x1Aul // unsigned long型の0x1A
```

[cppreference_expressions]: https://ja.cppreference.com/w/cpp/language/expressions-----------------------------

ファイル: ./ch02-04-pointers-and-references.md
-----------------------------
# ポインタと参照

## ポインタ

ポインタというのは他の変数を参照する仕組みの1つです。
Windows のショートカットや Linux のシンボリックリンクと同じような機能です。

```cpp
int x = 5;
int* p = &x;
```

`int*` と書くと `int` 型の変数を指すポインタ型となります。
`&x` というのは `x` を指すポインタを得るための演算です。

## nullptr

どの変数も参照していないポインタのことをヌルポインタと呼びます。C++ではヌルポインタを表すキーワードとして `nullptr` が用意されています。

```cpp
int* p = nullptr;
```

!!! warning "NULL マクロ"
    C++11 より前はヌルポインタを表すのに `nullptr` というキーワードではなくC言語から受け継いだ `NULL` を使用するのが一般的でした。
    C言語の処理系では、 `void*` 型の変数は任意のポインタ型に暗黙変換される仕様があるため、 `NULL` を `(void*)0` などと定義している例が見られました。
    C++ではそのような暗黙変換は許されていないため、 `NULL` は単に `0` と定義される例が見られました。
    しかし `0` というリテラルは文脈によってヌルポインタと解釈されたり `int` 型と解釈されたりするため不都合が生じることもありました。

    C++11 ではこの問題を解決するために `nullptr` が導入されました。
    そのため C++11 以降では `NULL` ではなく `nullptr` を使うようにしましょう。

    詳細は [nullptr - cpprefjp C++日本語リファレンス][cpprefjp_nullptr] を参照してください。

[cpprefjp_nullptr]: https://cpprefjp.github.io/lang/cpp11/nullptr.html

## デリファレンス（逆参照）

ポインタが指す変数の値を参照するには次のように書きます。

```cpp
int x = 5;
int* p = &x;
int y = *p;
```

変数からポインタを得るときには `&` を付け、ポインタから値を得るには `*` を付けます。

## constポインタ

ポインタ型に `const` を付ける場合、 `const` の付ける位置によって意味合いが変わります。

`*` の前に `const` を付けると、ポインタが指し示す値を書き換えることができなくなります。

```cpp
int x = 123;
const int* p = &x;
*p = 456; // エラー
```

`*` の後に `const` を付けると、ポインタ自身を書き換えることができなくなります。

```cpp
int x = 123;
int* const p = &x;
p = nullptr; // エラー
```

併用することも可能です。

```cpp
const int* const p = &x;
```

## 参照

ポインタに似た仕組みとして参照があります。

```cpp
int x = 100;
int* p = &x; // pはポインタ型
int& r = x; // rは参照型

*p = 200;
r = 200;
```

`int&` と書くと `int` の参照型となります。

ポインタが指し示す値を扱うには `*` を付けてデリファレンスする必要がありますが、
参照では何も付与する必要がないため、見た目上では値型のように使うことが出来ます。
-----------------------------

ファイル: ./ch02-05-comments.md
-----------------------------
# コメント

ソースコード内にコメントを書きたい場合は次のようにします。

```cpp
// '//' で始まる行はコメントと見なされます

int x = 5;

// このように
// 複数行にまたがって
// コメントを書くこともできます
```

`/* ... */` で囲まれた行もコメントと見なされます。
複数行にまたがるコメントを書く時に便利です。

```cpp
/*
 * 間に現れる '*' は書かなくてもいいですが
 * 習慣的に書くことのほうが多いです
 */
```

`/* ... */` は入れ子にして使うことはできないので注意して下さい。

```cpp
/* /* これは不正なコメントです */ */
```
-----------------------------

ファイル: ./ch02-06-control-flow.md
-----------------------------
# 制御文

## if

条件分岐をしたい時には `if` を使用します。

```cpp
int x = 5;

if (x == 5) {
    ...
}
```

`if` の条件を満たさなかった場合に何か処理をしたければ `else` を使用します。

```cpp
int x = 5;

if (x == 5) {
    ...
} else {
    ...
}
```

さらに別の条件で処理を分岐したければ `else if` を使用します。

```cpp
int x = 5;

if (x == 5) {
    ...
} else if (x == 6) {
    ...
} else {
    ...
}
```

## switch

一つの変数の値を調べながら分岐するような処理を書きたい場合は `switch` 文を使います。

```cpp
switch (x) {
    case 0:
        // x == 0 のときの処理
        break;
    case 1:
        // x == 1 のときの処理
        break;
    default:
        // x がそれ以外のときの処理
        break;
}
```

ただし `switch` 文が使用できるのは下記のいずれかの場合に限ります。

- [整数型](ch02-02-primitive-types.md#_3)
- [列挙型](ch02-02-primitive-types.md#_7)
- 整数型か列挙型へ暗黙に変換できるクラス型

上記の構文は `if` で書き直すと次と等価になります。

```cpp
if (x == 0) {
    // x == 0 のときの処理
} else if (x == 1) {
    // x == 1 のときの処理
} else {
    // x がそれ以外のときの処理
}
```

ただし `switch` 文のほうが `if` よりも比較回数が少ないため効率的です。
`if` はまずはじめに `x == 0` が `true` かどうかを調べ `false` であれば
次に `x == 1` を評価しますが、`switch` 文はいきなり特定の `case` にジャンプします。

### フォールスルー

`switch` の各 `case` 内に書かれている `break` は書かなくてもよいのですが、
その場合振る舞いが変わります。

```cpp
switch (x) {
    case 0:
        // x == 0 のときの処理
    case 1:
        // x == 1 のときの処理
    default:
        // x がそれ以外のときの処理
}
```

`break` を書いた場合は `switch` 文の処理はそこで終わりますが、
`break` を書かなかった場合はそのまま下の `case` に処理が流れてしまいます。
つまり上記のコードは `x == 0` であれば `case 0` 内の処理を行った後に
`case 1` 内の処理を行い、最後に `default` の処理を行います。
`x == 1` であれば同様の振る舞いが `case 1` から始まります。
このような `switch` 文の仕様をフォールスルーと言います。
これは `case 0` と `case 1` の処理が同じものになる場合に使用すると便利です。

```cpp
switch (x) {
    case 0:
    case 1:
        // x == 0 または x == 1 のときの処理
    default:
        // x がそれ以外のときの処理
}
```

それ以外のケースでフォールスルーをさせるシーンはまずないため、
`break` を忘れずに付けておく必要があります。

## while

`while` は `()` に渡された条件が `true` である限り
`{ ... }` 内の処理を実行し続けます。

```cpp
int x = 5;
bool done = false;

while (!done) {
    x += x - 3;

    std::cout << x << std::endl;

    if (x % 5 == 0) {
        done = true;
    }
}
```

### do-while

最初の1回は無条件で `do { ... }` 内の処理を実行し、
2回目以降は `while ()` に渡された条件が `true` である限り
`do { ... }` 内の処理を実行し続けます。

```cpp
int x = 5;
bool done = false;

do {
    x += x - 3;

    std::cout << x << std::endl;

    if (x % 5 == 0) {
        done = true;
    }
} while (!done);
```

## for

`for` はループするたびに変化する変数を使うことができます。

```cpp
for (int i = 0; i < 10; ++i) {
    std::cout << i << std::endl;
}
```

`i` はループするたびに `0, 1, 2, ..., 9` と値が変化し続けます。
`for (int i = 0; i < 10; ++i)` というのは `i` に `0` を設定して
`i < 10` を満たすまで `i` を `+1` しながらループを継続するという意味になります。

`for` はこの書き方以外に `範囲 for` という書き方もあります。
詳細は [3.9. 範囲 for][range-based-for] を参照してください。

[range-based-for]: ch03-09-range-based-for.md

## ループ処理の中断

ループ文 `while`、 `do-while`、 `for` のループ処理は
`break` または `continue` で中断することができます。

### break

現在のループ処理を中断してループ文を終了します。

```cpp
int x = 5;

while (true) {
    x += x - 3;

    std::cout << x << std::endl;

    if (x % 5 == 0) {
        break;  // while 文を抜ける
    }
}
```

ループ文がネストしている場合には、最も内側にある文のみが対象になります。

```cpp
for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
        if (i == j) {
            break;  // j のループ文を抜ける
        }

        std::cout << i << "," << j << std::endl;
    }
}
```

### continue

現在のループ処理を中断して、次のループ処理を行います。

```cpp
for (int i = 0; i < 10; ++i) {
    if (i == 5) {
        continue;  // 5 だけスキップ
    }

    std::cout << i << std::endl;
}
```

ループ文がネストしている場合には、最も内側にある文のみが対象になります。

```cpp
for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
        if (i == j) {
            continue;  // j のループ処理をスキップ
        }

        std::cout << i << "," << j << std::endl;
    }
}
```

`contiune` では次のループ処理を行うため、
`do-while` では先頭に戻るのではなく末尾へ移動する動作となります。

```cpp
do {
    std::cout << "done" << std::endl;
    continue;  // ループ処理をスキップ (先頭に戻る動作なら無限ループとなる)

    std::cout << "never reached" << std::endl;  // 実行されない
} while (false);  // 条件が false であるため1回目で終了
```
-----------------------------

ファイル: ./ch02-07-operators.md
-----------------------------
# 演算子

算術演算子を中心に、C++ で利用できる演算子を紹介します。
本項で紹介されていない演算子については [式 - cppreference.com][cppreference_expressions] を参照してください。

[cppreference_expressions]: https://ja.cppreference.com/w/cpp/language/expressions

## 四則演算と剰余

基本的な演算は次の演算子を使うことで可能です。

```cpp
x + y;  // 加算
x - y;  // 減算
x * y;  // 乗算
x / y;  // 除算
x % y;  // 剰余
```

`0` で除算(剰余)を行うと実行時エラーになるため、注意してください。

!!! failure "ゼロ除算"
    ```cpp
    int div = 100 / 0; // 実行時エラー
    int mod = 100 % 0; // 実行時エラー
    ```

演算の対象となるいずれかの値が `double` ( `float` )の場合、
他方の値も `double` ( `float` ) として変換された上で演算が行われます。

```cpp
int ix = 100;
int iy = 50;
double dx = 100.0;
double dy = 50.0;

auto a = ix / iy;  // int = int / int
auto b = ix / dy;  // double = double(intから変換) / double
auto c = dx / iy;  // double = double / double(intから変換)
auto d = dx / dy;  // double = double / double
```

## インクリメント/デクリメント

```cpp
++x;  // 前置インクリメント
x++;  // 後置インクリメント
--x;  // 前置デクリメント
x--;  // 後置デクリメント
```

前置の場合は、インクリメント/デクリメントの演算が先に行われます。

```cpp
int a = 5;
int b = 0;

b = ++a;  // aをインクリメントしてから、bに代入する
std::cout << a << std::endl;  // 6
std::cout << b << std::endl;  // 6
```

対して、後置の場合は、インクリメント/デクリメントの演算以外の処理が先に行われます。

```cpp
int a = 5;
int b = 0;

b = a++;  // aをbに代入してから、aをインクリメントする
std::cout << a << std::endl;  // 6
std::cout << b << std::endl;  // 5
```

使用する状況にも依りますが、
後置インクリメント/デクリメントよりも前置インクリメント/デクリメントのほうが効率が良いとされています。

## ビットの演算

ビットに対する演算は次の演算子を使うことで可能です。

```cpp
~x      // 否定
x << y  // 左シフト
x >> b  // 右シフト
x & y   // 論理積
x | y   // 論理和
x ^ y   // 排他的論理和
```

`std::bitset` を使うことで、ビット列(2進数)での表記が確認できます。

```cpp
#include <bitset>
#include <iostream>

auto bits_a = std::bitset<8>("00001111");  // 15を8ビットで表す: 00001111
std::cout << ~bits_a << std::endl;         // 否定: 11110000
std::cout << (bits_a << 2) << std::endl;   // 左に2シフト: 00111100
std::cout << (bits_a >> 2) << std::endl;   // 右に2シフト: 00000011

auto bits_b = std::bitset<8>("00111100");     // 60を8ビットで表す: 00111100
std::cout << (bits_a & bits_b) << std::endl;  // 論理積: 00001100
std::cout << (bits_a | bits_b) << std::endl;  // 論理和: 00111111
std::cout << (bits_a ^ bits_b) << std::endl;  // 排他的論理和: 00110011
```

数値型でもビット演算は行なえます。
ビットを取り扱う際は、 `unsigned` が付いた符号なし整数型を利用することが望ましいです。

```cpp
unsigned int a = 0x0000000f;            // 15
std::cout << std::showbase << std::hex; // 基数のプレフィックスを出力 + 16進法で出力
std::cout << ~a << std::endl;           // 0xfffffff0
std::cout << (a << 2) << std::endl;     // 0x3c
std::cout << (a >> 2) << std::endl;     // 0x3

unsigned int b = 0x0000003c;        // 60
std::cout << (a & b) << std::endl;  // 0xc
std::cout << (a | b) << std::endl;  // 0x3f
std::cout << (a ^ b) << std::endl;  // 0x33
```

??? question "ビット演算で符号あり整数型を避ける理由"
    符号あり整数型のシフト演算の動作は言語仕様で未定義や処理系定義になっているものがあります。
    それらを考慮しないで済むように、ビット演算では符号なし整数型を利用することが望ましいです。

    <!-- MEMO: C++11 の言語仕様では1の補数表現が許容されているため注釈を入れている -->

    ```cpp
    // 2の補数表現の場合の例

    // 0以上の数値の左シフト
    int8_t a1 = 0x40;        // 01000000
    int8_t s11 = (a1 << 1);  // 未定義 (C++14 以上では 10000000)
    int8_t s12 = (a1 << 2);  // 未定義 (C++20 以上では 00000000)

    // 0未満の数値の左シフト
    int8_t a2 = 0x80;       // 10000000
    int8_t s2 = (a2 << 1);  // 未定義 (C++20 以上では 00000000)

    // 0以上の数値の右シフト
    int8_t a3 = 0x41;       // 01000000
    int8_t s3 = (a3 >> 1);  // 00100000

    // 0未満の数値の右シフト
    int8_t a4 = 0x80;       // 10000000
    int8_t s4 = (a4 >> 1);  // 処理系定義 (C++20 以上では 11000000)
    ```

    詳細は [算術演算子 - cppreference.com][cppreference_operator_arithmetic] を参照してください。

[cppreference_operator_arithmetic]: https://ja.cppreference.com/w/cpp/language/operator_arithmetic

## 複合代入

算術演算子と代入演算子を組み合わせることで、算術と代入を同時に行うことが可能です。

```cpp
a += b   // a = a + b と同じ
a -= b   // a = a - b
a *= b   // a = a * b
a /= b   // a = a / b
a %= b   // a = a % b
a &= b   // a = a & b
a |= b   // a = a | b
a ^= b   // a = a ^ b
a <<= b  // a = a << b
a >>= b  // a = a >> b
```

代入演算子は算術演算子よりも後に解釈されます。
複合代入も、代入演算子と同様に算術演算子よりも後に解釈されることになります。

```cpp
int x = 2;
x *= 4 + 3;
std::cout << x << std::endl;  // 14

int y = 2;
y = y * 4 + 3;
std::cout << y << std::endl;  // 11
```

!!! tip "演算子の優先順位"
    演算子ごとに解釈される優先順位は決まっています。
    詳細は [C++の演算子の優先順位 - cppreference.com][cppreference-operator-precedence] を参照してください。

[cppreference-operator-precedence]: https://ja.cppreference.com/w/cpp/language/operator_precedence-----------------------------

ファイル: ./ch02-08-functions.md
-----------------------------
# 関数

C++での関数の使用方法について説明します。

関数`HelloWorld()`を作成し、`main()`から呼び出して利用する場合は次のようにします。

!!! example "main.cc"
    ```cpp hl_lines="3 4 5 6 7 10" linenums="1"
    #include <iostream>

    void HelloWorld(int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << "[" << i << "] " << "Hello World!" << std::endl;
        }
    }

    int main() {
        HelloWorld(10);

        return 0;
    }
    ```

ここで注目すべき点は、関数`HelloWorld()`が、呼び出されている10行目より上の行で記述されている点です。
コンパイラはソースコードを上から順に解釈しているため、コンパイラに対して`HelloWorld()`が何者なのかを事前に教えることで、`HelloWorld()`の関数呼び出しが行なえるようになります。

試しに`HelloWorld()`を`main()`よりも下の行に記述すると、コンパイルに失敗します。

!!! failure "main.cc"
    ```cpp hl_lines="4" linenums="1"
    #include <iostream>

    int main() {
        HelloWorld(10);  // ここでコンパイルエラー

        return 0;
    }

    void HelloWorld(int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << "[" << i << "] " << "Hello World!" << std::endl;
        }
    }
    ```

4行目の時点では、`HelloWorld()`が何者なのかコンパイラには理解できないためです。

## 関数の前方宣言

関数の宣言のみを呼び出し箇所よりも上の行に記述することで、関数の存在をコンパイラに教えることが出来ます。

!!! example "main.cc"
    ```cpp hl_lines="3" linenums="1"
    #include <iostream>

    void HelloWorld(int n);  // 前方宣言

    int main() {
        HelloWorld(10);

        return 0;
    }

    void HelloWorld(int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << "[" << i << "] " << "Hello World!" << std::endl;
        }
    }
    ```

`HelloWorld()`の本体は`main()`の呼び出し箇所よりも下に記述されていますが、前方宣言があることで問題なくコンパイルできます。

宣言についての詳細は、[4.1. 宣言と定義][declarations-and-definitions] を参照してください。
[declarations-and-definitions]: ch04-01-declarations-and-definitions.md

## main関数

これまでのサンプルコードで度々現れた`main()`をmain関数と呼びます。

C++で生成された実行ファイルを実行すると、main関数を起点に処理が進みます。

## コマンドライン引数

main関数にも引数を渡すことが可能です。main関数に渡される引数をコマンドライン引数と呼びます。
コマンドライン引数は、プログラム実行時に実行ファイル名に続けて半角スペース区切りで複数指定することが出来ます。

```bash
# 実行ファイル名 <引数1> <引数2> <引数3> ...
$ ./a.exe XXX YYY ZZZ
```

コマンドライン引数を受け取る場合、main関数の引数は次のようにします。

```cpp
int main(int argc, char* argv[]);
```

- `int argc`: コマンドライン引数の個数を表す
- `char* argv[]`: コマンドライン引数が格納される

!!! example "main.cc"
    ```cpp linenums="1"
    #include <iostream>

    int main(int argc, char* argv[]) {
        for (int i = 0; i < argc; ++i) {
            std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
        }

        return 0;
    }
    ```

```bash
# 実行結果
$ ./a.exe Hello World!
argv[0]: ./a.exe
argv[1]: Hello
argv[2]: World!
```

## オーバーロード

関数の引数の個数や型が異なる場合、同じ名前の関数を定義することが出来ます。
これを（関数の）オーバーロードと呼びます。引数の個数や型の情報を元に呼び出す関数を決定しています。

!!! example "main.cc"
    ```cpp linenums="1"
    #include <iostream>

    void Print(int x) {
        std::cout << "int: " << x << std::endl;
    }

    void Print(double x) {
        std::cout << "double: " << x << std::endl;
    }

    int main() {
        Print(2);
        Print(2.1);

        return 0;
    }
    ```

```bash
# 実行結果
$ ./a.exe
int: 2
double: 2.1
```

## 関数ポインタ

関数を指し示すポインタを作成する場合は次のようにします。

```cpp
// 戻り値の型 (*変数名)(引数の型);
int (*f1)(double);    // double を引数として int を返す関数のポインタ f1
int (*f2)(int, int);  // 2つの int を引数として int を返す関数のポインタ f2
```

関数ポインタには、戻り値の型と引数の型・数・順番が一致している関数のアドレスが代入可能です。

```cpp
#include <iostream>

int Add(int x, int y) {
    return x + y;
}

int main() {
    int (*fp)(int, int) = Add;  // 関数 Add のアドレスを保持する関数ポインタ fp
    int result = fp(3, 5);      // 関数ポインタ fp を介して関数 Add が実行される
    std::cout << result << std::endl;  // 8

    return 0;
}
```

関数ポインタを変数に代入する際は、 `auto` を使うことで複雑な関数ポインタの型を書く必要が無くなり簡潔になります。

```cpp
auto fp = Add;
```
-----------------------------

ファイル: ./ch02-09-lambda-expressions.md
-----------------------------
# ラムダ式

ラムダ式は、簡潔に関数オブジェクトを記述するための式です。
ラムダ式で生成される関数オブジェクトは `auto` で保持することが出来ます。

ラムダ式の構文は次のようになります。

```cpp
// auto 変数名 = [ キャプチャ ]( 引数リスト ) -> 戻り値の型 { 処理内容 };
auto func = [](int a, int b) -> int { return a + b; };  // int を2つ受け取り、足した結果を返すラムダ式

int result = func(4, 6);
std::cout << result << std::endl;  // 10
```

## キャプチャ

ラムダ式の外にある変数をラムダ式の中で使用する場合は、
ラムダ式先頭の `[]` 内でキャプチャと呼ばれるものの指定が必要です。

キャプチャには、コピーキャプチャと参照キャプチャの2種類が存在します。

|  記述例   | 内容                                                             |
|:---------:|------------------------------------------------------------------|
| `[=]`     | ラムダ式定義時に存在する全ての変数をコピーしてラムダ式の中で使う |
| `[&]`     | ラムダ式定義時に存在する全ての変数を参照してラムダ式の中で使う   |
| `[a]`     | 変数 `a` をコピーしてラムダ式の中で使う                          |
| `[&a]`    | 変数 `a` を参照してラムダ式の中で使う                            |
| `[&a, b]` | 変数 `a` は参照し、変数 `b` はコピーしてラムダ式の中で使う       |
| `[=, &a]` | 変数 `a` は参照し、それ以外はコピーしてラムダ式の中で使う        |

```cpp
int init = 5;

// キャプチャを指定することで {} 内で変数 init を使うことができる
auto f = [init](int a, int b) { return init + a * b; };   // コピーキャプチャ
auto g = [&init](int a, int b) { return init + a * b; };  // 参照キャプチャ

init = 0;

// 【コピーキャプチャの場合】
//    ラムダ式の定義時点で init がコピーされているので、ラムダ式内の init は 5
int result_copy = f(2, 4);
std::cout << result_copy << std::endl;  // 13

// 【参照キャプチャの場合】
//    ラムダ式実行時の init の値が参照されるので、ラムダ式内の init は 0
int result_ref = g(2, 4);
std::cout << result_ref << std::endl;   // 8
```

## 引数リスト

`( 引数リスト )` は、通常の関数と同じように記述することが出来ます。

```cpp
auto func1 = [](int x) -> int { return x * x; };  // int を引数とする
auto func2 = []() -> int { return 400; };         // 引数なし
auto func3 = [] { return 400; };                  // 戻り値の型の記述を省略した場合、 () ごと省略可能
```

## 戻り値の型の省略

`-> 戻り値の型` は、 ラムダ式内の型推論に任せる場合は省略可能です。

```cpp
auto func = [](int a, int b) { return a + b; };  // a, b は共に int なので、戻り値も int と推論される
```

## 関数ポインタへの変換

キャプチャを持たないラムダ式であれば関数ポインタに暗黙変換することが出来ます。

```cpp
int (*fp)(int, int) = [](int x, int y) { return x + y; };
```

## `std::function`

`std::function` で関数ポインタやラムダ式（キャプチャを持つラムダ式も含む）を保持することが出来ます。
`std::function` を使うことで、関数ポインタのような複雑な構文が簡潔になるという利点もあります。

```cpp
#include <functional>

int Add(int x, int y) {
    return x + y;
}

int main() {
    std::function<int(int, int)> f = Add;  // std::function<戻り値の型(引数の型)> 変数名
    int result = f(3, 5);                  // f を介して関数 Add が実行される
    std::cout << result << std::endl;      // 8

    f = [](int x, int y) { return x * y; };  // ラムダ式も保持可能
    std::cout << f(4, 7) << std::endl;       // 28

    return 0;
}
```
-----------------------------

ファイル: ./ch03-01-arrays.md
-----------------------------
# 配列

配列は同一の型を持つ複数の値をまとめて管理するための型です。
使い方は次のとおりです。

```cpp
int x[5] = {0, 1, 2, 3, 4};
```

これで 5 要素の値を持つ配列が宣言されます。

## 要素参照

配列の要素を参照するには配列の何番目の要素なのかを指定します。
数えの始まりは 0 からになります。

```cpp
int x[5] = {0, 1, 2, 3, 4};
int y = x[2];  // 2
```

## 初期化のバリエーション

配列の宣言と同時に要素を設定する場合は要素数の指定が省略できます。

```cpp
int x[] = {0, 1, 2, 3, 4, 5};
```

配列の宣言後に要素を設定する場合は要素数の指定が必要です。

```cpp
int x[5];

x[0] = 0;
x[1] = 1;
x[2] = 2;
x[3] = 3;
x[4] = 4;
```

要素数に比べて設定した要素の個数が少ない場合は残りの要素がゼロで初期化されます。

```cpp
int x[5] = {0, 1, 2};  // x[3], x[4] はゼロで初期化
```

要素を全く指定しないとすべての要素がゼロで初期化されます。

```cpp
int x[5] = {};
```

これが一番手軽な初期化方法です。

## 配列とポインタ

配列はいくつかの例外を除いて常にポインタ型に暗黙変換されます。このため配列を参照する時に、 `[]` を省略すると、配列の先頭を指し示すポインタが取得できます。
先頭のポインタにインデックスを足すことで、それぞれの要素に対応したポインタが取得できます。

```cpp
#include <iostream>

int x[] = {2, 4, 6, 8, 10};
int* p = x;
std::cout << *p << std::endl;        // 2
std::cout << *(p + 1) << std::endl;  // 4
std::cout << *(p + 2) << std::endl;  // 6
std::cout << *(p + 3) << std::endl;  // 8
std::cout << *(p + 4) << std::endl;  // 10
```

## 関数に配列を渡す

配列がポインタ型に暗黙変換される仕様があることに加えてもう一つ注意するべき仕様があります。関数の引数宣言で配列型をつかうとき、ポインタ型として解釈されるのです。つまり次の例では見た目に反して `PrintArray1` と `PrintArray2` は完全に同一です。

```cpp
#include <iostream>

void PrintArray1(const int x[5]) {
    static_assert(sizeof(x)==sizeof(int*), "");
    for (int i = 0; i < 5; ++i) {
        std::cout << x[i] << std::endl;
    }
}

void PrintArray2(const int* x) {
    for (int i = 0; i < 5; ++i) {
        std::cout << x[i] << std::endl;
    }
}

int main() {
    int x[5] = {0, 1, 2, 3, 4};

    PrintArray1(x);
    PrintArray2(x);

    return 0;
}
```

つまり、関数に配列を渡すというのは配列の先頭要素へのポインタを渡すことになってしまうのです。`int [5]`という型が`int*`になってしまうため、配列の要素数の情報が欠落してしまいます。

そのため、関数に配列を渡す場合は、配列の先頭要素へのポインタと要素数をセットで渡す必要があります。

```cpp
#include <iostream>

void PrintArray(const int* x, std::size_t num) {
    for (std::size_t i = 0; i < num; ++i) {
        std::cout << x[i] << std::endl;
    }
}

int main() {
    constexpr std::size_t num = 5;
    int x[num] = {0, 1, 2, 3, 4};

    PrintArray(x, num);

    return 0;
}
```

??? question "なぜ関数の引数宣言で配列型をつかうとき、ポインタ型として解釈される仕様があるのか"
    そもそもこの仕様はC言語から受け継いだものです。C言語には関数のオーバーロードもtemplateもありません。そんななかで任意の要素数の配列を渡すときこの仕様がないと、想定しうるすべての要素数について関数を定義しなければならなくなります。これはとても面倒なことです。また後に学ぶ動的確保された配列と処理が共通化できなくなります。
    
配列の要素数を求める方法としてC++11より前ではプリプロセッサマクロを使用するのが一般的でしたが、C++11からは次のようにして求めることができます。この関数はC++17以降では `std::size` という関数として標準ライブラリに存在します。

```cpp
#include <cstddef>
template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept { return N; }

int main() {
    int arr[3];
    static_assert(size(arr) == 3, "");
}
```

## std::array

より高機能な配列を使用したい場合は `std::array` を使用します。ただしC++11では初期化の時に二重に波括弧が必要です。

```cpp
#include <array>

std::array<int, 5> x = {{0, 1, 2, 3, 4}};
//std::array<int, 5> x = {0, 1, 2, 3, 4}; // C++14～
```

`x` は要素数が 5 であるような `int` の配列になります。
`std::array` を使用するには `<array>` のインクルードが必要です。
要素参照は通常の配列と同じようにできます。

```cpp
x[2] = 10;
```

`x.size()` とすると要素数が取得できます。C++17からは `std::size` 関数を用いても要素数を取得できます。

```cpp
auto size = x.size();  // 5
//auto size = std::size(x);  // C++17～
```

配列と要素数を保存した変数の2つを持ち回す必要がでてきたとき、`std::array` を使えばそれらをひとまとめにして扱えるので便利です。

また、配列とは異なり `std::array` は `int` 型などと同じ感覚で扱える特徴があります。例えば配列のコピーを例に上げると単なる代入のような書き方でコピーができます。

```cpp
int arr1_1[3] = {};
//int arr1_2[3] = arr1_1;//NG
std::array<int, 3> arr2_1{};
std::array<int, 3> arr2_2 = arr2_1;//OK
```
-----------------------------

ファイル: ./ch03-02-strings.md
-----------------------------
# 文字列

文字列を扱うには `std::string` という型を使用します。

```cpp
#include <string>

std::string s = "Hello";
```

`std::string` は文字列データを `char` の配列として扱うため
配列のように操作することができます。

```cpp
std::string s = "Hello";

s[0];   // 'H'
s[1];   // 'e'
s[2];   // 'l'
s[3];   // 'l'
s[4];   // 'o'
```

`s.size()` とすると文字列数を取得できます。

```cpp
s.size();   // 5
```

!!! info
    `std::string` はバイト列を保持しており `s.size()` が返す値はバイト数です。マルチバイト文字を保持する場合、`s.size()` が返す値は文字列数と一致しません。-----------------------------

ファイル: ./ch03-03-tuples.md
-----------------------------
# タプル

タプルは複数の値をひとまとめにして扱うことができる型です。
配列と似た部分がありますが、配列と異なり各要素は同じ型である必要はありません。
タプルを定義するには次のようにします。

```cpp
#include <tuple>

std::tuple<std::string, int> person { "Bob", 20 };
```

`< ... >` の部分に各要素の型を指定します。
要素数はいくつでも増やすことができます。

```cpp
std::tuple<std::string, int, std::string> person { "Bob", 20, "USA" };
```

## 要素参照

配列と同じようにタプルも要素参照を下記のようにすることができます。

```cpp
std::get<0>(person);    // "Bob"
std::get<1>(person);    // 20
```

## 初期化のバリエーション

タプルは初期化方法に幾つかのバリエーションがあります。

```cpp
std::tuple<std::string, int> person { "Bob", 20 };
std::tuple<std::string, int> person("Bob", 20);
std::tuple<std::string, int> person = std::make_tuple("Bob", 20);
```

## `std::tie()`

`std::tie()` という関数を使うとタプルの要素を個別の変数に
まとめて代入することができます。

```cpp
std::tuple<std::string, int, std::string> person { "Bob", 20, "USA" };

std::string name;
int age;
std::string country;

std::tie(name, age, country) = person;  // name: "Bob", age: 20, country: "USA"
```
-----------------------------

ファイル: ./ch03-04-pairs.md
-----------------------------
# ペア

ペアは2つの値をひとまとめにして扱うことができる型です。
要素数が2つのタプルと同じように扱うことができます。
ペアを定義するには次のようにします。

```cpp
#include <utility>

std::pair<std::string, int> person {"Bob", 20};
```

## 要素参照

タプルと同様に要素参照を下記のようにすることができます。

```cpp
std::get<0>(person);    // "Bob"
std::get<1>(person);    // 20
```

ペアでは0番目の要素を `first`、 1番目の要素を `second` で参照することができます。

```cpp
person.first;     // "Bob"
person.second;    // 20
```

## 初期化のバリエーション

タプルと同様に初期化方法に幾つかのバリエーションがあります。

```cpp
std::pair<std::string, int> person { "Bob", 20 };
std::pair<std::string, int> person("Bob", 20);
std::pair<std::string, int> person = std::make_pair("Bob", 20);
```

## `std::tie()`

`std::tie()` を使うとペアの要素を個別の変数にまとめて代入することができます。
`std::tie()` を使うには `<tuple>` のインクルードが必要です。

```cpp
#include <tuple>

std::pair<std::string, int> person { "Bob", 20 };

std::string name;
int age;

std::tie(name, age) = person;  // name: "Bob", age: 20
```
-----------------------------

ファイル: ./ch03-05-vectors.md
-----------------------------
# ベクタ

要素数を実行時に変更できる配列を扱うには `std::vector` を使用します。

```cpp
#include <vector>

std::vector<int> x = {0, 1, 2, 3, 4};
```

`x` は要素数が 5 であるような `int` の配列になります。
`std::vector` を使用するには `<vector>` のインクルードが必要です。
要素参照は通常の配列と同じようにできます。

```cpp
x[2] = 10;
```

`x.size()` とすると要素数が取得できます。

```cpp
auto size = x.size();  // 5
```

## 末尾へ要素追加

`x.emplace_back()` とすると末尾へ要素を追加することができます。

```cpp
#include <vector>

std::vector<int> x = {0, 1, 2, 3, 4};
auto size1 = x.size();  // 5

x.emplace_back(5);
auto size2 = x.size();  // 6
```

!!! question "`emplace_back` と `push_back`"
    C++11 より前は `push_back` という関数のみが末尾への要素追加を担っていました。
    C++11 で追加された `emplace_back` は要素型のコンストラクタに
    直接引数を渡すことができるので `push_back` と同じか
    それ以上のパフォーマンスを得られるケースがあります。
    両者の最適な使い分けは高度なトピックとなるため、
    詳細は [書籍 Effective Modern C++](https://www.oreilly.co.jp/books/9784873117362/) で紹介される
    「項目42：要素の挿入の代わりに直接配置を検討する」を参照ください。

## 末尾から要素削除

`x.pop_back()` とすると末尾から要素を削除することができます。

```cpp
#include <vector>

std::vector<int> x = {0, 1, 2, 3, 4};
auto size1 = x.size();  // 5

x.pop_back();
auto size2 = x.size();  // 4
```

## 配列の先頭ポインタを取得

`x.data()` とすると配列の先頭ポインタが取得できます。

```cpp
#include <vector>

std::vector<int> x = {4, 3, 2, 1, 0};
auto px = x.data();  // 先頭ポインタ
auto num = *px;  // 4
```

## bool に対する特殊化

`std::vector` は `bool` に対してテンプレート特殊化されており、
`std::vector<bool>` は `bool` 以外の `std::vector` とは動作が異なります。

詳細は [vector - cpprefjp C++日本語リファレンス][cpprefjp_vector] を参照してください。

[cpprefjp_vector]: https://cpprefjp.github.io/reference/vector/vector.html
-----------------------------

ファイル: ./ch03-06-maps.md
-----------------------------
# マップ

配列では要素参照のために何番目の要素と指定しますが、
`std::map` または `std::unordered_map` という型を使用すると
何番目という指定の代わりに任意の型をキーとして指定できます。

この機能は連想配列や辞書とも呼ばれます。

```cpp
#include <map>

std::map<std::string, int> persons = {
    {"Alice", 18},
    {"Bob", 20}
};
```

```cpp
#include <unordered_map>

std::unordered_map<std::string, int> persons = {
    {"Alice", 18},
    {"Bob", 20}
};
```

要素参照は次のようにします。

```cpp
persons["Alice"];  // 18
persons["Bob"];    // 20
```

## 要素追加

`insert()` で要素を追加することができます。

```cpp
persons.insert({"Eve", 19});
```

## 要素削除

`erase()` で要素を削除することができます。

```cpp
persons.erase("Bob");
```

## `std::map` と `std::unordered_map` の違い

`std::map` はキーでソートしてデータを管理するのに対し、
`std::unordered_map` はキーから計算するハッシュと呼ばれる値でデータを管理します。

キーの順番を保持したい場合を除いて、パフォーマンスは常に `std::unordered_map` の方が優れています。
-----------------------------

ファイル: ./ch03-07-sets.md
-----------------------------
# セット

`std::set` または `std::unordered_set` という型を使用すると
任意の型の集合を扱うことができます。

```cpp
#include <set>

std::set<std::string> persons = {
    "Alice",
    "Bob"
};
```

```cpp
#include <unordered_set>

std::unordered_set<std::string> persons = {
    "Alice",
    "Bob"
};
```

## 要素追加

`insert()` で要素を追加することができます。

```cpp
persons.insert("Eve");
```

## 要素削除

`erase()` で要素を削除することができます。

```cpp
persons.erase("Bob");
```

## std::set と std::unordered_set の違い

`std::set` はキーでソートしてデータを管理するのに対し、
`std::unordered_set` はキーから計算するハッシュと呼ばれる値でデータを管理します。

キーの順番を保持したい場合を除いて、パフォーマンスは常に `std::unordered_set` の方が優れています。
-----------------------------

ファイル: ./ch03-08-iterators.md
-----------------------------
# イテレータ

イテレータとはコンテナ内での要素の位置を指すもので、
ポインタのように扱うことができます。
イテレータを使用することで
コンテナの種類に依存しないで処理を共通化できます。

```cpp
std::vector<int> x = {0, 1, 2, 3, 4};

// begin() でコンテナ内の先頭要素を指すイテレータを取得
auto it = x.begin();

// イテレータを使用して要素を出力
std::cout << *it << std::endl;  // 0

// イテレータを1つ進める
++it;

// イテレータを使用して要素を出力
std::cout << *it << std::endl;  // 1
```

イテレータが指す要素を参照するには
ポインタのデリファレンス同様に `*` をつけます。

イテレータはインクリメントで1つ進めることができます。

```cpp
std::vector<int> x = {0, 1, 2, 3, 4};

// end() でコンテナ内の最終要素の1つ先を指すイテレータを取得
for (auto it = x.begin(); it != x.end(); ++it) {
    std::cout << *it << std::endl;
}
```

`end()` で取得するイテレータは最終要素ではなく、
最終要素の1つ先であるためループの終了条件として使用できます。

イテレータはコンテナの種類に依存しないで処理を行えるため、
次のように `std::set` に変更してもそのまま動作します。

```cpp
std::set<int> x = {0, 1, 2, 3, 4};

for (auto it = x.begin(); it != x.end(); ++it) {
    std::cout << *it << std::endl;
}
```

この性質によってコンテナの種類に依存せず
[`<algorithm>`][cpprefjp_algorithm] で提供される機能を使用できます。

[cpprefjp_algorithm]: https://cpprefjp.github.io/reference/algorithm.html

```cpp
#include <algorithm>

std::vector<int> x = {0, 1, 2, 3, 4};

// std::count_if は条件を満たすコンテナ要素の個数を数える処理
//   - 第1引数と第2引数で範囲を指定
//   - 第3引数で関数オブジェクトで条件を指定
auto n = std::count_if(x.begin(), x.end(), [](const int v) {
    // 0 より大きい 2 の倍数
    if (v <= 0) {
        return false;
    }
    if (v % 2 != 0) {
        return false;
    }
    return true;
});
std::cout << n << std::endl;  // 2
```

## イテレータを使用できるコンテナ

イテレータを使用できるコンテナとして、代表的なものはコンテナライブラリで提供されるコンテナです。
コンテナライブラリで提供されるコンテナは STL コンテナと呼ばれ、本書で紹介した以下ものが該当します。

* `std::array`
* `std::vector`
* `std::map`
* `std::set`
* `std::unordered_map`
* `std::unordered_set`

STL コンテナの一覧は
[コンテナライブラリ - cppreference.com][cppreference_container]
を参照してください。

[cppreference_container]: https://ja.cppreference.com/w/cpp/container

STL コンテナ以外にも `std::string` などでイテレータは使用できます。

## マップのイテレータ

`std::map` や `std::unordered_map` のイテレータが指す要素はペアとなっています。
このペアは `first` がキーで `second` が値です。

```cpp hl_lines="7 8 9"
std::map<std::string, int> persons = {
    {"Alice", 18},
    {"Bob", 20}
};

for (auto it = persons.begin(); it != persons.end(); ++it) {
    const auto& person = *it;  // std::pair<std::string, int>
    const std::string& name = person.first;
    const int age = person.second;
    std::cout << name << ": " << age << std::endl;
}
```

## イテレータの種類

標準ライブラリのイテレータは5種類ありますが、
本書ではそのうち以下3種類だけを紹介します。

* 前方向イテレータ (Forward Iterator)
* 双方向イテレータ (Bidirectional Iterator)
* ランダムアクセスイテレータ (Random Access Iterator)

この3種類は次のような is-a 関係があります。

![is-a関係を表した図][iterator-is-a-diagram]

[iterator-is-a-diagram]: img/iterator.svg

### 前方向イテレータ

イテレータを動かす場合に前に進めることだけができます。

`std::unordered_map` や `std::unordered_set` のイテレータが該当します。

```cpp
std::unordered_set<int> x = {0, 1, 2, 3, 4};

auto it = x.begin();
std::cout << *it << std::endl;

++it;  // 前に進める
std::cout << *it << std::endl;
```

### 双方向イテレータ

イテレータを動かす場合に前に進めるだけでなく、後ろへ戻すことができます。

`std::map` や `std::set` のイテレータが該当します。

```cpp
std::set<int> x = {0, 1, 2, 3, 4};

auto it = x.begin();
std::cout << *it << std::endl;  // 0

++it;  // 前に進める
std::cout << *it << std::endl;  // 1

--it;  // 後ろへ戻す
std::cout << *it << std::endl;  // 0
```

### ランダムアクセスイテレータ

イテレータを動かす場合に任意の位置へ動かすことができます。

`std::array` や `std::vector` のイテレータが該当します。

```cpp
std::vector<int> x = {0, 1, 2, 3, 4};

auto it = x.begin();
std::cout << *it << std::endl;  // 0

++it;  // 前に進める
std::cout << *it << std::endl;  // 1

--it;  // 後ろへ戻す
std::cout << *it << std::endl;  // 0

it = it + 3;  // 3つ前に進める
std::cout << *it << std::endl;  // 3

// it は変更せずに it から2つ後ろへ戻した要素を参照
std::cout << it[-2] << std::endl;  // 1 (it から2つ後ろへ戻した要素)
std::cout << *it << std::endl;  // 3 (it は変更されていない)
```

<!-- TODO: 範囲for文の説明 -->

## イテレータと参照の無効化

要素の追加や削除を行うと
既存のイテレータや要素への参照が無効になることがあります。
無効化されたイテレータや参照を使用した場合の挙動は未定義動作 (保証されない) です。

たとえば `std::vector` の要素を削除すると、
削除した要素の位置とそれ以降の位置のイテレータと参照が無効化されます。

```cpp
std::vector<int> x = {0, 1, 2, 3, 4, 5, 6};
auto it1 = x.begin() + 2;
auto it2 = x.begin() + 3;
auto it3 = x.begin() + 4;
std::cout << *it1 << std::endl;  // 2
std::cout << *it2 << std::endl;  // 3
std::cout << *it3 << std::endl;  // 4

x.erase(x.begin() + 3);  // index=3 の要素を削除

std::cout << *it1 << std::endl;  // 2 (有効なまま)
std::cout << *it2 << std::endl;  // 未定義動作 (無効化される)
std::cout << *it3 << std::endl;  // 未定義動作 (無効化される)
```
-----------------------------

ファイル: ./ch03-09-range-based-for.md
-----------------------------
# 範囲 for

## コンテナ

イテレータを使ったコンテナのループ

```cpp
std::vector<int> x = {0, 1, 2, 3, 4};

for (auto it = x.begin(); it != x.end(); ++it) {
    std::cout << *it << std::endl;
}
```

は範囲 for 文という構文を使って下記の様によりシンプルに書くことが出来ます。

```cpp
for (auto&& e : x) {
    std::cout << e << std::endl;
}
```

`&&` という記法については [6.4. ムーブセマンティクス](ch06-04-move-semantics.md#_4) の章で説明しますので、
今はおまじないだと思って下さい。

## 配列

配列に対しても範囲 for 文は使用できます。

```cpp
int x[] = {0, 1, 2, 3, 4};

for (auto&& e : x) {
    std::cout << e << std::endl;
}
```
-----------------------------

ファイル: ./ch04-01-declarations-and-definitions.md
-----------------------------
# 宣言と定義

関数や変数は、宣言と定義をすることが出来ます。
宣言と定義は、区別して扱われます。

## 宣言

宣言は、型の情報や名前などのシンボルの概要を示すことです。

次のような関数があったとします。

```cpp
void HelloWorld() {
    std::cout << "Hello World!" << std::endl;
}
```

この関数の宣言は次のように書きます。

```cpp
void HelloWorld();
```

関数の `{}` の前に書いてある返り値の型・関数名・引数リストを書くだけで宣言できます。
関数の宣言は、プロトタイプ宣言と呼ばれることもあります。

宣言は重複しても問題ありません。

```cpp
void HelloWorld();  // 宣言
void HelloWorld();  // 重複してもOK
```

??? tip "変数の宣言"
    関数と違い、変数の宣言をする場合は `extern` 指定子を付与する必要があります。

    ```cpp
    extern int x;  // 宣言
    extern int x;  // 重複してもOK
    ```

    `extern` 指定子の詳細については [記憶域クラス指定子 - cppreference.com][cppreference-storage_duration] を参照してください。

[cppreference-storage_duration]: https://ja.cppreference.com/w/cpp/language/storage_duration

## 定義

定義は、シンボルの詳細を示すことです。
定義があることで、そのシンボルが具体的にどういうものなのか分かります。
定義をした場合は、合わせて宣言が行われたことにもなります。

関数の場合は、実装そのものが定義としてみなされます。

```cpp
// 関数の定義。宣言も兼ねている。
void HelloWorld() {
    std::cout << "Hello World!" << std::endl;
}
```

変数の場合は、次のように書くだけで定義がされます。

```cpp
int x;  // 変数の定義。宣言も兼ねている。
int x = 100;  // 定義をしつつ初期化。宣言も兼ねている。
```

定義は重複が許されません。
定義されたシンボルを利用する側が、どれを使えば良いのか判別できなくなるため、リンク時にエラーとなります。

```cpp
int x;
int x;  // 重複のためエラー

void HelloWorld() {
    std::cout << "Hello World!" << std::endl;
}

void HelloWorld() {  // 重複のためエラー
    std::cout << "Hello World!!!!!!" << std::endl;
}
```

宣言されたシンボルを利用するコードがある場合、定義が必要になります。
宣言のみだと、その関数や変数が具体的にどのようなものなのか分からないためです。

```cpp
void HelloWorld();  // 宣言

int main() {
    HelloWorld();  // 定義が見つからないためエラー

    return 0;
}
```-----------------------------

ファイル: ./ch04-02-multiple-files.md
-----------------------------
# 複数ファイル

## ファイルの種類

C++ では2種類のファイルを扱います。

- ヘッダ (拡張子: `.h` , `.hpp` )
    - 関数のプロトタイプ宣言を記述します。
- ソース (拡張子: `.cpp` , `.cc` , `.cxx` )
    - 関数の実装を記述します。

## ソースファイルを分ける

1 つのソースファイルにコードを書き続けていると、
コードの量が多くなった時に、読みにくくなったり、書きにくくなったりするので、
適度にコードを複数のファイルに分ける必要があります。

複数のファイルを跨いだコードを書くには次のようにします。
`main.cc` 内で `a.cc` の関数を使うためにプロトタイプ宣言をしています。

=== "main.cc"

    ```cpp linenums="1" hl_lines="1 2 3 4 5"
    void DoSomething();   // プロトタイプ宣言
    void DoSomething2();  // プロトタイプ宣言
    void DoSomething3();  // プロトタイプ宣言
    void DoSomething4();  // プロトタイプ宣言
    void DoSomething5();  // プロトタイプ宣言

    int main() {
        DoSomething();
        DoSomething2();
        DoSomething3();
        DoSomething4();
        DoSomething5();

        return 0;
    }
    ```

=== "a.cc"

    ```cpp linenums="1"
    void DoSomething() { /* 実装省略 */ }
    void DoSomething2() { /* 実装省略 */ }
    void DoSomething3() { /* 実装省略 */ }
    void DoSomething4() { /* 実装省略 */ }
    void DoSomething5() { /* 実装省略 */ }
    ```

!!! info "複数ファイルのコンパイル"
    複数ファイルをコンパイルして実行ファイルを生成する場合は、
    次のようにコンパイルしたいソースファイルを並べてコマンドを実行します。

    ```bash
    $ g++ -std=c++11 main.cc a.cc
    ```

上記のコードでも動作はしますが、
`a.cc` に記述している関数を他の様々なソースから利用したいとなった場合に、
その都度、それぞれのソースにプロトタイプ宣言を追加することになり、手間がかかります。

## ヘッダファイルを利用する

ソースファイルを分けるだけでは、手間がかかりますが、合わせてヘッダを使うことで簡潔になります。
プロトタイプ宣言だけヘッダに記述することで、宣言を 1 回書くだけで済むようになります。

=== "main.cc"

    ```cpp linenums="1" hl_lines="1"
    #include "a.h"

    int main() {
        DoSomething();
        DoSomething2();
        DoSomething3();
        DoSomething4();
        DoSomething5();

        return 0;
    }
    ```

=== "a.h"

    ```cpp linenums="1" hl_lines="1 2 3 4 5"
    void DoSomething();   // プロトタイプ宣言
    void DoSomething2();  // プロトタイプ宣言
    void DoSomething3();  // プロトタイプ宣言
    void DoSomething4();  // プロトタイプ宣言
    void DoSomething5();  // プロトタイプ宣言
    ```

=== "a.cc"

    ```cpp linenums="1"
    void DoSomething() { /* 実装省略 */ }
    void DoSomething2() { /* 実装省略 */ }
    void DoSomething3() { /* 実装省略 */ }
    void DoSomething4() { /* 実装省略 */ }
    void DoSomething5() { /* 実装省略 */ }
    ```

`main.cc` 内で `a.cc` の関数を利用できるようにするために

1. `a.h` で `a.cc` の関数のプロトタイプ宣言をします。
1. `main.cc` で `a.h` を取り込むために `#include "a.h"` と記述します。

これで `main.cc` から `a.cc` の関数を利用することが出来ます。
例え、他のソースから `a.cc` の関数を利用したいとなっても、そのソース毎に `#include "a.h"` を記述するだけで済みます。

コンパイル時には、ヘッダファイルを指定する必要はありません。

```bash
# a.h は指定しなくて良い
g++ -std=c++11 main.cc a.cc
```

## インクルードガード

ヘッダにはインクルードガードが必要です。

=== "a.h"

    ```cpp linenums="1" hl_lines="1 2 7"

    #ifndef A_H_
    #define A_H_

    void DoSomething();
    void DoSomething2();

    #endif  // A_H_
    ```

インクルードガードがあることで、ソースが同じヘッダを複数回取り込む事がなくなり、
変数や関数の定義が重複することを防げます。

インクルードガードは一般的にプロジェクトごとに命名規則を設けます。

!!! warning "使用してはいけない名前"
    `_` で始まる名前や `__` を含むような名前は、
    コンパイラや標準ライブラリにて予約されている識別子と名前が被る恐れがあるため使ってはいけません。

    ```cpp
    #define _A_H_  //  _ で始まるのでNG
    #define A__H_  // __ を含むのでNG
    ```

インクルードガードはプリプロセッサ司令の仕組みを用いて実現しています。
プリプロセッサ司令の詳細については、 [プリプロセッサ司令] を参照してください。

[プリプロセッサ司令]: appendix-preprocessor-directives.md-----------------------------

ファイル: ./ch04-03-scopes.md
-----------------------------
# スコープ

プログラムは、特定の範囲毎にシンボルを識別しています。
この範囲のことを スコープ と言います。
同一のスコープ内に同名のシンボルが存在した場合、シンボルを一意に識別する事ができないのでリンク時にエラーになります。

また、スコープを決める範囲のことをブロックと言います。 `{}` で括られた範囲が一つのブロックになります。

!!! tip "名前修飾（名前マングリング）"
    C++ では同一のスコープ内に同名の関数があっても、引数の型が異なれば宣言することが可能です。（関数のオーバーロード）

    これは、シンボルに引数の型の情報なども含める名前マングリングを行なった上で関数を一意に識別することで実現しています。
    詳細は [11.4 動的ロードと名前マングリング][name-mangling] を参照してください。

[name-mangling]: ch11-04-dynamic-loading-and-name-mangling.md

## 名前空間スコープ

`namespace 名前 {}` で名前空間の定義をすることが出来ます。
`namespace` ブロックで括られたシンボルは、その名前空間に属することになります。

```cpp
namespace A {
    int count = 2;  // 名前空間 A に属する変数
}  // namespace A

namespace B {
    int count = 4;  // 名前空間 B に属する変数。名前空間 A とは別スコープなのでエラーにはならない。
}  // namespace B
```

スコープ解決演算子 `::` を付けることで、名前空間内のシンボルを利用する事ができます。

```cpp
#include <iostream>

namespace A {
    int count = 2;
}  // namespace A

namespace B {
    int count = 4;
}  // namespace B

int main() {
    std::cout << A::count << std::endl;  // 2
    std::cout << B::count << std::endl;  // 4

    return 0;
}
```

同一の名前空間に属する場合は、スコープ解決演算子 `::` による名前空間の指定を省略することが可能です。

```cpp
namespace A {
    int count = 2;

    int GetCount() {
      return count;  // A::count と同じ
    }
}  // namespace A
```

名前空間は入れ子にすることが出来ます。

```cpp
#include <iostream>

namespace A {
    int count = 2;  // A::count

    namespace P {
        int count = 4;  // A::P::count

        int GetCount() {
            return count;
        }
    }  // namespace P
}  // namespace A

int main() {
    std::cout << A::P::GetCount() << std::endl;  // 4;

    return 0;
}
```

同一の名前空間内に指定したシンボルが見つからなかった場合、シンボルを探す範囲を `namespace` ブロック毎に外に広げていき、最初に見つかったものが利用されます。

```cpp
#include <iostream>

namespace A {
    int count = 2;  // A::count

    namespace P {
        namespace X {
            int GetCount() {
                /*
                 * A::P::X::count は存在しない
                 * -> A::P::count は存在しない
                 *    -> A::count が利用される
                 */
                return count;
            }
        }  // namespace X
    }  // namespace P
}  // namespace A

int main() {
    std::cout << A::P::X::GetCount() << std::endl;  // 2;

    return 0;
}
```

!!! tip "std 名前空間"
    これまでに出てきた、 `std::cout` や `std::vector` 等の `std::` は std 名前空間の事を指しています。
    C++ の標準ライブラリの機能は、ほとんどが std 名前空間に属しています。

## 関数スコープ

関数内で宣言されたオブジェクトはその関数内でのみ有効になります。

```cpp hl_lines="4 5 6 7"
#include <iostream>

int GetCount() {
    int x = 5;  // GetCount() 内の x の有効範囲はここから

    return x;
}  // ここまで

int main() {
    int x = GetCount();  // main() の x と GetCount() の x は別スコープ
    std::cout << x << std::endl;

    return 0;
}
```

## ブロックスコープ

ブロック内もスコープの一つです。
`if` 文を始めとした制御文で使われる `{}` もブロックスコープに該当します。

名前空間同様、同一のブロック内に指定したシンボルが見つからなかった場合、シンボルを探す範囲をブロック毎に外に広げていき、最初に見つかったものが利用されます。

```cpp
#include <iostream>

int main() {
    int x = 3;

    {
        int x = 5;
        std::cout << x << std::endl;  // 5
    }

    {
        std::cout << x << std::endl;  // 3
    }

    return 0;
}
```

## グローバルスコープ

名前空間や関数に属さない場所はグローバルスコープと言います。
グローバルスコープに宣言された変数や関数は、宣言以降であればどこからでも利用することが出来ます。
また、グローバルスコープに宣言した変数・関数のことを一般的にグローバル変数・関数と言います。

```cpp hl_lines="3"
#include <iostream>

int x = 100;  // グローバル変数

int main() {
    std::cout << x << std::endl;  // 100

    return 0;
}
```

グローバル変数は「どこからでも利用することが出来る」という性質上、どこからでも値を書き換えることが出来ます。
どこで変数の値が書き換えられたのか特定しづらくなるため、可能な限り使わないことが望ましいです。

グローバルスコープは、一番外側の名前空間として捉えることも出来ます。
そのため、スコープ解決演算子 `::` を利用して、明示的にグローバルスコープを指定することが出来ます。

```cpp
#include <iostream>

int x = 20;

int main() {
    int x = 40;

    std::cout << x << std::endl;    // 40
    std::cout << ::x << std::endl;  // 20

    return 0;
}
```-----------------------------

ファイル: ./ch04-04-internal-linkages.md
-----------------------------
# 内部リンケージ

宣言された同名のシンボルを同一のものとして扱うかどうかを示す概念のことをリンケージと言います。

ここでは、内部リンケージについて紹介します。
内部リンケージを持つシンボルは宣言されたファイル内でのみ参照できるようになります。

<!-- MEMO: ここで言うファイルとは厳密にはプリプロセス後の翻訳単位である -->

## static

シンボルの宣言に `static` 指定子を付与することで内部リンケージを持たせることが出来ます。

=== "main.cc"

    ```cpp
    #include <iostream>

    int main() {
        std::cout << x << std::endl;  // リンクエラー。main.cc からは other.cc の x が参照できない。

        return 0;
    }
    ```

=== "other.cc"

    ```cpp
    static int x = 246;  // 内部リンケージ。 other.cc 内でのみ参照可能
    ```

## 無名名前空間

`namespace 名前 {}` で名前空間を定義することが出来ますが、
名前を付けずに `namespace {}` とすることで無名名前空間を定義することが出来ます。

無名名前空間内に宣言された変数や関数は、 `static` 指定子と同様に内部リンケージを持ちます。

=== "main.cc"

    ```cpp
    #include <iostream>

    #include "other.h"

    int main() {
        Print();

        std::cout << x << std::endl;  // ここから x は参照できない
    }
    ```

=== "other.h"

    ```cpp
    #ifndef OTHER_H_
    #define OTHER_H_

    void Print();

    #endif  // OTHER_H_
    ```

=== "other.cc"

    ```cpp hl_lines="5 6 7"
    #include "other.h"

    #include <iostream>

    namespace {
        int x = 50;  // x に内部リンケージを持たせる
    }  // unnamed namespace

    void Print() {
        std::cout << x << std::endl;  // ここから x は参照可能
    }
    ```

C++ において `static` は [様々な意味を持つ][cppreference-static] ため、分かりづらいキーワードとなっています。
宣言に内部リンケージを持たせる場合は、 `static` ではなく無名名前空間を使うようにしましょう。

[cppreference-static]: https://ja.cppreference.com/w/cpp/keyword/static

## 内部リンケージと定義重複

ソースファイル間で定義が重複している時、通常は定義の重複によるエラーになりますが、
各々に内部リンケージを持たせて別のファイルから見えなくしていれば、別の定義として扱うことができます。

=== "main.cc"

    ```cpp hl_lines="6"
    #include <iostream>

    #include "other.h"

    namespace {
        int hoge = 0;  // main.cc 内の hoge
    }

    int main() {
        hoge += 2;

        IncrementHoge();

        std::cout << "main.cc: " << hoge << std::endl;  // main.cc: 2

        PrintHoge();

        return 0;
    }
    ```

=== "other.h"

    ```cpp
    #ifndef OTHER_H_
    #define OTHER_H_

    void IncrementHoge();
    void PrintHoge();

    #endif  // OTHER_H_
    ```

=== "other.cc"

    ```cpp hl_lines="6"
    #include "other.h"

    #include <iostream>

    namespace {
        int hoge = 0;  // other.cc 内の hoge
    }

    void IncrementHoge() {
        ++hoge;
    }

    void PrintHoge() {
        std::cout << "other.cc: " << hoge << std::endl;  // other.cc: 1
    }
    ```
-----------------------------

ファイル: ./ch04-05-inline-functions.md
-----------------------------
# inline 関数

関数に `inline` をつけた関数のことを inline 関数といいます。

inline 関数は定義が同一である場合に限って、
異なるソースファイルで同一の定義をしてもいいと決められています。

=== "main.cc"

    ```cpp hl_lines="5 6 7"
    #include <iostream>

    #include "something.h"

    inline void HelloWorld() {
        std::cout << "Hello World!" << std::endl;
    }

    int main() {
        HelloWorld();
        Something();

        return 0;
    }
    ```

=== "something.h"

    ```cpp
    #ifndef SOMETHING_H_
    #define SOMETHING_H_

    void Something();

    #endif  // SOMETHING_H_
    ```

=== "something.cc"

    ```cpp hl_lines="5 6 7"
    #include "something.h"

    #include <iostream>

    inline void HelloWorld() {
        std::cout << "Hello World!" << std::endl;
    }

    void Something() {
        HelloWorld();
    }
    ```

この例では `main.cc` と `something.cc` で
定義が同一である inline 関数 `HelloWorld()` がそれぞれ存在します。

これによって inline 関数であればヘッダファイルで関数定義をしてもリンク時にエラーにはなりません。

=== "hello_world.h"

    ```cpp hl_lines="6 7 8"
    #ifndef HELLO_WORLD_H_
    #define HELLO_WORLD_H_

    #include <iostream>

    inline void HelloWorld() {
        std::cout << "Hello World!" << std::endl;
    }

    #endif  // HELLO_WORLD_H_
    ```

=== "main.cc"

    ```cpp
    #include "hello_world.h"
    #include "something.h"

    int main() {
        HelloWorld();
        Something();

        return 0;
    }
    ```

=== "something.h"

    ```cpp
    #ifndef SOMETHING_H_
    #define SOMETHING_H_

    void Something();

    #endif  // SOMETHING_H_
    ```

=== "something.cc"

    ```cpp
    #include "something.h"

    #include "hello_world.h"

    void Something() {
        HelloWorld();
    }
    ```

??? question "inlineとインライン展開"
    しばしば `inline` 指定を関数につけるのは「関数を強制的に[インライン展開]させるための機能」と誤解されていますが誤りです。
    [インライン展開]: https://github.com/EzoeRyou/cpp17book/blob/master/035-cpp17-core-inline-variables.md
    現代のコンパイラは十分に賢いので、 `inline` はインライン展開と関係が無くなっています。
    
    したがって、ヘッダーファイルに関数を定義するときに定義は一つだけというルールを回避するためにのみ `inline` 指定は用いられます。
    
-----------------------------

ファイル: ./ch05-01-standard-inout.md
-----------------------------
# 標準入出力

C++ で入出力を扱う場合は `<iostream>` ヘッダをインクルードする必要があります。


## 標準出力
`std::cout` で標準出力に対して出力します。

```cpp
#include <iostream>

std::cout << "標準出力";
```

!!! info
    `std::endl` で改行を出力します。
    ```cpp
    std::cout << 1 + 2 << std::endl;
    std::cout << 3 + 4 << std::endl;
    ```
    ```bash
    # 出力結果
    3
    7
    ```

## 標準エラー出力
`std::cerr` で標準エラー出力に対して出力します。

```cpp
#include <iostream>

std::cerr << "標準エラー出力";
```

## 標準入力
`std::cin` で標準入力に対して入力します。

```cpp
#include <iostream>
#include <string>

std::cout << "好きな食べ物を入力してください: "
std::string food;
std::cin >> food;
std::cout << "好きな食べ物は " << food << " です。" << std::endl;
```

`int` などの数値型を用意することで数値の入力を読み込むことも可能です。

また、読み込み成否をif文で判定することが可能です。

```cpp
#include <iostream>

int main() {
    int x = 0;

    std::cout << "整数を入力してください: ";
    if (std::cin >> x) {
        std::cout << "入力した整数は " << x << " です。" << std::endl;
    } else {
        std::cout << "不正な入力です。" << std::endl;
    }

    return 0;
}
```

```bash
# 実行例1
整数を入力してください: 3
入力した整数は 3 です。

# 実行例2
整数を入力してください: カレー
不正な入力です。
```-----------------------------

ファイル: ./ch05-02-file-operations.md
-----------------------------
# ファイル操作

`<fstream>` に用意されているクラスを使うことでファイルの操作が出来ます。

## ファイル読み込み

ファイルを読み込む場合は `std::ifstream` を使います。
`<string>` に用意されている `std::getline` で1行ずつ読み込むことが出来ます。

=== "main.cc"

    ```cpp
    #include <fstream>
    #include <iostream>
    #include <string>

    int main() {
        std::ifstream file("file.txt");  // 読み込むファイルのパスを指定
        std::string line;

        while (std::getline(file, line)) {  // 1行ずつ読み込む
            std::cout << line << std::endl;
        }

        return 0;
    }
    ```

=== "file.txt"

    ```
    Good friend, for Jesus' sake forbear,
    To dig the dust enclosed here.
    Blest be the man that spares these stones,
    And cursed be he that moves my bones.
    ```

=== "実行結果"

    ```
    Good friend, for Jesus' sake forbear,
    To dig the dust enclosed here.
    Blest be the man that spares these stones,
    And cursed be he that moves my bones.
    ```

## ファイル書き出し

ファイルへ書き出す場合は `std::ofstream` を使います。

=== "main.cc"

    ```cpp
    #include <fstream>
    #include <iostream>
    #include <string>
    #include <vector>

    int main() {
        std::ofstream file("fruits.txt");  // 書き出すファイルのパスを指定
        std::vector<std::string> fruits = { "apple", "strawberry", "pear", "grape" };

        for (const auto fruit : fruits) {
            file << fruit << std::endl;  // 書き出し
        }

        return 0;
    }
    ```

=== "プログラム実行後のfruits.txt"

    ```
    apple
    strawberry
    pear
    grape

    ```

書き出す前に、既に同名のファイルが存在していた場合、中身は上書きされます。
上書きせずに追記する場合は、コンストラクタの引数に `std::ios::app` を追加します。

=== "main.cc"

    ```cpp hl_lines="6"
    #include <fstream>
    #include <iostream>
    #include <string>

    int main() {
        std::ofstream file("file.txt", std::ios::app);
        std::string quotation("--- William Shakespeare's Epitaph");

        file << std::endl << quotation;

        return 0;
    }
    ```

=== "プログラム実行前のfile.txt"

    ```
    Good friend, for Jesus' sake forbear,
    To dig the dust enclosed here.
    Blest be the man that spares these stones,
    And cursed be he that moves my bones.
    ```

=== "プログラム実行後のfile.txt"

    ```
    Good friend, for Jesus' sake forbear,
    To dig the dust enclosed here.
    Blest be the man that spares these stones,
    And cursed be he that moves my bones.
    --- William Shakespeare's Epitaph
    ```
-----------------------------

ファイル: ./ch06-01-memory-areas.md
-----------------------------
# メモリ領域

プログラムが利用するメモリには様々な領域が存在します。ここでは、スタックとヒープについて紹介します。

## スタック

スタックはデータ構造上、ヒープに比べて高速に扱えます。スタックへのメモリの確保と解放はコンパイラ・OSが自動的に行います。

代わりに、使用できるスタックには限りがあるので、大きなデータを取り扱うのには向いていません。
また、スタックのサイズはプログラムのコンパイル・リンク時に決定しているので、実行前にメモリの確保期間が分かっているものに利用は限られます。

```cpp
void Function() {
    int x = 100; // ローカル変数xはスタックに確保される。
    int y = 200; // ローカル変数yはスタックに確保される。

} // 関数の終了とともに変数 x, y はスタックから取り除かれる。
  // スタックはLIFO（後入れ先出し）形式のため y, x の順で取り除かれる。

int main() {
    Function();

    return 0;
}
```

## ヒープ

ヒープのサイズはプログラム実行時に動的に変化します。ヒープはスタックのような制限がなく自由度が高いですが、アプリケーション側でメモリの確保と解放を行う必要があります。

メモリの確保期間が明確でない場合や、実行時にサイズが確定するようなものについてはヒープを利用します。例えば、 `std::vector` は、保持する要素をヒープ上に確保することで、要素数を実行時に変更できるという仕組みを実現しています。
-----------------------------

ファイル: ./ch06-02-new-and-delete.md
-----------------------------
# new/delete

## new

ヒープにメモリを動的に確保する場合は `new` 演算子を利用します。

```cpp
int* p1 = new int(100);  // p1 は new で確保されたメモリ領域を指すポインタ
int* p2 = new int[5];    // 配列の場合は [] を付ける
```

## delete

ヒープに動的に確保したメモリを解放する場合は `delete` 演算子を利用します。

```cpp
int* p1 = new int(100);
int* p2 = new int[5];

delete p1;    // new によって確保されたメモリを delete で解放
delete[] p2;  // 配列の場合は [] を付ける
```

`new` を利用して確保したメモリの解放を忘れるとメモリリークになります。 `new` と `delete` は必ずセットで使いましょう。

!!! error "メモリリーク"
    ```cpp
    void Function() {
        int* p = new int[100000];

        // delete せずに Function() が終了すると…
    }   // int[100000] 分のメモリが解放されないままになる。
    ```

!!! warning "malloc/free"
    [malloc/free][malloc-free] を利用することでもメモリの確保・解放は可能ですが、C++ での利用は推奨されていません。

[malloc-free]: appendix-malloc-and-free.md-----------------------------

ファイル: ./ch06-03-deep-and-shallow-copy.md
-----------------------------
# ディープコピーとシャローコピー

## ディープコピー
C++ のコピーは基本的にはディープコピーと呼ばれるものです。

ディープコピーは実体ごとコピーされるため、コピーした分のメモリ領域の確保が必要になります。
ディープコピーの場合、コピー先（or コピー元）のオブジェクトを編集しても、他方のオブジェクトには影響を及ぼしません。

```cpp
int x = 100;
int y = x; // x を y へディープコピー（図1）
y = 50; // y を 50 に書き換える（図2）
std::cout << x << std::endl; // x は100のまま
```

!!! info "図1"
    ![図1][deep_copy_a]

!!! info "図2"
    ![図1][deep_copy_b]


## シャローコピー

ポインタをコピーする場合はシャローコピーになります。

シャローコピーではポインタの向き先だけがコピーされ、実体はコピー元の領域のままなので、
ディープコピーのようなコピーした分のメモリの確保は起きません。

参照の場合も、ポインタと同様にシャローコピーになります。

```cpp
int* x = new int(100);
int* y = x; // x を y へシャローコピー（図3）
*y = 50; // y が指す先の値を 50 に書き換える（図4）
std::cout << *x << std::endl; // x が指す先の値も 50 になる
```

!!! info "図3"
    ![図3][shallow_copy_a]

!!! info "図4"
    ![図4][shallow_copy_b]

[deep_copy_a]: img/deep_copy_a.svg
[deep_copy_b]: img/deep_copy_b.svg
[shallow_copy_a]: img/shallow_copy_a.svg
[shallow_copy_b]: img/shallow_copy_b.svg

## 関数の引数

ディープコピーとシャローコピーは関数の引数でも区別されます。

```cpp
#include <iostream>

void ChangeToFifty1(int v) {  // ディープコピー
    v = 50;
}

void ChangeToFifty2(int* v) {  // シャローコピー
    *v = 50;
}

int main() {
    int a = 100;
    ChangeToFifty1(a);
    std::cout << a << std::endl;  // 100

    int b = 100;
    ChangeToFifty2(&b);
    std::cout << b << std::endl;  // 50

    return 0;
}
```
-----------------------------

ファイル: ./ch06-04-move-semantics.md
-----------------------------
# ムーブセマンティクス

## コピーとムーブ

```cpp
std::vector<int> x(1000000);
std::vector<int> y = x; // ディープコピー

// 以降 x は利用しない
```

この例の場合、`y` を生成するために `x` と同程度のメモリ領域を確保する必要があります。
これはコストの面ではかなりの無駄があります。

```cpp
std::vector<int>* x = new std::vector<int>(1000000);
std::vector<int>* y = x; // シャローコピー
x = nullptr;

// 以降 x は利用しない
```

この例では `x` を `y` にシャローコピーした後に、 `x` に `nullptr` を代入しています。

これがムーブの根底にある考え方で、
ポインタの付け替えだけで、あたかも `x` が `y` に移動しているような挙動を実現出来ているため、
ディープコピーのときよりもコストの面で有利です。

しかし、ポインタの操作を伴う実装になるため、プログラマが細心の注意を払って実装しないと、
ムーブの仕組みが実現できなくなるというリスクも存在します。

そこで、 C++11からはムーブの考え方をテクニックとしてでは無く、言語仕様として実現する仕組みが取り入れられました。

## 右辺値と左辺値

- 左辺値: 基本的にそのスコープの間生き続ける名前付きのオブジェクト
- 右辺値: リテラルや関数が返す一時オブジェクトのようなその瞬間に破棄されて不要になるもの

```cpp
int x = 300; // x は左辺値。300 のようなリテラルは右辺値。
int y = function(); // y は左辺値。関数 function が返す一時オブジェクトは右辺値。
int z = x; // z と x は左辺値。
```

右辺値は左辺値へ格納したら必要無くなるので、右辺値にはムーブの考え方が適用できることがわかります。
C++11 以降、コンパイラはこの考え方を認識し、ムーブを実現してくれるようになりました。

## std::move

次の例では、`x` はコンパイラからしてみると左辺値なので、`y` への代入時にディープコピーされます。

```cpp
std::vector<int> x(1000000);
std::vector<int> y = x; // y と x は左辺値

// 以降 x は利用しない
```

そこで、左辺値を右辺値にキャストする `std::move` を使います。
`x` を右辺値にキャストすることで、ディープコピーではなくムーブができるようになります。

```cpp
std::vector<int> x(1000000);
std::vector<int> y = std::move(x); // std::move で x を右辺値にキャスト

// 以降、xは利用しない
```

## 右辺値参照

右辺値を参照するには `&&` を付けます。

```cpp
int&& x = 100;
```

左辺値の参照と右辺値の参照は別の型として扱われるため、
オーバーロードの仕組みを利用することで、引数が左辺値参照の時と右辺値参照の時で処理を分けることが可能です。

```cpp
#include <iostream>
#include <string>

void Print(std::string&) {
    std::cout << "左辺値参照" << std::endl;
}

void Print(std::string&&) {
    std::cout << "右辺値参照" << std::endl;
}

int main() {
    std::string str = "hoge";

    Print(str);
    Print(std::move(str));

    return 0;
}
```

```bash
# 実行結果
左辺値参照
右辺値参照
```-----------------------------

ファイル: ./ch06-05-smart-pointers.md
-----------------------------
# スマートポインタ

## リソースの所有権

ポインタはコピー可能なため、ポインタが指す先のリソースを複数のオブジェクトから参照することが可能です。

```cpp
int main() {
    int* a = new int(100);
    int* b = a; // b からも a と同じリソースを参照できるようにする。

    // a と b のどちらを delete するべきか？
    return 0;
}
```

動的確保したリソースを扱う場合、
誤って `delete` を忘れたり、同じリソースを複数回 `delete` したりすることを防ぐために、
どの変数がリソースの所有権（リソースを参照する権利と解放する権利）を持つのかをプログラマが細心の注意を払ってコードを書く必要があります。

このようなポインタを扱う上での危険性や負担を下げるために、 C++ ではスマートポインタという仕組みが存在します。

スマートポインタは `<memory>` ヘッダにて提供されています。

## std::shared_ptr

`std::shared_ptr` は動的確保したリソースの所有権を共有することができるスマートポインタです。
内部で所有権を持つオブジェクトの一覧を管理し、所有者がいなくなった時に自動的に `delete` する仕組みを有しています。

`std::shared_ptr` オブジェクトを生成するには、 `std::make_shared` を利用します。

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> x = std::make_shared<int>(100); // int* x = new int(100); の代わり
                                                         // 所有者は1人。
    {
        std::shared_ptr<int> y = x; // 通常のポインタ同様、コピーすることで所有権が共有される
                                    // 所有者が2人に増える。
        std::cout << *y << std::endl;
    } // y が破棄されて所有者が1人になる。

    std::cout << *x << std::endl;

    return 0;
} // 所有者が0人になるので、 x のデストラクタで自動的に delete が行われる。
```

## std::unique_ptr

`std::unique_ptr` は、 `std::shared_ptr` と違い、コピーが出来ません。
そのため、確保したリソースの所有者が常に1人になります。

```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> x(new int(100));
    // std::unique_ptr<int> y = x; // コピー出来ない。コンパイルエラー。

    std::cout << *x << std::endl;

    return 0;
} // x が所有しているリソースが解放される。
```

所有権の共有はできませんが、`std::move` を使うことで所有権の移動は出来ます。このことで `std::shared_ptr` よりも軽快に動作します。

```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> x(new int(100));
    std::unique_ptr<int> y(std::move(x)); // ムーブは出来るため、所有権の移動は可能。
                                          // 所有権を移動したため、x は何も所有していない。

    std::cout << *y << std::endl;

    return 0;
} // y が所有しているリソースが解放される。
```

## std::auto_ptr

`std::auto_ptr` は C++11 では非推奨となっており C++17 では削除されているため使用しないでください。

詳細は [std::auto_ptr - cppreference.com][cppreference_auto_ptr] を参照してください。

[cppreference_auto_ptr]: https://ja.cppreference.com/w/cpp/memory/auto_ptr


## std::weak_ptr

`std::weak_ptr` は普段使うことは有りませんが、 `std::shared_ptr` を使う時に循環参照するような場合で `std::shared_ptr` のリソースの所有権を持つことなく、
そのリソースを監視する（弱参照）ことが出来るスマートポインタとして `std::weak_ptr` があります。
`lock()` を使うことで、監視している `std::shared_ptr` のリソースが有効な場合、
監視先とリソースを共有する `std::shared_ptr` が取得できます。

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(246);
    std::weak_ptr<int> wp = sp; // sp を監視対象として wp に登録する

    std::shared_ptr<int> sp2 = wp.lock(); // 有効な場合は sp とリソースを共有する sp2 が作られる
    if (sp2) {
        std::cout << *sp2 << std::endl;
    } else {
        std::cout << "リソースは解放済み" << std::endl;
    }

    return 0;
}
```
-----------------------------

ファイル: ./ch07-01-data-members.md
-----------------------------
# データメンバ

クラスとは変数と関数を集約した型をつくるための仕組みです。

クラスが持つ変数をデータメンバといいます。

!!! note "メンバ変数"
    データメンバのことを俗にメンバ変数と呼ぶこともありますが、
    C++ ではデータメンバという呼び方が正式な呼び方なので
    本ドキュメントもそれに従います。

長方形を扱う `Rectangle` クラスに
`int` 型のデータメンバ `height` と `width` を持たせるには次のようにします。

```cpp
class Rectangle {
 public:
    int height_;
    int width_;
};
```

データメンバを参照するには `.` を使用します。

```cpp
Rectangle r;
r.height_ = 10;
r.width_ = 20;
```

クラスのオブジェクトをポインタで扱う場合に、データメンバを参照するには次のようにします。

```cpp
Rectangle rectangle;
Rectangle* r = &rectangle;
(*r).height_ = 10;
(*r).width_ = 20;
```

括弧をつけずに `*r.height_` とすると意味が変わってコンパイルエラーとなります。

この記述方法は不便なため `(*r).` の代わりに `r->` と記述することができます。

```cpp
Rectangle rectangle;
Rectangle* r = &rectangle;
r->height_ = 10;
r->width_ = 20;
```

??? question "コンパイルエラーになる理由"
    演算子の優先順位が原因です。

    演算子には優先順位があります。
    たとえば加算 `+` と乗算 `*` では乗算 `*` を優先することになっているため、
    `1 + 2 * 3` は `1 + (2 * 3)` と解釈されて結果は `7` になります。
    `(1 + 2) * 3)` の結果である `9` にはなりません。

    デリファレンスの `*` とデータメンバ参照の `.` では
    データメンバ参照の `.` を優先することになっているため、
    `*r.height_` は `*(r.height_)` と解釈されます。
    しかしながら `r` の型である `std::unique_ptr<Rectangle>` には
    `height_` というデータメンバはないためコンパイルエラーとなります。

    詳細は [C++の演算子の優先順位 - cppreference.com][cppreference_operator_precedence]
    を参照してください。

[cppreference_operator_precedence]: https://ja.cppreference.com/w/cpp/language/operator_precedence
-----------------------------

ファイル: ./ch07-02-member-functions.md
-----------------------------
# メンバ関数

クラスが持つ関数をメンバ関数といいます。

長方形を扱う `Rectangle` クラスに
面積を求めるメンバ関数 `Area` を持たせるには次のようにします。

```cpp hl_lines="3 4 5"
class Rectangle {
 public:
    int Area() {
       return height_ * width_;
    }

    int height_;
    int width_;
};
```

メンバ関数を使用するには `.` を使用します。

```cpp hl_lines="4"
Rectangle r;
r.height_ = 10;
r.width_ = 20;
r.Area();
```

## クラス宣言とは別に定義

クラス宣言とは別にメンバ関数を定義するには次のようにします。

```cpp hl_lines="3 9 10 11"
class Rectangle {
 public:
    int Area();

    int height_;
    int width_;
};

int Rectangle::Area() {
    return height_ * width_;
}
```

どのクラスのメンバ関数であるかを表すために `Rectangle::` が必要になります。

??? question "暗黙的な inline 指定"
    クラス宣言の中でメンバ関数を定義した場合、暗黙的に `inline` 指定されます。
    そのため、ヘッダファイルのクラス宣言の中でメンバ関数を定義しても
    リンク時にエラーにはなりません。

    === "rectangle.h"

        ```cpp linenums="1" hl_lines="6 7 8"
        #ifndef RECTANGLE_H_
        #define RECTANGLE_H_

        class Rectangle {
        public:
            int Area() {
                return height_ * width_;
            }

            int height_;
            int width_;
        };

        #endif  // RECTANGLE_H_
        ```

    === "something.h"

        ```cpp linenums="1"
        #ifndef SOMETHING_H_
        #define SOMETHING_H_

        void Something();

        #endif  // SOMETHING_H_
        ```

    === "something.cc"

        ```cpp linenums="1"
        #include "something.h"

        #include <iostream>

        #include "rectangle.h"

        void Something() {
            Rectangle r;

            r.height_ = 2;
            r.width_ = 3;
            std::cout << r.Area() << std::endl;
        }
        ```

    === "main.cc"

        ```cpp linenums="1"
        #include <iostream>

        #include "rectangle.h"
        #include "something.h"

        int main() {
            Rectangle r;
            r.height_ = 10;
            r.width_ = 20;
            std::cout << r.Area() << std::endl;

            Something();

            return 0;
        }
        ```

    クラス宣言とは別にメンバ関数を定義すると暗黙的な inline 指定はされなくなります。
    ヘッダファイル内でクラス宣言とは別にメンバ関数の定義を行うとリンク時にエラーとなります。

    === "rectangle.h"

        ```cpp linenums="1" hl_lines="12 13 14"
        #ifndef RECTANGLE_H_
        #define RECTANGLE_H_

        class Rectangle {
        public:
            int Area();

            int height_;
            int width_;
        };

        int Rectangle::Area() {
            return height_ * width_;
        }

        #endif  // RECTANGLE_H_
        ```

    ヘッダファイル内でクラス宣言とは別にメンバ関数の定義を行うには、
    明示的に `inline` 指定する必要があります。

    === "rectangle.h"

        ```cpp linenums="1" hl_lines="12"
        #ifndef RECTANGLE_H_
        #define RECTANGLE_H_

        class Rectangle {
        public:
            int Area();

            int height_;
            int width_;
        };

        inline int Rectangle::Area() {
            return height_ * width_;
        }

        #endif  // RECTANGLE_H_
        ```

## const メンバ関数

引数リストのあとに `const` をつけることで `const` メンバ関数になります。

```cpp hl_lines="3"
class Rectangle {
 public:
    int Area() const;
};
```

`const` メンバ関数ではデータメンバを変更することができません。

```cpp hl_lines="10"
class Rectangle {
 public:
    int Area() const;

    int height_;
    int width_;
};

int Rectangle::Area() const {
    height_ = 0;  // データメンバを変更するとコンパイルエラーになります
    return height_ * width_;
}
```

`const` メンバ関数はデータメンバを変更しないため、
オブジェクトの状態を変化させずに呼び出すことができます。

データメンバを変更しないという制約を満たすために、
`const` メンバ関数から呼び出せるメンバ関数は `const` メンバ関数に限定されます。

## this ポインタ

メンバ関数では `this` で自オブジェクトのポインタを取得することができます。

```cpp
class Rectangle {
 public:
    int Area();

    int height_;
    int width_;
};

int Rectangle::Area() {
   // this ポインタ経由でデータメンバを使用
    return this->height_ * this->width_;
}
```
-----------------------------

ファイル: ./ch07-03-inheritance.md
-----------------------------
# 継承

クラスのメンバ (データメンバとメンバ関数) を引き継いで
新しいクラスを作成することを継承といいます。

長方形を扱う `Rectangle` クラスを継承して
正方形を扱う `Square` クラスを作るには次のようにします。

```cpp hl_lines="13"
#include <iostream>

class Rectangle {
 public:
    int Area() const {
       return height_ * width_;
    }

    int height_;
    int width_;
};

class Square : public Rectangle {
 public:
    void SetSize(int size) {
        height_ = size;
        width_ = size;
    }
};

int main() {
    Square s;
    s.SetSize(10);
    std::cout << s.Area() << std::endl;
    return 0;
}
```

`Square` クラスでは `Rectangle` クラスの全メンバを使用できます。
メンバ関数 `SetSize` で `Rectangle` クラスのデータメンバ `height_` と `width_` を参照したり、
メンバ関数の呼び出しで `s.Area` としたりすることができます。

継承を行った場合もメンバを持つことができるため、
`Square` クラスでは `Rectangle` クラスにはないメンバ関数 `SetSize` を追加することができます。

## 基底クラスと派生クラス

継承の元になったクラスのことを基底クラス、
継承して作ったクラスのことを派生クラスといいます。

`Rectangle` クラスを継承して `Square` クラスを作る場合、
`Rectangle` クラスが基底クラス、 `Square` クラスが派生クラスとなります。

## アクセス指定子

メンバを参照できる範囲はアクセス指定子によって制限することができます。
アクセス指定子には次の3つがあります。

| アクセス指定子 |      自クラス      |   継承したクラス   |       その他       |
| -------------- | ------------------ | ------------------ | ------------------ |
| public         | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| protected      | :white_check_mark: | :white_check_mark: | :x:                |
| private        | :white_check_mark: | :x:                | :x:                |

デフォルトでは `private` になります。

### メンバに対するアクセス指定子

`private` にすると自クラス内でのみメンバが参照できます。

!!! example "private_member.cc"
    ```cpp hl_lines="7 8 9 15 16 22 23" linenums="1"
    class Rectangle {
     public:
        int Area() const {
            height_ * width_;  // 参照可
        }

     private:
        int height_;
        int width_;
    };

    class Square : public Rectangle {
     public:
        void SetSize(int size) {
            height_ = size;  // コンパイルエラーになります
            width_ = size;   // コンパイルエラーになります
        }
    };

    int main() {
        Rectangle r;
        r.height_ = 10;  // コンパイルエラーになります
        r.width_ = 20;   // コンパイルエラーになります

        Square s;
        s.SetSize(10);
        return 0;
    }
    ```

`protected` にすると自クラス内に加え、継承したクラス内でも参照できるようになります。

!!! example "protected_member.cc"
    ```cpp hl_lines="7 8 9 22 23" linenums="1"
    class Rectangle {
     public:
        int Area() const {
            height_ * width_;  // 参照可
        }

     protected:
        int height_;
        int width_;
    };

    class Square : public Rectangle {
     public:
        void SetSize(int size) {
            height_ = size;  // 参照可
            width_ = size;   // 参照可
        }
    };

    int main() {
        Rectangle r;
        r.height_ = 10;  // コンパイルエラーになります
        r.width_ = 20;   // コンパイルエラーになります

        Square s;
        s.SetSize(10);
        return 0;
    }
    ```

`public` にすると参照できる範囲の制限はなくなります。

!!! example "public_member.cc"
    ```cpp hl_lines="7 8 9" linenums="1"
    class Rectangle {
     public:
        int Area() const {
            height_ * width_;  // 参照可
        }

     public:
        int height_;
        int width_;
    };

    class Square : public Rectangle {
     public:
        void SetSize(int size) {
            height_ = size;  // 参照可
            width_ = size;   // 参照可
        }
    };

    int main() {
        Rectangle r;
        r.height_ = 10;  // 参照可
        r.width_ = 20;   // 参照可

        Square s;
        s.SetSize(10);
        return 0;
    }
    ```

アクセス指定子は次のアクセス指定子が出現するまでが有効範囲となります。
また、アクセス指定子は何度でも使用できます。

```cpp
class AccessSpecifier {
    void Private1();  // デフォルトは private

 public:
    void Public1();
    void Public2();

 public:  // 対象となるメンバがなくても問題なし
 private:
    void Private2();

 private:  // アクセスレベルの変化がなくても問題なし
    void Private3();
};
```

読みづらいコードになってしまうのを防ぐため、
アクセス指定子の使い方についてコーディング規約で指定されることもあります。

### 継承に対するアクセス指定子

派生クラスではアクセス指定子によって
基底クラスのメンバを参照できる範囲をさらに制限することができます。

デフォルトでは `private` になります。

```cpp
class Base {};

class Sub1 : public Base {};  // public 継承
class Sub2 : protected Base {};  // protected 継承
class Sub3 : private Base {};  // private 継承
class Sub4 : Base {};  // private 継承 (デフォルト)
```

インターフェースのクラスを継承して実装を行う場合には `public` を使用します。

詳細は [派生クラス - cppreference.com][cppreference_derived_class] を参照してください。

[cppreference_derived_class]: https://ja.cppreference.com/w/cpp/language/derived_class
-----------------------------

ファイル: ./ch07-04-polymorphism.md
-----------------------------
# 多態性

## アップキャスト

派生クラスの参照やポインタから
基底クラスの参照やポインタへの型変換をアップキャストといいます。

アップキャストによって、
派生クラスのオブジェクトを基底クラスの参照またはポインタで扱うことができます。

!!! example "polymorphism_upcast.cc"
    ```cpp hl_lines="25 26" linenums="1"
    #include <iostream>

    class Rectangle {
     public:
        int Area() const {
            return height_ * width_;
        }

        int height_;
        int width_;
    };

    class Square : public Rectangle {
     public:
        void SetSize(int size) {
            height_ = size;
            width_ = size;
        }
    };

    int main() {
        Square s;
        s.SetSize(10);

        const Rectangle& r = s;
        std::cout << "area = " << r.Area() << std::endl;

        return 0;
    }
    ```

この例では `Square` クラスのオブジェクト `s` を `Rectangle` クラスの参照 `r` で扱っています。

アップキャストは暗黙的に行われるため、明示的に型変換を行う必要はありません。

## ダウンキャスト

基底クラスの参照やポインタから
派生クラスの参照やポインタへの型変換をダウンキャストといいます。

ダウンキャストを行わないで済むようなコードを書くことが望ましいです。
ダウンキャストの詳細については [ダウンキャスト][downcasts] を参照してください。

[downcasts]: appendix-downcasts.md

## 仮想関数とオーバーライド

派生クラスで挙動を変更できるメンバ関数を仮想関数といいます。
仮想関数にするには基底クラスのメンバ関数に `virtual` をつけます。

派生クラスで仮想関数の挙動を変更することをオーバーライドといいます。
派生クラスでオーバーライドを行うには、仮想関数シグニチャ（引数の型や `const` 修飾の有無）を厳密一致させる必要があります。
オーバーライドであることを明確化するため派生クラスのメンバ関数には `override` をつけることが推奨されます。

!!! note "`override` について"
    `override` はプログラマのミスや基底クラスの仕様変更により、
    関数シグニチャが厳密一致しなくなった際にオーバーライドに失敗するという
    トラブルを防ぐために導入された仕組みです。
    `override` をつけなくても関数シグニチャさえ厳密一致すればオーバーライドは可能ですが
    トラブルを防止するためには常につけたほうが良いでしょう。

    参考：[overrideとfinal - cpprefjp](https://cpprefjp.github.io/lang/cpp11/override_final.html)

!!! example "polymorphism_override.cc"
    ```cpp hl_lines="5 21 31" linenums="1"
    #include <iostream>

    class Rectangle {
     public:
        virtual void Describe() const {
            std::cout << "height = " << height_ << std::endl;
            std::cout << "width = " << width_ << std::endl;
        }

        int height_;
        int width_;
    };

    class Square : public Rectangle {
     public:
        void SetSize(int size) {
            height_ = size;
            width_ = size;
        }

        void Describe() const override {
            std::cout << "size = " << height_ << std::endl;
        }
    };

    int main() {
        Square s;
        s.SetSize(10);

        const Rectangle& r = s;
        r.Describe();

        return 0;
    }
    ```

実行結果は以下のようになります。

```
size = 10
```

この例ではメンバ関数 `Describe` がオーバーライドされているため、
`Rectangle` クラスではなく `Square` クラスの `Describe` が実行されます。

## 純粋仮想関数とインターフェース

定義をもたない仮想関数を純粋仮想関数といいます。
純粋仮想関数にするには仮想関数に `= 0` をつけます。

```cpp hl_lines="3"
class Polygon {
 public:
    virtual int Area() const = 0;
};
```

純粋仮想関数があるクラスのオブジェクトは作ることができません。

C++ にはインターフェースクラスをつくるための専用の記法はないため、
メンバ関数がすべて純粋仮想関数であるクラスをインターフェースとして使います。

```cpp hl_lines="3 8"
class Polygon {
 public:
    virtual int Area() const = 0;
};

class Rectangle : public Polygon {
 public:
    int Area() const override {
        return height_ * width_;
    }

    int height_;
    int width_;
};
```
-----------------------------

ファイル: ./ch07-05-constructors.md
-----------------------------
# コンストラクタ

オブジェクトを作成する際に呼び出されるメンバ関数をコンストラクタといいます。
コンストラクタはデータメンバの初期化を行うために使用します。

クラス名と同じ名前で戻り値がない関数がコンストラクタになります。

```cpp hl_lines="3"
class Rectangle {
 public:
    Rectangle(int height, int width);

    int Area() const;

 private:
    const int height_;
    const int width_;
};
```

このコンストラクタを使ってオブジェクトを作成するには次のようにします。

```cpp
Rectangle r(10, 20);
```

## データメンバの初期化

コンストラクタでデータメンバを初期化するには次のようにします。

```cpp hl_lines="3"
class Rectangle {
 public:
    Rectangle(int height, int width) : height_(height), width_(width) {}

    int Area() const {
        return height_ * width_;
    }

 private:
    const int height_;
    const int width_;
};
```

初期化は値の変更ではないため、
コンストラクタに渡された値から `const` データメンバの値を設定することができます。

## クラス宣言とは別に定義

クラス宣言とは別にコンストラクタを定義するには次のようにします。

```cpp hl_lines="3 14"
class Rectangle {
 public:
    Rectangle(int height, int width);

    int Area() const {
        return height_ * width_;
    }

 private:
    const int height_;
    const int width_;
};

Rectangle::Rectangle(int height, int width) : height_(height), width_(width) {}
```

## デフォルトコンストラクタ

値を1つも受け取らないコンストラクタをデフォルトコンストラクタといいます。

```cpp hl_lines="3"
class Rectangle {
 public:
    Rectangle() : height_(0), width_(0) {}

    int Area() const {
        return height_ * width_;
    }

 private:
    const int height_;
    const int width_;
};
```

デフォルトコンストラクタを使ってオブジェクトを作成するには次のようにします。

```cpp
Rectangle r;
```

明示的に定義するコンストラクタが1つもない場合のみ、
コンパイラが暗黙的にデフォルトコンストラクタを定義します。

## コピーコンストラクタ

そのクラスの参照だけを受け取るコンストラクタをコピーコンストラクタといいます。

```cpp
class Copyable {
 public:
    Copyable();  // デフォルトコンストラクタ
    Copyable(const Copyable& c);  // コピーコンストラクタ
};
```

コピーコンストラクタを使ってオブジェクトを作成するには次のようにします。

```cpp
Copyable c1;  // デフォルトコンストラクタでオブジェクト作成
Copyable c2(c1);  // コピーコンストラクタでオブジェクト作成
```

`const` ではない参照であってもコピーコンストラクタになりますが、
コピー元を変更せずにコピーを行うために `const` の参照にすることが多いです。

コピーコンストラクタを定義していないクラスでは、
コンパイラによって暗黙的にコピーコンストラクタが定義されます。

??? question "暗黙的にコピーコンストラクタが定義されないケース"
    コピーコンストラクタを定義していないクラスであっても、
    特定の条件を満たした場合には暗黙的なコピーコンストラクタの定義は行われなくなります。

    条件の一例として次のものがあります。

    - コピーできないデータメンバをもつ
    - 右辺値参照型のデータメンバをもつ
    - 下記のいずれかが明示的に定義されている
        - ムーブコンストラクタ
        - ムーブ代入演算子

    詳細は [コピーコンストラクタ - cppreference.com][cppreference_copy_constructor] を参照してください。

[cppreference_copy_constructor]: https://ja.cppreference.com/w/cpp/language/copy_constructor

## ムーブコンストラクタ

そのクラスの右辺値参照だけを受け取るコンストラクタをムーブコンストラクタといいます。

```cpp
class Movable {
 public:
    Movable();  // デフォルトコンストラクタ
    Movable(Movable&& m);  // ムーブコンストラクタ
};
```

ムーブコンストラクタを使ってオブジェクトを作成するには次のようにします。

```cpp
Movable m1;  // デフォルトコンストラクタでオブジェクト作成
Movable m2(std::move(m1));  // ムーブコンストラクタでオブジェクト作成
```

ムーブコンストラクタを定義していないクラスでは、
コンパイラによって暗黙的にムーブコンストラクタが定義されます。

??? question "暗黙的にムーブコンストラクタが定義されないケース"
    ムーブコンストラクタを定義していないクラスであっても、
    特定の条件を満たした場合には暗黙的なムーブコンストラクタの定義は行われなくなります。

    条件の一例として次のものがあります。

    - ムーブできないデータメンバをもつ
    - 下記のいずれかが明示的に定義されている
        - コピーコンストラクタ
        - コピー代入演算子
        - ムーブ代入演算子
        - デストラクタ

    詳細は [ムーブコンストラクタ - cppreference.com][cppreference_move_constructor] を参照してください。

[cppreference_move_constructor]: https://ja.cppreference.com/w/cpp/language/move_constructor

## 変換コンストラクタと explicit

値を1つだけ受け取るコンストラクタを変換コンストラクタといいます。
コピーコンストラクタやムーブコンストラクタも変換コンストラクタです。

```cpp hl_lines="3"
class Square {
 public:
    Square(int size) : size_(size) {}

    int Area() const {
        return size_ * size_;
    }

 private:
    int size_;
};
```

受け取る値が2個の場合と同様にオブジェクトを作成するには次のようにします。

```cpp
Square s(10);
```

以下のようにした場合、
`int` から `Square` への暗黙的な型変換で変換コンストラクタが使用されます。

```cpp
Square s = 10;
```

暗黙的な型変換で使用されないようにするには
変換コンストラクタに `explicit` をつけます。

暗黙的な型変換を意図して使用する場合を除き、
受け取る値が1つのコンストラクタには `explicit` をつけることが望ましいです。

!!! note "コピーコンストラクタとムーブコンストラクタ"
    コピーコンストラクタとムーブコンストラクタを `explicit` にすると
    関数の戻り値で値渡しすることができなくなります。
    一般的にコピーコンストラクタとムーブコンストラクタは `explicit` にはしません。

```cpp hl_lines="3"
class Square {
 public:
    explicit Square(int size) : size_(size) {}

    int Area() const {
        return size_ * size_;
    }

 private:
    int size_;
};
```

`explicit` をつけると以下の記述はコンパイルエラーになります。

```cpp
Square s = 10;
```

## 継承

派生クラスのコンストラクタは
基底クラスのデフォルトコンストラクタを暗黙的に呼び出します。

!!! example "constructor_inheritance.cc"
    ```cpp hl_lines="5 6 7 20 21 22 26" linenums="1"
    #include <iostream>

    class Rectangle {
     public:
        Rectangle() : height_(0), width_(0) {
            std::cout << "Rectangle::Rectangle() is called." << std::endl;
        }

        int Area() const {
            return height_ * width_;
        }

     private:
        const int height_;
        const int width_;
    };

    class Square : public Rectangle {
     public:
        Square() {
            std::cout << "Square::Square() is called." << std::endl;
        }
    };

    int main() {
        Square s;  // Square クラスのデフォルトコンストラクタを使用
        std::cout << "area = " << s.Area() << std::endl;
        return 0;
    }
    ```

実行結果は以下のようになります。

```
Rectangle::Rectangle() is called.
Square::Square() is called.
area = 0
```

コンストラクタの実行順序は、必ず次の順序になります。

1. 基底クラスのコンストラクタ
1. 派生クラスのコンストラクタ

基底クラスのコンストラクタを明示的に呼び出すこともできます。

```cpp hl_lines="16"
class Rectangle {
 public:
    Rectangle(int height, int width) : height_(height), width_(width) {}

    int Area() const {
        return height_ * width_;
    }

 private:
    const int height_;
    const int width_;
};

class Square : public Rectangle {
 public:
    Square(int size) : Rectangle(size, size) {}
};
```
-----------------------------

ファイル: ./ch07-06-destructors.md
-----------------------------
# デストラクタ

オブジェクトを破棄する際に呼び出されるメンバ関数をデストラクタといいます。
デストラクタはリソースの解放を行うために使用します。

`~` にクラス名をつけた名前で戻り値がない関数がデストラクタになります。
デストラクタは引数をもちません。

```cpp hl_lines="12 13 14 15"
#include <iostream>

class DynamicArray {
 public:
    DynamicArray(int size, int initial_value) {
        data_ = new int[size];
        for (auto i = 0; i < size; ++i) {
            data_[i] = initial_value;
        }
    }

    ~DynamicArray() {
        std::cout << "DynamicArray::~DynamicArray() is called." << std::endl;
        delete[] data_;
    }

    void Set(int index, int value) {
        data_[index] = value;
    }

    int Get(int index) const {
        return data_[index];
    }

 private:
    int* data_;
};

int main() {
    DynamicArray d(5, 1);
    std::cout << d.Get(2) << std::endl;
    d.Set(2, 10);
    std::cout << d.Get(2) << std::endl;

    return 0;
}
```

明示的に定義しない場合、
コンパイラが暗黙的にデストラクタを定義します。

## デストラクタを書かない

下に紹介するRAIIのためを除いてデストラクタを書く機会はありません。
なぜならばRAII技法が使われたリソース管理クラスをデータメンバに持つだけでそれらのデストラクタが自動的に呼び出されるからです。

デストラクタを定義( `= default` 指定も含む)した場合、ムーブコンストラクタ/代入演算子が自動定義されなくなり、またコピーコンストラクタ/代入演算子は自動生成されるものの非推奨(=使ってはいけない)になるので、残りの特殊メンバ関数もすべて定義するようにしましょう。

## デストラクタから例外を投げてはいけない

C++11からはデストラクタは暗黙のうちに `noexcept` 指定されます。したがってデストラクタから例外を投げてはいけません。詳しくは[例外の解説](ch10-01-exceptions.md)を参照してください。

## RAII(Resource Acquisition Is Initialization)

プログラムを書く時につきまとうのがリソースの管理です。リソースとは例えばメモリーや、ファイルポインタ、ハンドルなどが該当します。

クラス変数の寿命が尽きた時にデストラクタが呼ばれるという性質を利用して、リソースの割り当てと解放を紐付けて管理する技法があります。これをRAIIといいます。

もっとも頻繁に接するリソースであるメモリーについては[ガベージコレクション]による解決を試みる言語もありますが、その場合メモリー以外のリソースの管理に困ります。

[ガベージコレクション]: https://ja.wikipedia.org/wiki/ガベージコレクション

デストラクタを持たずに RAII を実現できる言語もありますが、一般に何らかの明示的な処理を必要とします。たとえば Python の `with` 文、C#の `using` 文などが該当します。

RAII技法を実装するクラスを作るときにはただ一つのリソースのみを管理するクラスを作ります。なぜならばコンストラクタで例外が発生したときデストラクタは呼ばれず、リソースの解放漏れが発生するからです

```cpp
// 複数のリソースを管理しようとしている→×
class inferior {
public:
    inferior() {
        data1_ = new int();
        data2_ = new int();//このnewに失敗するとdata1_は解放されない
    }
    ~inferior() noexcept {
        delete data1_;
        delete data2_;
    }
private:
    int* data1_;
    int* data2_;
};
// ただひとつのリソースを管理する
class resource {
public:
    resource() {
        data_ = new int();//このnewに失敗しても解放するべきものはない
    }
    ~resource() noexcept {
        delete data_;
    }
private:
    int* data_;
}
// RAII技法が使われただひとつのリソースを管理するクラスを複数メンバー変数として持つ→○
class good {
    resource data1_;
    resource data2_;
}
```

## クラス宣言とは別に定義

クラス宣言とは別にデストラクタを定義するには次のようにします。

```cpp hl_lines="10 24 25 26 27"
class DynamicArray {
 public:
    DynamicArray(int size, int initial_value) {
        data_ = new int[size];
        for (auto i = 0; i < size; ++i) {
            data_[i] = initial_value;
        }
    }

    ~DynamicArray();

    void Set(int index, int value) {
        data_[index] = value;
    }

    int Get(int index) const {
        return data_[index];
    }

 private:
    int* data_;
};

DynamicArray::~DynamicArray() {
    std::cout << "DynamicArray::~DynamicArray() is called." << std::endl;
    delete[] data_;
}
```

## 継承

派生クラスのデストラクタは基底クラスのデストラクタを暗黙的に呼び出します。

!!! example "destructor_inheritance.cc"
    ```cpp hl_lines="5 6 7 22 23 24 25" linenums="1"
    #include <iostream>

    class BasicArray {
     public:
        ~BasicArray() {
            std::cout << "BasicArray::~BasicArray() is called." << std::endl;
        }

        virtual void Set(int index, int value) = 0;
        virtual int Get(int index) const = 0;
    };

    class DynamicArray : public BasicArray {
     public:
        DynamicArray(int size, int initial_value) {
            data_ = new int[size];
            for (auto i = 0; i < size; ++i) {
                data_[i] = initial_value;
            }
        }

        ~DynamicArray() {
            std::cout << "DynamicArray::~DynamicArray() is called." << std::endl;
            delete[] data_;
        }

        void Set(int index, int value) { data_[index] = value; }

        int Get(int index) const { return data_[index]; }

     private:
        int* data_;
    };

    int main() {
        DynamicArray d(5, 1);
        std::cout << d.Get(2) << std::endl;
        d.Set(2, 10);
        std::cout << d.Get(2) << std::endl;

        return 0;
    }
    ```

実行結果は以下のようになります。

```
1
10
DynamicArray::~DynamicArray() is called.
BasicArray::~BasicArray() is called.
```

デストラクタの実行順序は、必ず次の順序になります。

1. 派生クラスのデストラクタ
1. 基底クラスのデストラクタ

## 仮想デストラクタ

アップキャストして基底クラスのポインタで扱う場合、
基底クラスのデストラクタだけが呼び出されて
派生クラスのデストラクタは呼び出されなくなります。

!!! failure "destructor_non_virtual.cc"
    ```cpp hl_lines="6 7 8 23 24 25 26 37" linenums="1"
    #include <iostream>
    #include <memory>

    class BasicArray {
     public:
        ~BasicArray() {
            std::cout << "BasicArray::~BasicArray() is called." << std::endl;
        }

        virtual void Set(int index, int value) = 0;
        virtual int Get(int index) const = 0;
    };

    class DynamicArray : public BasicArray {
     public:
        DynamicArray(int size, int initial_value) {
            data_ = new int[size];
            for (auto i = 0; i < size; ++i) {
                data_[i] = initial_value;
            }
        }

        ~DynamicArray() {
            std::cout << "DynamicArray::~DynamicArray() is called." << std::endl;
            delete[] data_;
        }

        void Set(int index, int value) { data_[index] = value; }

        int Get(int index) const { return data_[index]; }

     private:
        int* data_;
    };

    int main() {
        std::unique_ptr<BasicArray> b(new DynamicArray(5, 1));
        std::cout << b->Get(2) << std::endl;
        b->Set(2, 10);
        std::cout << b->Get(2) << std::endl;

        return 0;
    }
    ```

この例では
派生クラス `DynamicArray` をアップキャストして
基底クラス `BasicArray` のスマートポインタで扱っています。

実行結果は以下のようになります。

```
1
10
BasicArray::~BasicArray() is called.
```

`DynamicArray` のデストラクタが呼ばれておらずメモリリークが発生してしまいます。

このような問題を防ぐために、
基底クラスのデストラクタは仮想関数にします。
派生クラスではデストラクタをオーバーロードすることになるため
`override` をつけます。

!!! example "destructor_virtual.cc"
    ```cpp hl_lines="6 23" linenums="1"
    #include <iostream>
    #include <memory>

    class BasicArray {
     public:
        virtual ~BasicArray() {
            std::cout << "BasicArray::~BasicArray() is called." << std::endl;
        }

        virtual void Set(int index, int value) = 0;
        virtual int Get(int index) const = 0;
    };

    class DynamicArray : public BasicArray {
     public:
        DynamicArray(int size, int initial_value) {
            data_ = new int[size];
            for (auto i = 0; i < size; ++i) {
                data_[i] = initial_value;
            }
        }

        ~DynamicArray() override {
            std::cout << "DynamicArray::~DynamicArray() is called." << std::endl;
            delete[] data_;
        }

        void Set(int index, int value) { data_[index] = value; }

        int Get(int index) const { return data_[index]; }

     private:
        int* data_;
    };

    int main() {
        std::unique_ptr<BasicArray> b(new DynamicArray(5, 1));
        std::cout << b->Get(2) << std::endl;
        b->Set(2, 10);
        std::cout << b->Get(2) << std::endl;

        return 0;
    }
    ```

実行結果は以下のようになります。

```
1
10
DynamicArray::~DynamicArray() is called.
BasicArray::~BasicArray() is called.
```

<!-- STLコンテナの説明を事前に行う or 記述を修正する -->
!!! failure "STLコンテナクラスの継承"
    STLコンテナクラスのデストラクタは仮想関数になっていません。
    そのためSTLコンテナを継承したクラスを
    STLコンテナにアップキャストして使用してはいけません。
-----------------------------

ファイル: ./ch07-07-operator-overloading.md
-----------------------------
# 演算子オーバーロード

クラスに対する演算子を定義することで演算子が使用可能になります。
演算子は関数またはメンバ関数として定義します。

## 単項演算子

整数を扱う `Integer` クラスの負号演算子を関数として定義するには次のようにします。

```cpp hl_lines="13 14 15 16 17"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

 private:
    int value_;
};

// 負号演算子の対象が引数として渡される
Integer operator-(const Integer& v) {
    Integer tmp(-v.Value());
    return tmp;
}
```

この演算子を使用するには次のようにします。

```cpp hl_lines="2"
Integer a(2);
Integer b = -a;

std::cout << a.Value() << std::endl;  // 2
std::cout << b.Value() << std::endl;  // -2
```

メンバ関数として定義するには次のようにします。

```cpp hl_lines="9 10 11 12 13"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

    // 負号演算子の対象のメンバ関数
    Integer operator-() const {
        Integer tmp(-Value());  // 演算対象は自オブジェクトを使用する
        return tmp;
    }

 private:
    int value_;
};
```

## 二項演算子

整数を扱う `Integer` クラスの加算演算子を関数として定義するには次のようにします。

```cpp hl_lines="13 14 15 16 17"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

 private:
    int value_;
};

// 加算演算子の左辺が第1引数、右辺が第2引数として渡される
Integer operator+(const Integer& lhs, const Integer& rhs) {
    Integer tmp(lhs.Value() + rhs.Value());
    return tmp;
}
```

この演算子を使用するには次のようにします。

```cpp hl_lines="3"
Integer a(2);
Integer b(3);
Integer c = a + b;

std::cout << a.Value() << std::endl;  // 2
std::cout << b.Value() << std::endl;  // 3
std::cout << c.Value() << std::endl;  // 5
```

メンバ関数として定義するには次のようにします。

```cpp hl_lines="9 10 11 12 13"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

    // 加算演算子の左辺のメンバ関数に対して、右辺が引数として渡される
    Integer operator+(const Integer& rhs) const {
        Integer tmp(Value() + rhs.Value());  // 左辺は自オブジェクトを使用する
        return tmp;
    }

 private:
    int value_;
};
```

一般に二項演算子は対称性を維持するために関数として実装されます。
たとえば整数クラスと実数クラスの二項演算子は次のように実装します。

```cpp hl_lines="25 26 27 28 30 31 32 33"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

 private:
    int value_;
};

class RealNumber {
 public:
    explicit RealNumber(double value) : value_(value) {}

    double Value() const {
        return value_;
    }

 private:
    double value_;
};

RealNumber operator+(const Integer& lhs, const RealNumber& rhs) {
    RealNumber tmp(lhs.Value() + rhs.Value());
    return tmp;
}

RealNumber operator+(const RealNumber& lhs, const Integer& rhs) {
    RealNumber tmp(lhs.Value() + rhs.Value());
    return tmp;
}
```

## インクリメント/デクリメント

インクリメント/デクリメントには前置と後置の2種類があります。

前置は単行演算子の方法で定義します。

```cpp hl_lines="9 10 11 12"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

    Integer& operator++() {
        ++value_;
        return *this;
    }

 private:
    int value_;
};
```

次のように前置インクリメントが使用できるようになります。

```cpp hl_lines="2"
Integer a(2);
Integer b = ++a;

std::cout << a.Value() << std::endl;  // 3
std::cout << b.Value() << std::endl;  // 3
```

後置は二項演算子の方法で定義します。
これは前置と後置を区別するために後置では `int` (通常は値 `0`) が渡される決まりがあるからです。

```cpp hl_lines="9 10 11 12 13"
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

    Integer operator++(int) {  // 引数の int は使用しない
        Integer tmp(Value());
        ++value_;
        return tmp;
    }

 private:
    int value_;
};
```

次のように後置インクリメントが使用できるようになります。

```cpp hl_lines="2"
Integer a(2);
Integer b = a++;

std::cout << a.Value() << std::endl;  // 3
std::cout << b.Value() << std::endl;  // 2
```

## 期待される振る舞い

演算子の振る舞いについては制約がほとんどありませんが、
一般に組み込みの演算子と同様の振る舞いになることが期待されます。

たとえば次のように期待する動作と異なる実装にすることも可能ではあります。

```cpp
class Integer {
 public:
    explicit Integer(int value) : value_(value) {}

    int Value() const { return value_; }

    Integer& operator-() {
        return *this;  // 何もしないで自オブジェクトを返却
    }

 private:
    int value_;
};
```

この定義に対して演算子を使用すると次のようになります。

```cpp
Integer a(2);
Integer b = -a;

std::cout << a.Value() << std::endl;  // 2
std::cout << b.Value() << std::endl;  // 2 (-2 ではない)
```

このように期待される振る舞いと異なる振る舞いにならないように、
組み込みの演算子となるべく同じ振る舞いになるよう定義するのが一般的です。

期待される振る舞いについては
[演算子オーバーロード - cppreference.com][cppreference_operators] を参照してください。

[cppreference_operators]: https://ja.cppreference.com/w/cpp/language/operators
-----------------------------

ファイル: ./ch07-08-assignment-operator.md
-----------------------------
# 代入演算子

演算子オーバーロードの対象して代入演算子もあります。

代入演算子にはコピー代入演算子とムーブ代入演算子の2つがあります。

## コピー代入演算子

コピー代入演算子は通常以下を満たすメンバ関数として定義します。

* 引数はコピー元となるオブジェクトの `const` 左辺値参照
* 戻り値はコピー先オブジェクト (自オブジェクト) の左辺値参照

```cpp
class Copyable {
 public:
    Copyable();  // デフォルトコンストラクタ
    Copyable& operator=(const Copyable& c);  // コピー代入演算子
};
```

コピー代入演算子を使用するには次のようにします。

```cpp
Copyable c1;  // デフォルトコンストラクタでオブジェクト作成
Copyable c2;  // デフォルトコンストラクタでオブジェクト作成
c2 = c1;  // コピー代入演算子でコピー代入
```

一般にコピーコンストラクタとコピー代入演算子はセットで使用します。

```cpp
class Copyable {
 public:
    Copyable();  // デフォルトコンストラクタ
    Copyable(const Copyable& c);  // コピーコンストラクタ
    Copyable& operator=(const Copyable& c);  // コピー代入演算子
};
```

コピー代入演算子を定義していないクラスでは
コンパイラによって暗黙的にコピー代入演算子が定義されます。

??? question "暗黙的にコピー代入演算子が定義されないケース"
    コピー代入演算子を定義していないクラスであっても、
    特定の条件を満たした場合には暗黙的なコピー代入演算子の定義は行われなくなります。

    条件の一例として次のものがあります。

    - コピー代入演算子が定義されていないデータメンバをもつ
    - 下記のいずれかが明示的に定義されている
        - ムーブコンストラクタ
        - ムーブ代入演算子

    詳細は [コピー代入演算子 - cppreference.com][cppreference_copy_assignment] を参照してください。

[cppreference_copy_assignment]: https://ja.cppreference.com/w/cpp/language/copy_assignment

## ムーブ代入演算子

ムーブ代入演算子は通常以下を満たすメンバ関数として定義します。

* 引数はムーブ元となるオブジェクトの右辺値参照
* 戻り値はムーブ先オブジェクト (自オブジェクト) の左辺値参照

```cpp
class Movable {
 public:
    Movable();  // デフォルトコンストラクタ
    Movable& operator=(Movable&& m);  // ムーブ代入演算子
};
```

ムーブ代入演算子を使用するには次のようにします。

```cpp
Movable m1;  // デフォルトコンストラクタでオブジェクト作成
Movable m2;  // デフォルトコンストラクタでオブジェクト作成
m2 = std::move(m1);  // ムーブ代入演算子でムーブ代入
```

一般にムーブコンストラクタとムーブ代入演算子はセットで使用します。

```cpp
class Movable {
 public:
    Movable();  // デフォルトコンストラクタ
    Movable(Movable&& m);  // ムーブコンストラクタ
    Movable& operator=(Movable&& m);  // ムーブ代入演算子
};
```

ムーブ代入演算子を定義していないクラスでは
コンパイラによって暗黙的にムーブ代入演算子が定義されます。

??? question "暗黙的にムーブ代入演算子が定義されないケース"
    ムーブ代入演算子を定義していないクラスであっても、
    特定の条件を満たした場合には暗黙的なムーブ代入演算子の定義は行われなくなります。

    条件の一例として次のものがあります。

    - ムーブ代入演算子が定義されていないデータメンバをもつ
    - 下記のいずれかが明示的に定義されている
        - コピーコンストラクタ
        - コピー代入演算子
        - ムーブコンストラクタ
        - デストラクタ

    詳細は [ムーブ代入演算子 - cppreference.com][cppreference_move_assignment] を参照してください。

[cppreference_move_assignment]: https://ja.cppreference.com/w/cpp/language/move_assignment

## 初期化

C++ では代入と初期化が区別されます。

変数宣言と同時に使用する `=` は代入ではなく初期化として扱われます。

### コピー初期化

初期化をコピーによって行う場合、
コピー代入演算子ではなくコピーコンストラクタが使用されます。

```cpp
Copyable c1;
Copyable c2 = c1;  // コピーコンストラクタを使用
Copyable c3;
c3 = c2;  // コピー代入演算子を使用
```

### ムーブ初期化

初期化をムーブによって行う場合、
ムーブ代入演算子ではなくムーブコンストラクタが使用されます。

```cpp
Movable m1;
Movable m2 = std::move(m1);  // ムーブコンストラクタを使用
Movable m3;
m3 = std::move(m2);  // ムーブ代入演算子を使用
```
-----------------------------

ファイル: ./ch07-09-default-and-delete.md
-----------------------------
# default/delete

以下のメンバ関数は暗黙的に定義されることがある特別なメンバ関数です。

- デフォルトコンストラクタ
- コピーコンストラクタ
- コピー代入演算子
- ムーブコンストラクタ
- ムーブ代入演算子
- デストラクタ

これらに対する指定として `default` 指定と `delete` 指定があります。

## default 指定

暗黙的に定義される特別なメンバ関数に `= default` をつけることで、
暗黙的に定義されるものと同じものを明示的に定義できます。

```cpp hl_lines="8"
class Square {
 public:
    explicit Square(int size) : size_(size) {}

    // デフォルトコンストラクタ以外のコンストラクタが存在するので
    // デフォルトコンストラクタの暗黙的な定義は行われない。
    // デフォルトコンストラクタを使用するために default 指定で明示的に定義
    Square() = default;

    int Area() const {
        return size_ * size_;
    }

 private:
    int size_;
};

int main() {
    Square s1;
    Square s2(10);

    return 0;
}
```

## delete 指定

暗黙的に定義される特別なメンバ関数に `= delete` をつけることで、
暗黙的に定義される特別なメンバ関数の削除を指定します。

```cpp hl_lines="7 8"
class NonCopyable {
 public:
    NonCopyable() = default;

    // 暗黙的に定義されるコピーコンストラクタとコピー代入演算子を
    // 削除することでコピー禁止クラスを実現できる
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```
-----------------------------

ファイル: ./ch07-10-static-members.md
-----------------------------
# static メンバ

## static データメンバ

クラスのオブジェクトごとではなく、クラスそのものがもつ変数です。

!!! warning "初期化と破棄のタイミング"
    static データメンバの初期化/破棄はプログラムの開始/終了時にまとめて行われますが、
    実行順序を制御することができません。

    誤った扱いをすると原因特定が難しいエラーが発生しやすい機能であり、使用には注意が必要です。

データメンバの宣言に `static` をつけることで `static` データメンバを宣言することができます。

```cpp
class Counter {
 public:
    static int count_;
};
```

static データメンバはクラスの外で実体を定義する必要があります。

```cpp
int Counter::count_ = 10;  // 値 10 で初期化
```

ヘッダファイルが2つ以上のファイルでインクルードされる場合、
ヘッダファイルで実体の定義を行うと多重定義となりリンクエラーになってしまいます。
この問題を避けるために static データメンバの実体の定義はソースファイルで行います。

=== "counter.cc"

    ```cpp
    #include "counter.h"

    int Counter::count_ = 10;
    ```

=== "counter.h"

    ```cpp
    #ifndef COUNTER_H_
    #define COUNTER_H_

    class Counter {
    public:
        static int count_;
    };

    #endif  // COUNTER_H_
    ```

static データメンバを参照するには `Counter::count_` のようにします。

```cpp
#include <iostream>

#include "counter.h"

int main() {
    ++Counter::count_;
    std::cout << Counter::count_ << std::endl;  // 11
    return 0;
}
```

## static メンバ関数

クラスのオブジェクトごとではなく、クラスそのものがもつ関数です。

メンバ関数の宣言に static をつけることで static メンバ関数を宣言することができます。

```cpp
class Brightness {
 public:
    explicit Brightness(int value) : value_(value) {}

    int Value() const {
        return value_;
    }

    static Brightness Maximum();
    static Brightness Minimum();
    static Brightness Median();

 private:
    int value_;
};
```

static メンバ関数は static データメンバ以外のデータメンバは直接参照できないため、
static メンバ関数ではなく通常の関数で十分なことが多いです。

通常の関数との違いは static メンバ関数はクラスに属するため、
`protected` や `private` のメンバにもアクセスできることです。

```cpp
Brightness Brightness::Maximum() {
    return Brightness(100);
}

Brightness Brightness::Minimum() {
    return Brightness(0);
}

Brightness Brightness::Median() {
    return Brightness((Maximum().value_ + Minimum().value_) / 2);
}
```

static メンバ関数は実行順序が定まるため、
static データメンバの代わりに static メンバ関数を使用することで
初期化順序を制御できない問題を回避することができます。
-----------------------------

ファイル: ./ch07-11-structs.md
-----------------------------
# 構造体

クラスのアクセス指定子はデフォルトで `private` ですが、
デフォルトのアクセス指定子を `public` にしたものが構造体です。

`class` の代わりに `struct` とすると構造体になります。

```cpp
struct Rectangle {
    int height;
    int width;
};
```

この例では明示的にアクセス指定子は書いてありませんが、
デフォルトの値が `public` であるため次のようにデータメンバを参照することができます。

```cpp
Rectangle r;
r.height = 10;
r.width = 20;
```

クラスと構造体の使い分けについてコーディング規約で指定されることもあります。
-----------------------------

ファイル: ./ch07-12-unions.md
-----------------------------
# 共用体

共用体は複数の型のどれかを格納したい、という場合に用いるものです。

```cpp
#include <string>
union X {
    int m1;
    double m2;
    std::string m3;
    X() : m1(0) {}
    ~X() {}
};
template <class T>
void destroy_at(T* location)
{
    location->~T();
}
int main()
{
    X x;
    new (&x.m3) std::string("aaa");
    destroy_at(&x.m3);
}
```

共用体に暗黙ではない特殊メンバ関数(コンストラクタなど)が定義されているようなクラス型を入れる場合、いくつか注意があります。

- 共用体の対応する特殊メンバ関数は削除されるので自力で定義しなければならない
- そのクラス型の値を入れる場合、[配置new](https://cpprefjp.github.io/reference/new/op_new.html)という機能を使ってクラスのコンストラクタを呼び出さなければならない。またデストラクタも同様

デストラクタの呼び出しは上の例では `destory_at` という関数を定義して行っています。同様の処理をしてくれるものがC++17以降では `<memory>` ヘッダーに [`std::destory_at`](https://cpprefjp.github.io/reference/memory/destroy_at.html) としてあります。

構造体の大きさがメンバーのすべての型の大きさの総和にパディングなどを足したものであったのに対して、
共用体ではメンバーの型の大きさの最大値にパディングなどを足したものとなります。
結果としてメモリーを節約することができるので、複数の型のどれかを格納したいという場合にはよく用いられます。

## 実用的な例: JSONのパース

例えば[JSON](https://www.json.org/json-en.html)をパースすることを考えます。
JSONの値はオブジェクト、配列、文字列、数値、bool、nullを持つことができます。
とりあえず最もわかりやすく表現するデータ構造を考えると次のようになります。

```cpp
#include <map>
#include <string>
#include <vector>
#include <iostream>
template <class T>
void destroy_at(T* location)
{
    location->~T();
}
struct value {
    enum class kind {
        null,
        object,
        array,
        string,
        number,
        boolean
    };
    kind k_;
    union data {
        bool b_;
        double num_;
        std::string str_;
        std::vector<value> arr_;
        std::map<std::string, value> obj_;
        data() : b_{} {}
        ~data() {}
    } data_;
    value()  : k_() {}
    value(std::string s) : k_(kind::string)
    {
        new(&data_.str_) std::string(std::move(s));
    }
    ~value()
    {
        switch(k_) {
        case kind::object:
            destroy_at(&data_.obj_); break;
        case kind::array:
            destroy_at(&data_.arr_); break;
        case kind::string:
            destroy_at(&data_.str_); break;
        default:
            break;
        }
    }
    kind get_kind() { return k_; }
    std::string get_string_or(std::string default_value)
    {
        return (k_ == kind::string) ? data_.str_ : default_value;
    }
};
int main()
{
    value v1;
    std::cout << static_cast<int>(v1.get_kind()) << v1.get_string_or("bbb") << std::endl;
    value v2("aaa");
    std::cout << static_cast<int>(v2.get_kind()) << v2.get_string_or("bbb") << std::endl;
}
```

共用体にどんなデータが入っているかを別途変数で持っておき、読み出す時に条件分岐して処理するというのが一般的な扱いです。上の例では `value` クラスの中に `kind` という列挙型を定義してその型の変数 `k_` も定義しました。この `k_` に今なんのデータが共用体に入っているかを記録し、共用体にアクセスするときはこの `k_` を確認してからアクセスします。

## アクティブな共用体のデータメンバ

共用体のあるデータメンバにデータを入れたとき、そのデータメンバの寿命が開始しアクティブになります。

別のデータメンバにデータを入れるとそれまでアクティブだったメンバー変数の寿命が尽き、新たにデータが入ったメンバー変数の寿命が開始しアクティブになります。

アクティブになることができるデータメンバは最大で1つまでです。

```cpp
union A { int x; int y[4]; };
struct B { A a; };
union C { B b; int k; };
int f() {
  C c;                  // どの共用体のメンバの寿命も開始しない
  c.b.a.y[3] = 4;       // OK: c.bとc.b.a.yの寿命が開始してオブジェクトが作られる
  return c.b.a.y[3];    // OK: c.b.a.yは作られたオブジェクトを指す
}
struct X { const int a; int b; };
union Y { X x; int k; };
int g() {
  Y y = { { 1, 2 } };   // OK: y.x はアクティブな共用体のメンバ
  int n = y.x.a;
  y.k = 4;              // OK: y.xの寿命が尽き、y.kの寿命が開始、y.kはアクティブな共用体のメンバ
  y.x.b = n;            // undefined behavior: Xのデフォルトコンストラクタは削除されています
                        // したがってy.xの寿命は暗黙のうちに開始できません
}
union Z {
    int int_value;
    char char_value[4];
};
int main()
{
    f();
    g();
    Z z;// どの共用体のメンバの寿命も開始しない
    z.int_value = 65535;// OK: z.int_valueの寿命が開始してオブジェクトが作られる
    z.char_value[0];    // NG: z.char_valueの寿命は開始していない
}
```

!!! error "C++には存在しないtrap representation"
    C言語のC99以降にはtrap representationと言われる仕様があります。上の例でいう共用体 `Z` をみたとき、 `z.char_value[0]` のようなアクセスをすると新しい型のオブジェクト表現として再解釈されるというものです。しかしながらC++には存在しません。よくある誤りなので、共用体に値を入れたらその入れたものからだけ読み取るように注意しましょう。
-----------------------------

ファイル: ./ch08-01-cpp-casts.md
-----------------------------
# C++ のキャスト

C++ では4種類のキャスト演算子が用意されています。

|   キャスト演算子   | 主な用途                                         |
|------------------|:-----------------------------------------------|
| static_cast      | 型変換を明示的に行う                               |
| dynamic_cast     | 基底クラス型のポインタと派生クラス型のポインタを変換する |
| const_cast       | const修飾を変化させる                                |
| reinterpret_cast | 型情報だけ変える                             |

本節では基本的な使い方だけを説明します。
詳しい説明は [キャストの詳しい説明][cast-details] を参照してください。

[cast-details]: appendix-cast-details.md

## static_cast

型変換を明示的に行うためのキャストです。必要があれば値を変化させます。

```cpp
double dx = 3.14;
int x = static_cast<int>(dx);  // 3
```

列挙型と数値型の変換など
暗黙的に変換されない型変換も行うことができます。

```cpp
enum class Day {
    Sun,  // 0
    Mon,  // 1
    Tue,  // 2
    Wed,  // 3
    Thu,  // 4
    Fri,  // 5
    Sat   // 6
};

Day day1 = static_cast<Day>(1);         // Day::Mon
int day2 = static_cast<int>(Day::Tue);  // 2
```

型変換を明示的に行うことで、
`explicit` 指定された変換コンストラクタによる変換も行うことができます。

```cpp
class Square {
 public:
    explicit Square(int size) : size_(size) {}

 private:
    int size_;
};

Square square = static_cast<Square>(10);
```

## dynamic_cast

一般にダウンキャストをする際に、 `dynamic_cast` を使います。アップキャストに使うときは `static_cast` と同じ意味を持ちます。
`dynamic_cast` の詳細については [ダウンキャスト][downcasts] を参照してください。

[downcasts]: appendix-downcasts.md

## const_cast

一般にconst修飾子を外すときに用いるキャストです。const修飾を付加するときは `static_cast` と同じ意味を持ちます。

```cpp
const std::string str("hoge");
std::string& x = const_cast<std::string&>(str);
```

「オブジェクトに変更を加えないようにする」ために `const` が付いているにも関わらず、
`const_cast` で「オブジェクトに変更を加えられるようにする」ことは望ましくないので、基本的には使いません。

## reinterpret_cast

値はそのまま型情報の変換を行うキャストです。安全に使用するためにはいくつもの落とし穴があります。
[Strict Aliasing Rules]のようにキャスト単体でみれば問題なくても全体としてみると未定義動作を引き起こすこともあります。
`std::nullptr_t -> T -> std::nullptr_t` が反例で、常にA→B→Aというふうに変換できるという保証もありません。
`reinterpret_cast` とはこうした未定義動作と未規定の動作などがそこかしこに横たわる魔境といえるでしょう。
事実として `reinterpret_cast` の誤った用法をしばしば目にします。先人が書いたコードや解説を信用してはいけません。
したがってなるべく `reinterpret_cast` を使わないようなコードを書くことが望ましいです。

[Strict Aliasing Rules]: https://yohhoy.hatenadiary.jp/entry/20120220/p1

`reinterpret_cast` はバイナリデータの読み書き時に使われることがあります。
入力ストリームの `read()` や出力ストリームの `write()` の第 1 引数のポインタの型が決まっているためです。

```cpp hl_lines="18"
#include <fstream>
#include <vector>

int main() {
    std::vector<int> nums = {1, 2, 3, 4};

    // バイナリ + 出力モードでストリームを開く
    std::ofstream ofs("nums.bin", std::ios::binary | std::ios::out);
    if(!ofs) {
        return 1;
    }

    const auto size = sizeof(int) * nums.size();  // int のサイズ * 配列要素数

    // 配列の先頭から配列全体のサイズ分をファイルに書き込む
    // 先頭ポインタはキャストが必要
    // const char*型への変換はStrict Aliasing Rulesに反しない
    ofs.write(reinterpret_cast<const char *>(nums.data()), size);

    return 0;
}
```

??? question "Strict Aliasing Rules"
    ポインタがどう使われているかコンパイラが解析することは極めて困難なため、最適化を行いやすくするために定められた規則の一つです。  
    もう少し言うとどのようなとき2つの変数が実際には同じメモリ位置を参照するかもしれないと仮定すべきかが定められています。  
    特に `reinterpret_cast` を用いるとき、Strict Aliasing Rulesに十分注意する必要があります。規則に反すれば未定義動作になります。

    - [（翻訳）C/C++のStrict Aliasingを理解する または - どうして#$@##@^%コンパイラは僕がしたい事をさせてくれないの！ - yohhoyの日記](https://yohhoy.hatenadiary.jp/entry/20120220/p1)
    - [C++20規格書 [basic.lval#11]](https://timsong-cpp.github.io/cppwp/n4861/basic.lval#11)

    このルールの判定は実際にメモリーへのアクセスが行われたタイミングでどう振る舞うかというものであり、単一のキャストだけで判断できるものでは有りません。  
    例えば次のコードは、 `A` と `B` という全く関係のない型へのポインタを変換しようとしています。しかしキャストしているだけではStrict Aliasing Rulesに反していません  
    このあと実際に変数 `b` にアクセスしたときに違反し、未定義動作となります。

    ```cpp
    class A {};
    class B {};

    A a;
    B* b = reinterpret_cast<B*>(&a);
    ```

    よくあるStrict Aliasing Rulesを破っているコードの例を示します。これはネットワーク通信などでよく見られるエンディアンを変換しようとするコードです。  
    32bitのストレージを16bitごとに区切ってswapしようと試みていますが、未定義動作を踏んでいます。

    ```cpp
    #include <cstdint>
    #include <iostream>
    #include <iomanip>
    using std::uint32_t;
    using std::uint16_t;
    uint32_t swaphalves(uint32_t a) {
        uint32_t acopy=a;
        uint16_t *ptr=reinterpret_cast<uint16_t*>(&acopy);// ptrはacopyのaliasにならない
        uint16_t tmp=ptr[0];
        ptr[0]=ptr[1];// Undefined Behavior: ptrへの変更操作があるがaliasではない
        ptr[1]=tmp;
        return acopy;
    }

    int main()
    {
        uint32_t a = 32;
        std::cout << std::hex << std::setfill('0') << std::setw(8) << a << std::endl;
        a = swaphalves(a);
        std::cout << std::setw(8) << a << std::endl;
    }
    ```

    Strict Aliasing Rulesを回避するには `std::memcpy` を用いるかC++20で追加された [`std::bit_cast`](https://cpprefjp.github.io/reference/bit/bit_cast.html) を用います
-----------------------------

ファイル: ./ch08-02-c-cast.md
-----------------------------
# C言語形式のキャスト

C++ は C言語と互換性があるため、`(型名)`でC言語形式のキャストも利用することができます。

```cpp
double dx = 3.14;
int x = (int)dx;
```

しかし、C言語形式のキャストでは、コードからキャストの意図が汲み取りにくい上、実装者の意に反したキャストを行ったとしてもコンパイルが通るため、不具合を生み出す要因になる可能性があります。

対して、C++ のキャスト演算子は用途に合わせて種類が分かれているため、意図が明確になる上、実装者の意に反したキャストをコンパイル時に検知することが可能です。

```cpp
int x = 100;
int* px = static_cast<int*>(x); // static_castの意図に反しているためコンパイルエラー
```

キャストの意図を明確にするために、C++ のキャスト演算子を使うようにしましょう。-----------------------------

ファイル: ./ch09-01-function-templates.md
-----------------------------
# 関数テンプレート

型やコンパイル時に定まる値をパラメータ化する機能をテンプレートといいます。
型に依存せず処理を共通化するために使用されます。

関数に対するテンプレートを関数テンプレートといいます。
関数テンプレートを定義するには次のようにします。

```cpp
template <typename T>
T Sum(T a, T b) {
    return a + b;
}
```

型をパラメータ化するには `typename` を使用します。
この例では `T` という型で2つの引数と戻り値をパラメータ化しています。
この関数テンプレートの関数を呼び出すには次のようにします。

```cpp
Sum<int>(1, 2);         // 3
Sum<double>(1.2, 3.4);  // 4.6
```

関数呼び出し時に `< ... >` で `T` の型を指定します。

## テンプレート実引数の省略

実引数から型パラメータ `T` を推論できる場合には
呼び出し時の `< ... >` を省略することができます。

```cpp
Sum(1, 2);      // 3
Sum(1.2, 3.4);  // 4.6
```

第1引数を `int` 、第2引数を `double` にすると `T` の型を推論できず、
呼び出し時の `< ... >` を省略した場合コンパイルエラーになります。

```cpp
Sum<double>(1, 2.3);  // 3.3
// Sum(1, 2.3);       // コンパイルエラー
```

## 複数のテンプレート引数

パラメータ化する型やコンパイル時に定まる値は
1つだけではなく複数にすることができます。

戻り値を `double` に固定して第1引数と第2引数を
パラメータ化するには次のようにします。

```cpp
template <typename T, typename U>
double Sum(T a, U b) {
    return a + b;
}
```

この場合には次の関数呼び出しもコンパイルエラーにはなりません。

```cpp
Sum(1, 2.3);  // 3.3
```

## 戻り値の型推論

パラメータ化した引数の型から戻り値の型を推論するには `decltype` を使用します。

```cpp
template <typename T, typename U>
auto Sum(T a, U b) -> decltype(a + b) {
    return a + b;
}
```

## コンパイル時に定まる値のパラメータ化

テンプレートでは型だけではなく
コンパイル時に定まる値をパラメータ化することができます。
コンパイル時に定まる値として配列のサイズなどを指定することができます。

```cpp hl_lines="1 3"
template <int N>
int Fibonacchi() {
    int a[N + 1];
    a[0] = 0;
    a[1] = 1;
    for (auto i = 2; i <= N; ++i) {
        a[i] = a[i - 1] + a[i - 2];
    }
    return a[N];
}
```

この例は [フィボナッチ数] を計算する処理です。
次のように呼び出すことで値を計算することができます。

```cpp
Fibonacchi<10>();  // 55
```

[フィボナッチ数]: https://ja.wikipedia.org/wiki/フィボナッチ数
-----------------------------

ファイル: ./ch09-02-class-templates.md
-----------------------------
# クラステンプレート

クラスに対するテンプレートをクラステンプレートといいます。
クラステンプレートを定義するには次のようにします。

```cpp
template <typename T>
class Rectangle {
 public:
    Rectangle(T height, T width) : height_(height), width_(width) {}

    T Area() const {
       return height_ * width_;
    }

 private:
    const T height_;
    const T width_;
};
```

クラステンプレートのクラスのオブジェクトを生成するには次のようにします。

```cpp
Rectangle<int> r1(10, 20);
Rectangle<double> r2(1.2, 3.4);
```

クラステンプレートではテンプレート実引数を省略することはできません。

テンプレート引数が必要なのはオブジェクト生成時のみで、
生成後は通常のクラスと同様に使用することができます。

```cpp
r1.Area();  // 200
r2.Area();  // 4.08
```

## 複数のテンプレート引数

パラメータ化する型やコンパイル時に定まる値は
クラステンプレートでも複数にすることができます。

```cpp
template <typename T, typename U>
class Rectangle {
 public:
    Rectangle(T height, U width) : height_(height), width_(width) {}

    double Area() const {
       return height_ * width_;
    }

 private:
    const T height_;
    const U width_;
};
```

この例ではメンバ関数 `Area()` の戻り値を `double` に固定して
テンプレート引数を2つにしています。

## メンバ関数の戻り値の型推論

クラステンプレートでメンバ関数の戻り値の型を推論するには
`decltype` 内で `std::declval` を使用します。

```cpp hl_lines="6"
template <typename T, typename U>
class Rectangle {
 public:
    Rectangle(T height, U width) : height_(height), width_(width) {}

    auto Area() const -> decltype(std::declval<T>() * std::declval<U>()) {
        return height_ * width_;
    }

 private:
    const T height_;
    const U width_;
};
```

## コンパイル時に定まる値のパラメータ化

コンパイル時に定まる値のパラメータ化はクラステンプレートでも使用できます。

```cpp
template <typename T, int N>
class Array {
 public:
    int size() const {
       return N;
    }

    T data_[N];
};
```
-----------------------------

ファイル: ./ch09-03-template-specializations.md
-----------------------------
# 特殊化

テンプレートでは実引数に応じて関数やクラスを生成します。

```cpp
// 関数テンプレート
template <typename T>
T Sum(T a, T b) {
    return a + b;
}

// 関数テンプレートの関数の呼び出し
Sum<int>(1, 2);
```

`Sum<int>(1, 2)` という関数テンプレートの関数の呼び出しによって
`T` が `int` である関数が必要と判断され、次の関数が生成されます。

```cpp
int Sum(int a, int b) {
    return a + b;
}
```

このようにテンプレートを使用する箇所において、
関数テンプレートから関数を生成することおよび
クラステンプレートからクラスを生成することを特殊化 (または暗黙的インスタンス化) といいます。

特殊化はコンパイラによって行われるため、
ヘッダファイルで関数テンプレートを使用する場合にはそのヘッダファイルで定義も行います。

=== "sum.h"

    ```cpp
    #ifndef SUM_H_
    #define SUM_H_

    template <typename T>
    inline T Sum(T a, T b) {  // inline 指定が必要
        return a + b;
    }

    #endif  // SUM_H_
    ```

=== "main.cc"

    ```cpp
    #include <iostream>

    #include "sum.h"

    int main() {
        std::cout << Sum(1, 2) << std::endl;
        return 0;
    }
    ```

??? question "テンプレートの明示的インスタンス化とextern template"
    ヘッダーファイルなどのテンプレートを使用する箇所で関数やクラスを生成すると、
    コンパイル速度が低下してしまいます。
    ヘッダファイルでは宣言だけ行い、ソースファイルで明示的に関数やクラスを生成することで
    予めtemplateを実体化できるのでコンパイル速度が向上します。

    === "sum.h"

        ```cpp
        #ifndef SUM_H_
        #define SUM_H_

        template <typename T>
        T Sum(T a, T b);  // 宣言だけ行う (inline もつけない)

        #endif  // SUM_H_
        ```

    === "sum.cc"

        ```cpp
        #include "sum.h"

        // 関数テンプレートの定義
        template <typename T>
        T Sum(T a, T b) {
            return a + b;
        }

        // 明示的インスタンス化
        template int Sum<int>(int, int);
        ```

    こうした構成にすると使用可能な型はソースファイルで明示的な生成を行う型のみとなってしまいます。
    たとえば `Sum<double>(double, double)` は生成されていないため
    `Sum(1.2, 3.4)` のように関数テンプレートの関数を呼び出すとリンクエラーになります。
    かといって明示的なインスタンス化を増やしていくと、それを共有ライブラリにすることを考えた場合、
    ライブラリサイズが肥大化してしまいます。

    こうした問題を避けるためには、extern templateを利用します。
    通常通りヘッダファイルでtemplate関数/クラスの定義を行うのですが
    実体化する頻度が高いものだけをexternし、ソースファイルで実体化させます

    === "sum.h"

        ```cpp
        #ifndef SUM_H_
        #define SUM_H_

        // 関数テンプレートの定義
        template <typename T>
        T Sum(T a, T b) {
            return a + b;
        }

        //暗黙的実体化を阻止
        extern template int Sum<int>(int, int);
        #endif  // SUM_H_
        ```

    === "sum.cc"

        ```cpp
        #include "sum.h"

        //よく使うものだけ実体化させる
        template int Sum<int>(int, int);
        ```

## 完全特殊化

関数テンプレートやクラステンプレートでは、すべてのパラメータが確定した時に別の定義を書くことができます。
これによって特定のテンプレート引数に対する挙動を変更することができます。
これを完全特殊化 (または明示的特殊化) といいます。

関数テンプレートの完全特殊化は次のようにします。

```cpp hl_lines="6 7 8 9"
template <typename T>
T DoSomething(T a, T b) {
    return a + b;
}

template <>
double DoSomething<double>(double a, double b) {
    return a * b;
}

std::cout << DoSomething(2, 3) << std::endl;  // 5
std::cout << DoSomething(2.0, 3.0) << std::endl;  // 6
```

関数の前に `template <>` を付けて完全特殊化を行うことを指定し、
関数名の後に `< ... >` で対象となるテンプレート引数を指定します。

クラステンプレートの完全特殊化も同様です。

```cpp hl_lines="21 22"
template <typename T>
class Array {
 public:
    explicit Array(int size)
        : size_(size),
          data_(new T[size_]) {}

    ~Array() {
        delete[] data_;
    }

    int Size() const {
        return size_;
    }

 private:
    const int size_;
    T* data_;
};

template <>
class Array<bool> {
 public:
    explicit Array(int size)
        : size_(size),
          data_size_((size - 1) / 8 + 1),
          data_(new uint8_t[data_size_]) {}

    ~Array() {
        delete[] data_;
    }

    int Size() const {
        return size_;
    }

 private:
    const int size_;
    const int data_size_;
    uint8_t* data_;
};
```

この例では8個の `bool` 値を1個の `uint8_t` で扱って省メモリ化するために、
`bool` に対する完全特殊化を行っています。

## 部分特殊化

クラステンプレートの一部のテンプレート引数を確定させたり、制限することができます。これを部分特殊化といいます。

詳細は
[テンプレートの部分特殊化 - cppreference.com][cppreference_partial_specialization]
    
を参照してください。

[cppreference_partial_specialization]: https://ja.cppreference.com/w/cpp/language/partial_specialization

??? question "関数テンプレートを部分特殊化したいとき"
    部分特殊化はクラステンプレートに対してのみ行なえます。しかし関数テンプレートに対しても行いたいことがあります。  
    その場合はSFINAE(Substitution Failure Is Not An Error)を利用した書き方をします
    
    ```cpp
    template <bool cond, typename T>
    using enable_if_t = typename std::enable_if<cond, T>::type;
    template <typename T, enable_if_t<(なんか条件式), std::nullptr_t> = nullptr>
    void foo(T t) {}
    template <typename T, enable_if_t<!(なんか条件式), std::nullptr_t> = nullptr>
    void foo(T t) {}
    ```
    
    [std::enable_ifを使ってオーバーロードする時、enablerを使う？ - Qiita](https://qiita.com/kazatsuyu/items/203584ef4cb8b9e52462)
    
    あるいはC++17で追加された[constexpr if 文](https://cpprefjp.github.io/lang/cpp17/if_constexpr.html)を利用することができます。
-----------------------------

ファイル: ./ch10-01-exceptions.md
-----------------------------
# 例外処理

例外処理とはプログラム実行中にエラーが発生した場合に、
後続の処理を行うのをやめてエラー発生時用の処理を行うための機能です。

!!! warning "コーディング規約による例外処理の使用禁止"
    C++ における例外処理は問題点が多く、
    [Google C++ Style Guide] や [LLVM Coding Standards] では例外処理の使用を原則禁止しています。

[Google C++ Style Guide]: https://google.github.io/styleguide/cppguide.html#Exceptions
[LLVM Coding Standards]: http://llvm.org/docs/CodingStandards.html#do-not-use-rtti-or-exceptions

例外処理においてエラーを表すもの例外といいます。
例外処理は次の2つの段階で構成されます。

1. エラーが発生する箇所で例外を送出し、後続の処理を行うのをやめる
1. 送出された例外を捕捉し、エラー発生時用の処理を行う

正の整数を表す `std::string` を `int` に変換する処理において、
無効な文字があった場合に変換処理をやめてエラーメッセージを出力するには
次のようにします。

```cpp hl_lines="2 18 19 23 24 25 26"
std::string str = "123XY56";
try {
    int num = 0;
    for (const auto s : str) {
        num *= 10;
        switch (s) {
            case '0':  num += 0;  break;
            case '1':  num += 1;  break;
            case '2':  num += 2;  break;
            case '3':  num += 3;  break;
            case '4':  num += 4;  break;
            case '5':  num += 5;  break;
            case '6':  num += 6;  break;
            case '7':  num += 7;  break;
            case '8':  num += 8;  break;
            case '9':  num += 9;  break;
            default:
                // コンストラクタの引数でエラーメッセージを設定
                throw std::runtime_error("数値ではない文字が入っています");
        }
    }
    std::cout << num << std::endl;  // 問題なく変換できた場合には変換後の値を出力
} catch (const std::runtime_error& e) {
    // what() でエラーメッセージを取得
    std::cout << e.what() << std::endl;
}
```

例外の送出は `throw` で行います。

この例では数値ではない文字がある場合にエラーとして
例外 `std::runtime_error` を送出し、
残っている文字の変換処理は行わずにエラー発生時用の処理を行います。

`try` ブロック内で送出した例外は `catch` ブロックで捕捉します。

この例では例外 `std::runtime_error` が送出された場合に
参照 `e` で受けて `e.what()` でエラーメッセージを取得して出力します。

## 例外の型

例外にはあらゆる型が使用できます。

```cpp
try {
    throw 123;
} catch (const int v) {
    std::cout << v << std::endl;
}
```

通常は標準ライブラリの例外クラスやそれを継承したユーザ定義クラスを使用します。

## 型に応じた捕捉

1つの `try` ブロックに対して `catch` ブロックは複数記述することができます。
これによって例外の型に応じた処理を行うことができます。

```cpp
try {
    throw 123;  // int を送出
} catch (const bool v) {  // int は bool とは異なる型であるため捕捉されない
    std::cout << "bool: " << v << std::endl;
} catch (const int v) {  // ここで捕捉される
    std::cout << "int: " << v << std::endl;
}
```

例外の型がクラスである場合にはアップキャストを含めて捕捉は行われます。
捕捉は上から順に確認して最初に一致したものだけが処理されます。

```cpp
try {
    throw std::runtime_error("test");  // std::runtime_error を送出
} catch (const std::exception& e) {
    // std::runtime_error は std::exception の派生クラスであるためここで捕捉される
    std::cout << "std::exception: " << e.what() << std::endl;
} catch (const std::runtime_error& e) {
    // この処理は実行されない
    std::cout << "std::runtime_error: " << e.what() << std::endl;
}
```

`catch (...)` と記載することであらゆる例外を捕捉することができます。
この `catch` ブロックでは例外オブジェクトを参照することができません。

```cpp
try {
    throw 123;
} catch (...) {
    std::cout << "Unexpected exception was thrown." << std::endl;
}
```

## 関数から例外を送出

関数内で例外が捕捉されない場合、
捕捉されるまで関数の呼び出し元を順に辿っていきます。

正の整数を表す `std::string` を `int` に変換する処理を関数化し、
無効な文字があった場合に関数から例外を送出するには次のようにします。

```cpp hl_lines="17"
int StringToInt(const std::string& str) {
    int num = 0;
    for (const auto s : str) {
        num *= 10;
        switch (s) {
            case '0':  num += 0;  break;
            case '1':  num += 1;  break;
            case '2':  num += 2;  break;
            case '3':  num += 3;  break;
            case '4':  num += 4;  break;
            case '5':  num += 5;  break;
            case '6':  num += 6;  break;
            case '7':  num += 7;  break;
            case '8':  num += 8;  break;
            case '9':  num += 9;  break;
            default:
                throw std::runtime_error("数値ではない文字が入っています");
        }
    }
    return num;
}
```

この関数内では例外を捕捉しないため `try` ブロックがありません。

呼び出し元で捕捉するためには次のようにします。

```cpp hl_lines="2 3 5"
std::string str = "123XY56";
try {
    auto num = StringToInt(str);
    std::cout << num << std::endl;
} catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
}
```

例外を送出するのは呼び出す関数の内部であるため、
この `try` ブロックには `throw` がありません。

1文字ずつの数値への変換処理を関数化すると、
例外が捕捉されるまでの間に関数呼び出しを2回遡ります。

!!! example "exception.cc"
    ```cpp linenums="1" hl_lines="17 18 27 28 36 37"
    #include <iostream>
    #include <string>

    int CharToInt(const char c) {
        switch (c) {
            case '0':  return 0;
            case '1':  return 1;
            case '2':  return 2;
            case '3':  return 3;
            case '4':  return 4;
            case '5':  return 5;
            case '6':  return 6;
            case '7':  return 7;
            case '8':  return 8;
            case '9':  return 9;
            default:
                // 関数から例外を送出
                throw std::runtime_error("数値ではない文字が入っています");
        }
    }

    int StringToInt(const std::string& str) {
        int num = 0;
        for (const auto s : str) {
            num *= 10;

            // CharToInt から例外が送出される
            num += CharToInt(s);
        }
        return num;
    }

    int main() {
        std::string str = "123XY56";
        try {
            // StringToInt 内部の CharToInt から例外が送出される
            auto num = StringToInt(str);

            std::cout << num << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }

        return 0;
    }
    ```

## 例外が捕捉されない場合

送出された例外が捕捉されない場合、
[std::terminate][cpprefjp_terminate] が呼び出されてプログラムが異常終了します。

```cpp hl_lines="3"
int main() {
    std::string str = "123XY56";
    auto num = StringToInt(str);
    std::cout << num << std::endl;
    return 0;
}
```

## noexcept

関数が例外を送出しないことを明示的に表すには `noexcept` をつけます。
デストラクタは暗黙的に `noexcept` になります。

<!-- MEMO: delete 演算子もデフォルトで noexcept になる -->

```cpp
int Compare(int a, int b) noexcept {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {  // a == b
        return 0;
    }
}
```

`noexcept` には条件を指定することができます。

```cpp
int Compare(int a, int b) noexcept(true);  // 例外を送出しない
int CharToInt(const char c) noexcept(false);  // 例外を送出する
```

`noexcept` 内で `noexcept` を使用すると、
他の関数が `noexcept` であるかどうかを条件に指定することができます。

```cpp
int StringToInt(const std::string& str) noexcept(noexcept(CharToInt(char())));
```

`noexcept` 指定された関数から例外が送出された場合、
[std::terminate][cpprefjp_terminate] が呼び出されてプログラムが異常終了します。

!!! warning "非推奨の動的例外仕様"
    関数から送出される例外を列挙するための `throw` というキーワードがありますが、
    C++11 では非推奨となっており C++17 では削除されているため使用しないでください。

    ```cpp
    int CharToInt(const char c) throw(std::runtime_error);
    ```

    詳細は
    [非推奨だった古い例外仕様を削除 - cpprefjp C++日本語リファレンス][cpprefjp_dynamic_exception_specification]
    を参照してください。

[cpprefjp_dynamic_exception_specification]: https://cpprefjp.github.io/lang/cpp17/remove_deprecated_exception_specifications.html

## 標準ライブラリの例外クラス

標準ライブラリの例外クラスの一部を紹介します。

一覧は [std::exception - cppreference.com][cppreference_exception] を参照してください。

[cppreference_exception]: https://ja.cppreference.com/w/cpp/error/exception

![クラス図][class-diagram]

[class-diagram]: img/exception_class.svg

!!! question "std::logic_error と std::runtime_error の違い"
    一般に
    プログラム実行前に検出可能なものは `std::logic_error`、
    プログラム実行時にのみ検出可能なものは `std::runtime_error` として分類されています。

### std::exception

すべての標準ライブラリの例外クラスの基底クラスです。

このクラスで例外を捕捉することにより、
標準ライブラリの例外クラスをすべて捕捉することができます。

```cpp
int main() {
    std::string str = "123XY56";
    try {
        auto num = StringToInt(str);  // std::runtime_error を送出
        std::cout << num << std::endl;
    } catch (const std::exception& e) {
        // std::exception で std::runtime_error を捕捉
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

### std::logic_error

前提条件を満たしていないなど論理エラーを表すためのクラスです。

標準ライブラリで `std::logic_error` を送出するものはありません。

### std::invalid_argument

関数の実引数が不正な値である場合の論理エラーを表すためのクラスです。

`std::bitset` で変換できない文字列を指定した場合などに送出されます。

```cpp
try {
    std::bitset<8> b("0000x111");  // 不正な文字 x を含んでいる
    std::cout << b << std::endl;
} catch (const std::invalid_argument& e) {
    std::cout << "std::invalid_argument を捕捉" << std::endl;
    std::cout << e.what() << std::endl;
}
```

`std::bitset` では文字列から2進数数値への変換処理をコンストラクタで行っています。
一般にコンストラクタには戻り値がないため、戻り値によってエラー有無を判断することができません。
そのためコンストラクタでエラーが発生した場合には、例外を送出するものがあります。

### std::out_of_range

配列のようなデータに対する要素参照で
範囲外が指定された場合の論理エラーを表すためのクラスです。

`std::vector` の `at()` で範囲外の要素を参照しようとした場合などに送出されます。

```cpp
std::vector<int> x = {1, 2, 3, 4, 5};  // 要素数が 5 のベクタ

try {
    int a = x.at(5);  // at() で要素参照
    std::cout << "5番目の値: " << a << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "std::out_of_range を捕捉" << std::endl;
    std::cout << e.what() << std::endl;
}
```

`std::vector` の `[]` で範囲外の要素を参照しようとした場合には例外は送出されません。

```cpp
std::vector<int> x = {1, 2, 3, 4, 5};  // 要素数が 5 のベクタ

try {
    int a = x[5];  // [] で要素参照
    std::cout << "5番目の値: " << a << std::endl;  // 不定値が出力される
} catch (...) {
    std::cout << "例外を捕捉" << std::endl;  // 例外は送出されないため実行されない
}
```

!!! question "セグメンテーション違反"
    この例で `[]` で範囲外の要素参照をする際に
    セグメンテーション違反が発生して OS によってプログラムが終了される可能性もあります。

<!-- TODO: 追加予定のシグナルのページへのリンクを貼る -->

### std::runtime_error

実行時に評価する値の不正や実行環境の問題など
実行時エラーを表すためのクラスです。

<!-- TODO: std::locale 以外での例を追加する -->

### std::bad_cast

`dynamic_cast` で失敗した場合に送出されます。
`dynamic_cast` の詳細については [ダウンキャスト][downcasts] を参照してください。

[downcasts]: appendix-downcasts.md

## デストラクタと例外

例外を送出して捕捉するまでの間に、
さらに例外を送出すると [std::terminate][cpprefjp_terminate] が呼び出されて
プログラムが異常終了します。
この事象はデストラクタから例外を送出すると発生します。

例外を送出した場合、
その例外が捕捉されるまでに生存期間が終了するオブジェクトは
デストラクタを呼び出して破棄されます。

```cpp hl_lines="6 7 14 16"
#include <iostream>

class DestructorAndException {
 public:
    ~DestructorAndException() {
        // 例外を送出して捕捉するまでの間に実行される
        std::cout << "~DestructorAndException() is called." << std::endl;
    }
};

int main() {
    try {
        DestructorAndException obj;
        throw std::runtime_error("main()");
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

デストラクタから例外を送出すると、
「例外を送出して捕捉するまでの間に、さらにデストラクタから例外を送出する」ことになってしまい、
[std::terminate][cpprefjp_terminate] が呼び出されてプログラムが異常終了します。

```cpp hl_lines="10 11"
#include <iostream>

class DestructorAndException {
 public:
    // デストラクタは暗黙的に noexcept になるため noexcept(false) を明示的に指定
    ~DestructorAndException() noexcept(false) {
        // 例外を送出して捕捉するまでの間に実行される
        std::cout << "~DestructorAndException() is called." << std::endl;

        // さらに例外を送出
        throw std::runtime_error("~DestructorAndException()");
    }
};

int main() {
    try {
        DestructorAndException obj;
        throw std::runtime_error("main()");
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

こうした挙動にならないように、
一般にデストラクタからは例外を送出しないようにします。

[cpprefjp_terminate]: https://cpprefjp.github.io/reference/exception/terminate.html
-----------------------------

ファイル: ./ch10-02-signals.md
-----------------------------
# シグナル

シグナルとはプログラム実行中に外部から要求を通知する仕組みです。
OS からのエラー通知などで使用されます。

`<csignal>` で定義されるシグナルには以下の6種類があります。

* SIGABRT
* SIGFPE
* SIGILL
* SIGINT
* SIGSEGV
* SIGTERM

一部を紹介します。

## SIGABRT

[std::abort][cpprefjp_abort] の呼び出しによって発生します。

[std::abort][cpprefjp_abort] は
[std::terminate][cpprefjp_terminate] などから呼び出されます。

```cpp
#include <exception>

int main() {
    // 例外が捕捉されないため std::terminate が呼び出される
    throw std::exception();

    return 0;
}
```

[cpprefjp_abort]: https://cpprefjp.github.io/reference/cstdlib/abort.html
[cpprefjp_terminate]: https://cpprefjp.github.io/reference/exception/terminate.html

## SIGFPE

整数の0除算など不正な算術演算を行うと発生します。

```cpp
int x = 2;
int y = 0;
int z = x / y;  // 整数の0除算
```

!!! note "浮動小数点数に対する算術演算エラー"
    多くの処理系では浮動小数点数の規格として [IEEE 754] が使用されており、
    以下を値として使用することができます。

    * 非数 `NaN`
    * 符号付ゼロ ($+0$ と $-0$)
    * 無限大 ($+\infty$ と $-\infty$)

    こうした処理系では浮動小数点数の演算結果でこれらの値を使用し、
    浮動小数点数のシグナルを発生させないようにしている場合が多いです。

[IEEE 754]: https://ja.wikipedia.org/wiki/IEEE_754

<!-- MEMO: シグナルが発生しない場合でも <cfenv> を利用することで検知可能
https://ja.cppreference.com/w/cpp/numeric/fenv
-->

## SIGSEGV

無効なメモリアクセス (セグメンテーション違反) を行うと発生します。

```cpp
int* x = nullptr;

// nullptr に対するデリファレンスで SIGSEGV が発生
std::cout << *x << std::endl;
```
-----------------------------

ファイル: ./ch10-03-assertions.md
-----------------------------
# アサーション

## assert

実行時に条件を満たさないと
[std::abort][cpprefjp_abort] を呼び出してプログラムを異常終了させる処理です。

`assert` を使用するには `<cassert>` のインクルードが必要です。

[cpprefjp_abort]: https://cpprefjp.github.io/reference/cstdlib/abort.html

```cpp linenums="1" hl_lines="7"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

int Max(const std::vector<int>& v) {
    assert(!v.empty());

    int max = std::numeric_limits<int>::min();
    for (auto e : v) {
        if (e > max) {
            max = e;
        }
    }
    return max;
}

int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2;

    std::cout << Max(v1) << std::endl;
    std::cout << Max(v2) << std::endl;

    return 0;
}
```

実行結果は次のようになります。

```bash
$ ./a.exe
5
assertion "!v.empty()" failed: file "main.cc", line 7, function: int Max(const std::vector<int>&)
Aborted (コアダンプ)
```

`assert` は開発中にバグを取り除くことを想定した機能で、 `NDEBUG` が定義されるリリースビルドでは無効となります。
`NDEBUG` を定義するには `-DNDEBUG` を指定します。

```bash
$ g++ -std=c++11 -DNDEBUG main.cc
```

`NDEBUG` を定義してビルドすると実行結果は次のように変化します。

```bash
$ ./a.exe
5
-2147483648
```

## static_assert

コンパイル時に条件を満たさないとコンパイルエラーにする処理です。

```cpp
template <typename T, int N>
class Array {
    static_assert(N > 0, "サイズは0より大きくなければなりません");

 public:
    int size() const { return N; }

    T data_[N];  // サイズ 0 の配列はコンパイルエラーにならない
};

int main() {
    Array<int, 0> a;
    return 0;
}
```

コンパイル結果は以下のようになります。

```bash
$ g++ -std=c++11 -c main.cc
main.cc: In instantiation of ‘class Array<int, 0>’:
main.cc:12:19:   required from here
main.cc:3:5: エラー: static assertion failed: サイズは0より大きくなければなりま
せん
     static_assert(N > 0, "サイズは0より大きくなければなりません");
     ^~~~~~~~~~~~~
```
-----------------------------

ファイル: ./ch11-01-build.md
-----------------------------
# ビルド

!!! info "説明に使用する環境"
    Windows の MSYS2 環境は構成が複雑なため、説明では Linux 環境を使用します。

ソースファイルから実行ファイルを生成する処理をビルドといいます。
ビルドは次の手順で行われます。

1. プリプロセス
1. コンパイル
1. リンク

## プリプロセス

プリプロセスはコンパイル前に行われる前処理のことです。
コメントの削除と [プリプロセッサ司令] の実行を行います。

[プリプロセッサ司令]: appendix-preprocessor-directives.md

`-E` を指定するとプリプロセスだけを行うことができます。

```bash
$ g++ -std=c++11 -E main.cc
```

## コンパイル

人間が扱うソースファイルをコンピュータで扱うために0と1の表現 (機械語) に変換することをコンパイルといいます。
コンパイルはソースファイル単位で行います。

厳密にはコンパイルを行うプログラムのことをコンパイラといいますが、
コンパイル以外のビルド処理もコンパイラによって提供されるのが一般的です。

ソースファイルを機械語に変換した結果はオブジェクトファイルと呼ばれます。
コンパイルだけ実行するには `-c` を指定します。

```bash
$ g++ -std=c++11 -c main.cc
$ g++ -std=c++11 -c util.cc
```

このコマンドを実行すると
`main.cc` から `main.o`、 `util.cc` から `util.o` へコンパイルされます。

コンパイルだけでは実行ファイルは生成されません。

## リンク

オブジェクトファイルなどをまとめて実行ファイルを生成することをリンクといいます。
リンクを行うプログラムはリンカといいます。

`main.o` と `util.o` をリンクして実行ファイルを生成するには次のようにします。

```bash
$ g++ -std=c++11 main.o util.o
```

コンパイル時点ではソースファイルを1つずつ処理するため、
ソースファイル内で定義されていない関数や変数に対しては未定義であるという情報がオブジェクトファイルに格納されます。
リンクではこうした未定義の関数や変数の定義を他のオブジェクトファイルなどから探して対応付けを行います。

たとえば以下のコードの関数 `Sum` は `main.cc` ではプロトタイプ宣言だけで定義がないため、
`main.o` には `Sum` が未定義であるという情報が格納されます。

=== "main.cc"

    ```cpp
    int Sum(int a, int b);

    int main() {
        Sum(1, 2);
        return 0;
    }
    ```

=== "util.cc"

    ```cpp
    int Sum(int a, int b) {
        return a + b;
    }
    ```

`Sum` は `util.cc` で定義が行われているため、
`main.o` から実行ファイルを生成するには `util.o` が必要となります。
次のように `main.o` だけでリンクを行うと `main.o` で未定義の `Sum` を定義と対応付けできずエラーとなります。

```bash
$ g++ -std=c++11 main.o
main.o: 関数 `main' 内:
main.cc:(.text+0xf): `Sum(int, int)' に対する定義されていない参照です
collect2: error: ld returned 1 exit status
```
-----------------------------

ファイル: ./ch11-02-static-libraries-and-static-linking.md
-----------------------------
# 静的ライブラリと静的リンク

!!! info "説明に使用する環境"
    Windows の MSYS2 環境は構成が複雑なため、説明では Linux 環境を使用します。

複数のオブジェクトファイルを1つのファイルにまとめ、
リンク時にオブジェクトファイルの代わりとして使用することができます。
複数のオブジェクトファイルをまとめたファイルを静的ライブラリといい、
そのファイルをリンクすることを静的リンクといいます。

次のコードで説明します。

=== "main.cc"

    ```cpp linenums="1"
    int Add(int a, int b);
    int Sub(int a, int b);

    int main() {
        Add(1, 2);
        Sub(3, 4);
        return 0;
    }
    ```

=== "add.cc"

    ```cpp linenums="1"
    int Add(int a, int b) {
        return a + b;
    }
    ```

=== "sub.cc"

    ```cpp linenums="1"
    int Sub(int a, int b) {
        return a - b;
    }
    ```

`add.cc` と `sub.cc` をコンパイルして生成される
2つのオブジェクトファイル `add.o` と `sub.o` から
静的ライブラリ `libhoge.a` を作成するには下記コマンドを実行します。

```bash
$ ar rc libhoge.a add.o sub.o
```

`ar` はアーカイブを操作するコマンドです。
`rc` でアーカイブを作成してファイルを追加するという指定をします。

作成したアーカイブの内容は下記コマンドで確認できます。

```bash
$ ar t libhoge.a
add.o
sub.o
```

`libhoge.a` を静的リンクするには下記コマンドを実行します。

```bash
$ g++ -std=c++11 main.o libhoge.a
```
-----------------------------

ファイル: ./ch11-03-dynamic-libraries-and-dynamic-linking.md
-----------------------------
# 動的ライブラリと動的リンク

!!! info "説明に使用する環境"
    Windows の MSYS2 環境は構成が複雑なため、説明では Linux 環境を使用します。

実行に必要な処理の一部を分割して外部ファイルにしておき、実行時に結合することができます。
これはビルド時に依存関係の設定だけを行い、実行時に解決することで実現されます。
この外部ファイルを動的ライブラリといい、
そのファイルをリンクして依存関係を設定することを動的リンクといいます。

次のコードで説明します。

=== "main.cc"

    ```cpp linenums="1"
    int Add(int a, int b);
    int Sub(int a, int b);

    int main() {
        Add(1, 2);
        Sub(3, 4);
        return 0;
    }
    ```

=== "add.cc"

    ```cpp linenums="1"
    int Add(int a, int b) {
        return a + b;
    }
    ```

=== "sub.cc"

    ```cpp linenums="1"
    int Sub(int a, int b) {
        return a - b;
    }
    ```

`add.cc` と `sub.cc` をコンパイルして生成される
2つのオブジェクトファイル `add.o` と `sub.o` から
動的ライブラリ `libhoge.so` を作成するには下記コマンドを実行します。

```bash
$ g++ -std=c++11 -shared -o libhoge.so add.o sub.o
```

`-shared` をつけることで動的ライブラリの生成が行われます。
生成する動的ライブラリのファイル名は `-o` で指定します。

`libhoge.so` を動的リンクするには下記コマンドを実行します。

```bash
$ g++ -std=c++11 main.o libhoge.so
```

動的ライブラリの子依存関係は `ldd` コマンドで確認できます。

```bash
$ ldd a.out
        linux-vdso.so.1 =>  (0x00007ffeacf68000)
        libhoge.so => ./libhoge.so (0x00007f86f4381000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f86f3fb7000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f86f4583000)
```

`libhoge.so => not found` と出力される場合は
`export LD_LIBRARY_PATH=.` を実行してください。

```bash hl_lines="3 6 9"
$ ldd a.out
        linux-vdso.so.1 =>  (0x00007ffc49540000)
        libhoge.so => not found
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007feb00b3e000)
        /lib64/ld-linux-x86-64.so.2 (0x00007feb00f08000)
$ export LD_LIBRARY_PATH=.
$ ldd a.out
        linux-vdso.so.1 =>  (0x00007ffeacf68000)
        libhoge.so => ./libhoge.so (0x00007f86f4381000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f86f3fb7000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f86f4583000)
```

依存関係は実行ファイルだけでなく動的ライブラリにも存在します。

```bash
$ ldd /lib/x86_64-linux-gnu/libc.so.6
        /lib64/ld-linux-x86-64.so.2 (0x00007f53f0153000)
        linux-vdso.so.1 =>  (0x00007fff235c4000)
```

このように依存関係は子依存だけでは完結せず、連鎖して発生します。

子依存がない場合は次のように出力されます。

```bash
$ ldd libhoge.so
        statically linked
```

??? question "-l オプションによるライブラリのリンク指定"
    ライブラリパスに配置されているライブラリは
    `-l` でライブラリ名称を用いてリンク指定できます。
    ライブラリパスは処理系で必要なパスがデフォルトで入っており、
    `-L` でユーザ指定パスを追加できます。
    ライブラリ名称は接頭辞 `lib` と拡張子をとったもので
    `libhoge.so` や `libhoge.a` なら `hoge` となります。

    `-l` でカレントディレクトリにある `libhoge.so` を動的リンクするには次のようにします。

    ```bash
    $ g++ -std=c++11 main.o -lhoge -L.
    ```

    動的ライブラリ `libhoge.so` がない場合には、
    同じコマンドで静的ライブラリ `libhoge.a` の静的リンクが行われます。
-----------------------------

ファイル: ./ch11-04-dynamic-loading-and-name-mangling.md
-----------------------------
# 動的ロードと名前マングリング

!!! info "説明に使用する環境"
    Windows の MSYS2 環境は構成が複雑なため、説明では Linux 環境を使用します。

動的ライブラリを動的リンクする代わりに、
プログラム実行中に動的ライブラリを読み込んで使用することもできます。
プログラム実行中に動的ライブラリを読み込むことを動的ロードといいます。

動的ロードは C++ の標準機能ではないため、処理系固有の処理が必要です。
Linux 環境で使用する API の詳細は
[Man page of DLOPEN - JM Project][linuxjm_dlopen] を参照してください。
また、これらの API で使用される void ポインタについては
[void ポインタ][void-pointer] を参照してください。

[linuxjm_dlopen]: https://linuxjm.osdn.jp/html/LDP_man-pages/man3/dlopen.3.html
[void-pointer]: appendix-void-pointer.md

次のコードで説明します。

=== "main.cc"

    ```cpp linenums="1"
    #include <iostream>

    #include <dlfcn.h>

    int main() {
        void* handle = dlopen("libhoge.so", RTLD_NOW);
        if (handle == NULL) {
            const char* const error_message = dlerror();
            std::cerr << error_message << std::endl;
            return 1;
        }

        void* const symbol_add = dlsym(handle, "_Z3Addii");
        {
            const char* const error_message = dlerror();
            if (error_message != NULL) {
                std::cerr << error_message << std::endl;
                dlclose(handle);
                return 1;
            }
        }

        void* const symbol_sub = dlsym(handle, "_Z3Subii");
        {
            const char* const error_message = dlerror();
            if (error_message != NULL) {
                std::cerr << error_message << std::endl;
                dlclose(handle);
                return 1;
            }
        }

        auto Add = reinterpret_cast<int(*)(int, int)>(symbol_add);
        auto Sub = reinterpret_cast<int(*)(int, int)>(symbol_sub);

        std::cout << Add(1, 2) << std::endl;
        std::cout << Sub(3, 4) << std::endl;

        dlclose(handle);
        return 0;
    }
    ```

=== "add.cc"

    ```cpp linenums="1"
    int Add(int a, int b) {
        return a + b;
    }
    ```

=== "sub.cc"

    ```cpp linenums="1"
    int Sub(int a, int b) {
        return a - b;
    }
    ```

## 動的ロード

`add.cc` と `sub.cc` をコンパイルして生成される
2つのオブジェクトファイル `add.o` と `sub.o` から
作成した動的ライブラリを `libhoge.so` とします。

Linux 環境で動的ロードを行うためには
OS が提供する `libdl.so` を動的リンクする必要があります。
`libdl.so` を動的リンクして実行ファイルをビルドするには `-ldl` をつけます。

```bash
g++ -std=c++11 main.o -ldl
```

動的ロードは以下の手順で行います。

1. 動的ライブラリを開く
1. 関数や変数のポインタを取得
1. 動的ライブラリを閉じる

### 動的ライブラリを開く

動的ライブラリを開くには `dlopen()` を使います。
動的ロードに関する処理を使うには `<dlfcn.h>` のインクルードが必要です。

```cpp
#include <iostream>

#include <dlfcn.h>

// 第1引数に動的ライブラリのファイル名を指定する
void* handle = dlopen("libhoge.so", RTLD_NOW);
if (handle == NULL) {
    const char* const error_message = dlerror();
    std::cerr << error_message << std::endl;
    return 1;
}
```

`dlopen()` でエラーが発生した場合は `NULL` が返却されます。
`dlerror()` では最後に使用された動的ロードの API でエラーがあった場合に、エラーメッセージを返却します。

動的ライブラリの探し方は動的リンクした場合と同様です。
以下のエラーメッセージが出力される場合は `export LD_LIBRARY_PATH=.` を実行してください。

```bash
$ ./a.out
libhoge.so: cannot open shared object file: No such file or directory
```

`dlopen()` が正常に終了した場合はハンドルが返却されます。
このハンドルを用いて動的ライブラリを操作します。

### 関数や変数のポインタを取得

`dlopen()` で取得したハンドルから
関数や変数のポインタを取得するには `dlsym()` を使用します。

`dlsym()` では第1引数にハンドル、第2引数にシンボル名を指定します。
シンボル名は `nm` コマンドで
オブジェクトファイルや動的ライブラリを指定して確認することができます。

```bash
$ nm add.o
0000000000000000 T _Z3Addii
$ nm sub.o
0000000000000000 T _Z3Subii
$ nm libhoge.so
0000000000200e88 d _DYNAMIC
0000000000201000 d _GLOBAL_OFFSET_TABLE_
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
0000000000000620 T _Z3Addii
0000000000000634 T _Z3Subii
00000000000006f8 r __FRAME_END__
0000000000000654 r __GNU_EH_FRAME_HDR
0000000000200e80 d __JCR_END__
0000000000200e80 d __JCR_LIST__
0000000000201020 d __TMC_END__
0000000000201020 B __bss_start
                 w __cxa_finalize
00000000000005b0 t __do_global_dtors_aux
0000000000200e78 t __do_global_dtors_aux_fini_array_entry
0000000000201018 d __dso_handle
0000000000200e70 t __frame_dummy_init_array_entry
                 w __gmon_start__
0000000000201020 D _edata
0000000000201028 B _end
0000000000000648 T _fini
00000000000004e0 T _init
0000000000201020 b completed.7594
0000000000000520 t deregister_tm_clones
00000000000005f0 t frame_dummy
0000000000000560 t register_tm_clones
```

この例では
`int Add(int a, int b)` は `_Z3Addii`、
`int Sub(int a, int b)` は `_Z3Subii` というシンボル名になっていることがわかります。

`dlsym()` で `int Add(int a, int b)` の関数ポインタを取得するには次のようにします。

```cpp
// 第1引数にハンドル、第2引数にシンボル名を指定
void* const symbol_add = dlsym(handle, "_Z3Addii");
{
    const char* const error_message = dlerror();
    if (error_message != NULL) {
        std::cerr << error_message << std::endl;
        dlclose(handle);
        return 1;
    }
}
```

`dlsym()` が正常に終了した場合にはそのシンボルのポインタが返却されます。
シンボルが関数なら関数ポインタとなります。

`dlsym()` でエラーが発生した場合は `NULL` が返却されますが、
正常に終了した場合の結果が `NULL` になることもあるため、エラーの有無は直後の `dlerror()` の結果で判断します。
`dlerror()` は最後に使用された動的ロードの API でエラーがなければ `NULL` を返却します。

`dlsym()` の戻り値は `void*` でそのまま使用できないためキャストが必要です。
関数であれば以下のようにキャストして使用します。

```cpp
auto Add = reinterpret_cast<int(*)(int, int)>(symbol_add);
std::cout << Add(1, 2) << std::endl;
```

### 動的ライブラリを閉じる

開いた動的ライブラリは使用が終わったら閉じる必要があります。
動的ライブラリを閉じるには `dlclose()` を使用します。

```cpp
dlclose(handle);
```

## 名前マングリング

オブジェクトファイルでは変数や関数を名前だけで識別する必要があります。

C 言語はリンケージ指定が内部リンケージではない変数や関数を名前だけで識別していますが、
C++ は C 言語にはない以下の機能によって名前だけで識別することができません。

- クラス
- 名前空間
- テンプレート
- 関数オーバーロード

この問題を解決するために、
識別に必要な情報をすべて名前に含めるなどして生成した一意な名前を使用しています。
これを名前マングリングといいます。

`int Add(int a, int b)` が `_Z3Addii` といったシンボル名になるのは名前マングリングの結果です。

名前マングリングを行う前の情報は `c++filt` コマンドで確認することができます。

```bash
$ nm add.o
0000000000000000 T _Z3Addii
$ nm add.o | c++filt
0000000000000000 T Add(int, int)
```

名前マングリングの方法はコンパイラ依存です。
同じコンパイラであってもバージョンが異なれば、名前マングリングの結果が一致する保証はありません。
具体例は [名前修飾 - コンパイラによる名前修飾の相違 - Wikipedia][name-mangling-diff] を参照してください。

[name-mangling-diff]: https://ja.wikipedia.org/wiki/名前修飾#コンパイラによる名前修飾の相違

名前マングリングを無効化することでコンパイラに依存せずにシンボル名を指定することができます。
名前マングリングを無効化するには宣言を `extern "C"` のブロックに含めます。
これは C 言語でリンク可能にするという指定で、
名前の重複を禁止する代わりに名前マングリングが行われなくなります。

```cpp
extern "C" {

int Add(int a, int b) {
    return a + b;
}

}
```

`extern "C"` のブロックで宣言された場合には、関数名がそのままシンボル名として使用されます。

```bash
$ nm add.o
0000000000000000 T Add
```

`dlsym()` も次のように関数名を指定することになります。

```cpp
void* const symbol_add = dlsym(handle, "Add");
```
-----------------------------

ファイル: ./ch11-05-library-updating-and-compatibility.md
-----------------------------
# ライブラリ更新と互換性

!!! info "説明に使用する環境"
    Windows の MSYS2 環境は構成が複雑なため、説明では Linux 環境を使用します。

ライブラリの更新があった場合に、
ライブラリを使用するプログラムで必要な作業は以下の項目で決まります。

- 静的ライブラリと動的ライブラリのどちらであるか
- 更新前後での API 互換性
- 更新前後での ABI 互換性

![ライブラリ更新で必要な手順を表した図][library_updating]
[library_updating]: img/library_updating.svg

## API 互換性

API はアプリケーションプログラミングインタフェースの略で、
ソースコードレベルでのインターフェースのことをいいます。
更新前のライブラリに存在する API を
更新後のライブラリでそのまま使用できる場合に API 互換性があるといいます。

API 互換性があれば
ライブラリを使用するプログラムのコード修正は必要ありません。

API の変化を伴わない以下のような変更は API 互換性があります。

- コメントの変更 (誤字修正など)
- ソースファイルに記述されている実装の変更 (リファクタリングやバグ修正など)

API の変化を伴う変更は、
次のように API 互換性のあるものとないものがあります。

- API 互換性のある変更
    - API の新規追加
    - 更新前の仕様を維持して API を変更 (拡張)
- API 互換性のない変更
    - API の削除
    - 更新前の仕様を維持せず API を変更

## 静的ライブラリと動的ライブラリ

!!! info "静的ライブラリ"
    ![静的ライブラリ][static_library]

静的ライブラリはライブラリを使用するプログラムに取り込まれるため、
ライブラリを使用するプログラムの再ビルドが必要です。

!!! info "動的ライブラリ"
    ![動的ライブラリ][dynamic_library]

動的ライブラリはライブラリを使用するプログラムに取り込まれないため、
ライブラリを使用するプログラムの再ビルドは不要です。
ただし、後述の ABI 互換性がない場合には再ビルドが必要となります。

[static_library]: img/static_library.svg
[dynamic_library]: img/dynamic_library.svg

## ABI 互換性

ABI はアプリケーションバイナリインタフェースの略で、
バイナリレベルでのインターフェースのことをいいます。
更新前のライブラリに存在する ABI を
更新後のライブラリでそのまま使用できる場合に ABI 互換性があるといいます。

ABI 互換性があれば
実行環境の動的ライブラリを変更するだけで動作します。

通常は
API の変更がなければ ABI 互換性があり、
API 互換性がなければ ABI 互換性はありません。

??? question "ABI のコンパイラ依存"
    ABI はコンパイラ依存です。

    同じコンパイラであってもバージョンが異なれば ABI 互換性はないことがあります。
    たとえば GCC 4.x と GCC 5.x ではデフォルトの ABI は互換性がありません。
    GCC 5.x では `_GLIBCXX_USE_CXX11_ABI` マクロを `0` に定義することで
    GCC 4.x と ABI 互換性があるようにビルドすることができます。
    詳細は [Dual ABI - The GNU C++ Library][gcc_dual_abi] を参照してください。

    一方で、異なるコンパイラ間でも ABI 互換性がある場合もあります。
    たとえば Clang でビルドしたライブラリを GCC で使用できることがあります。

[gcc_dual_abi]: https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html

API 互換性のある API の変更は、
次のように ABI 互換性のあるものとないものがあります。

- ABI 互換性のある変更
    - クラスに属さない関数や変数の追加
- ABI 互換性のない変更
    - クラスにデータメンバを追加 (オブジェクトのサイズ変更)
    - クラスのデータメンバの宣言順序を変更 (オブジェクトのメモリ配置変更)
    - 仮想関数の追加 (vtable のサイズ変更)

詳細は
[Policies/Binary Compatibility Issues With C++ - KDE Community Wiki][kde_abi]
を参照してください。

[kde_abi]: https://community.kde.org/Policies/Binary_Compatibility_Issues_With_C%2B%2B
-----------------------------

ファイル: ./ch12-01-type-for-bytes.md
-----------------------------
# バイトを表す型

C++ では以下の型のサイズが1バイトと規定されています。
C でも同様です。

- `char`
- `signed char`
- `unsigned char`

ビットを取り扱う際には符号なしであることが望ましいため、
バイトを表す型としては `unsigned char` を使用します。

??? warning "char は signed char とは異なる型"
    以下の型はすべて異なる型として扱われます。

    - `char`
    - `signed char`
    - `unsigned char`

    異なる型であるため、次のようなオーバーロードが可能です。

    ```cpp linenums="1"
    #include <iostream>

    void Hoge(char c) {
        std::cout << "char: " << c << std::endl;
    }

    void Hoge(signed char c) {
        std::cout << "signed char: " << c << std::endl;
    }

    void Hoge(unsigned char c) {
        std::cout << "unsigned char: " << c << std::endl;
    }

    int main() {
        Hoge('A');                              // char: A
        Hoge(static_cast<char>('B'));           // char: B
        Hoge(static_cast<signed char>('C'));    // signed char: C
        Hoge(static_cast<unsigned char>('D'));  // unsigned char: D
        return 0;
    }
    ```

    `char` は処理系で最も効率的に処理できる文字表現の型です。
    `char` のビット表現は `signed char` または `unsigned char`
    のいずれか一方と一致しますが、どちらと一致するかは処理系依存です。

??? question "C++17 で追加された std::byte"
    文字とバイトデータの用途を明確にするため、
    C++17 で [std::byte][cpprefjp_byte] という型が追加されました。

    C++17 の機能であるため C++11 では使用できません。

[cpprefjp_byte]: https://cpprefjp.github.io/reference/cstddef/byte.html

## 1バイトは8ビットとは限らない

2008年に発行された [IEC 80000-13][wikipedia_byte] にて
$1 byte = 8 bits$ と正式に定義されました。

[wikipedia_byte]: https://ja.wikipedia.org/wiki/バイト_(情報)

それ以前は
処理系が1つのアドレスで扱うビット数 (メモリ操作の最小単位) を
1バイトと定めることが多く、
$1 byte = 8 bits$ とは限らず
$1 byte = 7 bits$ や $1 byte = 9 bits$ となることもありました。

C や C++ では以下の制約によって $1 byte = 8 bits$ 以上と規定しています。

- `char` 型のサイズを1バイトとする
- `char` 型のビット数 [CHAR_BIT] は8ビット以上とする

[CHAR_BIT]: https://cpprefjp.github.io/reference/climits/char_bit.html

C や C++ では
$1 byte = 7 bits$ は許容されませんが、
$1 byte = 9 bits$ は許容されています。

実際には
$1 byte = 8 bits$ ではない処理系は非常に少ないため、
$1 byte = 8 bits$ だけを想定した実装にすることも多いです。

$1 byte = 8 bits$ しか想定していないことを表明する必要があれば
次のようにします。

```cpp
#include <climits>
static_assert(CHAR_BIT == 8, "Not support 1byte != 8bits");
```
-----------------------------

ファイル: ./ch12-02-plain-old-data.md
-----------------------------
# POD

POD (Plain Old Data) とは C と ABI 互換性が保証されるデータ構造のことです。

データ構造が POD であるかは [std::is_pod][cpprefjp_is_pod] で判定することができます。
`std::is_pod` を使用するには `<type_traits>` のインクルードが必要です。
データ構造を POD にしたい場合には `static_assert` で保証するとよいです。

[cpprefjp_is_pod]: https://cpprefjp.github.io/reference/type_traits/is_pod.html

```cpp
#include <type_traits>
struct FundamentalTypes {
    int16_t i;
    double d;
};
static_assert(std::is_pod<FundamentalTypes>::value, "Should be POD.");
```

## 基本型

基本型は POD です。

```cpp
enum Direction {
    kLeft,
    kRight,
    kBoth
};

static_assert(std::is_pod<char>::value, "Should be POD.");
static_assert(std::is_pod<int32_t>::value, "Should be POD.");
static_assert(std::is_pod<double>::value, "Should be POD.");
static_assert(std::is_pod<Direction>::value, "Should be POD.");
```

## 配列

POD の配列は POD です。

```cpp
static_assert(std::is_pod<int[2]>::value, "Should be POD.");
```

POD の `std::array` も POD ですが、
POD の `std::vector` は POD ではありません。

```cpp hl_lines="2"
static_assert(std::is_pod<std::array<int, 2>>::value, "Should be POD.");
static_assert(std::is_pod<std::vector<int>>::value, "Should be POD.");  // failed
```

## 参照型

参照型は POD ではありません。

```cpp hl_lines="1"
static_assert(std::is_pod<int&>::value, "Should be POD.");  // failed
```

## ポインタ型

あらゆるポインタは POD です。
POD ではない型に対するポインタも POD です。

```cpp
static_assert(std::is_pod<int*>::value, "Should be POD.");

// std::vector<int> は POD ではないが std::vector<int>* は POD
static_assert(std::is_pod<std::vector<int>*>::value, "Should be POD.");
```

## 構造体

構造体の条件は複雑なため、本書では簡単な例だけを紹介します。

??? question "POD の要件"
    トリビアルかつスタンダードレイアウトである場合に POD となります。
    詳細は以下を参照してください。

    - [is_trivial - cpprefjp C++日本語リファレンス][cpprefjp_is_trivial]
    - [is_standard_layout - cpprefjp C++日本語リファレンス][cpprefjp_is_standard_layout]

[cpprefjp_is_trivial]: https://cpprefjp.github.io/reference/type_traits/is_trivial.html
[cpprefjp_is_standard_layout]: https://cpprefjp.github.io/reference/type_traits/is_standard_layout.html

### POD になる構造体の例

以下の条件をすべて満たす構造体は POD です。

- 継承していない
- メンバ関数を持たない (暗黙的に定義される特別なメンバ関数は明示しない)
- すべてのデータメンバは POD
- データメンバに対するアクセス指定子が1種類のみ (暗黙的な `public` 指定も含む)

```cpp
// データメンバを持たない
struct Empty {};
static_assert(std::is_pod<Empty>::value, "Should be POD.");

// すべてのデータメンバが基本型
struct FundamentalTypes {
    int16_t i;
    double d;
};
static_assert(std::is_pod<FundamentalTypes>::value, "Should be POD.");
```

POD の構造体は入れ子にすることができます。

```cpp
// POD の構造体 FundamentalTypes をデータメンバにもつ
struct FundamentalTypesAsChild {
    char c;
    FundamentalTypes f;
};
static_assert(std::is_pod<FundamentalTypesAsChild>::value, "Should be POD.");

// POD の構造体 FundamentalTypesAsChild をデータメンバにもつ
struct FundamentalTypesAsGrandchild {
    char c;
    FundamentalTypesAsChild f;
};
static_assert(std::is_pod<FundamentalTypesAsGrandchild>::value,
              "Should be POD.");
```

### POD にならない構造体の例

<!-- MEMO: 多重継承や仮想継承に関連するものは言及していない -->

#### 暗黙的に定義される特別なメンバ関数をユーザ定義

ユーザ定義のデフォルトコンストラクタをもつ構造体は POD ではありません。

```cpp hl_lines="4 5"
struct UserDefinedDefaultConstructor {
    UserDefinedDefaultConstructor() {}
};
static_assert(std::is_pod<UserDefinedDefaultConstructor>::value,
              "Should be POD.");  // failed
```

`default` 指定であれば POD になります。

```cpp
struct DefaultConstructorAsExplicitDefault {
    DefaultConstructorAsExplicitDefault() = default;
};

static_assert(std::is_pod<DefaultConstructorAsExplicitDefault>::value,
              "Should be POD.");
```

デフォルトコンストラクタ以外の
暗黙的に定義される特別なメンバ関数についても同様です。

#### 仮想関数

仮想関数をもつ構造体は POD ではありません。

```cpp hl_lines="4"
struct VirtualFunction {
    virtual void Hoge() {}
};
static_assert(std::is_pod<VirtualFunction>::value, "Should be POD.");  // failed
```

#### 非 POD のデータメンバ

POD ではない型の非 `static` データメンバを持つ構造体は POD ではありません。

```cpp hl_lines="4"
struct NonPodMemberVariable {
    std::vector<int> v;  // std::vector<int> は POD ではない
};
static_assert(std::is_pod<NonPodMemberVariable>::value, "Should be POD.");  // failed
```

#### データメンバに対するアクセス指定子が2種類以上

暗黙的なものを含めて、
`static` ではないデータメンバに対するアクセス指定子が2種類以上ある構造体は POD ではありません。

```cpp hl_lines="7"
struct MultipleAccessSpecifierTypes {
    int public_variable;

 private:
    int private_variable;
};
static_assert(std::is_pod<MultipleAccessSpecifierTypes>::value, "Should be POD.");  // failed
```

## クラス

C++ における構造体とクラスの違いはデフォルトのアクセス指定子だけなので、
構造体と同じ条件でクラスも POD になります。

```cpp
class FundamentalTypes {
 public:
    int16_t i;
    double d;
};
static_assert(std::is_pod<FundamentalTypes>::value, "Should be POD.");
```
-----------------------------

ファイル: ./ch12-03-plain-old-data-api-compatibility.md
-----------------------------
# POD の API 互換性

C と C++ でヘッダファイルを共有して、
同じ型宣言を使用するには API 互換性が必要です。
POD であれば ABI 互換性は保証されますが、 API 互換性は保証されません。

POD にする場合には API 互換性もあるように定義しましょう。

## C には存在しない C++ の機能

C に存在しない機能を使用していると API 互換性はありません。
C に存在しない機能の一例として次のものがあります。

- クラス
- 名前空間
- テンプレート
- C++ の標準ヘッダファイル

<!-- WARNING: stdbool.h の bool と C++ の bool は互換性があるか不明 -->

### クラス

C にはクラスはありませんが構造体はあります。
そのため POD の型はクラスではなく構造体にするのが一般的です。

C の構造体はデータメンバをもつ以外の機能はなく、以下の機能は使用できません。

- メンバ関数
- 継承
- データメンバに対するアクセス指定子

API 互換性を保つためには、
これらの機能を一切使用しないで構造体を定義するとよいです。

```cpp
struct Sample {
    unsigned char c;
    double d;
};
```

### C++ の標準ヘッダファイル

C++ の標準ヘッダファイルは C では使用できませんが、
C の標準ヘッダファイルは C++ でも使用できます。

C の標準ヘッダファイルに対して、
C++ では先頭に `c` をつけて拡張子を除いたものが用意されています。
たとえば C の標準ヘッダファイル `<stdint.h>` に対して
C++ の標準ヘッダファイル `<cstdint>` があります。

通常 C++ では C++ の標準ヘッダファイルを使用するのが望ましいのですが、
C の標準ヘッダファイルを使用することができます。
この2つの違いは C++ のものは `std` 名前空間に属するようになることです。

API 互換性を保つためには、 C の標準ヘッダファイルを使用します。

```cpp
#include <stdint.h>

struct FundamentalTypes {
    int16_t i;
    double d;
};
```

## C++ には存在しない C の機能

C++ は C と高い互換性がありますが、完全上位互換ではありません。
C++ に存在しない機能を使用していると API 互換性はありません。
C++11 は [C99] というバージョンの C の機能を概ね取り込んでいますが、
すべての機能を取り込んでいる訳ではありません。

[C99]: https://ja.wikipedia.org/wiki/C99

たとえば C99 には複合リテラルという機能がありますが C++ では使用できません。

```c hl_lines="9 10"
int Sum(const int v[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += v[i];
    }
    return sum;
}

// 複合リテラルによる配列の生成
int sum = Sum((int[]){1, 2, 3, 4, 5}, 5);
```

同様の処理を C++ で行うには `std::array` などを使用する必要があります。

```cpp
int sum = Sum(std::array<int, 5>({1, 2, 3, 4, 5}).data(), 5);
```

詳細は
[複合リテラル - cppreference.com][cppreference_compound_literal]
を参照してください。

[cppreference_compound_literal]: https://ja.cppreference.com/w/c/language/compound_literal

## C と C++ で異なるソースコードにする

[プリプロセッサ司令] を使用して C と C++ で異なるソースコードにすることができます。

[プリプロセッサ司令]: appendix-preprocessor-directives.md

C++ では `__cplusplus` というマクロが定義されますが、
C では定義されないことを利用して次のようにすることができます。

```cpp
#ifdef __cplusplus
// C++ だけで有効なソースコード
#else
// C だけで有効なソースコード
#endif  // __cplusplus
```

これを利用すれば C には存在しない C++ の機能を C++ だけで有効にすることができますが、
メモリレイアウトが同一になることを担保するのが難しいため基本的には推奨しません。

??? question "C++ だけで名前空間を有効にする"
    名前空間は名前マングリングに影響しますが、メモリレイアウトには影響しません。
    名前マングリングが問題にならなければ C++ だけで名前空間を有効にすることができます。

    ```cpp linenums="1"
    #ifdef __cplusplus
    namespace sample {
    #endif  // __cplusplus

    struct Sample {
        unsigned char c;
        double d;
    };

    #ifdef __cplusplus
    }
    #endif  // __cplusplus
    ```

??? question "C++ だけでメンバ関数を有効にする"
    仮想関数がある場合は POD ではありませんが、
    仮想関数ではないメンバ関数があっても POD になります。

    仮想関数ではないメンバ関数の有無はメモリレイアウトに影響しないため、
    C++ だけでメンバ関数を有効にすることができます。

    ```cpp linenums="1"
    struct Sample {
        unsigned char c;
        double d;

    #ifdef __cplusplus
        double GetD() const {
            return d;
        }
    #endif  // __cplusplus
    };
    ```

    メンバ関数を追加するだけの派生クラスを C++ だけで使用する方法もあります。

    ```cpp linenums="1"
    struct Sample {
        unsigned char c;
        double d;
    };

    #ifdef __cplusplus
    class SampleCpp : public Sample {
     public:
        double GetD() const {
            return d;
        }
    };
    #endif  // __cplusplus
    ```
-----------------------------

ファイル: ./ch12-04-byte-array-manipulations.md
-----------------------------
# バイト列操作

POD であれば以下の関数でデータを扱うことができます。
使用するには `<cstring>` のインクルードが必要です。

- `std::memset`
- `std::memcpy`
- `std::memcmp`

これらは C の関数であるため、
任意の型を扱うために [void ポインタ][void-pointer] が使用されます。

[void-pointer]: appendix-void-pointer.md

次のコードで説明します。

```cpp
static_assert(CHAR_BIT == 8, "Not support 1byte != 8bits");

struct FundamentalTypes {
    int16_t i;
    double d;
};
```

## std::memset

バイト列に指定した値をセットします。
仕様は [std::memset - cppreference.com][cppreference_memset] を参照してください。

[cppreference_memset]: https://ja.cppreference.com/w/cpp/string/byte/memset

```cpp
FundamentalTypes f;

// すべてのビットを0にする
std::memset(&f, 0, sizeof(f));
std::cout << f.i << std::endl;  // 0
std::cout << f.d << std::endl;  // 0

// すべてのビットを1にする
std::memset(&f, 0xff, sizeof(f));
std::cout << f.i << std::endl;  // -1   (2の補数表現の場合)
std::cout << f.d << std::endl;  // -nan (IEEE 754 の場合)
```

<!-- MEMO: C++11 の言語仕様では1の補数表現が許容されているため注釈を入れている -->

## std::memcpy

バイト列をコピーします。
仕様は [memcpy, memcpy_s - cppreference.com][cppreference_memcpy] を参照してください。

[cppreference_memcpy]: https://ja.cppreference.com/w/c/string/byte/memcpy

```cpp
FundamentalTypes f1;
f1.i = -2;
f1.d = 2.71;

FundamentalTypes f2;

// f1 から f2 へバイト列をコピー
std::memcpy(&f2, &f1, sizeof(FundamentalTypes));

std::cout << f2.i << std::endl;  // -2
std::cout << f2.d << std::endl;  // 2.71
```

## std::memcmp

バイト列を比較します。
仕様は [std::memcmp - cppreference.com][cppreference_memcmp] を参照してください。

[cppreference_memcmp]: https://ja.cppreference.com/w/cpp/string/byte/memcmp

```cpp
FundamentalTypes f1;
f1.i = -2;
f1.d = 2.71;

FundamentalTypes f2;
f2.i = 3 - 5;
f2.d = 2.71;

FundamentalTypes f3;
std::memset(&f3, 0, sizeof(f3));

if (std::memcmp(&f1, &f2, sizeof(FundamentalTypes)) == 0) {
    std::cout << "f1 and f2 are same" << std::endl;
} else {
    std::cout << "f1 and f2 are different" << std::endl;
}

if (std::memcmp(&f1, &f3, sizeof(FundamentalTypes)) == 0) {
    std::cout << "f1 and f3 are same" << std::endl;
} else {
    std::cout << "f1 and f3 are different" << std::endl;
}
```

実行結果は次のようになります。

```
f1 and f2 are same
f1 and f3 are different
```
-----------------------------

ファイル: ./ch12-05-bitfields.md
-----------------------------
# ビットフィールド

構造体のデータメンバはバイト単位でサイズが確保されますが、ビット単位でもサイズを確保することができます。
そのようなデータメンバをビットフィールドといいます。

```cpp
struct Bits {
    uint8_t a : 1;     //  1 ビット
    uint8_t b : 3;     //  3 ビット
    uint8_t c : 4;     //  4 ビット
};
```

データメンバ `a, b, c` は `uint8_t` 型の領域をそれぞれ指定したビット数で分割して利用します。
構造体のサイズをなるべく小さく抑えたいときなどに使用されます。

例えば 1 ビットのビットフィールドを用意すれば `0, 1` の 2 値を表現できるため、
`bool` の代わりとして使用することができます。

```cpp
struct Bool {
    uint8_t flag : 1;
};
```

ただし上記のような 1 ビットのビットフィールドを定義しても `Bool` のサイズは `uint8_t` 分のサイズを確保します。
すなわち `uint8_t` の残り 7 ビットは未使用な領域になります。
-----------------------------

