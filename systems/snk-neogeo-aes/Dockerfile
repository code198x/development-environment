# SNK Neo Geo AES - Home version of arcade system
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Neo Geo AES development"
LABEL version="1.0.0"
LABEL system="snk-neogeo-aes"
LABEL year="1990"
LABEL cpu="MC68000"
LABEL manufacturer="SNK"
LABEL emulator="MAME/FinalBurn Neo"
LABEL significance="Home console with arcade-perfect games"

# vasm is included in base image

USER root

# Copy Neo Geo AES-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/snk-neogeo-aes /opt/neogeo-aes-resources

# Set up environment for Neo Geo AES development
ENV NEOGEO_AES_INCLUDES=/opt/neogeo-aes-resources/includes
ENV NEOGEO_AES_LIBS=/opt/neogeo-aes-resources/libs
ENV NEOGEO_AES_EXAMPLES=/opt/neogeo-aes-resources/examples
ENV SYSTEM_INCLUDES=/opt/neogeo-aes-resources/includes
ENV SYSTEM_LIBS=/opt/neogeo-aes-resources/libs
ENV SYSTEM_EXAMPLES=/opt/neogeo-aes-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null