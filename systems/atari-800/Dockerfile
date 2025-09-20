# Atari 800 - 6502-based home computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="cc65 assembler for Atari 800 development"
LABEL version="1.0.0"
LABEL system="atari-800"
LABEL year="1979"
LABEL cpu="6502"
LABEL manufacturer="Atari"

# cc65 is included in base image

USER root

# Copy Atari 800-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/atari-800 /opt/atari800-resources

# Set up environment for Atari 800 development
ENV ATARI800_INCLUDES=/opt/atari800-resources/includes
ENV ATARI800_LIBS=/opt/atari800-resources/libs
ENV ATARI800_EXAMPLES=/opt/atari800-resources/examples
ENV SYSTEM_INCLUDES=/opt/atari800-resources/includes
ENV SYSTEM_LIBS=/opt/atari800-resources/libs
ENV SYSTEM_EXAMPLES=/opt/atari800-resources/examples

USER code198x

# Set ca65 as the entrypoint
ENTRYPOINT ["ca65"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ca65 --version > /dev/null