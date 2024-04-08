## makefile

###内部マクロ
$@ ターゲットファイル
$~ 必須ファイル（ソース）
$% ターゲットメンバ名（.aを構成する.oのようなターゲットの構成物)
$< 依存ファイルの先頭のファイル名
$? 依存ファイルの内、ターゲットより新しいファイルのリスト
$~ 依存ファイルのリスト
$+ 謎
$* 謎

###定義済マクロ
AR = ar     # アーカイブユーティリティ
AS = as     # アセンブラ
CC = cc     # Cコンパイラ
CXX = g++   # C++コンパイラ
CO = co     # RCSファイルからリビジョンをチェックアウトする
CPP = $(CC) -E # Cプリプロセッサ
RM = rm -f  # ファイルの削除

ARFLAGS     # ARの引数
ASFLAGS     # ASの引数
CFLAGS      # CCの引数
CXXFLAGS    # CXXの引数
COFLAGS     # COの引数
CPPFLAGS    # CPPの引数
FFLAGS      # FCの引数
PFLAGS      # PCの引数
LDFLAGS     # リンカldの引数

```
# Makefile2

PROGRAM = hello
OBJS = hello.o print.o
CC = gcc
CFLAGS = -Wall -O2

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

hello.o: hello.c
	$(CC) $(CFLAGS) -c $<

print.o: print.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
```

## ビルドツリーのMakefileを叩き繋げる方法は以下#####
SUBDIRS := src

all:= $(TARGET)

$(TARGET): $(SUBDIRS) $(OBJS)
    $(CC) -o $@ $(CFLAGS) -Wl, --start-group $(OBJS) $(LIBS) $(LDFLAGS) -Wl,--endgroup

$(TARGET): $(SUBDIRS)
$(SUBDIRS):
    $(MAKE) -C $@ $(MAKECMDGOALS)
####################################################


##サフィックスルール
サフィックスルールとは, ファイル名の拡張子 (サフィックス) ごとにルールを定義するものである. 例えばこんな感じである:
```
SUFFIXES: .o .c

.c.o:
      $(CC) $(CFLAGS) -c $<
”.SUFFIXE” は依存関係行と同じ形であるが, 意味が違う. サフィックスルールを適用する拡張子のリストを書く.
”.c.o” がサフィックスルールとなっており, 拡張子が ”.o” のファイルは拡張子 ”.c” 変えたファイルに依存していることを表す. 変換はコマンドで表されている.
例えば, ターゲット名が “hoge.o” ならば make はこのサフィックスルールより “hoge.c” に依存していると判断して, コマンドを実行し “hoge.o” を生成する.
サフィックスルールを用いると, こんな感じで書ける.
Makefile3
# Makefile3

# プログラム名とオブジェクトファイル名
PROGRAM = hello
OBJS = hello.o print.o

# 定義済みマクロの再定義
CC = gcc
CFLAGS = -Wall -O2

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# プライマリターゲット
$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS) -c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
```

ここまでくると, あとは “PROGRAM” や “OBJS” を書き換えるだけでいくらでも流用ができる. ちなみに, ヘッダファイルの依存関係だけは自分で記述しなければならない. 例えばこんな感じである.
```
Makefile_other
# Makefile_other

# プログラム名とオブジェクトファイル名
PROGRAM = main
OBJS = main.o

# 定義済みマクロの再定義
CC = gcc
CFLAGS = -Wall -O2

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# プライマリターゲット
$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS) -c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)

# ヘッダファイルの依存関係
main.o: str.h
```

# Makeはコマンドラインで与えて指定されたゴールのリストをMAKEGOALDSという変数にセットする。コマンドラインで与えられなかった場合は空っぽになる。
