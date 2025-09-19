# Nintendo Donkey Kong - Nintendo's first major arcade hit
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Donkey Kong arcade development"
LABEL version="1.0.0"
LABEL system="nintendo-donkey-kong"
LABEL year="1981"
LABEL cpu="Z80"
LABEL manufacturer="Nintendo"
LABEL emulator="MAME"
LABEL significance="Nintendo's arcade debut, introduced Mario"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null