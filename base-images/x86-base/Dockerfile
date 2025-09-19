# Version pinning for reproducible builds
ARG NASM_VERSION=2.16.01
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

# Re-declare ARGs for this stage
ARG NASM_VERSION

# Install NASM for x86 assembly
RUN cd /tmp && \
    wget -q https://www.nasm.us/pub/nasm/releasebuilds/${NASM_VERSION}/nasm-${NASM_VERSION}.tar.bz2 && \
    tar -xf nasm-${NASM_VERSION}.tar.bz2 && \
    cd nasm-${NASM_VERSION} && \
    ./configure --prefix=/opt/x86-tools && \
    make -j$(nproc) && \
    make install

# Install YASM as alternative assembler
RUN cd /tmp && \
    git clone https://github.com/yasm/yasm.git && \
    cd yasm && \
    ./autogen.sh && \
    ./configure --prefix=/opt/x86-tools && \
    make -j$(nproc) && \
    make install

# Install A86 assembler (for DOS compatibility)
RUN cd /tmp && \
    wget -q https://eji.com/a86/a86v405.zip && \
    unzip -q a86v405.zip && \
    mkdir -p /opt/x86-tools/bin && \
    cp A86.COM /opt/x86-tools/bin/a86 && \
    chmod +x /opt/x86-tools/bin/a86

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