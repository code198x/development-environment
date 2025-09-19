# Commodore Plus/4 - Budget computer with built-in software
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore Plus/4 development"
LABEL version="1.0.0"
LABEL system="commodore-plus4"
LABEL year="1984"
LABEL cpu="7501/8501"
LABEL manufacturer="Commodore"
LABEL emulator="VICE (xplus4)"
LABEL significance="Part of Commodore's unsuccessful budget line"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null