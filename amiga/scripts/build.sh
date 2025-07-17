#!/bin/bash
# build-amiga - Simple build helper for Amiga assembly projects

if [ $# -eq 0 ]; then
    echo "Usage: build-amiga <source.s> [output]"
    echo "Example: build-amiga main.s game"
    exit 1
fi

SOURCE=$1
OUTPUT=${2:-$(basename "$SOURCE" .s)}

echo "Building $SOURCE -> $OUTPUT"
vasmm68k_mot -Fhunkexe -nosym -o "$OUTPUT" "$SOURCE"

if [ $? -eq 0 ]; then
    echo "Success! Created $OUTPUT"
    echo "Create ADF with: makeadf $OUTPUT"
else
    echo "Build failed!"
    exit 1
fi