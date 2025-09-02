#!/bin/bash
# Build script for Dragon 32/64 assembly programs
# Uses lwtools (lwasm assembler for 6809)

echo "Dragon 32/64 Assembly Build System"
echo "=================================="

# Function to build a single .asm file
build_program() {
    local source=$1
    local name="${source%.asm}"
    
    echo "Building $source -> $name.bin"
    
    # Assemble with lwasm (6809 assembler)
    lwasm -f raw -o "$name.bin" "$source"
    if [ $? -eq 0 ]; then
        echo "✓ Built $name.bin successfully"
        # Show binary size
        size=$(wc -c < "$name.bin")
        echo "  Binary size: $size bytes"
        
        # Create CAS tape file for Dragon emulator
        lwar -c "$name.cas" "$name.bin"
        if [ $? -eq 0 ]; then
            echo "  Created $name.cas for emulator"
        fi
    else
        echo "✗ Failed to assemble $source"
        return 1
    fi
}

# Build all programs
echo ""
echo "Building Dragon programs..."

for asm in *.asm; do
    if [ -f "$asm" ]; then
        build_program "$asm"
        echo ""
    fi
done

echo "Build complete!"
echo ""
echo "To run in a Dragon emulator:"
echo "  1. MAME: mame dragon32 -cassette programname.cas"
echo "  2. XRoar: xroar -machine dragon32 -tape programname.cas"
echo "  3. Online: Various web-based Dragon emulators"
echo ""
echo "In emulator BASIC, type: RUN\"\" to load and run the program"