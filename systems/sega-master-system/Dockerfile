# Sega Master System - Z80-based game console
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="Pasmo assembler for Sega Master System development"
LABEL version="1.0.0"
LABEL system="sega-master-system"
LABEL year="1985"
LABEL cpu="Z80"
LABEL manufacturer="Sega"

# Pasmo is included in base image

USER root

# Copy Sega Master System-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sega-master-system /opt/sms-resources

# Set up environment for Sega Master System development
ENV SMS_INCLUDES=/opt/sms-resources/includes
ENV SMS_LIBS=/opt/sms-resources/libs
ENV SMS_EXAMPLES=/opt/sms-resources/examples
ENV SYSTEM_INCLUDES=/opt/sms-resources/includes
ENV SYSTEM_LIBS=/opt/sms-resources/libs
ENV SYSTEM_EXAMPLES=/opt/sms-resources/examples

USER code198x

# Set pasmo as the entrypoint
ENTRYPOINT ["pasmo"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD pasmo --help > /dev/null