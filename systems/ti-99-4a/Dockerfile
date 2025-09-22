# TI-99/4A Development Environment
# Based on TMS9900 processor (16-bit)
FROM ghcr.io/code198x/tms9900-base:latest

LABEL maintainer="code198x"
LABEL description="TI-99/4A assembly development environment"
LABEL version="1.0.0"
LABEL system="ti-99-4a"
LABEL year="1981"
LABEL cpu="TMS9900"
LABEL manufacturer="Texas Instruments"
LABEL significance="Popular 16-bit home computer with unique architecture"

# Copy TI-99/4A-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/ti-99-4a /opt/ti99-resources

# Set up environment for TI-99/4A development
ENV TI99_INCLUDES=/opt/ti99-resources/includes
ENV TI99_LIBS=/opt/ti99-resources/libs
ENV TI99_EXAMPLES=/opt/ti99-resources/examples
ENV SYSTEM_INCLUDES=/opt/ti99-resources/includes
ENV SYSTEM_LIBS=/opt/ti99-resources/libs
ENV SYSTEM_EXAMPLES=/opt/ti99-resources/examples

WORKDIR /workspace

# Health check inherits from base image
# Default command inherits from base image