# Base image for Intel 8080/8085 processors
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for Intel 8080/8085 development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/asm8080:latest /opt/asm8080 /opt/8080-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/8080-tools

USER code198x

# Set environment variables
ENV PATH="/opt/8080-tools/bin:$PATH"
ENV RETRO_ARCH="8080"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD asm8080 --version > /dev/null 2>&1 || z80asm --help > /dev/null