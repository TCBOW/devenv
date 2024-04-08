### リモートへのpushを無かったことにする
    git log
    git checkout <commitID>
    git branch -d <無かったことにしたいブランチ>
    git checkout -b <無かったことにしたいブランチ>
    git push origin +<無かったことにしたいブランチ>

### gpg key 生成 と確認
    gpg --full-generate-key
    gpg --list-secret-keys --keyid-format=long
    
/home/nt12/.gnupg/pubring.kbx
-----------------------------
sec   rsa4096/B6589B7C00E3B251 2022-05-30 [SC]
      F8E6901E60F6FD10CC9E4DAAB6589B7C00E3B251
uid                 [  究極  ] sato.toshiaki <sato.toshiaki261@mail.canon>
ssb   rsa4096/7ADE94699705FEC8 2022-05-30 [E]

    gpg --armor --export B6589B7C00E3B251
    
    表示されたGPGキーをgithubへ登録する

### gpg key 登録
    git config --global credential.credentialStore gpg

### gpg署名を無効にする
    git config --global --unset commit.gpgsign

### git configのgpg関連のステータスを確認する
    git config -l | grep gpg

### ブランチから現在ブランチに特定ファイルのみをパッチ適用
    * patchを作成
    git format-patch --histogram '..feature/ptptest' -- test/functest/ptplibtest/common/util_config.sh
    
    * patchを充てる
    git am -3 *.patch

### 特定のファイルのみコミットを戻す
    git checkout <commitID> <file or dir>

### 過去のコミットコメントの変更方法
    git log --oneline
した結果からコメントを変更したいコミットの一つ前のハッシュをコピー
    git rebase -i HASH
コメント変更するコミットのpickをeditに変更して閉じる
    git commit --amend
するとコミットコメントを修正できるので修正して閉じる
        
### タグ
    git tag -a [タグ名] -m `タグコメント`
    git tag -a [タグ名] -m `タグコメント` コミットsha
    git push origin [タグ名]
    git push origin --tags
  ローカルとリモートのタグ名を削除する    
    git tag -d [タグ名]
    git push origin :[タグ名]
  ローカルのタグを確認する
    git tag

### エイリアスコマンド
    git sta     status確認
    git sd
    git ld
    git ll
    git lg
### patchファイル作成方法
    git diff ＜ハッシュ値＞ 

### git ブランチ指定でクローン
    git clone -b [branch] [repository]

### 既存のローカルブランチにリモートブランチを追跡させる
    - 現在のブランチを指定
    git branch -u [origin]/[branch]
    - ローカルブランチを指定
    git branch -u origin/[branch] [branch]
    - 現在のローカルブランチの追跡先を確認
    git branch -vv
### リモートブランチを追跡するブランチの作成
    - git branch [branch] [origin]/[branch

### ブランチを削除する
    - git branch --delete ブランチ名

### ブランチを作成
    - git branch -b ローカルに作成するブランチ名
### ローカルブランチをリモートに登録
    - git push -u origin 作成したブランチ名
### コミットの編集
    - 自分が何を今コミットしたか？
    git show
or  git log -n 1 -p

    - 特定コミットのファイルを参照
    git show <commitid>:filename

### プッシュ前のコミットメッセージに間違ったことを書いたので編集する
    - git commit --amend --only -m "xxxx"

### 特定ファイルのみをコミット
    git commit -m "add" -- file list

### gitでsvn export的なことをやる
    git checkout-index -a -f --prefix=export/

    -a：管理されている全てのファイルを対象にするために必要
    
    -f：export先に既に同じ名前のファイルがあっても上書きでexportする
    
    –prefix：エクスポート先のパス


###リモートブランチをローカルブランチにチェックアウトする
    git checkout -b 作成するローカルブランチ名 origin/リモートブランチ名

###ブランチ名を変更する
    git branch -m 旧ブランチ名 新ブランチ名

### ファイル名称を変更する
    git mv search.html Search.html

###ローカルの変更を元に戻す
    git checkout .

###ステージングを取り消す
    git reset [ファイル名]

###ステージしたファイルを最後にコミットした状態に戻す
    git checkout HEAD -- [ファイル名]

###別ブランチから特定のファイルを取得する
    git checkout <取り込み元ブランチ> <取り込むファイル>

###ステージされたファイルを直前のコミットに追加する
    git add [ファイル名]
    git commit --amend --no-edit

###編集・ステージングともに変更内容を取り消し、最後にコミットした状態に戻す
    git reset --hard HEAD

###stashを適用する
    git stash apply stash@{0}　または
    git stash pop stash@{0}

### stashで一部ファイルをインタラクティブに隠す
    git stash -p 

### ファイル単位でstashする
    git stash push -- <filepath>

###マージコンフリクトを解決する
    git mergetool -t vimdiff

### マージにpotienceアルゴリズムを使う
    git merge --strategy-option=patience
  potienceアルゴリズム使うことで関数やタグの不適切な確固を調整する助けになる    

###ブランチ間の同じファイルを比較する
    git diff master branch hoge.txt

###リモートのリポジトリURLを変更する
    git remote set-url origin git@172.29.54.213:110662/XD334.git
    git remote -v
    
###異なるブランチの異なるファイルを比較する
    git diff br1:foo/bar.txt br2:hoge/fuga.txt
###異なるブランチの同じファイルを比較する
    git diff br1 br2 foo/bar.txt

### 特定のコミットの打ち消し
    git revert コミットのハッシュ値

### 複数のコミットを一つのコミットに統合する
    git log --oneline
    git rebase -i HEAD~3
        統合したcommitのpickをfixupに書き換える
### rebaseに失敗した場合は下記で一連の処理を取り消す
    git rebase --abort


### 指定ファイルを指定コミット番号のものに戻す
    git checkout [コミット番号] [ファイル名]

### Reference
    https://blog.labot.jp/entry/2019/07/01/183204

### 外部モジュールをサブモジュール化する
    git submodule add <追加したいrepository>

### 外部サブモジュールだけをアップデートしたい
    git submodule update --init

### 外部サブモジュールを最新にしてmergeする
    git submodule update --remote --merge

### Git管理ファイル一式をアーカイブする。archiveを無視

    git archive ignore list
    ex) git archive master --worktree-attributes --output=svnw-svCbTrans.zip

