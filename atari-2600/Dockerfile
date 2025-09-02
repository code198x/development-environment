# Atari 2600 development environment
FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    make \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install DASM assembler (the standard for 2600 development)
RUN git clone https://github.com/dasm-assembler/dasm.git /tmp/dasm \
    && cd /tmp/dasm \
    && make \
    && cp bin/dasm /usr/local/bin/ \
    && cd / \
    && rm -rf /tmp/dasm

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-2600
RUN chmod +x /usr/local/bin/build-2600

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"

# Default command
CMD ["/bin/bash"]