#!/bin/bash

function build_video_frames() {
    height=$(identify -format "%[fx:max(h)]" integration-testing/snapshots/0.png)
    convert -size 1x$height canvas:white build/spacer.png

    for i in $(seq 0 68);
    do
        local file="integration-testing/snapshots/new_$i.png"
        local file_old="integration-testing/snapshots/$i.png"
        if [ ! -f "$file" ]; then
            continue
        fi

        convert +append $file_old build/spacer.png $file build/video_$i.png
    done
}

function generate_video() {
    local frames=$(mktemp)
    find "build" -name "video_*.png" | sort -V | while read -r file; do
        echo "file '$(pwd)/$file'" >> "$frames"
    done

    ffmpeg -safe 0 -r 10 -f concat -i "$frames" -c:v libvpx-vp9 -b:v 1M "build/video.webm" > /dev/null 2>&1

    rm $frames
}

function upload_to_imgur() {
    local response=$(curl -s -H "Authorization: Client-ID $IMGUR_TOKEN" -F "image=@build/video.webm" https://api.imgur.com/3/upload)
    echo "$response" | grep -o '"link":"[^"]*' | cut -d\" -f4 > "./build/url"
    echo $response > "./build/full_response"
}

rm "./build/video.webm"
build_video_frames
generate_video
upload_to_imgur
