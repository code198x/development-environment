# Version pinning for reproducible builds
ARG MIPS_GCC_VERSION=12.2.0
ARG BINUTILS_VERSION=2.40

# Base image for MIPS processors (PlayStation, N64, SGI)
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
ARG MIPS_GCC_VERSION
ARG BINUTILS_VERSION

# Build MIPS cross-compiler toolchain
RUN cd /tmp && \
    wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.xz && \
    tar -xf binutils-${BINUTILS_VERSION}.tar.xz && \
    cd binutils-${BINUTILS_VERSION} && \
    ./configure --target=mips-unknown-elf --prefix=/opt/mips-tools --disable-nls && \
    make -j$(nproc) && \
    make install

# Install SPASM-ng for older MIPS systems
RUN cd /tmp && \
    git clone https://github.com/alberthdev/spasm-ng.git && \
    cd spasm-ng && \
    make && \
    mkdir -p /opt/mips-tools/bin && \
    cp spasm-ng /opt/mips-tools/bin/spasm

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for MIPS development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/mips-tools /opt/mips-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/mips-tools

USER code198x

# Set environment variables
ENV PATH="/opt/mips-tools/bin:$PATH"
ENV RETRO_ARCH="mips"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD mips-unknown-elf-as --version > /dev/null