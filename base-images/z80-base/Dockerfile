# Base image for Z80-family processors
# Includes common Z80 tools and utilities
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for Z80 family development"
LABEL version="1.0.0"

USER root

# Install Z80-specific dependencies
RUN apt-get update && apt-get install -y \
    # Common libraries for Z80 tools
    zlib1g-dev \
    libpng-dev \
    # Required for sjasmplus
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Create common directories for Z80 development
RUN mkdir -p /opt/z80-tools/bin /opt/z80-tools/share && \
    chown -R code198x:code198x /opt/z80-tools

# Version pinning for reproducible builds
ARG SJASMPLUS_VERSION=v1.20.3
ARG PASMO_VERSION=0.5.5

# Install sjasmplus (for ZX Spectrum, MSX, etc.)
RUN cd /tmp && \
    wget -q https://github.com/z00m128/sjasmplus/archive/refs/tags/${SJASMPLUS_VERSION}.tar.gz && \
    tar -xzf ${SJASMPLUS_VERSION}.tar.gz && \
    cd sjasmplus-* && \
    make && \
    cp sjasmplus /opt/z80-tools/bin/ && \
    cd / && rm -rf /tmp/sjasmplus*

# Install pasmo (alternative Z80 assembler)
RUN cd /tmp && \
    wget -q http://pasmo.speccy.org/bin/pasmo-${PASMO_VERSION}.tar.gz && \
    tar -xzf pasmo-${PASMO_VERSION}.tar.gz && \
    cd pasmo-${PASMO_VERSION} && \
    ./configure --prefix=/opt/z80-tools && \
    make && make install && \
    cd / && rm -rf /tmp/pasmo*

USER code198x

# Set common environment variables for Z80 development
ENV PATH="/opt/z80-tools/bin:$PATH"
ENV RETRO_ARCH="z80"