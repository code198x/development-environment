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
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null