### コミットの差分をアーカイブする

    git archive HEAD `git diff --name-only HEAD HEAD~2` -o archive.zip

# Tips

###GitHubへのpushで毎回パスワードを聞かれないようにする設定
- ssh-keygenで公開鍵と秘密鍵のペアを作成
    ssh-keygen -t rsa -C sato.toshiaki261@mail.canon
    chmod 600 id_rsa
- GitHubに公開鍵を登録し.ssh/configに秘密鍵を登録する
    Host gitlab.example.com
      User git
      Port 指定のポート番号
      HostName gitlab.example.com
      TCPKeepAlive yes
      identitiesonly yes
      identityFile ~/.ssh/id_rsa  →key（id_rsa）秘密鍵までのパスを記述
- set-urlでリモートリポジトリの向き先をhttpsからgit@github.comに修正
     git remote set-url origin git@172.29.54.213:110662/XD334.git
 
### gitリポジトリ登録
  git init
  git add README.md
  git commit -m "first commit"
  git branch -M main
  git remote add origin git@github.com:110662/devenv.git
  git push -u origin main

# ssh key generation
    ssh-keygen -t ed25519 -C "your_email@example.com"
    eval "$(ssh-agent -s)"
    ssh-add ~/.ssh/id_ed25519
    clip < ~/.ssh/id_ed25519.pub

### submodule 追加
  git submodule add <repo> <追加したいフォルダパス>

### submodule 更新
  git submoule update --remote --merge

