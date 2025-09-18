#!/bin/bash

# Build and push Docker images for all supported systems
# Usage: ./build-images.sh [--push]

set -e

DOCKER_ORG="code198x"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DOCKER_DIR="$SCRIPT_DIR/../docker"
PUSH_IMAGES=false

# Parse arguments
if [ "$1" == "--push" ]; then
    PUSH_IMAGES=true
fi

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔨 Building Docker Images for Code198x Development Environment${NC}"
echo

# Systems to build
systems=(
    "commodore-64"
    "sinclair-zx-spectrum"
    "nintendo-entertainment-system"
    "commodore-amiga"
)

# Track results
successful_builds=()
failed_builds=()

# Build each system's Docker image
for system in "${systems[@]}"; do
    dockerfile="$SCRIPT_DIR/../$system/Dockerfile"
    tag="$DOCKER_ORG/$system:latest"

    echo -e "${YELLOW}Building $system...${NC}"

    if [ ! -f "$dockerfile" ]; then
        echo -e "${RED}  ✗ Dockerfile not found: $dockerfile${NC}"
        failed_builds+=("$system")
        continue
    fi

    # Build the image
    if docker build -f "$dockerfile" -t "$tag" "$SCRIPT_DIR/../$system" 2>&1 | tail -5; then
        echo -e "${GREEN}  ✓ Successfully built $tag${NC}"
        successful_builds+=("$system")

        # Push if requested
        if [ "$PUSH_IMAGES" = true ]; then
            echo -e "${YELLOW}  Pushing $tag...${NC}"
            if docker push "$tag"; then
                echo -e "${GREEN}  ✓ Successfully pushed${NC}"
            else
                echo -e "${RED}  ✗ Failed to push${NC}"
            fi
        fi
    else
        echo -e "${RED}  ✗ Failed to build $system${NC}"
        failed_builds+=("$system")
    fi

    echo
done

# Summary
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${BLUE}Build Summary${NC}"
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

if [ ${#successful_builds[@]} -gt 0 ]; then
    echo -e "${GREEN}✓ Successful builds (${#successful_builds[@]}):${NC}"
    for system in "${successful_builds[@]}"; do
        echo "  - $system"
    done
fi

if [ ${#failed_builds[@]} -gt 0 ]; then
    echo -e "${RED}✗ Failed builds (${#failed_builds[@]}):${NC}"
    for system in "${failed_builds[@]}"; do
        echo "  - $system"
    done
    exit 1
fi

echo
echo -e "${GREEN}🎉 All images built successfully!${NC}"

if [ "$PUSH_IMAGES" = false ]; then
    echo
    echo "To push images to Docker Hub, run:"
    echo "  $0 --push"
fi