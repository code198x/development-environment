# Dragon 32 - Welsh 6809-based home computer
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Dragon 32 development"
LABEL version="1.0.0"
LABEL system="dragon-32"
LABEL year="1982"
LABEL cpu="MC6809E"
LABEL manufacturer="Dragon Data"
LABEL emulator="XRoar"
LABEL significance="Popular in UK, based on CoCo design"

# lwasm is included in base image

USER root

# Copy Dragon 32-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/dragon-32 /opt/dragon32-resources

# Set up environment for Dragon 32 development
ENV DRAGON32_INCLUDES=/opt/dragon32-resources/includes
ENV DRAGON32_LIBS=/opt/dragon32-resources/libs
ENV DRAGON32_EXAMPLES=/opt/dragon32-resources/examples
ENV SYSTEM_INCLUDES=/opt/dragon32-resources/includes
ENV SYSTEM_LIBS=/opt/dragon32-resources/libs
ENV SYSTEM_EXAMPLES=/opt/dragon32-resources/examples

USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null