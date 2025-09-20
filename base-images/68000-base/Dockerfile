# Build stage for additional tools
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Create directory structure first
RUN mkdir -p /opt/68000-tools/bin

# Copy pre-built tools from toolchain images
# This is MUCH faster than building from source!
COPY --from=ghcr.io/code198x/toolchains/vasm:latest /opt/vasm/bin/vasmm68k_mot /opt/68000-tools/bin/vasmm68k_mot
COPY --from=ghcr.io/code198x/toolchains/vasm:latest /opt/vasm/bin/vobjdump_m68k /opt/68000-tools/bin/vobjdump

# Build vlink linker
RUN cd /tmp && \
    wget -q https://github.com/Leffmann/vlink/archive/d78459de.tar.gz && \
    tar -xzf d78459de.tar.gz && \
    cd vlink-* && \
    make && \
    cp vlink /opt/68000-tools/bin/

# Runtime stage
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
    CMD vasmm68k_mot 2>&1 | head -1 > /dev/null && vlink -h > /dev/null