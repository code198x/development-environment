# Base image for NEC V30 processors (WonderSwan)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for NEC V30 development"
LABEL version="1.0.0"

USER root

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/nasm:latest /opt/nasm /opt/v30-tools/nasm
COPY --from=ghcr.io/code198x/toolchains/wla-dx:latest /opt/wla-dx /opt/v30-tools/wla-dx

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/v30-tools

USER code198x

# Set environment variables
ENV PATH="/opt/v30-tools/nasm/bin:/opt/v30-tools/wla-dx/bin:$PATH"
ENV RETRO_ARCH="v30"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD /opt/v30-tools/nasm/bin/nasm --version > /dev/null