# Sharp X68000 - 68000-based Japanese personal computer
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="VASM assembler for Sharp X68000 development"
LABEL version="1.0.0"
LABEL system="sharp-x68000"
LABEL year="1987"
LABEL cpu="68000"
LABEL manufacturer="Sharp"

# VASM is included in base image
USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot -help > /dev/null