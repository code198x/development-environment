# Using GitHub mirrors for reliable downloads (phoenix.owl.de unreliable)

# Base image for 68000-family processors
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    zlib1g-dev \
    libpng-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# No ARGs needed - using latest from GitHub mirrors

# Build VASM from GitHub mirror (phoenix.owl.de unreliable)
RUN cd /tmp && \
    wget -q https://github.com/StarWolf3000/vasm-mirror/archive/master.tar.gz && \
    tar -xzf master.tar.gz && \
    cd vasm-mirror-* && \
    make CPU=m68k SYNTAX=mot && \
    mkdir -p /opt/68000-tools/bin && \
    cp vasmm68k_mot /opt/68000-tools/bin/ && \
    cp vobjdump /opt/68000-tools/bin/

# Build vlink from GitHub mirror (phoenix.owl.de unreliable)
RUN cd /tmp && \
    wget -q https://github.com/Leffmann/vlink/archive/master.tar.gz -O vlink.tar.gz && \
    tar -xzf vlink.tar.gz && \
    cd vlink-* && \
    make && \
    cp vlink /opt/68000-tools/bin/

# Runtime stage - much smaller
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for 68000 family development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/68000-tools /opt/68000-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/68000-tools

USER code198x

# Set common environment variables for 68000 development
ENV PATH="/opt/68000-tools/bin:$PATH"
ENV RETRO_ARCH="68000"

# Health check to verify assemblers work
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot -help > /dev/null && vlink -h > /dev/null