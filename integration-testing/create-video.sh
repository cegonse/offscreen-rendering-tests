#!/bin/bash

height=$(identify -format "%[fx:max(h)]" integration-testing/snapshots/0.png)
convert -size 1x$height canvas:white build/spacer.png

counter=0
for i in $(seq 0 68);
do
    file="integration-testing/snapshots/new_$i.png"
    file_old="integration-testing/snapshots/$i.png"
    if [ ! -f "$file" ]; then
        continue
    fi

    convert +append $file_old build/spacer.png $file build/video_$i.png
done

frames=$(mktemp)
find "build" -name "video_*.png" | sort -V | while read -r file; do
    echo "file '$(pwd)/$file'" >> "$frames"
done

echo $frames
ffmpeg -safe 0 -r 10 -f concat -i "$frames" -c:v libvpx-vp9 -b:v 1M "build/video.webm"
