# Bandai WonderSwan - Gunpei Yokoi's final handheld
FROM ghcr.io/code198x/v30-base:latest

LABEL maintainer="code198x"
LABEL description="NASM assembler for WonderSwan development"
LABEL version="1.0.0"
LABEL system="bandai-wonderswan"
LABEL year="1999"
LABEL cpu="NEC V30MZ"
LABEL manufacturer="Bandai"
LABEL emulator="Mednafen/Beetle Cygne"
LABEL significance="Gunpei Yokoi's final handheld design"

# NASM is included in base image
USER code198x

# Set NASM as the entrypoint
ENTRYPOINT ["nasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD nasm --version > /dev/null