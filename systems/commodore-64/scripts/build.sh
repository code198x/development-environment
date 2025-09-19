#!/bin/bash
# build-c64 - Simple build helper for C64 assembly projects

if [ $# -eq 0 ]; then
    echo "Usage: build-c64 <source.asm> [output.prg]"
    echo "Example: build-c64 main.asm game.prg"
    exit 1
fi

SOURCE=$1
OUTPUT=${2:-$(basename "$SOURCE" .asm).prg}

echo "Building $SOURCE -> $OUTPUT"
acme -f cbm -o "$OUTPUT" "$SOURCE"

if [ $? -eq 0 ]; then
    echo "Success! Created $OUTPUT"
    echo "Run in emulator: x64sc $OUTPUT"
else
    echo "Build failed!"
    exit 1
fi