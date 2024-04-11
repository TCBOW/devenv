### errnoの意味を表示
    $ sudo apt install moreutils
    $ errno 65
    ENOPKG 65 パッケージはインストールされていません

### man 日本語化
    sudo apt install manpoages-ja manpages-ja-dev
    sudo apt install manpages-ja manpages-ja-dev
    sudo apt install language-pack-ja
    sudo update-locale LANG=ja_JP.UTF-8
    戻す場合
    sudo update-locale LANG=en_US.UTF-8

### snap プロキシ設定
    sudo snap set system proxy.http=http://proxy.canon.co.jp:10080
    sudo snap set system proxy.https=http://proxy.canon.co.jp:10080

### apt の履歴参照
    less /var/log/apt/history.log
   次を表示したい場合は
    zless /var/log/apt/history.log.1.gz

### コンソールサイズをリサイズする
    export COLUMNS=100
    export LINES=35
    eval `resize`

### clc
    cloc <source> --json | jq '.SUM' | jq '.code'

### record console log
    script <logfile>
    
    exit

### binary Hex dump
    od  litle endian
    hex big endian

    od -Ax -tx <binary> | less 

    hexdump -C <binary> | less // bigendian
    hexdump <binary> | less    // littleendian

### rsync
    rsync --checksum --delete -rlopcv ${File} ${RemoteHost}:${TestDir}

### SSHkeyの登録

ssh-copy-id -i ~/.ssh/id_ed25519.pub <user>@<IP>

### LinuxからWindowsへリモートデスクトップ

    remmina を起動
    172.23.150.38 に接続

### .configure でクロスコンパイル
    ./configure --host=aarch64-linux-gnu
    make

### 固定IP設定方法
    固定IP申請で取得した情報をセット
> 『IPアドレス』　　　　　　　　　172.29.40.44
> 『サブネットマスク』            255.255.252.0
> 『デフォルトゲートウエイ』　　　172.29.43.254
> 『設置場所』                    川崎／高層棟／12階／全域
> 『ＰＣ管理番号』                A-2013-P49383
DNSの設定を忘れずに
sudo vim /etc/systemd/resolved.conf に下記をセット
    DNS=172.26.224.1 150.61.109.1

# systemctl restart resolve-conf.service
    
### 現在使っているnetworkドライバを確認する
    sudo lshw -C network

### PTP関連
    ethtool -T <DEVICENAME>   #NICがPTP対応か否か確認

### NTP
    sudo ntpdate <URL> 

### phc2sys
    *PHCをsystemタイマに合わせる
    phc2sys -s <ETHNAME> -c CLOCK_REALTIME -w &
    *systemタイマをPHCに合わせる
    phc2sys -s CLOCK_REALTIME -c <ETHNAME> -w &

### hardwareクロックを確認する
    sudo hwclock --show --debug

### systemtimer write down to hwclock
    sudo hwclock -w

### Etherドライバの情報を確認する方法
    dmesg　でeth0などインタフェース名で検索して igbなどコマンドログを吐いている名前を探す
    modinfo igb　　#←でロードされているドライバモジュールの詳細を確認
    modinfo -F version igb # でバージョンだけ確認も可
    udevadm info -a --path=/sys/class/net/enp1s0

### interfaceのMTUを広げる
    sudo ifconfig eth0 mtu 9000

### システム時刻の各種表示形式を確認する
    timedatectl

### 定期的にＮＴＰサーバーから時刻を同期する
    vim /etc/systemd/timesyncd.conf
        ntp.cgn.canon.co.jp  を追記
    sudo timedatectl set-ntp true
    上記実行後状態確認でsudo timedatectl statusしてNTP enabled:yesになっていればＯＫ

### NTPサーバーになる
    root@dlp:~# vi /etc/chrony/chrony.conf
    # 20行目：コメント化
    # pool 2.debian.pool.ntp.org offline iburst
    # 同期をとるサーバーを指定
    server ntp.cgn.canon.co.jp offline iburst

    # 69行目：時刻同期を許可する範囲を追記
    # allow 10/8
    # allow 192.168/16
    # allow 172.16/12
    allow 192.168/16
    root@dlp:~# systemctl restart chrony
    # 動作確認
    root@dlp:~# chronyc sources

