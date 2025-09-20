# Commodore VIC-20 - 6502-based home computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore VIC-20 development"
LABEL version="1.0.0"
LABEL system="commodore-vic-20"
LABEL year="1980"
LABEL cpu="6502"
LABEL manufacturer="Commodore"

# ACME is included in base image

USER root

# Copy Commodore VIC-20-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/commodore-vic-20 /opt/vic20-resources

# Set up environment for Commodore VIC-20 development
ENV VIC20_INCLUDES=/opt/vic20-resources/includes
ENV VIC20_LIBS=/opt/vic20-resources/libs
ENV VIC20_EXAMPLES=/opt/vic20-resources/examples
ENV SYSTEM_INCLUDES=/opt/vic20-resources/includes
ENV SYSTEM_LIBS=/opt/vic20-resources/libs
ENV SYSTEM_EXAMPLES=/opt/vic20-resources/examples

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help > /dev/null