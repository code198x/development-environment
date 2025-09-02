# Vectrex Development Environment  
# 6809 processor with vector graphics display
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
    && rm -rf /var/lib/apt/lists/*

# Install lwtools for 6809 assembly (backup source)
WORKDIR /tmp
RUN git clone https://github.com/stahta01/lwtools.git && \
    cd lwtools && \
    make && \
    make install PREFIX=/usr/local && \
    cd .. && \
    rm -rf lwtools

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]