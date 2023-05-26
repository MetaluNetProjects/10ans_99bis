#!/bin/bash

#xrandr -d :0 --output DVI-I-1 --panning 1366x768+0+0
#xrandr -d :0 --output DP-0 --panning 1366x768+1366+0

export DISPLAY=$1

pd -lib Gem -noaudio -nrt -open $(dirname $0)/0Gem.pd