### google翻訳
    git clone https://github.com/soimort/translate-shell
    cd translate-shell/
    make && sudo make install

    alias transen="trans -b ja:en $1"
    alias transjp="trans -b en:ja $1"
### objdump
    objdump -S -m i386 dry.axf > tmp.txt

### 文字コードを変換する
    * iconvで変換する
    $ iconv -f sjis -t utf-8 sample.pl -o sample.pl

### ホームディレクトリを日本語化
    LANG=C xdg-user-dirs-gtk-update

### ユーザーを追加しパスワードを登録する
    useradd -m <username>   #ホームディレクトリが無ければ作成してユーザを追加
    passwd <username>
    cat /etc/passwd         #ユーザ一覧表示
    cat /etc/shadow         #passwdのハッシュを確認

### 現在のディレクトリをGUIで開く
    xdg-open .

### ^M(アスキー改行コード)をsedで削除する
    $ sed -e s/^M//
    * vimで削除する
    :%s/^M//g

### invalidate  と　flushについて
    * flush キャッシュの吐き出し
        - 指定した領域に該当するキャッシュメモリの内容を実メモリに書き出す。
        - キャッシュからＤＭＡバッファにライトスルーするのでDMACとのコヒーレンスが保てる。
    * invalidate　キャッシュの無効化
        - 指定した領域に該当するキャッシュメモリの内容を無効にする。
        - CPUが読み出すとミスヒットするのでレジスタの情報がキャッシュにロードされる。

### DMAバッファとｱﾄﾞﾚｽアライメント
    * DMACアーキテクチャに依存した制約
        - DMAバスマスタデバイスのデータシートにある〇ＫＢ境界のバッファを指定に従ってＤＭＡバッファは配置する必要がある。
    * キャッシュラインサイズに依存した制約
        - DMAバッファをキャッシュ可能領域に配置する場合はそのアドレスをキャッシュラインサイズの境界に一致させる必要がある。
        　ＤＭＡバッファのサイズはキャッシュラインサイズの整数倍にしておく必要がある。

### 03 - systemctl
    * serviceにプロキシを設定する
    ```
    # プロキシの設定を開始
    sudo systemctl edit snapd.service
     
    # 以下記述
    [Service]
    Environment=http_proxy=http://proxy:port
    Environment=https_proxy=http://proxy:port
     
    # デーモンの設定をリロードしてサービスを再起動
    sudo systemctl daemon-reload
    sudo systemctl restart snapd.service
    ```
### kernelバージョン
    cat /etc/redhad-release

### ifconfigファイル
    vim /etc/sysconfig/network-scripts/ifcfg-eth1
    systemctl restart NetworkManager
    systemcl restart network

### python 3と2のvirtualenvの実行
    cd /home/sato/python_run/
    . py2env/bin/activate
    上記実行でpython2環境に移行出来る。2と3でインストールモジュールを分けたい時に使う

### KVM
    virsh list --all
    virt-manager
自動起動を設定
    sudo virsh autostart centos6.10

自動起動を止める場合
    ls /etc/libvirt/qemu/autostart/

ログを見る
    vim /var/log/messages

### KVMにコンソール接続する GRUBの設定変更
  ホストOSのgrubを編集する
    sudo vim /etc/default/grub
  GRUB_CMDLINE_LINUX="console=tty0 console=ttyS0,115200n8r"を追記
    grub2-mkconfig -o /boot/grub2/grub.cfg

    sudo virsh console centos610

### domainにシリアルコンソールで接続する
    virsh console domain [--devname devicename] [--force] [--safe]

### KVMの各種設定
    vim /etc/libvirt/qemu/centos610.xml

### serviceの起動など
Cent7
    systemctl restart sshd

Cent6
    /etc/rc.d/init.d/sshd restart

### serviceの自動起動
Cent6
    chkconfig --list
    chkconfig sshd on

### CapslockをCtrlキーに変更する
    ~/.profileに下記を記述する
    setxkbmap -option ctrl:nocaps

### patchファイルの生成
    diff -up
    diff -uprN  <変更前ファイル> <変更後ファイル> > パッチファイル名
    git diff <ハッシュ値>

