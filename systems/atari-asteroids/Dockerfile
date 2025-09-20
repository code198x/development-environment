# Atari Asteroids - Classic vector graphics arcade
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Asteroids arcade development"
LABEL version="1.0.0"
LABEL system="atari-asteroids"
LABEL year="1979"
LABEL cpu="6502"
LABEL manufacturer="Atari"
LABEL emulator="MAME"
LABEL significance="Pure vector graphics programming"

# ACME is included in base image

USER root

# Copy Atari Asteroids-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-asteroids /opt/asteroids-resources

# Set up environment for Asteroids arcade development
ENV ASTEROIDS_INCLUDES=/opt/asteroids-resources/includes
ENV ASTEROIDS_LIBS=/opt/asteroids-resources/libs
ENV ASTEROIDS_EXAMPLES=/opt/asteroids-resources/examples
ENV SYSTEM_INCLUDES=/opt/asteroids-resources/includes
ENV SYSTEM_LIBS=/opt/asteroids-resources/libs
ENV SYSTEM_EXAMPLES=/opt/asteroids-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null