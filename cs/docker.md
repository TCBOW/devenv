### DockerでGitlabオンプレミス構築

Step1. 下記ファイルを適宜編集して作る

``` docker-compose.yml
version: '3'
services:
  gitlab:
    image: 'gitlab/gitlab-ee:latest'
    restart: always
    environment:
      GITLAB_OMNIBUS_CONFIG: |
        external_url 'http://gitlab.example.com:8080'
        gitlab_rails['gitlab_shell_ssh_port'] = 2222
        nginx['listen_port'] = 80
        gitlab_rails['smtp_enable'] = true
        gitlab_rails['smtp_address'] = "smtp.gmail.com"
        gitlab_rails['smtp_port'] = 587
        gitlab_rails['smtp_user_name'] = "your-email@gmail.com"
        gitlab_rails['smtp_password'] = "your-password"
        gitlab_rails['smtp_domain'] = "smtp.gmail.com"
        gitlab_rails['smtp_authentication'] = "login"
        gitlab_rails['smtp_enable_starttls_auto'] = true
        gitlab_rails['smtp_tls'] = false
        gitlab_rails['smtp_openssl_verify_mode'] = 'peer'
    ports:
      - '8080:80'
      - '2222:22'
    volumes:
      - '/srv/gitlab/config:/etc/gitlab'
      - '/srv/gitlab/logs:/var/log/gitlab'
      - '/srv/gitlab/data:/var/opt/gitlab'
```
Step2. 下記実行してroot_passwordを設定する

```
sudo docker-compose up -d
docker-compose ps
```

Step3. 下記実行してroot_passwordを設定する

```
sudo docker-compose exec gitlab gitlab-rails console -e production

irb(main):001:0> user = User.where(id: 1).first
=> #<user id:1 @root>
irb(main):002:0> user.password = 'root_password'
=> "root_password"
irb(main):003:0> user.password_confirmation = 'root_password'
=> "root_password"
irb(main):004:0> user.save!
=> true
irb(main):005:0> exit
```

Step4. ブラウザでログインする (終わり)


# dockerに proxyをさす
    systemdに環境変数を設定する
    $ sudo systemctl edit docker
    1[Service]
     Environment = 'http_proxy=http://192.168.1.10:8080' 'https_proxy=http://192.168.0.10:8080'
    Dockerクライアントを設定する
    $ vim ~/.docker/config.json
    ```
    {
  "proxies": {
    "default": {
      "httpProxy": "http://192.168.0.10:8080",
      "httpsProxy": "http://192.168.0.10:8080"
      }
    }
  }
    ``` 
# Redmineサーバーを立てる

    $ sudo docker pull redmine
    $ sudo docker images
    $ docker volume create --name main-redmine-db
    $ docker volume create --name main-redmine-files
    $ docker volume create --name main-redmine-plugins
    $ docker volume create --name main-redmine-vplugins
    $ docker volume create --name main-redmine-themes

    $ mkdir -p ~/dockerDB/redmine
    $ mkdir -p ~/dockerDB/redmine-pgdata
    $ sudo docker run -d --name my-redmine-postgres -v ~/dockerDB/redmine-pgdata:/var/lib/postgresql/data/gpd
ata -e PGDATA=/var/lib/postgresql/data/pgdata -e POSTGRES_PASSWORD=secret -e POSTGRES_USER=redmine postgres:9.5.0

    $ sudo docker run -d --restart=always --name main-redmine \
             -v main-redmine-files:/usr/src/redmine/files \
             -v main-redmine-plugins:/usr/src/redmine/plugins \
             -v main-redmine-vplugins:/usr/src/redmine/vendor/plugins \
             -v main-redmine-themes:/usr/src/redmine/public/themes \
             -e REDMINE_DB_PASSWORD=rdpassword \
             -p 3000:3000 --link main-postgres:postgres redmine:3.3.4
    確認
    $ sudo docker ps
参考
https://kiracchi.com/2017/01/17/docker_redmine_gitlab/
redmineを永続化するためのDBと起動方法について
https://qiita.com/ir-shin1/items/65b935b7a57787a76053

## firewalldでRedmineのポートを開ける
    $ sudo apt install farewalld
    $ sudo firewall-cmd --zone=public --add-service=http --permanent
    $ sudo firewall-cmd --zone=public --add-port=3000/tcp --permanent
    $ sudo firewall-cmd --reload
    空いているか確認は
    $ firewall-cmd --list-all
      
# dockerを有効化
    systemctl start docker
    systemctl enable docker

# dockerイメージをダウンロード
    docker pull centos:centos8

# TESTという名前でコンテナを起動
    docker run --privileged -d --name cent8 centos:centos8 /sbin/init

# コンテナにログイン
    docker exec -it TEST /bin/bash

# ローカルに配置されているdocker imageのリストを表示
    docker images
# 起動中か停止中かを確認
    docker ps -a

## 自動起動有効/無効設定
    sudo docker update --restart=always ID #有効化
    sudo docker update --restart=no ID     #無効化


# REFERENCE
    https://mseeeen.msen.jp/activate-docker-and-start-centos7/
