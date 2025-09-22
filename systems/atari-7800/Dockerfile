# Atari 7800 Development Environment
# Based on 6502C processor (compatible with 2600 games)
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="Atari 7800 assembly development environment"
LABEL version="1.0.0"

# Copy Atari 7800-specific resources
COPY --chown=code198x:code198x resources/ /resources/


# Set Atari 7800-specific environment
ENV SYSTEM_NAME="Atari 7800"
ENV CPU_ARCH="6502C"
ENV ATARI7800_INCLUDES="/resources/includes"
ENV ATARI7800_LIBS="/resources/libs"

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD acme --help || exit 1

# Default command shows usage
CMD ["sh", "-c", "echo 'Atari 7800 Development Environment\\nAssemblers: ACME, CA65\\nExample: acme -o game.a78 main.asm'"]