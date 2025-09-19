# BBC Micro - 6502-based British computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for BBC Micro development"
LABEL version="1.0.0"
LABEL system="acorn-bbc-micro"
LABEL year="1981"
LABEL cpu="6502"
LABEL manufacturer="Acorn"

# ACME is included in base image
USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null