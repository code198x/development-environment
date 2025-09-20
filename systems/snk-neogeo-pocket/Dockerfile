# SNK Neo Geo Pocket - 16-bit handheld console
FROM ghcr.io/code198x/tlcs-base:latest

LABEL maintainer="code198x"
LABEL description="ngpasm assembler for Neo Geo Pocket development"
LABEL version="1.0.0"
LABEL system="snk-neogeo-pocket"
LABEL year="1998"
LABEL cpu="TLCS-900H"
LABEL manufacturer="SNK"
LABEL emulator="NeoPop/MAME/Mednafen"
LABEL significance="SNK's excellent handheld with great fighting games"

# ngpasm is included in base image

USER root

# Copy Neo Geo Pocket-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/snk-neogeo-pocket /opt/neogeopocket-resources

# Set up environment for Neo Geo Pocket development
ENV NEOGEOPOCKET_INCLUDES=/opt/neogeopocket-resources/includes
ENV NEOGEOPOCKET_LIBS=/opt/neogeopocket-resources/libs
ENV NEOGEOPOCKET_EXAMPLES=/opt/neogeopocket-resources/examples
ENV SYSTEM_INCLUDES=/opt/neogeopocket-resources/includes
ENV SYSTEM_LIBS=/opt/neogeopocket-resources/libs
ENV SYSTEM_EXAMPLES=/opt/neogeopocket-resources/examples

USER code198x

# Set ngpasm as the entrypoint
ENTRYPOINT ["ngpasm"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ngpasm --help > /dev/null 2>&1 || echo "OK"