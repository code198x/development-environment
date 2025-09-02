# Atari 800/400/XL/XE Development Environment
# 6502 processor with ANTIC/GTIA/POKEY custom chips
FROM ubuntu:20.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Install ca65 assembler (part of cc65 suite)
# Can assemble for Atari 800 as well
RUN apt-get update && apt-get install -y \
    cc65 \
    && rm -rf /var/lib/apt/lists/*

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]