### patch適用
    patch -d < test.patch
    or
    patch -p1 < test.patch

### patch適用を元に戻す
    patch -R -d <適用したファイル名> < <patchファイル名>

### doxygen
    doxygen 

### valgrind
sudo $VALGRIND_PATH --error-limit=no --leak-check=full --show-leak-kinds=all --log-file=$LOGDIR_PATH/${test_name_arg}_valgrind.log $QSROC_PATH --datadir $QSROC_OPT_DATADIR -t $* $count

### 恒久的にホスト名を変更する
sudo hostnamectl set-hostname <HOSTNAME> 

### dmesg クリア
 dmesg -c

### dmesg 出力しない
 dmesg -D

### applicationのヒープ　スタックサイズを確認する
    ./testApp &
    ps -o <testApp_PID>
    cat /proc/<PID>/status | grep -e VmSize -e VmRSS -e VmHWM --VmStk -eVmDat -e VmExe



### ファイルの文字コードを変換する
    nkf 

# Ubuntu関連

### proxy
    vim /etc/apt/apt.conf
    Acquire::http::proxy "http://プロキシアドレス:ポート番号/";
    #を追記

### network設定
    vim /etc/netplan/50-cloud-init.yaml
    netplan apply

### 実行プロセスのステータスを確認する
    ps -ef | grep 実行プロセス名
    pidstat -s PID

### スタックサイズの上限を変更する
    ulimit -s 16384
    または
    ./a.out -s 0x1000000　で実行プロセスの引数に渡してやる

    pidstat -s -p PID,PID
### SDファイルシステム確認
    df -T

### SDデバイスのパーティションを切る
    fdisk -l デバイス名
    （指定したデバイスのパーティション情報を表示する）

    fdisk -l /dev/sda
    （/dev/sdaの情報を表示する）（画面1）

    fdisk -s デバイス名
    （指定したデバイスのブロック数を表示する）

    $ sudo fdisk /dev/sd**

    コマンド (m でヘルプ): t
    No partition is defined yet!
    
    コマンド (m でヘルプ): n
    Partition type:
       p   primary (0 primary, 0 extended, 4 free)
       e   extended
    Select (default p): p
    パーティション番号 (1-4, default 1): 1
    最初 sector (2048-15196159, 初期値 2048):
    初期値 2048 を使います
    Last sector, +sectors or +size{K,M,G} (2048-15196159, 初期値 15196159): +1G
    Partition 1 of type Linux and of size 1 GiB is set
    
    コマンド (m でヘルプ): n
    Partition type:
       p   primary (1 primary, 0 extended, 3 free)
       e   extended
    Select (default p): p
    パーティション番号 (2-4, default 2): 2
    最初 sector (2099200-15196159, 初期値 2099200):
    初期値 2099200 を使います
    Last sector, +sectors or +size{K,M,G} (2099200-15196159, 初期値 15196159):
    初期値 15196159 を使います
    Partition 2 of type Linux and of size 6.3 GiB is set
    
    コマンド (m でヘルプ): p
    
    Disk /dev/sdd: 7780 MB, 7780433920 bytes, 15196160 sectors
    Units = sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O サイズ (最小 / 推奨): 512 バイト / 512 バイト
    Disk label type: dos
    ディスク識別子: 0x6f20736b
    
    デバイス ブート      始点        終点     ブロック   Id  システム
    /dev/sdd1            2048     2099199     1048576   83  Linux
    /dev/sdd2         2099200    15196159     6548480   83  Linux
    
    コマンド (m でヘルプ): t
    パーティション番号 (1,2, default 2): 1
    Hex code (type L to list all codes): b
    
    WARNING: If you have created or modified any DOS 6.xpartitions, please see the fdisk manual page for additionalinformation.
    
    Changed type of partition 'Linux' to 'W95 FAT32'
    
    コマンド (m でヘルプ): p
    
    Disk /dev/sdd: 7780 MB, 7780433920 bytes, 15196160 sectors
    Units = sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O サイズ (最小 / 推奨): 512 バイト / 512 バイト
    Disk label type: dos
    ディスク識別子: 0x6f20736b
    
    デバイス ブート      始点        終点     ブロック   Id  システム
    /dev/sdd1            2048     2099199     1048576    b  W95 FAT32
    /dev/sdd2         2099200    15196159     6548480   83  Linux
    
    コマンド (m でヘルプ): w
    パーティションテーブルは変更されました！
    
    ioctl() を呼び出してパーティションテーブルを再読込みします。
    
    WARNING: Re-reading the partition table failed with error 16: デバイスもしくはリソースがビジー状態です.
    The kernel still uses the old table. The new table will be used at
    the next reboot or after you run partprobe(8) or kpartx(8)
    
    コマンド (m でヘルプ): q
    
    $ sudo mkfs --type=vfat -v -c /dev/sdd1
    
    Searching for bad blocks 80352... 160208... 239824... 319584... 399584... 479456... 559200... 638816... 718944... 799200... 879440... 959568...
    
    $ sudo mkfs --type=ext4 -v -c /dev/sdd2
    Superblock backups stored on blocks:
            32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632


