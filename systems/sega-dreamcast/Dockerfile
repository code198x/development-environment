# Sega Dreamcast - Last Sega console with built-in modem
FROM ghcr.io/code198x/sh-base:latest

LABEL maintainer="code198x"
LABEL description="SuperH assembler for Sega Dreamcast development"
LABEL version="1.0.0"
LABEL system="sega-dreamcast"
LABEL year="1998"
LABEL cpu="SH-4"
LABEL manufacturer="Sega"
LABEL emulator="Flycast/Redream"
LABEL significance="Advanced graphics, built-in networking"

# SuperH tools are included in base image
USER code198x

# Set SH assembler as the entrypoint
ENTRYPOINT ["sh-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sh-elf-as --version > /dev/null