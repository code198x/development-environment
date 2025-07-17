#!/bin/bash
# makeadf - Create bootable ADF from executable

if [ $# -eq 0 ]; then
    echo "Usage: makeadf <executable> [output.adf]"
    echo "Example: makeadf game game.adf"
    exit 1
fi

EXECUTABLE=$1
ADF=${2:-$(basename "$EXECUTABLE").adf}

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: $EXECUTABLE not found!"
    exit 1
fi

echo "Creating bootable ADF: $ADF"

# Create new ADF
xdftool create "$ADF" bootable

# Write executable
xdftool "$ADF" write "$EXECUTABLE"

# Install boot block
xdftool "$ADF" boot install boot1x

if [ $? -eq 0 ]; then
    echo "Success! Created $ADF"
    echo "Contents:"
    xdftool "$ADF" list
else
    echo "Failed to create ADF!"
    exit 1
fi