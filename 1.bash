#!/bin/bash
read -p "Enter prefix: " PREFIX
read -p "Enter suffix: " SUFFIX

for file in $(pwd)/*
    do
    name=$(basename $file)
    suffixname=${name##*.}
    if [[ -f $file ]] && [[ "$suffixname" == "$SUFFIX" ]]; then
    	mv -v $name $PREFIX"_"$name
    fi
done

