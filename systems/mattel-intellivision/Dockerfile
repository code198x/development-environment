# Mattel Intellivision Development Environment
# Based on CP1610 processor (unique 16-bit processor)
FROM ghcr.io/code198x/cp1610-base:latest

LABEL maintainer="code198x"
LABEL description="Mattel Intellivision assembly development environment"
LABEL version="1.0.0"
LABEL system="mattel-intellivision"
LABEL year="1979"
LABEL cpu="CP1610"
LABEL manufacturer="Mattel"
LABEL significance="Popular 16-bit gaming console with unique architecture"

# Copy Intellivision-specific resources
COPY --chown=code198x:code198x resources/ /resources/

# Set Intellivision-specific environment
ENV SYSTEM_NAME="Mattel Intellivision"
ENV CPU_ARCH="CP1610"
ENV INTELLIVISION_INCLUDES="/resources/includes"
ENV INTELLIVISION_LIBS="/resources/libs"

WORKDIR /workspace

# Health check inherits from base image
# Default command inherits from base image