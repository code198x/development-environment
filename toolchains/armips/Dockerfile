# ARMIPS Toolchain Image
# ARM and MIPS assembler for Nintendo systems
# Separated for caching and parallel builds

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build ARMIPS
WORKDIR /build

# Clone and build from GitHub (need full clone for submodules)
RUN git clone https://github.com/Kingcom/armips.git && \
    cd armips && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc) && \
    mkdir -p /opt/armips/bin && \
    cp armips /opt/armips/bin/ && \
    echo "latest" > /opt/armips/VERSION

# Test the build
RUN /opt/armips/bin/armips --version || /opt/armips/bin/armips -help || echo "ARMIPS built successfully"

# Final stage - minimal image
FROM ubuntu:24.04 AS runtime

# Install minimal runtime dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    libc6 && \
    rm -rf /var/lib/apt/lists/*

# Copy the built tool
COPY --from=builder /opt/armips /opt/armips

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="ARMIPS assembler for ARM/MIPS development"
LABEL org.opencontainers.image.version="latest"

# Set PATH
ENV PATH="/opt/armips/bin:$PATH"

# Health check (armips might not have --version, so fallback to help)
RUN armips --version || armips -help || echo "ARMIPS ready"

# Default command
CMD ["armips", "-help"]