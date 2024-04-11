#shell チートシート

## 環境変数の継承方法
環境変数の扱いは /etc/sudoersで管理される
*env_resetが有効の場合変身後に最小限の環境が採用される
* env_keep
 - env_reset有効時に実行ユーザから継承される環境変数を定義する。
*継承方法
- env_resetとenv_secureをコメントアウトしてenv_keep+="PATH"を追加する(非推奨だがやっちゃう）


## $*, $@, "$@"の違い
シェルスクリプト実行時の引数（位置パラメータ）
```
echo '--- $* ---'; for P in $*; do echo $P; done
echo '--- $@ ---'; for P in $@; do echo $P; done        # $* と同じ
echo '--- "$@" ---'; for P in "$@"; do echo $P; done
```
実質$* "$@"の違いを気を付ければよい
```
./sample.sh "1 2" "hoge huga"
--- $* ---
1
2
hoge
fuga
--- "$@" ---
1 2
hoge fuga
```

# set
  -e : コマンドが失敗した時点でスクリプト全体を即座にエラー終了する
  -u : 初期化していない変数があればエラーにする
  -x : 実行するコマンドを出力する。何をしたらどうなったかがログに残せる
  -o pipefail : パイプの途中でエラーがあればexit codeする
  IFS : 区切り文字の設定 デフォルトはIFS=$' \n\t'スペース、改行、タブ

# grep で正規表現
    基本正規表現は -G , 拡張正規表現 は -E

 基本正規表現
    空白　　　　は              \s
    行頭        は              ^
    行末        は              $
    語頭        は              \<
    語尾        は              \>
    改行以外の任意の文字        .
    アルファベットと数字        \w
    アルファベットと数字以外    \W
    囲まれている文字のどれか    [...]
    囲まれているもじでない文字  [^...]
    指定範囲のどれかの文字      [n-n]   [a-c] : abcのどれか

 拡張正規表現
    直前文字の0回以上の繰り返し　は *
    直前文字の1回以上の繰り返し　は +
    直前文字のn回の繰り返し　　　は {n}
    直前文字のn回以上の繰り返し　は {n,}
    直前文字のm回以下の繰り返し　は {,m}
    直前文字のn回からm回の繰り返し　は {n,m}
    または                       は |       txt|doc
    ()内をひとまとまりとする　　 は ()      (abc){2}

    grep -v -E "root\s+root"

# 変数から前方指定文字を除く
    DUTIP=${DUTNUM##0}

# FILEの実行パスとFILE名の取得
    FILEPATH=`echo $(realpath "$0")`
    SELFSH=`basename $FILEPATH`

# 変数から指定文字を置換文字で置き換える
    FILEDIR=${FILEPATH///指定文字/置換文字}
    echo $FILEDIR
    /mnt/sd-mmcblk0p1

# 変数デフォルト指定.中身が見えなければデフォルト値 :- 下記はデフォルトをbrに指定
    IFMODE=
    echo ${IFMODE:-br}
    br

# 変数が未定義ならばデフォルト値 -
    echo ${hoge-exist}
    # Hello
    echo ${foo-empty}
    #

# sshで指定ホスト上でコマンドを実行する

    if [ -n "$PASSWORD" ]; then
        cat <<< "$PASSWORD"
        exit 0
    fi
    
    read PASSWORD
    export PASSWORD
    export SSH_ASKPASS=$0
    export DISPLAY=dummy:0
    
    exec setsid "$@" 

    echo "${CBACK_IP}\$ ${SSH_ARGS}"
    echo "root" | ${SSH_ASKPASSSH} ssh -o "StrictHostKeyChecking=no" -o "UserKnownHostsFile=/dev/null" -q root@${CBACK_IP} "source /etc/profile; ${SSH_ARGS}" || ret=$?

# devmemで所定レジスタへ値をセット
    devmem 0xa4090010 32 $((`devmem 0xa4090010`&0xfffffffe))

#ディスクリプタをテンポラリで作成する(/tmp/readfifoが存在する前提で８番のディスクリプタで置き換える)
    exec 8<>/tmp/readfifo

# atコマンドでタイマセット
    load_attime (){
      local min=$1
      local exefile=$2
      at `date +"%H:%M %d.%m.%Y" -d "$min minutes"` -f "$exefile"
    }

##### 同階層のシェルスクリプトをファイル数分ひとつづ実行する
    filename=$(ls -1 SHFILE_*)
    
    echo "${filename}" | while read line
    do
        sleep 1
        ./${line}
        echo ""
    done
    
    //

### while loop
    while :
    do
        ./linkctrl.sh 0 down
        sleep 2
        ./linkctrl.sh 0 up
    done

##### シェルスクリプト内で一時ファイルを生成してスクリプト終了時に削除する
    
    tmpdir=$(mktemp -d)
    trap "rm -rf $tmpdir" EXIT # 最後に実行されるコマンドを登録
        #ここで色々処理する

# 一時的な名前付きパイプを作る
    #以下のやり方の場合複数のプロセスで同時にそれぞれの名前付きパイプを作ろうとした場合に、mktempが
    #偶然同じ名前になってしまい衝突リスクがある。
    mkfifo `mktmp -u`
    
# case文

case 値 in
   条件1) 処理1 ;;
   条件2) 処理2 ;;
   条件3) 処理3 ;;
