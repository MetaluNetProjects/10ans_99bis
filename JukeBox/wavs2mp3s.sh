#!/bin/bash

for x in wavs/*.wav ; do
	filename=`basename $x`
	soundname=${filename:0:-4}
	echo encoding $soundname...
	#ffmpeg -i $x -codec:a libmp3lame -qscale:a 2 mp3s/$soundname.mp3
	lame --preset standard $x mp3s/$soundname.mp3
done
echo finished

#ffmpeg -i input.wav -codec:a libmp3lame -qscale:a 2 output.mp3
