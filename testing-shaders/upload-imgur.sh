#!/bin/bash

file=$(ls *_new.png 2>/dev/null | head -n 1)
file_old="${file/_new/}"
[ -z "$file" ] && exit 1
[ -z "$IMGUR_TOKEN" ] && exit 1

height=$(identify -format "%[fx:max(h)]" $file)
convert -size 1x$height canvas:black spacer.png
convert +append $file_old spacer.png $file failed_file.png

response=$(curl -s -H "Authorization: Client-ID $IMGUR_TOKEN" -F "image=@failed_file.png" https://api.imgur.com/3/upload)
echo "$response" | grep -o '"link":"[^"]*' | cut -d\" -f4 > url

rm spacer.png
rm failed_file.png
