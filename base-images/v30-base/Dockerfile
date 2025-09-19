# Version pinning for reproducible builds
ARG NASM_VERSION=2.16.01

# Base image for NEC V30 processors (WonderSwan)
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget

# Re-declare ARGs for this stage
ARG NASM_VERSION

# Install NASM for V30 assembly (V30 is 8086-compatible)
RUN cd /tmp && \
    wget -q https://www.nasm.us/pub/nasm/releasebuilds/${NASM_VERSION}/nasm-${NASM_VERSION}.tar.bz2 && \
    tar -xf nasm-${NASM_VERSION}.tar.bz2 && \
    cd nasm-${NASM_VERSION} && \
    ./configure --prefix=/opt/v30-tools && \
    make -j$(nproc) && \
    make install

# Install WLA-DX for WonderSwan development
RUN cd /tmp && \
    git clone https://github.com/vhelin/wla-dx.git && \
    cd wla-dx && \
    cmake . && \
    make -j$(nproc) && \
    mkdir -p /opt/v30-tools/bin && \
    cp binaries/* /opt/v30-tools/bin/

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for NEC V30 development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/v30-tools /opt/v30-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/v30-tools

USER code198x

# Set environment variables
ENV PATH="/opt/v30-tools/bin:$PATH"
ENV RETRO_ARCH="v30"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD nasm --version > /dev/null