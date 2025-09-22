# Nintendo SNES (Super Nintendo) Development Environment
# Based on 65C816 processor (16-bit extension of 6502)
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="Nintendo SNES assembly development environment"
LABEL version="1.0.0"

# SNES uses 65C816 processor, supported by ca65 from cc65 suite
# The 6502-base already includes ca65 which supports 65816

# Copy SNES-specific resources
COPY --chown=code198x:code198x resources/ /resources/

# Copy test program if exists
COPY --chown=code198x:code198x test.asm /workspace/test.asm 2>/dev/null || true

# Set SNES-specific environment
ENV SYSTEM_NAME="Nintendo SNES"
ENV CPU_ARCH="65C816"
ENV SNES_INCLUDES="/resources/includes"
ENV SNES_LIBS="/resources/libs"

WORKDIR /workspace

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ca65 --version || exit 1

# Default command shows usage
CMD ["sh", "-c", "echo 'Nintendo SNES Development Environment\\nAssembler: ca65 (65816 mode)\\nExample: ca65 -t snes main.asm -o main.o && ld65 -t snes main.o -o game.sfc'"]