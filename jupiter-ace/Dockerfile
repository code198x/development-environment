# Jupiter Ace Development Environment
# Z80 processor with Forth language instead of BASIC
FROM ubuntu:20.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install development tools and Python for Forth tools
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    vim \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install Z80 assembler (same as other Z80 systems)
WORKDIR /tmp
RUN wget https://github.com/Lerc/z80asm/archive/refs/heads/master.zip && \
    unzip master.zip && \
    cd z80asm-master && \
    make && \
    cp z80asm /usr/local/bin/ && \
    cd .. && \
    rm -rf z80asm-* master.zip

# Install Jupiter Ace emulator and tools
# We'll create Forth programs that compile to Z80 machine code
RUN pip3 install numpy

# Create a simple Forth-to-Z80 cross-compiler
COPY ace_forth.py /usr/local/bin/ace_forth.py
RUN chmod +x /usr/local/bin/ace_forth.py

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]