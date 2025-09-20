# TRS-80 Color Computer (CoCo) - Motorola 6809-based
FROM ghcr.io/code198x/6809-base:latest

LABEL maintainer="code198x"
LABEL description="lwasm assembler for TRS-80 Color Computer development"
LABEL version="1.0.0"
LABEL system="tandy-coco"
LABEL year="1980"
LABEL cpu="6809E"
LABEL manufacturer="Tandy/RadioShack"
LABEL nickname="CoCo"

# lwasm is included in base image

USER root

# Copy Tandy CoCo-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/tandy-coco /opt/coco-resources

# Set up environment for Tandy CoCo development
ENV COCO_INCLUDES=/opt/coco-resources/includes
ENV COCO_LIBS=/opt/coco-resources/libs
ENV COCO_EXAMPLES=/opt/coco-resources/examples
ENV SYSTEM_INCLUDES=/opt/coco-resources/includes
ENV SYSTEM_LIBS=/opt/coco-resources/libs
ENV SYSTEM_EXAMPLES=/opt/coco-resources/examples

USER code198x

# Set lwasm as the entrypoint
ENTRYPOINT ["lwasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD lwasm --version > /dev/null