# Commodore PET - First Commodore computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore PET development"
LABEL version="1.0.0"
LABEL system="commodore-pet"
LABEL year="1977"
LABEL cpu="6502"
LABEL manufacturer="Commodore"
LABEL emulator="VICE (xpet)"

# ACME is included in base image

USER root

# Copy Commodore PET-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/commodore-pet /opt/pet-resources

# Set up environment for Commodore PET development
ENV PET_INCLUDES=/opt/pet-resources/includes
ENV PET_LIBS=/opt/pet-resources/libs
ENV PET_EXAMPLES=/opt/pet-resources/examples
ENV SYSTEM_INCLUDES=/opt/pet-resources/includes
ENV SYSTEM_LIBS=/opt/pet-resources/libs
ENV SYSTEM_EXAMPLES=/opt/pet-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null