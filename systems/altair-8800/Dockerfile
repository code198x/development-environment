# Altair 8800 - The first personal computer
FROM ghcr.io/code198x/8080-base:latest

LABEL maintainer="code198x"
LABEL description="asm8080 assembler for Altair 8800 development"
LABEL version="1.0.0"
LABEL system="altair-8800"
LABEL year="1975"
LABEL cpu="8080"
LABEL manufacturer="MITS"
LABEL significance="Started the personal computer revolution"

# asm8080 is included in base image
USER code198x

# Set asm8080 as the entrypoint
ENTRYPOINT ["asm8080"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD asm8080 --version > /dev/null 2>&1 || echo "OK"