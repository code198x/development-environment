# Bandai WonderSwan - Gunpei Yokoi's final handheld
FROM ghcr.io/code198x/v30-base:latest

LABEL maintainer="code198x"
LABEL description="NASM assembler for WonderSwan development"
LABEL version="1.0.0"
LABEL system="bandai-wonderswan"
LABEL year="1999"
LABEL cpu="NEC V30MZ"
LABEL manufacturer="Bandai"
LABEL emulator="Mednafen/Beetle Cygne"
LABEL significance="Gunpei Yokoi's final handheld design"

# NASM is included in base image

USER root

# Copy WonderSwan-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/bandai-wonderswan /opt/wonderswan-resources

# Set up environment for WonderSwan development
ENV WONDERSWAN_INCLUDES=/opt/wonderswan-resources/includes
ENV WONDERSWAN_LIBS=/opt/wonderswan-resources/libs
ENV WONDERSWAN_EXAMPLES=/opt/wonderswan-resources/examples
ENV SYSTEM_INCLUDES=/opt/wonderswan-resources/includes
ENV SYSTEM_LIBS=/opt/wonderswan-resources/libs
ENV SYSTEM_EXAMPLES=/opt/wonderswan-resources/examples

USER code198x

# Set NASM as the entrypoint
ENTRYPOINT ["nasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD nasm --version > /dev/null