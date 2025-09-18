# Base image for 68000-family processors
# Includes common 68000 tools and utilities
FROM ghcr.io/code198x/retro-base:latest

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
RUN mkdir -p /opt/68000-tools && \
    chown -R retro:retro /opt/68000-tools

USER retro

# Set common environment variables for 68000 development
ENV PATH="/opt/68000-tools/bin:$PATH"
ENV RETRO_ARCH="68000"