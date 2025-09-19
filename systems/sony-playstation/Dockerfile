# Sony PlayStation - 32-bit 3D gaming console
FROM ghcr.io/code198x/mips-base:latest

LABEL maintainer="code198x"
LABEL description="MIPS assembler for Sony PlayStation development"
LABEL version="1.0.0"
LABEL system="sony-playstation"
LABEL year="1994"
LABEL cpu="R3000A"
LABEL manufacturer="Sony"
LABEL emulator="DuckStation/PCSX-Redux/Mednafen"
LABEL significance="Brought 3D gaming to the masses"

# MIPS tools are included in base image
USER code198x

# Set MIPS assembler as the entrypoint
ENTRYPOINT ["mips-unknown-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD mips-unknown-elf-as --version > /dev/null