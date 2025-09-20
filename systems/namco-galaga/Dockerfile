# Namco Galaga - Multi-CPU arcade shooter
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Galaga arcade development"
LABEL version="1.0.0"
LABEL system="namco-galaga"
LABEL year="1981"
LABEL cpu="Z80 (triple)"
LABEL manufacturer="Namco"
LABEL emulator="MAME"
LABEL significance="Advanced multi-CPU coordination"

# sjasmplus is included in base image

USER root

# Copy Namco Galaga-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/namco-galaga /opt/galaga-resources

# Set up environment for Galaga arcade development
ENV GALAGA_INCLUDES=/opt/galaga-resources/includes
ENV GALAGA_LIBS=/opt/galaga-resources/libs
ENV GALAGA_EXAMPLES=/opt/galaga-resources/examples
ENV SYSTEM_INCLUDES=/opt/galaga-resources/includes
ENV SYSTEM_LIBS=/opt/galaga-resources/libs
ENV SYSTEM_EXAMPLES=/opt/galaga-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null