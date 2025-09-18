# cc65 for Nintendo Entertainment System
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="cc65 assembler suite for NES development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    && rm -rf /var/lib/apt/lists/*

# Build cc65 from source
RUN git clone https://github.com/cc65/cc65.git /tmp/cc65 && \
    cd /tmp/cc65 && \
    make && \
    make install PREFIX=/usr/local && \
    rm -rf /tmp/cc65

# Create workspace directory
WORKDIR /workspace

# Copy NES configuration file
COPY nes.cfg /usr/local/share/cc65/cfg/

# Create wrapper script for easier usage
RUN echo '#!/bin/bash\nif [ "$1" = "build" ]; then\n  ca65 main.asm -o main.o && ld65 main.o -C /usr/local/share/cc65/cfg/nes.cfg -o program.nes\nelse\n  ca65 "$@"\nfi' > /usr/local/bin/nes-build && \
    chmod +x /usr/local/bin/nes-build

# Set ca65 as the entrypoint
ENTRYPOINT ["ca65"]

# Default command shows version
CMD ["--version"]