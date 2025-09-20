# Dragon 64 - Enhanced version of the Dragon 32
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Dragon 64 development"
LABEL version="1.0.0"
LABEL system="dragon-64"
LABEL year="1983"
LABEL cpu="MC6809E"
LABEL manufacturer="Dragon Data"
LABEL emulator="XRoar"
LABEL significance="Extended Dragon 32 with more memory"

# lwasm is included in base image

USER root

# Copy Dragon 64-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/dragon-64 /opt/dragon64-resources

# Set up environment for Dragon 64 development
ENV DRAGON64_INCLUDES=/opt/dragon64-resources/includes
ENV DRAGON64_LIBS=/opt/dragon64-resources/libs
ENV DRAGON64_EXAMPLES=/opt/dragon64-resources/examples
ENV SYSTEM_INCLUDES=/opt/dragon64-resources/includes
ENV SYSTEM_LIBS=/opt/dragon64-resources/libs
ENV SYSTEM_EXAMPLES=/opt/dragon64-resources/examples

USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null