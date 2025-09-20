# SAM Coupé - Enhanced Spectrum architecture
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for SAM Coupé development"
LABEL version="1.0.0"
LABEL system="sam-coupe"
LABEL year="1989"
LABEL cpu="Z80B"
LABEL manufacturer="Miles Gordon Technology"
LABEL emulator="SimCoupé"
LABEL significance="Advanced graphics capabilities, Spectrum successor"

# sjasmplus is included in base image

USER root

# Copy SAM Coupé-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sam-coupe /opt/samcoupe-resources

# Set up environment for SAM Coupé development
ENV SAMCOUPE_INCLUDES=/opt/samcoupe-resources/includes
ENV SAMCOUPE_LIBS=/opt/samcoupe-resources/libs
ENV SAMCOUPE_EXAMPLES=/opt/samcoupe-resources/examples
ENV SYSTEM_INCLUDES=/opt/samcoupe-resources/includes
ENV SYSTEM_LIBS=/opt/samcoupe-resources/libs
ENV SYSTEM_EXAMPLES=/opt/samcoupe-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null