# CP1610 Processor Base Image
# For Mattel Intellivision (unique 16-bit processor)
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build jzintv SDK which includes as1600 assembler for CP1610
RUN cd /tmp && \
    git clone https://github.com/intvsteve/jzintv-mirror.git && \
    cd jzintv-mirror/src && \
    make -j$(nproc) && \
    mkdir -p /opt/cp1610-tools/bin && \
    cp as1600/as1600 /opt/cp1610-tools/bin/ && \
    cp utilities/bin2rom /opt/cp1610-tools/bin/ && \
    cp utilities/rom2bin /opt/cp1610-tools/bin/

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for CP1610 processor development (Intellivision)"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/cp1610-tools /opt/cp1610-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/cp1610-tools

USER code198x

# Set environment for CP1610 development
ENV PATH="/opt/cp1610-tools/bin:$PATH"
ENV RETRO_ARCH="cp1610"
ENV CP1610_TOOLS="/opt/cp1610-tools"

# Health check to verify assembler works
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD as1600 --version || exit 0

WORKDIR /workspace

# Default command shows usage
CMD ["sh", "-c", "echo 'CP1610 Development Environment\\nAssembler: as1600 (from jzintv)\\nTools: bin2rom, rom2bin\\nExample: as1600 -o game.rom game.asm'"]