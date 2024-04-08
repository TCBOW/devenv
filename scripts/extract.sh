#!/bin/bash

dir=${2-/tmp}
case $1 in
    *.tar.gz|*.tar.Z)
        tar zxvf "$1" -C "$dir"
        ;;
    *.tar.bz2)
        tar jxvf "$1" -C "$dir"
        ;;
    *)
        echo "$1"'の展開方法が不明です' 1>&2
        exit 1
        ;;
esac
