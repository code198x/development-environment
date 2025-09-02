# Atari ST Development Environment
# Motorola 68000 processor with custom chips
FROM ubuntu:20.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    vim \
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Install VASM 68000 assembler for Atari ST
WORKDIR /tmp
RUN wget http://server.owl.de/~frank/tags/vasm1_9e.tar.gz && \
    tar xzf vasm1_9e.tar.gz && \
    cd vasm && \
    make CPU=m68k SYNTAX=mot && \
    cp vasmm68k_mot /usr/local/bin/ && \
    make CPU=m68k SYNTAX=std && \
    cp vasmm68k_std /usr/local/bin/ && \
    cd .. && \
    rm -rf vasm vasm1_9e.tar.gz

# Install VLINK linker
RUN wget http://server.owl.de/~frank/tags/vlink0_17a.tar.gz && \
    tar xzf vlink0_17a.tar.gz && \
    cd vlink && \
    make && \
    cp vlink /usr/local/bin/ && \
    cd .. && \
    rm -rf vlink vlink0_17a.tar.gz

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]