### 大きなものをあぶり出す
    du -s <dir> | sort -n

### 現在のLinuxカーネル
    uname -r

### 不要なLinuxパッケージを削除するで dpkg -l 'linux-image-*'した時に存在する今使っていないカーネルを削除できる
    dpkg -l 'linux-*' | sed '/^ii/!d;/'"$(uname -r | sed "s/\(.*\)-\([^0-9]\+\)/\1/")"'/d;s/^[^ ]* [^ ]* \([^ ]*\).*/\1/;/[0-9]/!d' | xargs sudo apt-get -y purge

### journalが使用しているサイズを確認後、減らす
    du -h /var/log/journal/
    journalctl --vacuum-time=2d
   
### yumのキャッシュを削除
   yum clean all


### peek のインストール 
-  #動画スクリーンキャプチャツール
https://github.com/phw/peek

### SSH HOST認証を省く

scp -o "StrictHostKeyChecking=no" -o "UserKnownHostsFile=/dev/null" -r ./deploy/ root@192.168.10.84:

### wiresahar luaを有効化

    sudo vim /usr/share/wireshark/init.lua

    enable_lua = true  -> false

### wiresharkで各CBACKからの指定スループットが出ていることを確認する方法

    ➀下記いずれかででフィルタする
    
    eth.src == 74:38:b7:d6:05:88
    eth.src == 74:38:b7:d6:06:60
    eth.src == 74:38:b7:d6:06:4c
    
    ②統計　>　キャプチャファイルプロパティ　を選択して　「平均ビット数毎秒」　Mbps　を参照する
    
    または
    
### 経時的なスループットを計測
    ②統計　>　入出力グラフ　を選択して　参照したいポートのフィルタをかけてグラフ参照する
    
### wol 設定
    BIOSでWOLをONにする
    ethtoolでインタフェースのwolがdならgに設定する
    sudo ethtool -s enp4s0 wol g

    上記を書いた/devenv/scripts/wolg をsystemdのユニット定義ファイルに登録する
    sudo cp ${HOME}/git/devenv/scripts/service/wolg.service /etc/systemc/system/
    sudo systemctl daemon-reload
    sudo systemctl enable wolg.service
    sudo systemctl start wolg.service

###  sudo権限付与
$ usermod -G sudo username
$ visudo

 username   ALL=(ALL:ALL) ALL


### lsof
    lsof -i -P | grep "LISTEN"   # LISTENポートのプロセスを確認する

### 共有メモリ
    ipcs  // 自分が獲得している共有メモリやセマフォを参照
    ipcrm shm <id> // 共有メモリの解放

### pythonなどのコマンドバージョンを切り替える

    sudo update-alternatives --config python
    ls /usr/bin/ | grep python
    sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 1
    sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1
    sudo update-alternatives --config python

### grubで仮想レジスタ領域の確保
    $ sudo vim /etc/default/grub
    GRUB_CMDLINE_LINUX="console=ttyS0,115200 mem=0xbfe00000"

        ドライバ（テスト対象など）はこのレジスタ領域に対して実カーネルAPI
        request_mem_region/ioremap_nocache)を通してメモリマップする

    GRUB2の設定を変更するには
    $ sudo grub-mkconfig -o /boot/grub/grub.cfg

        ※GRUB2が起動するたびに読み込まれる設定ファイルは
        /boot/grub/grub.cfg

