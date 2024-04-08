#!/bin/bash

function usage(){
    echo usage
}

if [ $# -le 8 ]; then
    for N in `seq 1 $#`;
    do
        if [[ ${@:$N:1} =~ [0-3] ]] && [[ ${@:($N+1):1} =~ [down|up] ]]; then
            echo hoge ${@:$N:1} ${@:($N+1):1} 
        fi
    done
else
    usage 
fi
