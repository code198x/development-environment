#!/bin/bash
# build-nes - Simple build helper for NES assembly projects

if [ $# -eq 0 ]; then
    echo "Usage: build-nes <source.asm> [output.nes]"
    echo "Example: build-nes main.asm game.nes"
    exit 1
fi

SOURCE=$1
OUTPUT=${2:-$(basename "$SOURCE" .asm).nes}
OBJECT=$(basename "$SOURCE" .asm).o

echo "Building $SOURCE -> $OUTPUT"

# Assemble
ca65 "$SOURCE" -o "$OBJECT"
if [ $? -ne 0 ]; then
    echo "Assembly failed!"
    exit 1
fi

# Link
ld65 -C /usr/local/share/cc65/cfg/nes.cfg "$OBJECT" -o "$OUTPUT"
if [ $? -eq 0 ]; then
    echo "Success! Created $OUTPUT"
    echo "Run in emulator: fceux $OUTPUT"
    rm -f "$OBJECT"
else
    echo "Linking failed!"
    rm -f "$OBJECT"
    exit 1
fi