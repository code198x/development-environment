# cc65 for Nintendo Entertainment System
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="cc65 assembler suite for NES development"
LABEL version="1.0.0"
LABEL system="nintendo-entertainment-system"

USER root

# cc65 is now included in the base image
# This image adds NES-specific configuration

# Copy NES configuration file
RUN mkdir -p /opt/6502-tools/share/cc65/cfg/
COPY nes.cfg /opt/6502-tools/share/cc65/cfg/

# Copy NES-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nintendo-nes /opt/nes-resources

# Create wrapper script for easier usage
RUN echo '#!/bin/bash\nif [ "$1" = "build" ]; then\n  ca65 main.asm -o main.o && ld65 main.o -C /opt/6502-tools/share/cc65/cfg/nes.cfg -o program.nes\nelse\n  ca65 "$@"\nfi' > /opt/6502-tools/bin/nes-build && \
    chmod +x /opt/6502-tools/bin/nes-build

# Set up environment for NES development
ENV NES_INCLUDES=/opt/nes-resources/includes
ENV NES_LIBS=/opt/nes-resources/libs
ENV NES_EXAMPLES=/opt/nes-resources/examples
ENV SYSTEM_INCLUDES=/opt/nes-resources/includes
ENV SYSTEM_LIBS=/opt/nes-resources/libs
ENV SYSTEM_EXAMPLES=/opt/nes-resources/examples

USER code198x

# Set ca65 as the entrypoint
ENTRYPOINT ["ca65"]

# Default command shows version
CMD ["--version"]
# Health check to verify assembler is working
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ca65 --version > /dev/null