esac


# if文

if [ ]; then
elif []; then
fi

演算子

内容

例

結果


+ 加法 echo $(( 2 + 3 )) 5 
- 減法 echo $(( 2 - 3 )) -1 
/ 除法 echo $(( 6 / 2 )) 3 
* 乗法 echo $(( 2 * 3 )) 6 
% 余り echo $(( 3 % 2 )) 1 
x++ インクリメント x=2
echo $(( x++ ))
echo $(( x++ )) 2
3 
++x インクリメント x=2
echo $(( ++x ))
echo $(( ++x )) 3
4 
x-- デクリメント x=2
echo $(( x-- ))
echo $(( x-- )) 2
1 
--x デクリメント x=2
echo $(( --x ))
echo $(( --x )) 1
0 
** べき乗 echo $(( 2 ** 3 )) 8 
    

比較演算子


演算子

例

結果


> echo $(( 2 > 3 )) 0 
== echo $(( 2 == 3 )) 0 
!= echo $(( 2 != 3 )) 1 
< echo $(( 2 < 3 )) 1 
   

これは, 以下で扱う条件文には使えません.

コマンドを繋げる演算子

&&と||の使い方は, 次の条件文のところでも例示します.


演算子

書き方

内容

例


; command1;command2 別々のコマンドを連続して書くことができます. コマンドは連続して実行されます pwd ; ls 
& command & コマンドをバックグラウンドで実行します sleep 3 & → バックグラウンドでスリープ処理が行われるので, その場ではスリープしません. 処理後にもとのシェルに通知されます 
&& command1 && command2 command1が実行され, 戻り値が0であれば, command2を実行する pwd && ls → pwdは実行され, 戻り値0を返すので, pwdのあとlsが実行される 
|| command1 || command2 command1が実行され, 戻り値が0であれば, command2を実行する pwd || ls → lsは実行されない 
| command1 | command2 command1の標準出力をcommand2に渡す cat file名 | grep 

条件文に使える比較演算子

数値を比較する場合は,


演算子

書き方

意味

例


eq x -eq y x = y [ 5 -eq 5 ] && echo "True" → True 
ge x -ge y x >= y [ 5 -ge 3 ] && echo "True" → True 
gt x -gt y x > y [ 5 -gt 3 ] && echo "True" → True 
le x -le y x <= y [ 3 -le 5 ] && echo "True" → True 
lt x -lt y x < y [ 3 -lt 5 ] && echo "True" → True 
ne x -ne y x != y [ 1 -ne 2 ] && echo "True" → True 
    

文字列を比較する場合は,


演算子

書き方

意味

例


= x = y xとyが全く同じ文字列 [ "apple" = "apple" ] && echo "True" → True 
!= x != y xとyが同じ文字列でない [ "apple" = "orange" ] && echo "True" → True 
z -z x 文字列xの長さが0である [ -z "" ] && echo "True" → True 




演算子

書き方

意味

例


f -f file fileがファイルである [ -f file ] && echo "True" → True 
d -d dir dirがディレクトリである [ -d dir ] && echo "True" → True 
e -e file(or directory) file(or directory)が存在する [ -e file ] && echo "True" → True 
r -r file(or directory) file(or directory)が読み込み可能である [ -r file ] && echo "True" → True 
w -w file(or directory) file(or directory)が書き込み可能である [ -w file ] && echo "True" → True 
x -x file(or directory) file(or directory)が実行可能である [ -x file ] || echo "True" → True 

Ａｎｄ条件
if [ "A" = "B" -a "B" = "C" ]; then
ＯＲ条件
if [ "A" = "B" -o "B" = "C" ]; then

# for

for 変数 in リスト; do
    処理
done

# 時限　実行コマンド at で指定時間exefileを実行する
load_attime (){
  local min=$1
  local exefile=$2
  at `date +"%H:%M %d.%m.%Y" -d "$min minutes"` -f "$exefile"
}

# 27h * 60min + 10min(margin) = 1630 min
load_attime 1630 $exefile 


# chatscript
# SSH 踏み台スクリプト
\[root@node ~]# 
ssh root@192.168.100.22\r
Are you sure you want to continue connecting \(yes/no)\? 
yes\r
root@[0-9]+\.[0-9]+\.[0-9]\.[0-9]+'s password: 
pass\r


### 実行 小技
    以下のように実行結果をRESULTに格納しておいてあとでechoする
    RESULT=$(${exefile})
    echo "${RESULT}" > logfile

### コメント

<<COMMENT
echo "Hello world!"
echo "Hello world!"
echo "Hello world!"
COMMENT

### 

```
read -p "Please input your name: " name
echo "Hi, $name."

```


