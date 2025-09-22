# Base image for SuperH processors (Saturn, Dreamcast, 32X)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for SuperH development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/binutils-sh:latest /opt/binutils-sh /opt/sh-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/sh-tools

USER code198x

# Set environment variables
ENV PATH="/opt/sh-tools/bin:$PATH"
ENV RETRO_ARCH="sh"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sh-elf-as --version > /dev/null