### dockerでRedmineサーバーを立てる
    $ sudo docker pull redmine
    $ sudo docker images
    $ sudo docker run -d -p 3000:3000 --name some-redmine redmine
    確認は
    $ sudo docker ps

### firewalld で特定ポートを開ける
    $ sudo apt install farewalld
    $ sudo firewall-cmd --zone=public --add-service=http --permanent
    $ sudo firewall-cmd --zone=public --add-port=3000/tcp --permanent
    $ sudo firewall-cmd --reload
    空いているか確認は
    $ firewall-cmd --list-all

### network

## yum

```
    yum history         // history IDを表示する
    yum history undo 4  // history IDを取り消す
```

# Kernel再構築
1.     下記でKernel再構築
       $ make menuconfig
2.     設定が完了すると/linux/.configが更新されるので下記でビルド。
$ make linux
3.     もし下記エラーが出た場合はu-boot-toolsをインストールしてmkimageできるようにする。
"mkimage" command not found - U-Boot images will not be built. "
4.     ビルドが終わると/linux/arch/arm/bootに下記カーネルイメージができる。
uImage: U-Bootでブートされるイメージ　TFTPブートなどに使用。
U-Boot環境変数がTFTP: TFTPブート
U-Boot環境変数がNAND：通常のKernelブート
zImage: gzipで圧縮されたカーネルイメージ
vmlinux: 非圧縮のカーネルイメージ

# U-Boot
デスクトップ用Linuxはx86向けにGRUBだが、組み込み用途はU-Bootが一般的。
U-Boot環境変数でどこからブートするか設定する。
1.     U-Bootはhushに対応しておりコマンドラインで操作可能。
$ printenv
bootcmd=nand read.e 0x800000 0x100000 0x400000; bootm 0x800000
2.     ROMから起動する場合はsetenvで設定する。
$ setenv bootcmd 'nand read.e 0x800000 0x100000 0x400000; bootm 0x800000'
$ saveenv

# 通常のLinuxKernel起動の仕組み
MBR(Master Boot Record)という領域にブートローダがあり、ROMからmvlinuz（非圧縮ELFバイナリ）またはzImage(圧縮バイナリ)を展開してmemcpyで特定のメモリ番地にjumpする。起動は展開を行わない非圧縮バイナリの
 が速くなる。
次にinitrdというファイルが呼ばれてHDDをマウントするデバイスドライバによってルートファイルシステムが利用可能になる。
そして/sbin/initプロセスから各種プログラムが起動する。例えば/etc/initや/etc/rc5dに設定を書く。

# TFTPサーバの設定
1.TFTPサーバにtftpd-hpaをインストール
       $ apt-get install tftpd-hpa
2．設定
       $vim /etc/default/tftp
uImageの設置場所を     /var/lib/tftpboot/　に設定
3. uImageを上記/var/lib/tftpboot/に配置する
4. U-Bootの環境変数にTFTPクライアントの設定をする。
$ setenv bootcmd 'tftp 0xc0700000 uImage; tftp 0xc1180000 ; bootm 0xc0700000'
$ saveenv
5. デーモン化しておく
Defaults for tftpd-hpa
RUN_DAEMON="yes"
OPTIONS="-l -s /var/lib/tftpboot"
6. 再起動する
# xinetdの場合あり
$ /etc/init.d/tftpd-hpa restart

#NFSマウントの方法
1.     NFSサーバをインストール
$ apt-get install nfs-kernel-server
2.     /etc/exports でNFSを許可するマシン（クライアント）とmount対象のディレクトリを設定する。
/path/to/your/directory 168.192.7.2/255.255.255.0(rw,no_root_squash)
3.     Nfsを再起動
$ /etc/init.d/nfs-kernel-server restart
4.     ターゲットデバイスでマウントポイントを作成してマウントする
$ mkdir ./mfs
$ mount -t /path/to/your/directory ./mfs -o nolock

