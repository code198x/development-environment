# Dragon 64 - Enhanced version of the Dragon 32
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Dragon 64 development"
LABEL version="1.0.0"
LABEL system="dragon-64"
LABEL year="1983"
LABEL cpu="MC6809E"
LABEL manufacturer="Dragon Data"
LABEL emulator="XRoar"
LABEL significance="Extended Dragon 32 with more memory"

# lwasm is included in base image
USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null