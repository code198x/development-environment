# Base image for all Code Like It's 198x development environments
# Provides common build tools and utilities
# Pinned to specific SHA for reproducible builds
FROM ubuntu@sha256:353675e2a41babd526e2b837d7ec780c2a05bca0164f7ea5dbbd433d21d166fc

LABEL maintainer="code198x"
LABEL description="Base image for Code Like It's 198x retro assembly development"
LABEL version="1.0.0"

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV WORKSPACE=/workspace

# Install common build dependencies
# Use cache mount for apt to improve caching
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget \
    curl \
    unzip \
    cmake \
    pkg-config \
    python3 \
    python3-pip \
    make \
    autoconf \
    automake \
    libtool \
    flex \
    bison

# Create workspace directory
WORKDIR $WORKSPACE

# Set up common environment
RUN useradd -m -s /bin/bash code198x && \
    chown -R code198x:code198x $WORKSPACE

USER code198x