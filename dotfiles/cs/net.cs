# networkあれこれ

### IPアドレスとMACアドレスの対応をARPキャッシュへ追加する
　arp -s 192.168.1.100
  aa:bb:cc:dd:ee:ff

### ifconfigファイル
    vim /etc/sysconfig/network-scripts/ifcfg-eth1
    systemctl restart NetworkManager
    systemcl restart network

## ifcfgの説明
    * DEFROUTE: 複数のNICがある場合デフォルトのNICとして設定するか
        - yes  このインターフェースをデフォルトルートとして設定します。
        - no  このインターフェースをデフォルトルートとして設定しません。

    * PEERDNS：
        - yes  DNSディレクティブがセットしてある場合は、 /etc/resolv.confを変更します。DCHPを使用する場合、 yesがデフォルトです。
        - no  /etc/resolv.confを変更しません。

    * IPV4＿FAILURE_FATAL: IPv4が使えない時IPv6を使うか
    * IPV6INIT: IPv6の有効化


### NICのモデルを確認する
    dmesg | grep eth0
    modinfo ロードされているモジュール名(例えばtg3)
  その他のやり方
    ethtool -i eth0

### NetworkManagerをリスタートする
Cent7
    systemctl restart NetworkManager
    systemctl restart network
Cent6
    /etc/rc.d/init.d/NetworkManager restart
    /etc/rc.d/init.d/network restart

## MTUとMSS

MTUはIPベースの考え方でＮＷ機器やホストが送受信できる、IPヘッダを含めた最大サイズ

MSSはTCPベースの考え方でＴＣＰヘッダを含めない最大サイズ
この設定値はクライアントやサーバ等のホスト端末に設定が入っている。大抵はＭＴＵの設定に沿って
ＩＰ＋ＴＣＰヘッダ40バイト分を差し引いた1460バイトになっている。


* netif_napi_add( ndev, &lp->napi[i], svCbEth_rx_poll, XAXIENET_NAPI_WEIGHT );
    ch毎にsvCbEth_rx_pollを登録する。svCbEth_probeで実行される

* napi_schedule(): NAPI処理をスケジュールする,svCbEth_mcdma_rx_intr_handlerで実行される

* netif_recieve_skb: 上位ネットワークスタックへ受信skbを渡す。

* skb_put(skb, length): skbの内部ポインタをlength分調整する。

* netif_receive_skb(skb); 



* netif_msg_rx_status( slp ); ethtool mgs_lvlで rx_status がONか確認する。

* netif_msg_rx_pktdata( slp ); ethtool mgs_lvlで pktdata がONか確認する。











