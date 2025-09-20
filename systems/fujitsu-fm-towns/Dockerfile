# Fujitsu FM Towns - Advanced Japanese multimedia computer
FROM ghcr.io/code198x/x86-base:latest

LABEL maintainer="code198x"
LABEL description="NASM assembler for FM Towns development"
LABEL version="1.0.0"
LABEL system="fujitsu-fm-towns"
LABEL year="1989"
LABEL cpu="80386DX"
LABEL manufacturer="Fujitsu"
LABEL emulator="Tsugaru/MAME"
LABEL significance="Advanced multimedia, arcade-perfect ports"

# NASM is included in base image

USER root

# Copy Fujitsu FM Towns-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/fujitsu-fm-towns /opt/fmtowns-resources

# Set up environment for FM Towns development
ENV FMTOWNS_INCLUDES=/opt/fmtowns-resources/includes
ENV FMTOWNS_LIBS=/opt/fmtowns-resources/libs
ENV FMTOWNS_EXAMPLES=/opt/fmtowns-resources/examples
ENV SYSTEM_INCLUDES=/opt/fmtowns-resources/includes
ENV SYSTEM_LIBS=/opt/fmtowns-resources/libs
ENV SYSTEM_EXAMPLES=/opt/fmtowns-resources/examples

USER code198x

# Set NASM as the entrypoint
ENTRYPOINT ["nasm"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD nasm --version > /dev/null