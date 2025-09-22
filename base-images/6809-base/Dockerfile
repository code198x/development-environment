# Base image for Motorola 6809 processors
# Uses pre-built toolchain images for fast assembly
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for Motorola 6809 development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain image
# This is MUCH faster than building from source!
COPY --from=ghcr.io/code198x/toolchains/lwasm:v4.20 /opt/lwasm /opt/6809-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/6809-tools

USER code198x

# Set environment variables
ENV PATH="/opt/6809-tools/bin:$PATH"
ENV RETRO_ARCH="6809"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null