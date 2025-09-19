# MSX - Z80-based standard by Microsoft/ASCII
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for MSX development"
LABEL version="1.0.0"
LABEL system="msx"
LABEL year="1983"
LABEL cpu="Z80"
LABEL manufacturer="Microsoft/ASCII"

# sjasmplus is included in base image
USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null