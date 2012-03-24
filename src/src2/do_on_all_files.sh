#!/usr/bin/env bash

for i in $(ls | grep -E "^*\.(cpp|hpp)")
    do
        sed s/FunctionObject/Listener/g $i > temp.tmp

        mv temp.tmp $i
    done
