# MSX - Z80-based standard by Microsoft/ASCII
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for MSX development"
LABEL version="1.0.0"
LABEL system="msx"
LABEL year="1983"
LABEL cpu="Z80"
LABEL manufacturer="Microsoft/ASCII"

# sjasmplus is included in base image

USER root

# Copy MSX-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/msx /opt/msx-resources

# Set up environment for MSX development
ENV MSX_INCLUDES=/opt/msx-resources/includes
ENV MSX_LIBS=/opt/msx-resources/libs
ENV MSX_EXAMPLES=/opt/msx-resources/examples
ENV SYSTEM_INCLUDES=/opt/msx-resources/includes
ENV SYSTEM_LIBS=/opt/msx-resources/libs
ENV SYSTEM_EXAMPLES=/opt/msx-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null