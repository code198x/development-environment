# Enterprise 128 - Advanced Hungarian home computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Enterprise 128 development"
LABEL version="1.0.0"
LABEL system="enterprise-128"
LABEL year="1985"
LABEL cpu="Z80A"
LABEL manufacturer="Enterprise Computers"
LABEL emulator="EP128EMU"
LABEL significance="Advanced graphics and sound capabilities"

# sjasmplus is included in base image

USER root

# Copy Enterprise 128-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/enterprise-128 /opt/enterprise128-resources

# Set up environment for Enterprise 128 development
ENV ENTERPRISE128_INCLUDES=/opt/enterprise128-resources/includes
ENV ENTERPRISE128_LIBS=/opt/enterprise128-resources/libs
ENV ENTERPRISE128_EXAMPLES=/opt/enterprise128-resources/examples
ENV SYSTEM_INCLUDES=/opt/enterprise128-resources/includes
ENV SYSTEM_LIBS=/opt/enterprise128-resources/libs
ENV SYSTEM_EXAMPLES=/opt/enterprise128-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null