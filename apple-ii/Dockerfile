# Apple II development environment
FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    make \
    wget \
    curl \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Install cc65 (includes ca65 assembler optimized for Apple II)
RUN git clone https://github.com/cc65/cc65.git /tmp/cc65 \
    && cd /tmp/cc65 \
    && make \
    && make install PREFIX=/usr/local \
    && cd / \
    && rm -rf /tmp/cc65

# Install AppleCommander for disk image creation (optional)
RUN wget -q https://github.com/AppleCommander/AppleCommander/releases/download/v1.9.0/applecommander-1.9.0.jar -O /usr/local/bin/applecommander.jar || echo "AppleCommander download failed - continuing without it"

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-apple2
RUN chmod +x /usr/local/bin/build-apple2

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"
ENV CC65_HOME="/usr/local/share/cc65"

# Default command
CMD ["/bin/bash"]