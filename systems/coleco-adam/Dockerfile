# Coleco Adam - Home computer expansion of ColecoVision
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Coleco Adam development"
LABEL version="1.0.0"
LABEL system="coleco-adam"
LABEL year="1983"
LABEL cpu="Z80A"
LABEL manufacturer="Coleco"
LABEL emulator="AdamEm"
LABEL significance="Advanced features but poor reliability"

# sjasmplus is included in base image

USER root

# Copy Coleco Adam-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/coleco-adam /opt/adam-resources

# Set up environment for Coleco Adam development
ENV ADAM_INCLUDES=/opt/adam-resources/includes
ENV ADAM_LIBS=/opt/adam-resources/libs
ENV ADAM_EXAMPLES=/opt/adam-resources/examples
ENV SYSTEM_INCLUDES=/opt/adam-resources/includes
ENV SYSTEM_LIBS=/opt/adam-resources/libs
ENV SYSTEM_EXAMPLES=/opt/adam-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null