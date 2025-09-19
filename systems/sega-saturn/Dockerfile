# Sega Saturn - Dual SH-2 32-bit console
FROM ghcr.io/code198x/sh-base:latest

LABEL maintainer="code198x"
LABEL description="SuperH assembler for Sega Saturn development"
LABEL version="1.0.0"
LABEL system="sega-saturn"
LABEL year="1994"
LABEL cpu="SH-2 (dual)"
LABEL manufacturer="Sega"
LABEL emulator="Mednafen/SSF/Kronos"
LABEL significance="Complex dual-CPU 32-bit system"

# SuperH tools are included in base image
USER code198x

# Set SH assembler as the entrypoint
ENTRYPOINT ["sh-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sh-elf-as --version > /dev/null