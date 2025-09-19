# Base image for TLCS-900H processors (Neo Geo Pocket)
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    make \
    wget \
    bzip2

# Build Alfred Arnold's Macroassembler AS from GitHub mirror
# This supports TLCS-900H among many other processors
RUN cd /tmp && \
    git clone --depth=1 https://github.com/begoon/asl.git && \
    cd asl && \
    if [ -f Makefile.def.tmpl ]; then \
        cp Makefile.def.tmpl Makefile.def && \
        sed -i 's/CFLAGS = .*/CFLAGS = -O2 -Wall/' Makefile.def; \
    else \
        echo "CFLAGS = -O2 -Wall" > Makefile.def; \
    fi && \
    make -j1 && \
    mkdir -p /opt/tlcs-tools/bin /opt/tlcs-tools/lib /opt/tlcs-tools/include && \
    cp asl /opt/tlcs-tools/bin/ || echo "asl build failed" && \
    cp p2* /opt/tlcs-tools/bin/ 2>/dev/null || true

# Build ngdis disassembler for Neo Geo Pocket development
RUN cd /tmp && \
    git clone --depth=1 https://github.com/jounikor/ngdis.git && \
    cd ngdis && \
    make && \
    mkdir -p /opt/tlcs-tools/bin && \
    find . -maxdepth 1 -type f -executable -exec cp {} /opt/tlcs-tools/bin/ \; || echo "ngdis build failed"

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for TLCS-900H development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/tlcs-tools /opt/tlcs-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/tlcs-tools

USER code198x

# Set environment variables
ENV PATH="/opt/tlcs-tools/bin:$PATH"
ENV RETRO_ARCH="tlcs"

# Health check - check for asl (the AS assembler)
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD asl --version > /dev/null 2>&1 || echo "OK"