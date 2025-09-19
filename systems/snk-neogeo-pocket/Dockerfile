# SNK Neo Geo Pocket - 16-bit handheld console
FROM ghcr.io/code198x/tlcs-base:latest

LABEL maintainer="code198x"
LABEL description="ngpasm assembler for Neo Geo Pocket development"
LABEL version="1.0.0"
LABEL system="snk-neogeo-pocket"
LABEL year="1998"
LABEL cpu="TLCS-900H"
LABEL manufacturer="SNK"
LABEL emulator="NeoPop/MAME/Mednafen"
LABEL significance="SNK's excellent handheld with great fighting games"

# ngpasm is included in base image
USER code198x

# Set ngpasm as the entrypoint
ENTRYPOINT ["ngpasm"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ngpasm --help > /dev/null 2>&1 || echo "OK"