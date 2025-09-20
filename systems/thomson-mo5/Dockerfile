# Thomson MO5 - French educational computer with games
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Thomson MO5 development"
LABEL version="1.0.0"
LABEL system="thomson-mo5"
LABEL year="1984"
LABEL cpu="MC6809E"
LABEL manufacturer="Thomson"
LABEL emulator="DCMOTO/MAME"
LABEL significance="Popular French educational computer"

# lwasm is included in base image

USER root

# Copy Thomson MO5-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/thomson-mo5 /opt/mo5-resources

# Set up environment for Thomson MO5 development
ENV MO5_INCLUDES=/opt/mo5-resources/includes
ENV MO5_LIBS=/opt/mo5-resources/libs
ENV MO5_EXAMPLES=/opt/mo5-resources/examples
ENV SYSTEM_INCLUDES=/opt/mo5-resources/includes
ENV SYSTEM_LIBS=/opt/mo5-resources/libs
ENV SYSTEM_EXAMPLES=/opt/mo5-resources/examples

USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null