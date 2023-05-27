#!/bin/bash

for x in mp3s/*.mp3 ; do
	filename=`basename $x`
	soundname=${filename:0:-4}
	echo decoding $soundname...
	echo ffmpeg -i $x wavs/$soundname.wav
	#lame --preset standard $x mp3s/$soundname.mp3
done
echo finished

#ffmpeg -i input.wav -codec:a libmp3lame -qscale:a 2 output.mp3
