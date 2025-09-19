# Commodore VIC-20 - 6502-based home computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore VIC-20 development"
LABEL version="1.0.0"
LABEL system="commodore-vic-20"
LABEL year="1980"
LABEL cpu="6502"
LABEL manufacturer="Commodore"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null