# Base image for 68000-family processors
# Uses pre-built toolchain images for fast assembly
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for 68000 family development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain images
# This is MUCH faster than building from source!
COPY --from=ghcr.io/code198x/toolchains/vasm:v1.9.1 /opt/vasm/bin/vasmm68k_mot /opt/68000-tools/bin/vasmm68k_mot
COPY --from=ghcr.io/code198x/toolchains/vasm:v1.9.1 /opt/vasm/bin/vobjdump_m68k /opt/68000-tools/bin/vobjdump

# TODO: Add vlink as a separate toolchain if needed
# For now, quick inline build for this smaller tool
RUN apt-get update && apt-get install -y wget build-essential && \
    cd /tmp && \
    wget -q https://github.com/Leffmann/vlink/archive/d78459de.tar.gz && \
    tar -xzf d78459de.tar.gz && \
    cd vlink-* && \
    make && \
    cp vlink /opt/68000-tools/bin/ && \
    rm -rf /tmp/* && \
    apt-get remove -y wget build-essential && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/68000-tools

USER code198x

# Set common environment variables for 68000 development
ENV PATH="/opt/68000-tools/bin:$PATH"
ENV RETRO_ARCH="68000"

# Health check to verify assemblers work
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot -version > /dev/null && vlink -h > /dev/null