# SjASMPlus for ZX Spectrum
FROM code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for ZX Spectrum development"
LABEL version="1.0.0"
LABEL system="sinclair-zx-spectrum"

USER root

# Install additional dependencies for SjASMPlus
RUN apt-get update && apt-get install -y \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Build SjASMPlus from source (with submodules for dependencies)
RUN git clone --recursive https://github.com/z00m128/sjasmplus.git /tmp/sjasmplus && \
    cd /tmp/sjasmplus && \
    make && \
    cp sjasmplus /opt/z80-tools/bin/ && \
    rm -rf /tmp/sjasmplus

USER retro

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]