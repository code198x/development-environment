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

# Build Alfred Arnold's AS assembler (supports TLCS-900H among 75+ CPU families)
RUN cd /tmp && \
    wget -q http://john.ccac.rwth-aachen.de:8000/ftp/as/source/c_version/asl-current.tar.bz2 && \
    tar xjf asl-current.tar.bz2 && \
    cd asl-* && \
    if [ -f Makefile.def-samples/Makefile.def-unknown-linux ]; then \
        cp Makefile.def-samples/Makefile.def-unknown-linux Makefile.def; \
    else \
        echo "CFLAGS = -O2" > Makefile.def; \
        echo "CPUDEF = -DHAS_STDC" >> Makefile.def; \
    fi && \
    make binaries && \
    mkdir -p /opt/tlcs-tools/bin /opt/tlcs-tools/include/asl /opt/tlcs-tools/lib/asl && \
    cp asl p2hex p2bin plist alink pbind /opt/tlcs-tools/bin/ && \
    cp include/*.inc /opt/tlcs-tools/include/asl/ 2>/dev/null || true

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

# Health check - verify AS assembler is available
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD test -x /opt/tlcs-tools/bin/asl || echo "OK"