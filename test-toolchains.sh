#!/bin/bash
# Test all toolchain builds locally before pushing

set -e

echo "🔧 Testing all toolchain builds with Ubuntu 24.04..."
echo "================================="

# Track successes and failures
SUCCEEDED=""
FAILED=""

# Function to build and test a toolchain
build_toolchain() {
    local name=$1
    local version=$2

    echo ""
    echo "📦 Building $name:$version..."

    if docker build -t ghcr.io/code198x/toolchains/$name:$version toolchains/$name/ 2>&1 | tail -5; then
        echo "✅ Build successful"

        # Test if the image runs
        if docker run --rm ghcr.io/code198x/toolchains/$name:$version ls /opt 2>/dev/null | head -5; then
            echo "✅ $name:$version - SUCCESS"
            SUCCEEDED="$SUCCEEDED $name:$version"
        else
            echo "❌ $name:$version - Runtime test failed"
            FAILED="$FAILED $name:$version"
        fi
    else
        echo "❌ $name:$version - Build failed"
        FAILED="$FAILED $name:$version"
    fi
}

# Test all toolchains
echo "🔨 Testing toolchains..."

# Existing toolchains
build_toolchain "cc65" "v2.19"
build_toolchain "acme" "v0.97.0"
build_toolchain "sjasmplus" "v1.20.3"
build_toolchain "vasm" "latest"

# New toolchains
build_toolchain "lwasm" "v4.20"
build_toolchain "asm8080" "latest"
build_toolchain "yasm" "latest"
build_toolchain "asl" "latest"
build_toolchain "fasmarm" "latest"
build_toolchain "wla-dx" "latest"

echo ""
echo "================================="
echo "📊 Build Summary:"
echo "✅ Succeeded:$SUCCEEDED"
if [ -n "$FAILED" ]; then
    echo "❌ Failed:$FAILED"
    exit 1
else
    echo "🎉 All toolchains built successfully with Ubuntu 24.04!"
fi