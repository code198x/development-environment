# Sharp X68000 Development Environment
# Advanced 68000-based system with sophisticated graphics and sound
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
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Install vasm for 68000 (same as used for Amiga)
WORKDIR /tmp
RUN git clone https://github.com/kusma/vasm.git && \
    cd vasm && \
    make CPU=m68k SYNTAX=mot && \
    cp vasmm68k_mot /usr/local/bin/ && \
    cp vobjdump /usr/local/bin/ && \
    cd .. && \
    rm -rf vasm

# Install vlink linker
RUN wget http://sun.hasenbraten.de/vlink/release/vlink.tar.gz && \
    tar -xzf vlink.tar.gz && \
    cd vlink && \
    make && \
    cp vlink /usr/local/bin/ && \
    cd .. && \
    rm -rf vlink*

# Create workspace
WORKDIR /workspace

# Set up environment  
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]