export PATH=/Applications/MacVim.app/Contents/MacOS:$PATH
export PATH=/Library/Frameworks/Python.framework/Versions/2.7/bin/python:$PATH
alias=`pwd | tr -d "\n" | pbcopy`
# Setting PATH for Python 3.5
# The original version is saved in .bash_profile.pysave
PATH="/Library/Frameworks/Python.framework/Versions/3.5/bin:${PATH}"
PATH="/usr/local/sbin:$PATH"
export PATH="/usr/local/opt/openssl@1.1/bin:$PATH"

export PATH

# added by Anaconda3 4.2.0 installer
#export PATH="/Users/ToshiakiSato/anaconda/bin:$PATH"
# added by Anaconda3 5.3.1 installer
# >>> conda init >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$(CONDA_REPORT_ERRORS=false '/Users/ToshiakiSato/anaconda3/bin/conda' shell.bash hook 2> /dev/null)"
if [ $? -eq 0 ]; then
    \eval "$__conda_setup"
else
    if [ -f "/Users/ToshiakiSato/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/Users/ToshiakiSato/anaconda3/etc/profile.d/conda.sh"
        CONDA_CHANGEPS1=false conda activate base
    else \export PATH="/Users/ToshiakiSato/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup

alias pwdc=`pwd | tr -d "\n" | pbcopy`
alias ctags="`brew --prefix`/bin/ctags"
#

#
# <<< conda init <<<
export PATH="/usr/local/opt/php@7.2/bin:$PATH"
export PATH="/usr/local/opt/php@7.2/sbin:$PATH"
export PATH="/usr/local/bin:$PATH"
# added by Anaconda3 2019.10 installer
# >>> conda init >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$(CONDA_REPORT_ERRORS=false '/Users/ToshiakiSato/opt/anaconda3/bin/conda' shell.bash hook 2> /dev/null)"
if [ $? -eq 0 ]; then
    \eval "$__conda_setup"
else
    if [ -f "/Users/ToshiakiSato/opt/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/Users/ToshiakiSato/opt/anaconda3/etc/profile.d/conda.sh"
        CONDA_CHANGEPS1=false conda activate base
    else
        \export PATH="/Users/ToshiakiSato/opt/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda init <<<
#export PS1="\e[1;34m[\u@\e[1;35m\w]\n\e[m\$ "
export PS1="\e[1;34m[\u@\e[1;35m\w]\$ "
export PATH="/usr/local/opt/openssl@1.1/bin:$PATH"
export PATH="/usr/local/opt/ruby/bin:$PATH"
export PATH="/usr/local/opt/libpcap/bin:$PATH"

sshgo() {
     ssh $(/Users/ToshiakiSato/git/devenv/scripts/sshgo/disp.pl $1)
}

go() {
	cd $(/Users/ToshiakiSato/git/devenv/scripts/go/disp.pl $1)
	ls -F
}

centgo() {
	ssh -i id_rsa tochibow9@192.168.1.11
}

ubuntugo() {
	ssh -i id_rsa tochibow9@192.168.1.3
}

yum (){
	brew $1
}


