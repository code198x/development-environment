# Sega Game Gear - Color handheld console
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Sega Game Gear development"
LABEL version="1.0.0"
LABEL system="sega-game-gear"
LABEL year="1990"
LABEL cpu="Z80"
LABEL manufacturer="Sega"
LABEL emulator="MAME/Mednafen"
LABEL significance="Color handheld with Master System compatibility"

# sjasmplus is included in base image

USER root

# Copy Sega Game Gear-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sega-game-gear /opt/gamegear-resources

# Set up environment for Sega Game Gear development
ENV GAMEGEAR_INCLUDES=/opt/gamegear-resources/includes
ENV GAMEGEAR_LIBS=/opt/gamegear-resources/libs
ENV GAMEGEAR_EXAMPLES=/opt/gamegear-resources/examples
ENV SYSTEM_INCLUDES=/opt/gamegear-resources/includes
ENV SYSTEM_LIBS=/opt/gamegear-resources/libs
ENV SYSTEM_EXAMPLES=/opt/gamegear-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null