# Amstrad CPC - Z80-based color personal computer
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="Pasmo assembler for Amstrad CPC development"
LABEL version="1.0.0"
LABEL system="amstrad-cpc"
LABEL year="1984"
LABEL cpu="Z80"
LABEL manufacturer="Amstrad"

# Pasmo is included in base image

USER root

# Copy Amstrad CPC-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/amstrad-cpc /opt/cpc-resources

# Set up environment for Amstrad CPC development
ENV CPC_INCLUDES=/opt/cpc-resources/includes
ENV CPC_LIBS=/opt/cpc-resources/libs
ENV CPC_EXAMPLES=/opt/cpc-resources/examples
ENV SYSTEM_INCLUDES=/opt/cpc-resources/includes
ENV SYSTEM_LIBS=/opt/cpc-resources/libs
ENV SYSTEM_EXAMPLES=/opt/cpc-resources/examples

USER code198x

# Set pasmo as the entrypoint
ENTRYPOINT ["pasmo"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD pasmo --help > /dev/null