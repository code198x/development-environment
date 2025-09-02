# Dragon 32/64 development environment
FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    make \
    wget \
    curl \
    python3 \
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Install lwtools (6809 assembler suite)
RUN git clone https://github.com/stahta01/lwtools.git /tmp/lwtools \
    && cd /tmp/lwtools \
    && make \
    && make install PREFIX=/usr/local \
    && cd / \
    && rm -rf /tmp/lwtools

# Install MAME for Dragon emulation (optional)
RUN apt-get update && apt-get install -y \
    mame \
    && rm -rf /var/lib/apt/lists/* || echo "MAME install failed - continuing"

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-dragon
RUN chmod +x /usr/local/bin/build-dragon

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"

# Default command
CMD ["/bin/bash"]