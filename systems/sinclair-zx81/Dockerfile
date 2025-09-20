# Sinclair ZX81 - Ultra-low-cost home computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Sinclair ZX81 development"
LABEL version="1.0.0"
LABEL system="sinclair-zx81"
LABEL year="1981"
LABEL cpu="Z80A"
LABEL manufacturer="Sinclair Research"
LABEL emulator="EightyOne"
LABEL significance="Made computing accessible to millions"

# sjasmplus is included in base image

USER root

# Copy Sinclair ZX81-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sinclair-zx81 /opt/zx81-resources

# Set up environment for Sinclair ZX81 development
ENV ZX81_INCLUDES=/opt/zx81-resources/includes
ENV ZX81_LIBS=/opt/zx81-resources/libs
ENV ZX81_EXAMPLES=/opt/zx81-resources/examples
ENV SYSTEM_INCLUDES=/opt/zx81-resources/includes
ENV SYSTEM_LIBS=/opt/zx81-resources/libs
ENV SYSTEM_EXAMPLES=/opt/zx81-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null