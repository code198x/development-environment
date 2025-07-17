# Amiga development environment
FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    make \
    wget \
    curl \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Build and install vasm
RUN wget -q http://phoenix.owl.de/vasm/daily/vasm.tar.gz -O /tmp/vasm.tar.gz \
    && cd /tmp \
    && tar xzf vasm.tar.gz \
    && cd vasm \
    && make CPU=m68k SYNTAX=mot \
    && cp vasmm68k_mot /usr/local/bin/ \
    && cd / \
    && rm -rf /tmp/vasm*

# Install amitools for ADF manipulation
RUN pip3 install amitools

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-amiga
COPY scripts/makeadf.sh /usr/local/bin/makeadf
COPY templates/Makefile.amiga /usr/local/share/amiga/Makefile.template
COPY templates/bootblock.bin /usr/local/share/amiga/bootblock.bin
RUN chmod +x /usr/local/bin/build-amiga /usr/local/bin/makeadf

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"

# Default command
CMD ["/bin/bash"]