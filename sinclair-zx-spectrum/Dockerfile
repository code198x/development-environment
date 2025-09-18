# SjASMPlus for ZX Spectrum
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for ZX Spectrum development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Build SjASMPlus from source
RUN git clone https://github.com/z00m128/sjasmplus.git /tmp/sjasmplus && \
    cd /tmp/sjasmplus && \
    make && \
    cp sjasmplus /usr/local/bin/ && \
    rm -rf /tmp/sjasmplus

# Create workspace directory
WORKDIR /workspace

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]