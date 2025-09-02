# TI-99/4A Development Environment
# TMS9900 16-bit processor with unique memory-mapped registers
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

# Install xdt99 (TMS9900 cross-assembler)
WORKDIR /tmp
RUN git clone https://github.com/endlos99/xdt99.git && \
    cp -r xdt99/* /usr/local/bin/ && \
    chmod +x /usr/local/bin/x*.py && \
    rm -rf xdt99

# Alternative: Install gcc-tms9900 if available
# RUN apt-get update && apt-get install -y gcc-tms9900 || echo "gcc-tms9900 not available"

# Create workspace
WORKDIR /workspace

# Set up environment
ENV PATH="/usr/local/bin:$PATH"

# Default command
CMD ["/bin/bash"]