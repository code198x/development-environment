# Atari 2600 - 6507 variant of 6502
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Atari 2600 development"
LABEL version="1.0.0"
LABEL system="atari-2600"
LABEL year="1977"
LABEL cpu="6507"

# ACME is included in base image

USER root

# Copy Atari 2600-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-2600 /opt/atari2600-resources

# Set up environment for Atari 2600 development
ENV ATARI2600_INCLUDES=/opt/atari2600-resources/includes
ENV ATARI2600_LIBS=/opt/atari2600-resources/libs
ENV ATARI2600_EXAMPLES=/opt/atari2600-resources/examples
ENV SYSTEM_INCLUDES=/opt/atari2600-resources/includes
ENV SYSTEM_LIBS=/opt/atari2600-resources/libs
ENV SYSTEM_EXAMPLES=/opt/atari2600-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null