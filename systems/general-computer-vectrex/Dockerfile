# General Computer Vectrex - Pure vector graphics console
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Vectrex development"
LABEL version="1.0.0"
LABEL system="general-computer-vectrex"
LABEL year="1982"
LABEL cpu="MC6809E"
LABEL manufacturer="General Computer Corporation"
LABEL emulator="ParaJVE/MAME"
LABEL significance="Only commercial vector graphics home console"

# lwasm is included in base image
USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null