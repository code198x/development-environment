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
    unzip

# Create tools directory
RUN mkdir -p /opt/arm-tools/bin

# Install FASMARM for additional ARM assembly
RUN cd /tmp && \
    wget -q https://flatassembler.net/fasmarm.zip && \
    unzip -q fasmarm.zip && \
    cp fasmarm/fasmarm /opt/arm-tools/bin/ && \
    chmod +x /opt/arm-tools/bin/fasmarm || echo "FASMARM installation failed"

# Build GBA tools (for Game Boy Advance)
RUN cd /tmp && \
    git clone --depth=1 https://github.com/devkitPro/grit.git && \
    cd grit && \
    make && \
    cp grit /opt/arm-tools/bin/ || echo "grit build failed - continuing with GNU tools"

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for ARM development"
LABEL version="1.0.0"

USER root

# Install runtime ARM tools
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    gdb-multiarch

# Copy additional built tools from builder stage
COPY --from=builder /opt/arm-tools /opt/arm-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/arm-tools

USER code198x

# Set environment variables
ENV PATH="/opt/arm-tools/bin:/usr/bin:$PATH"
ENV RETRO_ARCH="arm"
ENV DEVKITARM="/opt/arm-tools"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null 2>&1