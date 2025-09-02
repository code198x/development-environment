#!/bin/bash
# build-apple2 - Build helper for Apple II assembly projects

if [ $# -eq 0 ]; then
    echo "Usage: build-apple2 <source.asm> [output.dsk]"
    echo "Example: build-apple2 program.asm program.dsk"
    exit 1
fi

SOURCE=$1
OUTPUT=${2:-$(basename "$SOURCE" .asm).dsk}
BINARY=$(basename "$SOURCE" .asm)

echo "Building $SOURCE -> $OUTPUT"

# Assemble with ca65 (Apple II target)
ca65 -t apple2 "$SOURCE" -o "${BINARY}.o"
if [ $? -ne 0 ]; then
    echo "Assembly failed!"
    exit 1
fi

# Link with ld65
ld65 -t apple2 "${BINARY}.o" -o "$BINARY"
if [ $? -ne 0 ]; then
    echo "Linking failed!"
    exit 1
fi

# Create disk image with AppleCommander (if Java available)
if command -v java >/dev/null 2>&1 && [ -f /usr/local/bin/applecommander.jar ]; then
    java -jar /usr/local/bin/applecommander.jar -cc140 "$OUTPUT" BLANK
    java -jar /usr/local/bin/applecommander.jar -as "$OUTPUT" "$BINARY" < "$BINARY"
    echo "Success! Created $OUTPUT disk image"
    echo "Run in emulator: Load $OUTPUT"
else
    echo "Success! Created $BINARY binary"
    echo "Use AppleCommander to create disk image for emulator"
fi

# Clean up
rm -f "${BINARY}.o" "$BINARY"