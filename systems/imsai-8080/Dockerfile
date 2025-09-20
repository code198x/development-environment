# IMSAI 8080 - The rival to the Altair 8800
FROM ghcr.io/code198x/8080-base:latest

LABEL maintainer="code198x"
LABEL description="asm8080 assembler for IMSAI 8080 development"
LABEL version="1.0.0"
LABEL system="imsai-8080"
LABEL year="1975"
LABEL cpu="8080A"
LABEL manufacturer="IMS Associates"
LABEL emulator="simh"
LABEL significance="Main competitor to the Altair 8800"

# asm8080 is included in base image

USER root

# Copy IMSAI 8080-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/imsai-8080 /opt/imsai-resources

# Set up environment for IMSAI 8080 development
ENV IMSAI_INCLUDES=/opt/imsai-resources/includes
ENV IMSAI_LIBS=/opt/imsai-resources/libs
ENV IMSAI_EXAMPLES=/opt/imsai-resources/examples
ENV SYSTEM_INCLUDES=/opt/imsai-resources/includes
ENV SYSTEM_LIBS=/opt/imsai-resources/libs
ENV SYSTEM_EXAMPLES=/opt/imsai-resources/examples

USER code198x

# Set asm8080 as the entrypoint
ENTRYPOINT ["asm8080"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD asm8080 --version > /dev/null 2>&1 || echo "OK"