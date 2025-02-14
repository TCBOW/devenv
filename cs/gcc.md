# gcc オプション
参考
https://qiita.com/janus_wel/items/07140fcd1127b568087d

### -Wall, -W
    基本的な警告オプションを on にする 
    バグ可能性部分に警告を出す。
    潜在的なミスを指摘するため基本的につけておくべき
### -std=c++11, 14, 17 ...
    それぞれ、c++11,c++14,c++17の機能を有効にする
### -std=c++11 
    対象ソースが C++11 準拠としてコンパイルする 
### -O1, -O2, -O3, -Os
    最適化オプション
### -g, -g3
    デバッグオプション
### -fno-pic
    位置非依存コード（PIC）を生成しないことを指示する。
    通常は配置されたアドレスに依存したプログラムになる。
    このため例えば0x4000番地に配置するように作られたプログラムは0x8000にロードしても実行できない。
### -fomit-fname-pointer
    フレームポインタを管理するコードを生成しないことを指示する。
    gccは通常デバッガの監視下でプログラムを実行した時にスタックフレームの状態を把握できるようにするために
    フレームポインタを管理するコードを生成する。このオプションでその生成が抑制される。
### -Wextra 
    追加の警告オプションを on にする 
### -pedantic
    ISO C/C++ に存在しない文法を警告する 
### -Wcast-align 
    char* から int* などアラインメント長が大きくなるキャストを警告する 
### -Wcast-qual 
    const char* を char* にキャストするなど型修飾子が外れる場合に警告する 
### -Wconversion 
    暗黙的なキャストや型変換が実施されると警告する 
### -Wdisabled-optimization 
    コンパイル時最適化が途中で打ち切られると警告する 
### -Wendif-labels 
    #else FOO や #endif FOO などコメントにすべき位置に識別子があると警告する 
### -Wfloat-equal 
    浮動小数点数を == で比較していると警告する 
### -Winit-self 
    int i = i; など未定義の変数が自分を初期化すると警告する 
### -Winline 
    inline 指定した関数がインライン展開されない場合に警告する 
### -Wlogical-op 
    ビット演算子がふさわしいところに論理演算子を用いた場合に警告する 
### -Wmissing-include-dirs 
    ユーザーが指定した include ディレクトリーが存在しない場合に警告する 
### -Wnon-virtual-dtor 
    仮想関数を持っているのに非仮想なデストラクターを持つクラスを定義すると警告する 
### -Wold-style-cast 
    C 言語形式のキャストをすると警告する 
### -Woverloaded-virtual 
    親クラスの仮想メンバー関数を隠してしまうメンバー関数を定義すると警告する 
### -Wpacked 
    packed attribute が構造体やクラスに指定されているが、指定なしのときとサイズが変わらない場合に警告する 
### -Wpointer-arith 
    関数型や void のポインター、 NULL に対して数値計算すると警告する 
### -Wredundant-decls 
    同一スコープで同一シンボルを複数回宣言すると警告する 
### -Wshadow 
    ローカル変数や型宣言が他の変数、パラメーター、型、クラスメンバー、組み込み関数を隠すと警告する 
### -Wsign-promo 
    オーバーロード解決時に unsigned / 列挙型から同一サイズの unsigned を経由して signed へ昇格すると警告する 
### -Wswitch-default 
    switch 文に default case がないと警告する 
### -Wswitch-enum 
    列挙型の case を持つ switch 文で、その列挙型のうちひとつ以上の値が case として定義されていないと default case があっても警告する 
### -Wunsafe-loop-optimizations 
    終了条件を仮定できず、ループを最適化できない場合に警告する 
### -Wvariadic-macros 
    可変引数マクロが ISO C90 モードで使われると警告する 
### -Wwrite-strings 
    文字列リテラルの型 const char* を char* に変換すると警告する 

# -Wallの内訳

### -Waddress 
    関数ポインターを条件式に使うなど、おかしいポインターの使い方を警告する
