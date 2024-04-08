# conf/local.conf

### 追加パッケージをbitbakeする
    IMAGE_INSTALL_append = " cypress-fmac"
    追加できるものは bitbake-layers show-recipesで参照可能なレシピ

### 機能を追加する
    EXTRA_IMAGE_FEATURES_append = " openssh"
    追加できる機能は。。。
 
  
