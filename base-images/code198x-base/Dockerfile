# Base image for all Code Like It's 198x development environments
# Provides common build tools and utilities
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="Base image for Code Like It's 198x retro assembly development"
LABEL version="1.0.0"

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV WORKSPACE=/workspace

# Install common build dependencies
RUN apt-get update && apt-get install -y \
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
    bison \
    && rm -rf /var/lib/apt/lists/*

# Create workspace directory
WORKDIR $WORKSPACE

# Set up common environment
RUN useradd -m -s /bin/bash code198x && \
    chown -R code198x:code198x $WORKSPACE

USER code198x