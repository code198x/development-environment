# Amstrad PCW Development Environment
# Based on Z80 processor
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="Amstrad PCW assembly development environment"
LABEL version="1.0.0"
LABEL system="amstrad-pcw"
LABEL year="1985"
LABEL cpu="Z80"
LABEL manufacturer="Amstrad"
LABEL significance="Popular CP/M word processor and computer"

# Z80 tools are included in base image

USER root

# Copy Amstrad PCW-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/amstrad-pcw /opt/pcw-resources

# Set up environment for Amstrad PCW development
ENV PCW_INCLUDES=/opt/pcw-resources/includes
ENV PCW_LIBS=/opt/pcw-resources/libs
ENV PCW_EXAMPLES=/opt/pcw-resources/examples
ENV SYSTEM_INCLUDES=/opt/pcw-resources/includes
ENV SYSTEM_LIBS=/opt/pcw-resources/libs
ENV SYSTEM_EXAMPLES=/opt/pcw-resources/examples

USER code198x

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --version > /dev/null

# Default command shows usage
CMD ["sh", "-c", "echo 'Amstrad PCW Development Environment\nAssembler: SjASMPlus\nExample: sjasmplus main.asm --raw=output.com'"]