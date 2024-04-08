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



