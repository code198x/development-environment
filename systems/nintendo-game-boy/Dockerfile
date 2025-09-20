# Nintendo Game Boy - Modified Z80 (Sharp LR35902)
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for Game Boy development"
LABEL version="1.0.0"
LABEL system="nintendo-game-boy"
LABEL year="1989"
LABEL cpu="LR35902"
LABEL manufacturer="Nintendo"

# sjasmplus is included in base image

USER root

# Copy Game Boy-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nintendo-game-boy /opt/gameboy-resources

# Set up environment for Game Boy development
ENV GB_INCLUDES=/opt/gameboy-resources/includes
ENV GB_LIBS=/opt/gameboy-resources/libs
ENV GB_EXAMPLES=/opt/gameboy-resources/examples
ENV SYSTEM_INCLUDES=/opt/gameboy-resources/includes
ENV SYSTEM_LIBS=/opt/gameboy-resources/libs
ENV SYSTEM_EXAMPLES=/opt/gameboy-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null