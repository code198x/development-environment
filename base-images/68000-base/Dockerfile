# Version pinning for reproducible builds (must be before FROM)
ARG VASM_COMMIT=d14dda15
ARG VLINK_COMMIT=d78459de

# Base image for 68000-family processors
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
# Use cache mount for apt to improve caching
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    zlib1g-dev \
    libpng-dev \
    wget

# Re-declare ARGs for this stage
ARG VASM_COMMIT
ARG VLINK_COMMIT

# Build VASM from GitHub mirror (pinned to specific commit for cache stability)
RUN cd /tmp && \
    wget -q https://github.com/StarWolf3000/vasm-mirror/archive/${VASM_COMMIT}.tar.gz && \
    tar -xzf ${VASM_COMMIT}.tar.gz && \
    cd vasm-mirror-* && \
    make CPU=m68k SYNTAX=mot && \
    mkdir -p /opt/68000-tools/bin && \
    cp vasmm68k_mot /opt/68000-tools/bin/ && \
    cp vobjdump /opt/68000-tools/bin/

# Build vlink from GitHub mirror (pinned to specific commit for cache stability)
RUN cd /tmp && \
    wget -q https://github.com/Leffmann/vlink/archive/${VLINK_COMMIT}.tar.gz && \
    tar -xzf ${VLINK_COMMIT}.tar.gz && \
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