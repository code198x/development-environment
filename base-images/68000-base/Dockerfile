# Base image for 68000-family processors
# Includes common 68000 tools and utilities
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for 68000 family development"
LABEL version="1.0.0"

USER root

# Install 68000-specific dependencies
RUN apt-get update && apt-get install -y \
    # Common libraries for 68000 tools
    zlib1g-dev \
    libpng-dev \
    # 68000-specific tools
    # (placeholder for specific 68000 utilities)
    && rm -rf /var/lib/apt/lists/*

# Create common directories for 68000 development
RUN mkdir -p /opt/68000-tools/bin /opt/68000-tools/share && \
    chown -R code198x:code198x /opt/68000-tools

# Version pinning for reproducible builds
ARG VASM_VERSION=1_9e
ARG VLINK_VERSION=0_17a

# Install VASM (multi-target assembler for 68000)
# Using specific version from official release
RUN cd /tmp && \
    wget -q http://phoenix.owl.de/tags/vasm${VASM_VERSION}.tar.gz && \
    tar -xzf vasm${VASM_VERSION}.tar.gz && \
    cd vasm && \
    make CPU=m68k SYNTAX=mot && \
    cp vasmm68k_mot /opt/68000-tools/bin/ && \
    cp vobjdump /opt/68000-tools/bin/ && \
    cd / && rm -rf /tmp/vasm*

# Install vlink (linker for VASM)
RUN cd /tmp && \
    wget -q http://phoenix.owl.de/tags/vlink${VLINK_VERSION}.tar.gz && \
    tar -xzf vlink${VLINK_VERSION}.tar.gz && \
    cd vlink && \
    make && \
    cp vlink /opt/68000-tools/bin/ && \
    cd / && rm -rf /tmp/vlink*

USER code198x

# Set common environment variables for 68000 development
ENV PATH="/opt/68000-tools/bin:$PATH"
ENV RETRO_ARCH="68000"