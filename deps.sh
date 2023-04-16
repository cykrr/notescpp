#!/bin/bash
nanovg_src="https://raw.githubusercontent.com/memononen/nanovg/master/src/"
nanovg_files=(
    "nanovg.c"
    "nanovg.h"
    "nanovg_gl.h"
    "stb_image.h"
    "stb_truetype.h"
    "fontstash.h"
)

mkdir -p lib/nanovg
for file in ${nanovg_files[@]}; do
    printf "$file\n"
    curl $nanovg_src$file -o lib/nanovg/$file
done

glad --profile=core --out-path=lib/glad --generator=c  
mv lib/glad/src/glad.{c,cpp}
