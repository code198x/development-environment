#!/bin/bash
# Build base images for the retro development environment
# This script builds base images in dependency order

set -e

echo "🔨 Building retro development base images..."

# Build order based on dependencies
BASE_IMAGES=(
    "retro-base"
    "6502-base"
    "z80-base"
    "68000-base"
)

REGISTRY_PREFIX="${DOCKER_REGISTRY:-code198x}"

for base_image in "${BASE_IMAGES[@]}"; do
    echo "📦 Building base image: $base_image"

    # Build the base image
    docker build \
        --platform linux/amd64,linux/arm64 \
        -t "${REGISTRY_PREFIX}/${base_image}:latest" \
        -t "${REGISTRY_PREFIX}/${base_image}:$(date +%Y%m%d)" \
        "base-images/${base_image}/" \
        --progress=plain

    echo "✅ Successfully built ${REGISTRY_PREFIX}/${base_image}:latest"
done

echo "🎉 All base images built successfully!"
echo ""
echo "Available base images:"
for base_image in "${BASE_IMAGES[@]}"; do
    echo "  - ${REGISTRY_PREFIX}/${base_image}:latest"
done