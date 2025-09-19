# SNK Neo Geo AES - Home version of arcade system
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Neo Geo AES development"
LABEL version="1.0.0"
LABEL system="snk-neogeo-aes"
LABEL year="1990"
LABEL cpu="MC68000"
LABEL manufacturer="SNK"
LABEL emulator="MAME/FinalBurn Neo"
LABEL significance="Home console with arcade-perfect games"

# vasm is included in base image
USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null