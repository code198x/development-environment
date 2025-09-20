# Panasonic 3DO - Early 32-bit multimedia console
FROM ghcr.io/code198x/arm-base:latest

LABEL maintainer="code198x"
LABEL description="ARM assembler for 3DO Interactive development"
LABEL version="1.0.0"
LABEL system="panasonic-3do"
LABEL year="1993"
LABEL cpu="ARM60"
LABEL manufacturer="Panasonic/3DO Company"
LABEL emulator="Phoenix/4DO"
LABEL significance="Early 32-bit multimedia gaming"

# ARM tools are included in base image

USER root

# Copy Panasonic 3DO-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/panasonic-3do /opt/3do-resources

# Set up environment for 3DO development
ENV 3DO_INCLUDES=/opt/3do-resources/includes
ENV 3DO_LIBS=/opt/3do-resources/libs
ENV 3DO_EXAMPLES=/opt/3do-resources/examples
ENV SYSTEM_INCLUDES=/opt/3do-resources/includes
ENV SYSTEM_LIBS=/opt/3do-resources/libs
ENV SYSTEM_EXAMPLES=/opt/3do-resources/examples

USER code198x

# Set ARM assembler as the entrypoint
ENTRYPOINT ["arm-none-eabi-as"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD arm-none-eabi-as --version > /dev/null