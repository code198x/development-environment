# Panasonic 3DO - Early 32-bit multimedia console
FROM ghcr.io/code198x/arm-base:latest

LABEL maintainer="code198x"
LABEL description="ARM assembler for 3DO Interactive development"
LABEL version="1.0.0"
LABEL system="panasonic-3do"
LABEL year="1993"
LABEL cpu="ARM60"
LABEL manufacturer="Panasonic/3DO Company"
LABEL emulator="Phoenix/4DO"
LABEL significance="Early 32-bit multimedia gaming"

# ARM tools are included in base image
USER code198x

# Set ARM assembler as the entrypoint
ENTRYPOINT ["arm-none-eabi-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null