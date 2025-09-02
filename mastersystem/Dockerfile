# Sega Master System Development Environment
# Z80 processor with advanced VDP graphics chip
FROM ubuntu:20.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    unzip \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Install WLA-DX assembler (try package first, build if needed)
RUN apt-get update && apt-get install -y wla-dx || \
    (cd /tmp && \
     wget -O wla-dx.tar.gz https://github.com/vhelin/wla-dx/archive/refs/tags/v10.5.tar.gz && \
     tar xzf wla-dx.tar.gz && \
     cd wla-dx-10.5 && \
     mkdir build && cd build && \
     cmake .. && make && make install && \
     cd ../.. && rm -rf wla-dx*) \
    && rm -rf /var/lib/apt/lists/*

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]