# Base image for Z80-family processors
# Includes common Z80 tools and utilities
FROM code198x/retro-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for Z80 family development"
LABEL version="1.0.0"

USER root

# Install Z80-specific dependencies
RUN apt-get update && apt-get install -y \
    # Common libraries for Z80 tools
    zlib1g-dev \
    libpng-dev \
    # Z80-specific tools
    # (placeholder for specific Z80 utilities)
    && rm -rf /var/lib/apt/lists/*

# Create common directories for Z80 development
RUN mkdir -p /opt/z80-tools && \
    chown -R retro:retro /opt/z80-tools

USER retro

# Set common environment variables for Z80 development
ENV PATH="/opt/z80-tools/bin:$PATH"
ENV RETRO_ARCH="z80"