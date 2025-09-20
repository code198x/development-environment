# Nintendo Donkey Kong - Nintendo's first major arcade hit
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="sjasmplus assembler for Donkey Kong arcade development"
LABEL version="1.0.0"
LABEL system="nintendo-donkey-kong"
LABEL year="1981"
LABEL cpu="Z80"
LABEL manufacturer="Nintendo"
LABEL emulator="MAME"
LABEL significance="Nintendo's arcade debut, introduced Mario"

# sjasmplus is included in base image

USER root

# Copy Nintendo Donkey Kong-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/nintendo-donkey-kong /opt/donkeykong-resources

# Set up environment for Donkey Kong arcade development
ENV DONKEYKONG_INCLUDES=/opt/donkeykong-resources/includes
ENV DONKEYKONG_LIBS=/opt/donkeykong-resources/libs
ENV DONKEYKONG_EXAMPLES=/opt/donkeykong-resources/examples
ENV SYSTEM_INCLUDES=/opt/donkeykong-resources/includes
ENV SYSTEM_LIBS=/opt/donkeykong-resources/libs
ENV SYSTEM_EXAMPLES=/opt/donkeykong-resources/examples

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus --help > /dev/null