# NEC PC Engine SuperGrafx - Enhanced TurboGrafx-16
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for PC Engine SuperGrafx development"
LABEL version="1.0.0"
LABEL system="nec-pc-engine-supergx"
LABEL year="1989"
LABEL cpu="HuC6280 (enhanced)"
LABEL manufacturer="NEC"
LABEL emulator="Mednafen/MAME"
LABEL significance="Enhanced graphics capabilities over standard PC Engine"

# ACME is included in base image

USER root

# Copy PC Engine SuperGrafx-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nec-pc-engine-supergx /opt/supergx-resources

# Set up environment for PC Engine SuperGrafx development
ENV SUPERGX_INCLUDES=/opt/supergx-resources/includes
ENV SUPERGX_LIBS=/opt/supergx-resources/libs
ENV SUPERGX_EXAMPLES=/opt/supergx-resources/examples
ENV SYSTEM_INCLUDES=/opt/supergx-resources/includes
ENV SYSTEM_LIBS=/opt/supergx-resources/libs
ENV SYSTEM_EXAMPLES=/opt/supergx-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null