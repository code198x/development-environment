# Base image for Intel 8080/8085 processors
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
# Use cache mount for apt to improve caching
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    zlib1g-dev

# Build simple 8080 assembler from source
RUN cd /tmp && \
    mkdir -p /opt/8080-tools/bin && \
    git clone https://github.com/begoon/asm8080.git && \
    cd asm8080 && \
    if [ -f CMakeLists.txt ]; then \
        cmake . && make && cp asm8080 /opt/8080-tools/bin/; \
    elif [ -f Makefile ]; then \
        make && cp asm8080 /opt/8080-tools/bin/; \
    else \
        gcc -o asm8080 *.c && cp asm8080 /opt/8080-tools/bin/; \
    fi

# Build z80asm with 8080 support (fallback)
RUN cd /tmp && \
    git clone https://github.com/udo-munk/z80asm.git && \
    cd z80asm && \
    make && \
    cp z80asm /opt/8080-tools/bin/ || \
    echo "z80asm build failed - asm8080 should be sufficient"

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for Intel 8080/8085 development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/8080-tools /opt/8080-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/8080-tools

USER code198x

# Set environment variables
ENV PATH="/opt/8080-tools/bin:$PATH"
ENV RETRO_ARCH="8080"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD asm8080 --version > /dev/null 2>&1 || z80asm --help > /dev/null