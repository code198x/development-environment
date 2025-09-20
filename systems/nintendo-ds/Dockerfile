# Nintendo DS - Dual-screen handheld with touch input
FROM ghcr.io/code198x/arm-base:latest

LABEL maintainer="code198x"
LABEL description="ARM assembler for Nintendo DS development"
LABEL version="1.0.0"
LABEL system="nintendo-ds"
LABEL year="2004"
LABEL cpu="ARM9 + ARM7"
LABEL manufacturer="Nintendo"
LABEL emulator="DeSmuME/melonDS"
LABEL significance="Dual ARM processors, dual screens, touch input"

# ARM tools are included in base image

USER root

# Copy Nintendo DS-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nintendo-ds /opt/nds-resources

# Set up environment for Nintendo DS development
ENV NDS_INCLUDES=/opt/nds-resources/includes
ENV NDS_LIBS=/opt/nds-resources/libs
ENV NDS_EXAMPLES=/opt/nds-resources/examples
ENV SYSTEM_INCLUDES=/opt/nds-resources/includes
ENV SYSTEM_LIBS=/opt/nds-resources/libs
ENV SYSTEM_EXAMPLES=/opt/nds-resources/examples

USER code198x

# Set ARM assembler as the entrypoint
ENTRYPOINT ["arm-none-eabi-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null