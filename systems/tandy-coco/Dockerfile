# TRS-80 Color Computer (CoCo) - Motorola 6809-based
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for TRS-80 Color Computer development"
LABEL version="1.0.0"
LABEL system="tandy-coco"
LABEL year="1980"
LABEL cpu="6809E"
LABEL manufacturer="Tandy/RadioShack"
LABEL nickname="CoCo"

# lwasm is included in base image
USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null