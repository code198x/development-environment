# Base image for Z80-family processors
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    zlib1g-dev \
    libpng-dev \
    cmake \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Version pinning for reproducible builds
ARG SJASMPLUS_VERSION=v1.20.3
ARG PASMO_VERSION=0.5.5

# Build sjasmplus (needs git for submodules)
RUN cd /tmp && \
    git clone --recursive https://github.com/z00m128/sjasmplus.git && \
    cd sjasmplus && \
    git checkout ${SJASMPLUS_VERSION} && \
    git submodule update --init --recursive && \
    make && \
    mkdir -p /opt/z80-tools/bin && \
    cp sjasmplus /opt/z80-tools/bin/

# Build pasmo
RUN cd /tmp && \
    wget -q http://pasmo.speccy.org/bin/pasmo-${PASMO_VERSION}.tar.gz && \
    tar -xzf pasmo-${PASMO_VERSION}.tar.gz && \
    cd pasmo-${PASMO_VERSION} && \
    ./configure --prefix=/opt/z80-tools && \
    make && make install

# Runtime stage - much smaller
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for Z80 family development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/z80-tools /opt/z80-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/z80-tools

USER code198x

# Set common environment variables for Z80 development
ENV PATH="/opt/z80-tools/bin:$PATH"
ENV RETRO_ARCH="z80"

# Health check to verify assemblers work
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null && pasmo --help > /dev/null