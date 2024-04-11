### rosパッケージアップデート
  インストール済みのrosパッケージすべての依存関係を調べて、必要ならapt-get installで更新してくれる。
  rosdep update

### rosdepのsudo修正 
  rosdepは基本sudoをつけずに各種操作を実行する。もしつけてしまった場合はこれで修正する。
  sudo rosdep fix-permission

### ros初期化
  ROSインストール時に一度だけ実行する
  sudo rosdep init
 
