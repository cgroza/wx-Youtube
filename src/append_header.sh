#!/usr/bin/env bash

for i in $(ls | grep -E "^*\.(cpp|hpp)")
    do
    cat header.txt $i > temp.tmp
    mv temp.tmp $i
done
