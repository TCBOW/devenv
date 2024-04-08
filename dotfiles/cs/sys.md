# system監視などに関する情報

## sarでsystemリソース監視
1.sysstatを有効化する
vim /etc/default/sysstat
false -> trueに編集する

2. sysstatを起動
sudo systemctl enable sysstat
sudo systemctl start sysstat

3. 情報取得間隔を変更したい場合
vim /etc/cron.d/sysstat
5-55/10 * * * * root command -v debian-sa1 > /dev/null && debian-sa1 1 1
↓
5-55/10 * * * * root command -v debian-sa1 > /dev/null && debian-sa1 60 10
で10 -> 1分間隔に変更できる

## vmstat

vmstatコマンドは、物理メモリやスワップ領域の詳細な情報や、プロセスやCPUの統計情報などを表示します。  以下はvmstatコマンドの実行例およびその表示項目です。 
￼
「procs」欄：プロセスの統計情報を表示 
  ・r　実行待ちプロセスの数 
  ・b　I/O待ちなどで割り込み不可のスリープ状態にあるプロセスの数 
  ・w　スワップアウトされているプロセスの数(w列が表示されない場合もある)  
「memory」欄：メモリの使用状況を表示 
  ・swpd　使用中のスワップ領域のサイズ 
  ・free　空いている物理メモリのサイズ 
  ・buff　バッファキャッシュのサイズ 
  ・cache　ページキャッシュのサイズ  
  「swap」欄：スワップイン・アウトの状況を表示 
  ・si　スワップインされているメモリのサイズ(KB/秒) 
  ・so　スワップアウトされているメモリのサイズ(KB/秒)  
  「io」欄：ディスクI/Oの状態を表示 
  ・bi デバイスからの読み取りブロック数/秒 
  ・bo デバイスへの書き込みブロック数/秒  
「system」欄：割り込み回数やコンテキストスイッチ回数を表示
  ・in　1秒あたりの割り込み回数(クロック割り込み含む) 
  ・cs　1秒あたりのコンテキストスイッチ回数  
「cpu」欄：CPUの使用状況を表示 ・
  ・us　ユーザプロセスの割合 
  ・sy　システムプロセス(カーネル)の割合 
  ・id　アイドル時間の割合 
  ・wa　I/O待ち時間の割合 
  ・st　バーチャルマシンに使用された時間の割合
