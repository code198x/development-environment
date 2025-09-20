# Nintendo Game Boy Advance - 32-bit handheld console
FROM ghcr.io/code198x/arm-base:latest

LABEL maintainer="code198x"
LABEL description="ARM assembler for Game Boy Advance development"
LABEL version="1.0.0"
LABEL system="nintendo-gba"
LABEL year="2001"
LABEL cpu="ARM7TDMI"
LABEL manufacturer="Nintendo"
LABEL emulator="mGBA/VBA-M/Mednafen"
LABEL significance="Powerful 32-bit handheld with excellent homebrew scene"

# ARM tools are included in base image

USER root

# Copy GBA-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nintendo-gba /opt/gba-resources

# Set up environment for GBA development
ENV GBA_INCLUDES=/opt/gba-resources/includes
ENV GBA_LIBS=/opt/gba-resources/libs
ENV GBA_EXAMPLES=/opt/gba-resources/examples
ENV SYSTEM_INCLUDES=/opt/gba-resources/includes
ENV SYSTEM_LIBS=/opt/gba-resources/libs
ENV SYSTEM_EXAMPLES=/opt/gba-resources/examples

USER code198x

# Set ARM assembler as the entrypoint
ENTRYPOINT ["arm-none-eabi-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null