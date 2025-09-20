# Sharp X1 - Japanese home computer with excellent games
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Sharp X1 development"
LABEL version="1.0.0"
LABEL system="sharp-x1"
LABEL year="1982"
LABEL cpu="Z80A"
LABEL manufacturer="Sharp"
LABEL emulator="X1EMU"
LABEL significance="Popular Japanese computer with rich game library"

# sjasmplus is included in base image

USER root

# Copy Sharp X1-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sharp-x1 /opt/x1-resources

# Set up environment for Sharp X1 development
ENV X1_INCLUDES=/opt/x1-resources/includes
ENV X1_LIBS=/opt/x1-resources/libs
ENV X1_EXAMPLES=/opt/x1-resources/examples
ENV SYSTEM_INCLUDES=/opt/x1-resources/includes
ENV SYSTEM_LIBS=/opt/x1-resources/libs
ENV SYSTEM_EXAMPLES=/opt/x1-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null