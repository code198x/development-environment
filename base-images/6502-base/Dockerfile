# Base image for 6502-family processors
# Uses pre-built toolchain images for fast assembly
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for 6502 family development"
LABEL version="1.0.0"

USER root

# Install only runtime dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    xxd \
    bsdmainutils && \
    rm -rf /var/lib/apt/lists/*

# Copy pre-built tools from toolchain images
# This is MUCH faster than building from source!
COPY --from=ghcr.io/code198x/toolchains/cc65:v2.19 /opt/cc65 /opt/6502-tools/cc65
COPY --from=ghcr.io/code198x/toolchains/acme:v0.97.0 /opt/acme /opt/6502-tools/acme

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/6502-tools

USER code198x

# Set common environment variables for 6502 development
# Include both cc65 and acme in PATH
ENV PATH="/opt/6502-tools/cc65/bin:/opt/6502-tools/acme/bin:$PATH"
ENV RETRO_ARCH="6502"

# Health check to verify assemblers work
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null && ca65 --version > /dev/null