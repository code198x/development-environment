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

# Create wrapper script for easier usage
RUN echo '#!/bin/bash\nif [ "$1" = "build" ]; then\n  ca65 main.asm -o main.o && ld65 main.o -C /opt/6502-tools/share/cc65/cfg/nes.cfg -o program.nes\nelse\n  ca65 "$@"\nfi' > /opt/6502-tools/bin/nes-build && \
    chmod +x /opt/6502-tools/bin/nes-build

USER code198x

# Set ca65 as the entrypoint
ENTRYPOINT ["ca65"]

# Default command shows version
CMD ["--version"]