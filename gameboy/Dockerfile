# Game Boy development environment
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
    bison \
    flex \
    pkg-config \
    libpng-dev \
    && rm -rf /var/lib/apt/lists/*

# Install RGBDS (build from source)
RUN git clone https://github.com/gbdev/rgbds.git /tmp/rgbds \
    && cd /tmp/rgbds \
    && make \
    && make install PREFIX=/usr/local \
    && cd / \
    && rm -rf /tmp/rgbds

# Install bgb (Game Boy emulator) - optional for testing
RUN mkdir -p /opt/bgb \
    && wget -q https://bgb.bircd.org/bgb.zip -O /tmp/bgb.zip || echo "BGB download skipped - continuing" \
    && cd /tmp && unzip -q bgb.zip -d /opt/bgb 2>/dev/null || echo "BGB extraction skipped"

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-gameboy
RUN chmod +x /usr/local/bin/build-gameboy

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"

# Default command
CMD ["/bin/bash"]