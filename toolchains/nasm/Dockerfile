# NASM Toolchain Image
# Builds the NASM assembler for x86 development
# Separated for caching and parallel builds

ARG NASM_VERSION=2.16.03

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    wget \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build NASM
ARG NASM_VERSION
WORKDIR /build

# Download and extract
RUN wget -q https://www.nasm.us/pub/nasm/releasebuilds/${NASM_VERSION}/nasm-${NASM_VERSION}.tar.xz && \
    tar -xf nasm-${NASM_VERSION}.tar.xz && \
    rm nasm-${NASM_VERSION}.tar.xz

# Build and install
RUN cd nasm-* && \
    ./configure --prefix=/opt/nasm && \
    make -j$(nproc) && \
    make install && \
    echo "${NASM_VERSION}" > /opt/nasm/VERSION

# Test the build
RUN /opt/nasm/bin/nasm -v

# Final stage - minimal image
FROM ubuntu:24.04 AS runtime

# Install minimal runtime dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    libc6 && \
    rm -rf /var/lib/apt/lists/*

# Copy the built tool
COPY --from=builder /opt/nasm /opt/nasm

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="NASM assembler for x86 development"
LABEL org.opencontainers.image.version="2.16.03"

# Set PATH
ENV PATH="/opt/nasm/bin:$PATH"

# Health check
RUN nasm -v

# Default command
CMD ["nasm", "-v"]