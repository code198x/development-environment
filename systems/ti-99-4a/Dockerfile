# TI-99/4A Development Environment
# Based on TMS9900 processor (16-bit)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="TI-99/4A assembly development environment"
LABEL version="1.0.0"
LABEL system="ti-99-4a"
LABEL year="1981"
LABEL cpu="TMS9900"
LABEL manufacturer="Texas Instruments"
LABEL significance="Popular 16-bit home computer with unique architecture"

# Note: TMS9900 is a unique processor - needs specific assembler

USER root

# Install xdt99 tools for TMS9900 development
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-venv \
    && python3 -m pip install --upgrade pip \
    && python3 -m pip install xdt99 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Copy TI-99/4A-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/ti-99-4a /opt/ti99-resources

# Set up environment for TI-99/4A development
ENV TI99_INCLUDES=/opt/ti99-resources/includes
ENV TI99_LIBS=/opt/ti99-resources/libs
ENV TI99_EXAMPLES=/opt/ti99-resources/examples
ENV SYSTEM_INCLUDES=/opt/ti99-resources/includes
ENV SYSTEM_LIBS=/opt/ti99-resources/libs
ENV SYSTEM_EXAMPLES=/opt/ti99-resources/examples

USER code198x

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD xas99.py --version > /dev/null

# Default command shows usage
CMD ["sh", "-c", "echo 'TI-99/4A Development Environment\nAssembler: xas99 (xdt99 suite)\nExample: xas99.py -R -b main.asm -o program.bin'"]