# Williams Defender - Advanced scrolling arcade game
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for Williams Defender arcade development"
LABEL version="1.0.0"
LABEL system="williams-defender"
LABEL year="1981"
LABEL cpu="MC6809E"
LABEL manufacturer="Williams Electronics"
LABEL emulator="MAME"
LABEL significance="Advanced scrolling and gameplay mechanics"

# lwasm is included in base image

USER root

# Copy Williams Defender-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/williams-defender /opt/defender-resources

# Set up environment for Williams Defender development
ENV DEFENDER_INCLUDES=/opt/defender-resources/includes
ENV DEFENDER_LIBS=/opt/defender-resources/libs
ENV DEFENDER_EXAMPLES=/opt/defender-resources/examples
ENV SYSTEM_INCLUDES=/opt/defender-resources/includes
ENV SYSTEM_LIBS=/opt/defender-resources/libs
ENV SYSTEM_EXAMPLES=/opt/defender-resources/examples

USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null