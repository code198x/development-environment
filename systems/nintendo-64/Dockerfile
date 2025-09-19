# Nintendo 64 - 64-bit gaming console with unique controller
FROM ghcr.io/code198x/mips-base:latest

LABEL maintainer="code198x"
LABEL description="MIPS assembler for Nintendo 64 development"
LABEL version="1.0.0"
LABEL system="nintendo-64"
LABEL year="1996"
LABEL cpu="R4300i"
LABEL manufacturer="Nintendo"
LABEL emulator="Mupen64Plus/Project64/simple64"
LABEL significance="First major 64-bit gaming console"

# MIPS tools are included in base image
USER code198x

# Set MIPS assembler as the entrypoint
ENTRYPOINT ["mips-unknown-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD mips-unknown-elf-as --version > /dev/null