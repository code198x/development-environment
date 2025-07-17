# NES development environment
FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    make \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install cc65
RUN git clone https://github.com/cc65/cc65.git /tmp/cc65 \
    && cd /tmp/cc65 \
    && make \
    && make install PREFIX=/usr/local \
    && rm -rf /tmp/cc65

# Create workspace directory
WORKDIR /workspace

# Add NES configuration file
COPY config/nes.cfg /usr/local/share/cc65/cfg/nes.cfg

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-nes
COPY templates/Makefile.nes /usr/local/share/nes/Makefile.template
RUN chmod +x /usr/local/bin/build-nes

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"
ENV CC65_HOME="/usr/local/share/cc65"

# Default command
CMD ["/bin/bash"]