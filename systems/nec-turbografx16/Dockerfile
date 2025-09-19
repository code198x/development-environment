# NEC TurboGrafx-16/PC Engine - Unique 6502-based 16-bit console
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for TurboGrafx-16/PC Engine development"
LABEL version="1.0.0"
LABEL system="nec-turbografx16"
LABEL year="1987"
LABEL cpu="HuC6280 (6502-based)"
LABEL manufacturer="NEC"
LABEL emulator="Mednafen/MAME"
LABEL significance="Unique 6502-based console with advanced graphics capabilities"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null