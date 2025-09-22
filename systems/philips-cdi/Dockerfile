# Philips CD-i Development Environment
# Based on 68000/68070 processor
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="Philips CD-i assembly development environment"
LABEL version="1.0.0"

# Copy CD-i-specific resources
COPY --chown=code198x:code198x resources/ /resources/

# Copy test program if exists
COPY --chown=code198x:code198x test.asm /workspace/test.asm 2>/dev/null || true

# Set CD-i-specific environment
ENV SYSTEM_NAME="Philips CD-i"
ENV CPU_ARCH="68070"
ENV CDI_INCLUDES="/resources/includes"
ENV CDI_LIBS="/resources/libs"

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD vasmm68k_mot 2>&1 | head -1 || exit 1

# Default command shows usage
CMD ["sh", "-c", "echo 'Philips CD-i Development Environment\\nAssembler: VASM (68000 mode)\\nExample: vasmm68k_mot -Fbin -o game.cdi main.asm'"]