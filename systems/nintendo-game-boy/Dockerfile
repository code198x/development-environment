# Nintendo Game Boy - Modified Z80 (Sharp LR35902)
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for Game Boy development"
LABEL version="1.0.0"
LABEL system="nintendo-game-boy"
LABEL year="1989"
LABEL cpu="LR35902"
LABEL manufacturer="Nintendo"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null