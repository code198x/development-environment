# NEC PC Engine SuperGrafx - Enhanced TurboGrafx-16
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for PC Engine SuperGrafx development"
LABEL version="1.0.0"
LABEL system="nec-pc-engine-supergx"
LABEL year="1989"
LABEL cpu="HuC6280 (enhanced)"
LABEL manufacturer="NEC"
LABEL emulator="Mednafen/MAME"
LABEL significance="Enhanced graphics capabilities over standard PC Engine"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null