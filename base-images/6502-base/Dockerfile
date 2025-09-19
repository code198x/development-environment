# Base image for 6502-family processors
# Includes common 6502 tools and utilities
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for 6502 family development"
LABEL version="1.0.0"

USER root

# Install 6502-specific dependencies
RUN apt-get update && apt-get install -y \
    # Common libraries for 6502 tools
    zlib1g-dev \
    libpng-dev \
    # Additional tools often needed
    xxd \
    bsdmainutils \
    && rm -rf /var/lib/apt/lists/*

# Create common directories for 6502 development
RUN mkdir -p /opt/6502-tools/bin /opt/6502-tools/share && \
    chown -R code198x:code198x /opt/6502-tools

# Version pinning for reproducible builds
ARG ACME_VERSION=0.97
ARG CC65_VERSION=V2.19

# Install ACME cross-assembler (for Commodore 64, etc.)
RUN cd /tmp && \
    wget -q https://github.com/meonwax/acme/archive/refs/tags/v${ACME_VERSION}.tar.gz && \
    tar -xzf v${ACME_VERSION}.tar.gz && \
    cd acme-${ACME_VERSION}/src && \
    make && \
    cp acme /opt/6502-tools/bin/ && \
    cd / && rm -rf /tmp/acme*

# Install cc65 suite (for NES, Atari, etc.)
RUN cd /tmp && \
    wget -q https://github.com/cc65/cc65/archive/refs/tags/${CC65_VERSION}.tar.gz && \
    tar -xzf ${CC65_VERSION}.tar.gz && \
    cd cc65-* && \
    make PREFIX=/opt/6502-tools && \
    make install PREFIX=/opt/6502-tools && \
    cd / && rm -rf /tmp/cc65*

USER code198x

# Set common environment variables for 6502 development
ENV PATH="/opt/6502-tools/bin:$PATH"
ENV RETRO_ARCH="6502"