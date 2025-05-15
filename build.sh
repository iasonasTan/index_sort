#!/bin/bash

while [ true ]; do
	vim mysort.c
	./compile.sh

	echo "start?"
	in=read
	if [ "$in" == 'n' ]; then
		break
	fi
	
	break
done
