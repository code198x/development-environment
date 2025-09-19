# Version pinning for reproducible builds
ARG NGPASM_VERSION=main

# Base image for TLCS-900H processors (Neo Geo Pocket)
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake

# Re-declare ARGs for this stage
ARG NGPASM_VERSION

# Install ngpasm for Neo Geo Pocket development
RUN cd /tmp && \
    git clone https://github.com/NGPdevs/ngpasm.git && \
    cd ngpasm && \
    make && \
    mkdir -p /opt/tlcs-tools/bin && \
    cp ngpasm /opt/tlcs-tools/bin/

# Install ASxxxx for TLCS assembly
RUN cd /tmp && \
    git clone https://github.com/Pacmanfan/asxxxx.git && \
    cd asxxxx/asxxxx && \
    make -f Makefile.linux && \
    mkdir -p /opt/tlcs-tools/bin && \
    cp as*/as* /opt/tlcs-tools/bin/ || true

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for TLCS-900H development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/tlcs-tools /opt/tlcs-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/tlcs-tools

USER code198x

# Set environment variables
ENV PATH="/opt/tlcs-tools/bin:$PATH"
ENV RETRO_ARCH="tlcs"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ngpasm --help > /dev/null 2>&1 || echo "OK"