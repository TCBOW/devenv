### threadの状態を調べる
    info thread     # 起動しているthreadの状態を確認する
    thr <threadNo>  # thread番号に切り替える
    bt              # backtraceでスタックをさかのぼって表示

### breakpoint
    info break
    delete breakp 番号
    break linenum
    break file:function

### 配列の中身を10個の要素で表示
    p *x@10
    p (int [25]) *x

### mb_dataの中身を50バイト表示する
    p/x (char [50]) *mb->mb_data

### printコマンドの書式指定
    p/o    8進数表示
    p/x    16進数表示
    p/t    2進数表示
    p/f    浮動小数点表示
    p/d    10進数表示
    p/u    符号なし10進数表示
    p/c    文字表示
    p/a    ｱﾄﾞﾚｽ表示

### 一覧表示
    whatis
    info b
    info stack
    info Thread

### 指定行やｱﾄﾞﾚｽから実行を継続
    jump linspec
    jump *address

### ｱﾄﾞﾚｽが分かっている場合のメモリリーク出力
    p (char *)ｱﾄﾞﾚｽ番号
    x/ (文字数) c ｱﾄﾞﾚｽ番号

### 実行停止のたびに引数指定した変数を表示
    display 変数
    undisplay 変数
    info display 変数
   
### 引数で指定したスタックフレームを見る
    up
    down
    backtrace

### objdump
    objdump -D -m i386 dry.axf > tmp.txt
    objdump -S -m i386 dry.axf > tmp.txt


#参考
https://uguisu.skr.jp/Windows/gdb.html

# 起動済アプリをgdbで追跡する方法
    gdb （実行中の）実行可能ファイル名
    (gdb) attach 実行中のプロセスのID

# attachコマンドが失敗する
gdbでattachコマンドを実行したときに権限の問題で実行できない場合があるUbuntuの場合はデフォルトで出来ない設定。
これを以下で直す。

    sudo vim /etc/sysctl.d/10-ptrace.conf

    kernel.yama.ptrace_scope = 0
