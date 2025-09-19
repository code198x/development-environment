# Atari 800 - 6502-based home computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="cc65 assembler for Atari 800 development"
LABEL version="1.0.0"
LABEL system="atari-800"
LABEL year="1979"
LABEL cpu="6502"
LABEL manufacturer="Atari"

# cc65 is included in base image
USER code198x

# Set ca65 as the entrypoint
ENTRYPOINT ["ca65"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ca65 --version > /dev/null