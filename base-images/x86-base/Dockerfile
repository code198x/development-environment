# Base image for x86 processors (DOS, early Windows games)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for x86 development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/nasm:latest /opt/nasm /opt/x86-tools/nasm
COPY --from=ghcr.io/code198x/toolchains/yasm:latest /opt/yasm /opt/x86-tools/yasm

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/x86-tools

USER code198x

# Set environment variables
ENV PATH="/opt/x86-tools/nasm/bin:/opt/x86-tools/yasm/bin:$PATH"
ENV RETRO_ARCH="x86"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD /opt/x86-tools/nasm/bin/nasm --version > /dev/null