# vimcs

###  Copilotの設定有無

:let b:copilot_enabled=v:ture
:let b:copilot_enabled=v:false

#Termdebugで実行ファイルをデバッグ
:Termdebug 実行ファイル名

##grepを再帰検索してQuickfixウィンドウを開く
:grep 検索文字 **/ |cw

:cn //cnextで次にジャンプ 
:cp //cprevで前にジャンプ

##Termdebugでデバッグ
:Termdebug 実行ファイル名

##コマンド履歴参照
q:
##検索履歴参照
q/

#スペルチェックモードへON/OFF
,s
##スペルチェックコマンド
]s  次のスペルミス単語へjump
[s  最後のスペルミス単語へjump
z=  修正案を参照
zg  スペルミスしている単語を正しいものとマークする
zw  スペルミスしている単語であるとマークする

## 文字コード確認
:set enc?
## 開いている文字コードを別の文字コードで表示する
:e ++enc=文字コード
##保存する文字コードを変更する
:set fenc=文字コード

# 選択範囲を置換
    Shift + v で VISUAL LINE モードへ
    選択したい範囲を h or k で指定
    コロンをタイプ :
    コマンドラインに :'<,'> のように表示されるので、続けて置換コマンドである s をタイプ
    置換文字列をスラッシュで区切り入力 /検索対象文字列/置換後文字列/
    確認を挟むための gc をタイプ
    Enter をタイプ
    
## 新しい環境にvim8.2をインストールする

git clone https://github.com/vim/vim.git
sudo apt install ncurses-dev
cd vim/src
make
alias vim='~/git/vim/src/vim'

### tab文字入力方法
 ctrl+v 押してからtab

### tabを>-で可視化
set list listchars=tab:>-
