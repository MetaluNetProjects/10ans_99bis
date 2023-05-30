#!/bin/bash

#xrandr -d :0 --output DVI-I-1 --panning 1366x768+0+0
#xrandr -d :0 --output DP-0 --panning 1366x768+1366+0

if [ $DISPLAY = ":0" ];then FLAG="-stderr"; fi

export DISPLAY=$1

pd -lib Gem $FLAG -noaudio -nrt -open $(dirname $0)/0Gem.pd

