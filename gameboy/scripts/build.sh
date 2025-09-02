#!/bin/bash
# Build script for Game Boy assembly programs
# Uses RGBDS (Rednex Game Boy Development System)

echo "Game Boy Assembly Build System"
echo "=============================="

# Function to build a single .asm file
build_program() {
    local source=$1
    local name="${source%.asm}"
    
    echo "Building $source -> $name.gb"
    
    # Assemble with rgbasm
    rgbasm -o "$name.o" "$source"
    if [ $? -ne 0 ]; then
        echo "✗ Assembly failed for $source"
        return 1
    fi
    
    # Link with rgblink
    rgblink -o "$name.gb" "$name.o"
    if [ $? -ne 0 ]; then
        echo "✗ Link failed for $source"
        return 1
    fi
    
    # Fix ROM header with rgbfix
    rgbfix -v -p 0 "$name.gb"
    if [ $? -eq 0 ]; then
        echo "✓ Built $name.gb successfully"
        # Show ROM size
        size=$(wc -c < "$name.gb")
        echo "  ROM size: $size bytes"
        # Clean up object file
        rm -f "$name.o"
    else
        echo "✗ Failed to fix ROM header for $source"
        return 1
    fi
}

# Build all programs
echo ""
echo "Building Game Boy programs..."

for asm in *.asm; do
    if [ -f "$asm" ]; then
        build_program "$asm"
        echo ""
    fi
done

echo "Build complete!"
echo ""
echo "To run in a Game Boy emulator:"
echo "  1. BGB: https://bgb.bircd.org/"
echo "  2. SameBoy: https://sameboy.github.io/"
echo "  3. mGBA: https://mgba.io/"
echo "  4. Online: https://thenewboston.com/emulators/gameboy"
echo ""
echo "ROM files (.gb) can be loaded directly into any Game Boy emulator"