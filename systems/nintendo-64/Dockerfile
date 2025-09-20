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

USER root

# Copy Nintendo 64-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nintendo-64 /opt/n64-resources

# Set up environment for Nintendo 64 development
ENV N64_INCLUDES=/opt/n64-resources/includes
ENV N64_LIBS=/opt/n64-resources/libs
ENV N64_EXAMPLES=/opt/n64-resources/examples
ENV SYSTEM_INCLUDES=/opt/n64-resources/includes
ENV SYSTEM_LIBS=/opt/n64-resources/libs
ENV SYSTEM_EXAMPLES=/opt/n64-resources/examples

USER code198x

# Set MIPS assembler as the entrypoint
ENTRYPOINT ["mips-unknown-elf-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD mips-unknown-elf-as --version > /dev/null