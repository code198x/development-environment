# ZX Spectrum development environment
FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    libboost-all-dev \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Build and install sjasmplus
RUN git clone --recursive https://github.com/z00m128/sjasmplus.git /tmp/sjasmplus \
    && cd /tmp/sjasmplus \
    && make \
    && make install \
    && rm -rf /tmp/sjasmplus

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-spectrum
COPY templates/Makefile.spectrum /usr/local/share/spectrum/Makefile.template
RUN chmod +x /usr/local/bin/build-spectrum

# Set up environment
ENV PATH="/usr/local/bin:${PATH}"

# Default command
CMD ["/bin/bash"]