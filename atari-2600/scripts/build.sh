#!/bin/bash
# build-2600 - Build helper for Atari 2600 assembly projects

if [ $# -eq 0 ]; then
    echo "Usage: build-2600 <source.asm> [output.bin]"
    echo "Example: build-2600 game.asm game.bin"
    exit 1
fi

SOURCE=$1
OUTPUT=${2:-$(basename "$SOURCE" .asm).bin}

echo "Building $SOURCE -> $OUTPUT"
dasm "$SOURCE" -f3 -o"$OUTPUT" -l"${OUTPUT%.bin}.lst" -s"${OUTPUT%.bin}.sym"

if [ $? -eq 0 ]; then
    echo "Success! Created $OUTPUT"
    echo "Run in emulator: stella $OUTPUT"
else
    echo "Build failed!"
    exit 1
fi