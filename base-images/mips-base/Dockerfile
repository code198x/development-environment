# Base image for MIPS processors (PlayStation, N64, SGI)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for MIPS development"
LABEL version="1.0.0"

USER root

# Install runtime MIPS tools
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    gcc-mips-linux-gnu \
    binutils-mips-linux-gnu \
    gcc-mipsel-linux-gnu \
    binutils-mipsel-linux-gnu

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/armips:latest /opt/armips /opt/mips-tools/armips

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/mips-tools

USER code198x

# Set environment variables
ENV PATH="/opt/mips-tools/armips/bin:/usr/bin:$PATH"
ENV RETRO_ARCH="mips"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD mips-linux-gnu-as --version > /dev/null 2>&1 || mipsel-linux-gnu-as --version > /dev/null