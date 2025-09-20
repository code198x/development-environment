# SjASMPlus for ZX Spectrum
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for ZX Spectrum development"
LABEL version="1.0.0"
LABEL system="sinclair-zx-spectrum"

# sjasmplus is now included in the base image
# This image provides ZX Spectrum specific configuration

USER root

# Copy ZX Spectrum-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sinclair-zx-spectrum /opt/spectrum-resources

# Set up environment for ZX Spectrum development
ENV SPECTRUM_INCLUDES=/opt/spectrum-resources/includes
ENV SPECTRUM_LIBS=/opt/spectrum-resources/libs
ENV SPECTRUM_EXAMPLES=/opt/spectrum-resources/examples
ENV SYSTEM_INCLUDES=/opt/spectrum-resources/includes
ENV SYSTEM_LIBS=/opt/spectrum-resources/libs
ENV SYSTEM_EXAMPLES=/opt/spectrum-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]
# Health check to verify assembler is working
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null
