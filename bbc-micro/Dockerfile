# BBC Micro Development Environment
# 6502 processor with sophisticated BBC BASIC OS
FROM ubuntu:20.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    vim \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install CC65 for 6502 assembly (we'll configure for BBC Micro)
RUN apt-get update && apt-get install -y \
    cc65 \
    && rm -rf /var/lib/apt/lists/*

# Install BeebAsm - build from source
WORKDIR /tmp
RUN git clone https://github.com/stardot/beebasm.git && \
    cd beebasm/src && \
    make code && \
    cp ../beebasm /usr/local/bin/ && \
    cd ../.. && \
    rm -rf beebasm

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]