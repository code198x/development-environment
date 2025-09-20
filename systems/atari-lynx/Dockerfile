# Atari Lynx - First color handheld with hardware scaling/rotation
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Atari Lynx development"
LABEL version="1.0.0"
LABEL system="atari-lynx"
LABEL year="1989"
LABEL cpu="65SC02"
LABEL manufacturer="Atari"
LABEL emulator="Mednafen/MAME"
LABEL significance="Advanced handheld with hardware sprite scaling and rotation"

# ACME is included in base image

USER root

# Copy Atari Lynx-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-lynx /opt/lynx-resources

# Set up environment for Atari Lynx development
ENV LYNX_INCLUDES=/opt/lynx-resources/includes
ENV LYNX_LIBS=/opt/lynx-resources/libs
ENV LYNX_EXAMPLES=/opt/lynx-resources/examples
ENV SYSTEM_INCLUDES=/opt/lynx-resources/includes
ENV SYSTEM_LIBS=/opt/lynx-resources/libs
ENV SYSTEM_EXAMPLES=/opt/lynx-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null