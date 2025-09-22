# Sinclair QL Development Environment
# Based on 68008 processor (68000 family)
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="Sinclair QL assembly development environment"
LABEL version="1.0.0"
LABEL system="sinclair-ql"
LABEL year="1984"
LABEL cpu="68008"
LABEL manufacturer="Sinclair Research"
LABEL significance="Sinclair's business computer with 68000-family processor"

# 68000 tools are included in base image

USER root

# Copy Sinclair QL-specific resources (headers, libs, examples)
COPY --chown=code198x:code198x resources/sinclair-ql /opt/ql-resources

# Set up environment for Sinclair QL development
ENV QL_INCLUDES=/opt/ql-resources/includes
ENV QL_LIBS=/opt/ql-resources/libs
ENV QL_EXAMPLES=/opt/ql-resources/examples
ENV SYSTEM_INCLUDES=/opt/ql-resources/includes
ENV SYSTEM_LIBS=/opt/ql-resources/libs
ENV SYSTEM_EXAMPLES=/opt/ql-resources/examples

USER code198x

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot 2>&1 | head -1 > /dev/null

# Default command shows usage
CMD ["sh", "-c", "echo 'Sinclair QL Development Environment\nAssembler: VASM (68000 mode)\nExample: vasmm68k_mot -Fbin -o program.bin main.asm'"]