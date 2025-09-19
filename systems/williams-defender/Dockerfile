# Williams Defender - Advanced scrolling arcade game
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Williams Defender arcade development"
LABEL version="1.0.0"
LABEL system="williams-defender"
LABEL year="1981"
LABEL cpu="MC6809E"
LABEL manufacturer="Williams Electronics"
LABEL emulator="MAME"
LABEL significance="Advanced scrolling and gameplay mechanics"

# lwasm is included in base image
USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null