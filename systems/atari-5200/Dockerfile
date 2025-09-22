# Atari 5200 Development Environment
# Based on 6502C processor (same as Atari 800)
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="Atari 5200 assembly development environment"
LABEL version="1.0.0"

# Copy Atari 5200-specific resources
COPY --chown=code198x:code198x resources/ /resources/

# Copy test program if exists
COPY --chown=code198x:code198x test.asm /workspace/test.asm 2>/dev/null || true

# Set Atari 5200-specific environment
ENV SYSTEM_NAME="Atari 5200"
ENV CPU_ARCH="6502C"
ENV ATARI5200_INCLUDES="/resources/includes"
ENV ATARI5200_LIBS="/resources/libs"

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help || exit 1

# Default command shows usage
CMD ["sh", "-c", "echo 'Atari 5200 Development Environment\\nAssemblers: ACME, CA65\\nExample: acme -o game.rom main.asm'"]