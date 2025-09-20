# NEC PC-9801 - Japanese PC gaming standard
FROM ghcr.io/code198x/x86-base:latest

LABEL maintainer="code198x"
LABEL description="NASM assembler for PC-9801 development"
LABEL version="1.0.0"
LABEL system="nec-pc9801"
LABEL year="1982"
LABEL cpu="8086/V30"
LABEL manufacturer="NEC"
LABEL emulator="Neko Project II/MAME"
LABEL significance="Dominant Japanese PC gaming platform"

# NASM is included in base image

USER root

# Copy NEC PC-9801-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nec-pc9801 /opt/pc9801-resources

# Set up environment for PC-9801 development
ENV PC9801_INCLUDES=/opt/pc9801-resources/includes
ENV PC9801_LIBS=/opt/pc9801-resources/libs
ENV PC9801_EXAMPLES=/opt/pc9801-resources/examples
ENV SYSTEM_INCLUDES=/opt/pc9801-resources/includes
ENV SYSTEM_LIBS=/opt/pc9801-resources/libs
ENV SYSTEM_EXAMPLES=/opt/pc9801-resources/examples

USER code198x

# Set NASM as the entrypoint
ENTRYPOINT ["nasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD nasm --version > /dev/null