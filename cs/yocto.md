# conf/local.conf

### 追加パッケージをbitbakeする
    IMAGE_INSTALL_append = " cypress-fmac"
    追加できるものは bitbake-layers show-recipesで参照可能なレシピ

### 機能を追加する
    EXTRA_IMAGE_FEATURES_append = " openssh"
    追加できる機能は。。。
 
 ### タスクの追加
addtask after_configure after do_configure before do_build
do_after_configure() {
    install -m 0644 ${WORKDIR}/55573/build.config.field ${B}/.config
}
~            
### 主なタスク
addtask fetch
addtask unpack after do_fetch
addtask configure after do_patch
addtask compile after do_configure
addtask install after do_compile
addtask build after do_populate_sysroot
addtask cleansstate after do_clean
addtask cleanall after do_cleansstate 
