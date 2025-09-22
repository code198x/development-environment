# Base image for ARM processors (GBA, DS, 3DO)
FROM ghcr.io/code198x/code198x-base:latest

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

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/armips:latest /opt/armips /opt/arm-tools/armips
COPY --from=ghcr.io/code198x/toolchains/fasmarm:latest /opt/fasmarm /opt/arm-tools/fasmarm

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/arm-tools

USER code198x

# Set environment variables
ENV PATH="/opt/arm-tools/armips/bin:/opt/arm-tools/fasmarm/bin:/usr/bin:$PATH"
ENV RETRO_ARCH="arm"
ENV DEVKITARM="/opt/arm-tools"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null 2>&1