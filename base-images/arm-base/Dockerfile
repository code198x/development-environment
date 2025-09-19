# Base image for ARM processors (GBA, DS, 3DO)
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
    libncurses6

# Install GNU ARM cross-compiler (alternative to devkitPro)
RUN cd /tmp && \
    apt-get update && apt-get install -y --no-install-recommends \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi && \
    mkdir -p /opt/arm-tools/bin && \
    ln -s /usr/bin/arm-none-eabi-* /opt/arm-tools/bin/ || true

# Install FASMARM for additional ARM assembly
RUN cd /tmp && \
    wget -q https://flatassembler.net/fasmarm.zip && \
    unzip -q fasmarm.zip && \
    mkdir -p /opt/arm-tools/bin && \
    cp fasmarm/fasmarm /opt/arm-tools/bin/ && \
    chmod +x /opt/arm-tools/bin/fasmarm

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for ARM development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/arm-tools /opt/arm-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/arm-tools

USER code198x

# Set environment variables
ENV PATH="/opt/arm-tools/bin:$PATH"
ENV RETRO_ARCH="arm"
ENV DEVKITARM="/opt/arm-tools"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null