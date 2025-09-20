# ACME Cross-Assembler for Commodore 64
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore 64 development"
LABEL version="1.0.0"
LABEL system="commodore-64"

# ACME assembler is now included in the base image
# This image provides C64-specific configuration and resources

USER root

# Copy C64-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/commodore-64 /opt/c64-resources

# Set up environment for C64 development
ENV C64_INCLUDES=/opt/c64-resources/includes
ENV C64_LIBS=/opt/c64-resources/libs
ENV C64_EXAMPLES=/opt/c64-resources/examples
ENV ACME_LIB=/opt/c64-resources/includes:/opt/c64-resources/libs
ENV SYSTEM_INCLUDES=/opt/c64-resources/includes
ENV SYSTEM_LIBS=/opt/c64-resources/libs
ENV SYSTEM_EXAMPLES=/opt/c64-resources/examples

USER code198x

# Create a workspace directory
WORKDIR /workspace

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check to verify ACME is working
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null