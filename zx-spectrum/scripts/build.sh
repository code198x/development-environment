#!/bin/bash
# build-spectrum - Simple build helper for ZX Spectrum assembly projects

if [ $# -eq 0 ]; then
    echo "Usage: build-spectrum <source.asm> [output.tap]"
    echo "Example: build-spectrum main.asm game.tap"
    exit 1
fi

SOURCE=$1
OUTPUT=${2:-$(basename "$SOURCE" .asm).tap}

echo "Building $SOURCE -> $OUTPUT"
sjasmplus "$SOURCE" --lst --tap="$OUTPUT"

if [ $? -eq 0 ]; then
    echo "Success! Created $OUTPUT"
    echo "Load in emulator with: LOAD \"\""
else
    echo "Build failed!"
    exit 1
fi