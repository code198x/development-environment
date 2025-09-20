# CompuPro System 8/16 - Professional 8080/Z80 system
FROM ghcr.io/code198x/8080-base:latest

LABEL maintainer="code198x"
LABEL description="asm8080 assembler for CompuPro System 8/16 development"
LABEL version="1.0.0"
LABEL system="compupro-system816"
LABEL year="1982"
LABEL cpu="8085A/Z80"
LABEL manufacturer="CompuPro"
LABEL emulator="simh"
LABEL significance="Professional S-100 bus system"

# asm8080 is included in base image

USER root

# Copy CompuPro System 8/16-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/compupro-system816 /opt/compupro-resources

# Set up environment for CompuPro System 8/16 development
ENV COMPUPRO_INCLUDES=/opt/compupro-resources/includes
ENV COMPUPRO_LIBS=/opt/compupro-resources/libs
ENV COMPUPRO_EXAMPLES=/opt/compupro-resources/examples
ENV SYSTEM_INCLUDES=/opt/compupro-resources/includes
ENV SYSTEM_LIBS=/opt/compupro-resources/libs
ENV SYSTEM_EXAMPLES=/opt/compupro-resources/examples

USER code198x

# Set asm8080 as the entrypoint
ENTRYPOINT ["asm8080"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD asm8080 --version > /dev/null 2>&1 || echo "OK"