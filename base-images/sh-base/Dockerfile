# Version pinning for reproducible builds
ARG BINUTILS_VERSION=2.40
ARG GCC_VERSION=12.2.0

# Base image for SuperH processors (Saturn, Dreamcast, 32X)
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
    texinfo \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    flex \
    bison

# Re-declare ARGs for this stage
ARG BINUTILS_VERSION
ARG GCC_VERSION

# Build SuperH cross-compiler toolchain
RUN cd /tmp && \
    wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.xz && \
    tar -xf binutils-${BINUTILS_VERSION}.tar.xz && \
    cd binutils-${BINUTILS_VERSION} && \
    ./configure --target=sh-elf --prefix=/opt/sh-tools --disable-nls && \
    make -j$(nproc) && \
    make install

# Install asmsh for Saturn/Dreamcast development
RUN cd /tmp && \
    git clone https://github.com/superctr/asmsh.git && \
    cd asmsh && \
    make && \
    mkdir -p /opt/sh-tools/bin && \
    cp asmsh /opt/sh-tools/bin/

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for SuperH development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/sh-tools /opt/sh-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/sh-tools

USER code198x

# Set environment variables
ENV PATH="/opt/sh-tools/bin:$PATH"
ENV RETRO_ARCH="sh"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sh-elf-as --version > /dev/null