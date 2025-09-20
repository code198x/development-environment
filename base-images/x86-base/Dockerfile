# Version pinning for reproducible builds
ARG DJGPP_VERSION=12.2.0

# Base image for x86 processors (DOS, early Windows games)
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget \
    unzip \
    bzip2

# Create tools directory
RUN mkdir -p /opt/x86-tools/bin

# Copy pre-built NASM from toolchain image
COPY --from=ghcr.io/code198x/toolchains/nasm:latest /opt/nasm/bin/nasm /opt/x86-tools/bin/nasm
COPY --from=ghcr.io/code198x/toolchains/nasm:latest /opt/nasm/bin/ndisasm /opt/x86-tools/bin/ndisasm

# Install YASM as alternative assembler
RUN cd /tmp && \
    git clone https://github.com/yasm/yasm.git && \
    cd yasm && \
    ./autogen.sh && \
    ./configure --prefix=/opt/x86-tools && \
    make -j$(nproc) && \
    make install

# A86 assembler not available - NASM and YASM provide complete x86 coverage

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for x86 development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/x86-tools /opt/x86-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/x86-tools

USER code198x

# Set environment variables
ENV PATH="/opt/x86-tools/bin:$PATH"
ENV RETRO_ARCH="x86"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD nasm --version > /dev/null