### -Warray-bounds 
    配列に対して範囲外の添字指定をした場合に警告する -O2 と同時に指定された場合のみ有効
### -Wc++11-compat 
    ISO C++ 1998 から ISO C++ 2011 までと異なるソースの場合に警告する
### -Wchar-subscripts 
    配列の添字を char 型で指定した場合に警告する
### -Wenum-compare 
    異なる列挙型の値同士で比較した場合に警告する
### -Wcomment 
    /* が /* コメント内に現れた場合とバックスラッシュが // コメントの最後に現れた場合に警告する
### -Wformat 
    printf などのフォーマット内の書式指定シーケンスについて変数引数と数が異なったり、適切な変換ができない場合に警告する
### -Wmaybe-uninitialized 
    自動変数が初期化されないルートがある場合に警告する
### -Wmissing-braces 
    int a[2][2] = { 0, 1, 2, 3 }; などアグリゲートや共用体の初期化にブレースが足りないと警告する
### -Wnonnull 
    nonnull 属性がついた関数に null ポインターを渡すと警告する
### -Wparentheses 
    ネストした if 文の中の else などカッコがないと混乱する文脈でカッコを省略すると警告する
### -Wreorder 
    メンバー初期化子の順番が宣言と異なる場合に警告する
### -Wreturn-type 
    関数の戻り値型が指定されているのに値なしの return をするなど return に関するおかしなコードを警告する
### -Wsequence-point 
    n = n++; など、評価順序によって結果が異なるコードを警告する
### -Wsign-compare 
    singed 型と unsigned 型の比較において、 singed 型を unsigned 型に変換すると結果がおかしくなるコードを警告する
### -Wstrict-aliasing 
    int x = 0; short* y = (short*)&x; など無理な型変換によってコンパイラーが最適化できない場合に警告する
### -Wstrict-overflow=1 
    j符号付きオーバーフローが発生しないと仮定した最適化が実施されると警告する
### -Wswitch-enum 
    列挙型の case を持つ switch 文で、その列挙型のうちひとつ以上の値が case として定義されていないと警告する default case があれば ok
### -Wtrigraphs 
    プログラムの意味を変える可能性のあるトライグラフがコードに含まれていると警告する
### -Wuninitialized 
    非 static 参照や非 static const なメンバー変数がコンストラクターなしのクラスに定義されていると警告する
### -Wunknown-pragmas 
    gcc が理解できない #pragma ディレクティブが存在する場合に警告する
### -Wunused-function 
    static な関数が宣言されかつ定義されていないか、非 inline な static 関数が使われていない場合に警告する
### -Wunused-label 
    使われていないラベルがあると警告する
### -Wunused-value 
    i = (1, 2, 3); など結果を計算する文が明示的に使われていない場合に警告する
### -Wunused-variable 
    ローカル変数や非 const な static 変数が宣言されているが使われていない場合に警告する
### -Wvolatile-register-var 
    レジスター変数が volatile 修飾されている場合に警告する

# -Wextraの内訳

### -Wclobbered 
    longjmp や vfork によって変数が変更されるかもしれない場合に警告する
### -Wempty-body 
    if, else, do while 文の本体がない場合に警告する
### -Wignored-qualifiers 
    const int a(); など関数の戻り値の型が const などの型修飾子を持つ場合に警告する
### -Wmissing-field-initializers 
    定義されたフィールド数に比べて構造体の初期化子の数が少ない場合に警告する
### -Wsign-compare 
    singed 型と unsigned 型の比較において、 singed 型を unsigned 型に変換すると結果がおかしくなるコードを警告する
### -Wtype-limits 
    unsigned int a; if (a < 0) など、データ型の範囲が限定されているために比較が常に真または偽になる場合に警告する
### -Wuninitialized 
    非 static 参照や非 static const なメンバー変数がコンストラクターなしのクラスに定義されていると警告する
### -Wunused-parameter 
    関数引数が定義されているが使われていない場合に警告する
### -Wunused-but-set-parameter 
    関数に引数が渡されているが使用されていない場合に警告する



