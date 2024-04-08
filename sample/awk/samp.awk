#!/bin/awk
cat in.txt | awk '
{
    for i in 0 1 2 3 4 5; do 
        num[i] = substr( $1, 0+i*2, 2)
    done
    print "num[0]":"num[1]":"num[2]":"num[3]":"num[4]":"num[5]"""
}
'

