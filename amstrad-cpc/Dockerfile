# Amstrad CPC Development Environment
# Z80 processor with unique Gate Array graphics and CRTC
FROM ubuntu:20.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    unzip \
    python3 \
    python3-pip \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Install WLA-DX assembler (works great for Z80)
WORKDIR /tmp
RUN apt-get update && apt-get install -y cmake && \
    wget -O wla-dx.tar.gz https://github.com/vhelin/wla-dx/archive/refs/tags/v10.5.tar.gz && \
    tar xzf wla-dx.tar.gz && \
    cd wla-dx-10.5 && \
    mkdir build && cd build && \
    cmake .. && make && make install && \
    cd ../.. && rm -rf wla-dx* && \
    rm -rf /var/lib/apt/lists/*

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]