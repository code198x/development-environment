# Base image for 6502-family processors
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

# Version pinning for reproducible builds
ARG ACME_VERSION=0.97
ARG CC65_VERSION=V2.19

# Build ACME cross-assembler
RUN cd /tmp && \
    wget -q https://github.com/meonwax/acme/archive/refs/tags/v${ACME_VERSION}.tar.gz && \
    tar -xzf v${ACME_VERSION}.tar.gz && \
    cd acme-${ACME_VERSION}/src && \
    make && \
    mkdir -p /opt/6502-tools/bin && \
    cp acme /opt/6502-tools/bin/

# Build cc65 suite
RUN cd /tmp && \
    wget -q https://github.com/cc65/cc65/archive/refs/tags/${CC65_VERSION}.tar.gz && \
    tar -xzf ${CC65_VERSION}.tar.gz && \
    cd cc65-* && \
    make PREFIX=/opt/6502-tools && \
    make install PREFIX=/opt/6502-tools

# Runtime stage - much smaller
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for 6502 family development"
LABEL version="1.0.0"

USER root

# Install only runtime dependencies
RUN apt-get update && apt-get install -y \
    xxd \
    bsdmainutils \
    && rm -rf /var/lib/apt/lists/*

# Copy built tools from builder stage
COPY --from=builder /opt/6502-tools /opt/6502-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/6502-tools

USER code198x

# Set common environment variables for 6502 development
ENV PATH="/opt/6502-tools/bin:$PATH"
ENV RETRO_ARCH="6502"

# Health check to verify assemblers work
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null && ca65 --version > /dev/null