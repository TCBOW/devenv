# Wireshark コマンドサンプル

# filter example

eth.src == **:**:**:**:**:**
eth.dst == **:**:**:**:**:**
eth.src[0:3] == **:**:**            # 特定ベンダー指定のMACアドレス
eth.ig == 1                         # ブロードキャストのみ
ip.addr == 192.168.1.5              # 宛先IPアドレス

arp.opcode == 1
arp.opcode == 2

tcp.port == 443


sudo vim /usr/share/wireshark/init.lua

    enable_lua = true  -> false

# 区間切出し

frame.time >= "2022-01-31 23:57:01.535737420" && frame.time <= "2022-01-31 23:57:29.156466790"


# sniffer方法

sudo wfa_sniffer --port 9999 -if wlp2s0 -host 192.168.1.10 -if2 wlan0 -host2 192.168.1.100 &
 sudo iw dev wlp2s0 set channel 100 80MHz

 sudo wireshark

