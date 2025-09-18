# Base image for 6502-family processors
# Includes common 6502 tools and utilities
FROM ghcr.io/code198x/retro-base:latest

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
    hexdump \
    && rm -rf /var/lib/apt/lists/*

# Create common directories for 6502 development
RUN mkdir -p /opt/6502-tools && \
    chown -R retro:retro /opt/6502-tools

USER retro

# Set common environment variables for 6502 development
ENV PATH="/opt/6502-tools/bin:$PATH"
ENV RETRO_ARCH="6502"