# git cheet-sheet
```
$ git rev-parse --is-inside-work-tree
現在gitのツリー上にいるかチェック。いる場合trueを返す。

$ git symbolic-ref --quiet --short HEAD
現在のブランチ名を取得

$ git branch
リモート追跡ブランチ以外の Local Branch 確認

$ git branch -a
全ての Local Branch 確認

$ git status
ファイル状態確認

$ git add --dry-run .
addで実行される予定内容表示

$ git ls-files
Local Repository Staging ファイルリスト表示

$ git diff
WorkTree と Staging の差異表示
(ソース差異なので膨大なログが表示されます)

$ git diff --staged
Staging と Committing の差異表示

$ git log -2
Commit 履歴 最新２コミット表示

$ git log -2 --stat
Commit 履歴２コミット表示 + 変更ファイル表示

$ git log -2 --patch
$ git log -2 --p
Commit ファイル差分 ２コミット表示
( そのままだとコード全表示で膨大な行数　になるため、
　$ git log -2 -p など表示を減らすためオプションを組み合わせるのがオススメ )

$ $ git log -p ファイルパス/ファイル名
( 誰が編集したかなど ) 特定ファイルの変更履歴を表示

$ git stash list
保存状態一覧表示

$ git clean -nd
Untrackedファイルの確認

$ git show
最新 Commit 内容表示

$ git branch -r
Remote Branch 確認

$ git remote
Remoteリポジトリ表示

$ git remote -v
Remoteリポジトリ + URL 表示

$ git remote rm origin
Remoteリポジトリ削除

$ git help
ヘルプページ表示

$ git help -a
Git全コマンドリスト

$ git tag
Tag 一覧表示

$ git reflog
過去の HEAD Commit 一覧表示

$ git config -l
Repository 設定内容表示

$ git config user.email
設定 e-mail 表示

$ git config user.name
設定ユーザー名 表示

$ find ~/ -name ".git"
gitフォルダの場所を忘れてしまった際に使用。.gitがあるフォルダがローカルリポジトリフォルダ

$ git --version
gitインスールバージョン確認

変更
$ git add .
WorkTree ファイルを全て add で Staging

$ git commit -m "commit comment"
コメントを付けて commit 実行

$ git commit -am "commit comment"
add & コメント付きで commit 実行

$ git commit -F- <<EOM
複数行コメントでコミット 1

$ git commit -m "コメント1行目" -m "コメント2行目" -m "コメント3行目"
複数行コメントでコミット 2

$ git commit --amend
直前のコミットを編集

$ git push origin master
Remote Repository に Local Repository を反映

$ git push -f origin master
Remote Repository に Local Repository を強制反映
上記 -f なしで conflict などで rejected エラー発生したときも
エラー回避しPush可能。

$ git fetch
Remote Bookmark をダウンロード。FETCH_HEADブランチ作成

$ git pull
Local WorkTree に Remote Repository を ダイレクト反映
※ git pull しても、git fetch と同じ状態になり merge まで実行されないケースがある。
　その際は再度 git merge origin/ブランチ名 で解決する。

$ git pull origin <Remote Branch Name>
既に存在する Local Branch へ 最新の Remote Branch を反映
※ ! [rejected] error: failed to push some refs ~
　といったコンフリクト(競合)エラー発生時にも有効

$ git branch <branch name>
branch 作成

$ git branch -m <old branch name> <new branch name>
branch 名 変更

$ git checkout <branch name>
作業 branch (HEAD) 変更
WorkTree / Index も 作業branch に合わせたファイル内容に変更

$ git checkout -b <branch name>
上記 branch作成 & 作業 branch (HEAD) 変更 (同時実行)

$ git checkout -b feature/hogehoge origin/feature/hogehoge
( developなどをpullした上で )
ローカル上にない Remote Branch を、ローカル上に作成・移動

$ git merge <branch name>
現在の HEAD branch の Working / Index / Local Repository 全てに、
別の branch を 統合

merge - 親 Commit が２つになる
Rebase - 親 Commit が１つになる

$git stash
変更退避

$ git branch --delete ブランチ名
$ git branch -D ブランチ名
ブランチ削除

$ git reflog
削除したブランチの最後のコミットを見つけ
$ git branch ブランチ名 HEAD@{ログ番号}
ブランチ復活

$ git reset
全ての add を取り消し
Index を WorkTree 状態に戻す

$ git reset HEAD <file>
Staging を Commit の状態に戻す

$ git reset --soft HEAD^
Local Repository のみ 以前の Commit 状態に戻す ( 最新の Commit 取り消し )

$ git reset HEAD^
Local Repository / Staging ２つを、以前の Commit 状態に戻す

$ git reset --hard HEAD
HEAD / Index / WorkTree 全てを、最新 Commit 状態に戻す
( WorkTree差分データが消えるので要注意 )

$ git reset --hard HEAD^
HEAD / Index / WorkTree 全て を 一つ前の Commit 状態に戻す
( WorkTree差分データが消えるので要注意 )

$ git checkout -- <file>
WorkTree を Staging の状態に戻す

$ git revert
コミット打ち消して記録残る

$ git clean -fd
Untracked ファイルの削除

$ git merge --abort
直前 Merge 取り消し

$ git reflog
復活する可能性のある呪文。。

$ git push --delete origin リモートブランチ名
GitHubなどのリモート上ブランチを削除する

$ git rm -r --cached .
ファイル全体キャッシュ削除
$ git rm -r --cached [ファイル名]
ファイル指定してキャッシュ削除

``
# gitflow

$ git flow init -d`
ローカルリポジトリを初期化し推奨ブランチ名を自動で生成

$ git clone --bare --shared フォルダ名共有リポジトリ名.git
リポジトリ名.gitの共有リポジトリを作成する
--bareオプション
作業フォルダを持たないリポジトリ
--sharedオプション
リポジトリに書き込みパーミッションを追加

$ cd フォルダ
$ git remote add origin ../共有リポジトリ名.git
デフォルトのプッシュ先を共有リポジトリに設定

$ git flow feature start ブランチ名
新規開発のブランチ名を指定してブランチを作成

$ git branch -vv
ブランチをverboseで参照

$ git flow feature finish ブランチ名
developブランチにマージされたうえで削除される。

$ git flow feature publish ブランチ名
ブランチ名のfeatureブランチを共有

$ git flow feature track ブランチ名
共有されているブランチを取得する

$ git branch -d feature/ブランチ名
不要になったfeature/ブランチを削除する

# リリース作業
```
$ git flow release start ver1.1
リリースブランチver1.1を開始

$ git flow release publish ver1.1
リリースブランチver1.1を共有

$ git flow release track ver1.1
リリースブランチver1.1を追跡

$ git flow release finish ver1.1
リリースブランチを終了. developとmasterにマージされmasterにはタグを設定する

$ git push --all
ローカルのブランチ全てをpushする
```

# リリース後のバグ修正
```
$ git flow hotfix start ver1.2.1
バグ修正ブランチver1.2.1を開始、masterブランチからhotfixブランチが作成

$ git flow hotfix publish ver1.2.1
バグ修正ブランチver1.2.1を共有

$ git flow hotfix track ver1.2.1
バグ修正ブランチを追跡

$ git flow hotfix finish ver1.2.1
バグ修正ブランチを終了、developとmasterにマージされ、masterにタグを残す







