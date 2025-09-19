# Coleco Adam - Home computer expansion of ColecoVision
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Coleco Adam development"
LABEL version="1.0.0"
LABEL system="coleco-adam"
LABEL year="1983"
LABEL cpu="Z80A"
LABEL manufacturer="Coleco"
LABEL emulator="AdamEm"
LABEL significance="Advanced features but poor reliability"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null