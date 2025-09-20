# Capcom Street Fighter II - CPS-1 fighting game arcade
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="vasm assembler for Street Fighter II/CPS-1 development"
LABEL version="1.0.0"
LABEL system="capcom-street-fighter-ii"
LABEL year="1991"
LABEL cpu="MC68000"
LABEL manufacturer="Capcom"
LABEL emulator="MAME/FinalBurn Neo"
LABEL significance="Revolutionary fighting game mechanics"

# vasm is included in base image

USER root

# Copy Street Fighter II-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/capcom-street-fighter-ii /opt/sf2-resources

# Set up environment for Street Fighter II development
ENV SF2_INCLUDES=/opt/sf2-resources/includes
ENV SF2_LIBS=/opt/sf2-resources/libs
ENV SF2_EXAMPLES=/opt/sf2-resources/examples
ENV SYSTEM_INCLUDES=/opt/sf2-resources/includes
ENV SYSTEM_LIBS=/opt/sf2-resources/libs
ENV SYSTEM_EXAMPLES=/opt/sf2-resources/examples

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasm6800_mot"]

# Default command shows help
CMD ["-help"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasm6800_mot -help > /dev/null