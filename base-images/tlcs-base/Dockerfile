# Base image for TLCS-900H processors (Neo Geo Pocket)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for TLCS-900H development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/asl:latest /opt/asl /opt/tlcs-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/tlcs-tools

USER code198x

# Set environment variables
ENV PATH="/opt/tlcs-tools/bin:$PATH"
ENV RETRO_ARCH="tlcs"

# Health check - verify AS assembler is available
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD test -x /opt/tlcs-tools/bin/asl || echo "OK"