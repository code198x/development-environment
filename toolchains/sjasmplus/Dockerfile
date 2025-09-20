# SjASMPlus Toolchain Image
# Z80 assembler for ZX Spectrum, Amstrad CPC, MSX, etc.
# Separated for caching and parallel builds

ARG SJASMPLUS_VERSION=v1.20.3

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build SjASMPlus
ARG SJASMPLUS_VERSION
WORKDIR /build

# Clone and build from GitHub
RUN git clone --depth=1 --branch ${SJASMPLUS_VERSION} https://github.com/z00m128/sjasmplus.git && \
    cd sjasmplus && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j$(nproc) && \
    mkdir -p /opt/sjasmplus/bin && \
    cp sjasmplus /opt/sjasmplus/bin/ && \
    # Create version file
    echo "${SJASMPLUS_VERSION}" > /opt/sjasmplus/VERSION

# Test the build
RUN /opt/sjasmplus/bin/sjasmplus --version

# Final stage
FROM ubuntu:24.04 AS runtime

# Runtime dependencies (libstdc++ for C++)
RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    libc6 \
    && rm -rf /var/lib/apt/lists/*

# Copy built tool
COPY --from=builder /opt/sjasmplus /opt/sjasmplus

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="SjASMPlus Z80 assembler"
LABEL org.opencontainers.image.version="${SJASMPLUS_VERSION}"

# Set PATH
ENV PATH="/opt/sjasmplus/bin:$PATH"

# Health check
RUN sjasmplus --version

# Default command
CMD ["sjasmplus", "--version"]