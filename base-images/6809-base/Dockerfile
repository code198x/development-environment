# Version pinning for reproducible builds
ARG LWASM_VERSION=4.20
ARG ASM6809_VERSION=2.13

# Base image for Motorola 6809 processors
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
# Use cache mount for apt to improve caching
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget

# Re-declare ARGs for this stage
ARG LWASM_VERSION
ARG ASM6809_VERSION

# Build lwasm (part of lwtools)
RUN cd /tmp && \
    wget -q http://www.lwtools.ca/releases/lwtools/lwtools-${LWASM_VERSION}.tar.gz && \
    tar -xzf lwtools-${LWASM_VERSION}.tar.gz && \
    cd lwtools-${LWASM_VERSION} && \
    make && \
    mkdir -p /opt/6809-tools/bin && \
    cp lwasm/lwasm /opt/6809-tools/bin/ && \
    cp lwlink/lwlink /opt/6809-tools/bin/

# Build asm6809
RUN cd /tmp && \
    wget -q https://www.6809.org.uk/asm6809/dl/asm6809-${ASM6809_VERSION}.tar.gz && \
    tar -xzf asm6809-${ASM6809_VERSION}.tar.gz && \
    cd asm6809-${ASM6809_VERSION} && \
    ./configure --prefix=/opt/6809-tools && \
    make && make install

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for Motorola 6809 development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/6809-tools /opt/6809-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/6809-tools

USER code198x

# Set environment variables
ENV PATH="/opt/6809-tools/bin:$PATH"
ENV RETRO_ARCH="6809"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null && asm6809 --version > /dev/null