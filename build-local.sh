#!/bin/bash
# Build toolchains and base images locally for testing

set -e

echo "🔨 Building toolchain images locally..."

# Build existing toolchains that we know work
docker pull ghcr.io/code198x/toolchains/cc65:v2.19 || echo "CC65 not in registry yet"
docker pull ghcr.io/code198x/toolchains/acme:v0.97.0 || echo "ACME not in registry yet"

# Build new toolchains locally
echo "Building LWASM toolchain..."
docker build -t ghcr.io/code198x/toolchains/lwasm:v4.20 toolchains/lwasm/ || echo "LWASM build failed"

echo "Building ASM8080 toolchain..."
docker build -t ghcr.io/code198x/toolchains/asm8080:latest toolchains/asm8080/ || echo "ASM8080 build failed"

echo "Building YASM toolchain..."
docker build -t ghcr.io/code198x/toolchains/yasm:latest toolchains/yasm/ || echo "YASM build failed"

echo "🔨 Building base images locally..."

# Build base images
echo "Building 6809-base..."
docker build -t ghcr.io/code198x/6809-base:latest base-images/6809-base/ || echo "6809-base build failed"

echo "Building 8080-base..."
docker build -t ghcr.io/code198x/8080-base:latest base-images/8080-base/ || echo "8080-base build failed"

echo "🔨 Testing a system image..."

# Test C64 build (we know this works)
echo "Building Commodore 64..."
docker build -f systems/commodore-64/Dockerfile -t test-c64-full .

echo "✅ Testing C64 image..."
docker run --rm test-c64-full

echo "🎉 Build test complete!"