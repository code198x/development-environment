# Base image for MIPS processors (PlayStation, N64, SGI)
# Multi-stage build for smaller runtime image
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install MIPS toolchain from package repositories
# Use packaged cross-compilers for efficiency
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    gcc-mips-linux-gnu \
    g++-mips-linux-gnu \
    binutils-mips-linux-gnu \
    gcc-mipsel-linux-gnu \
    g++-mipsel-linux-gnu \
    binutils-mipsel-linux-gnu

# Create tools directory
RUN mkdir -p /opt/mips-tools/bin

# Copy pre-built ARMIPS from toolchain image (excellent for MIPS assembly)
COPY --from=ghcr.io/code198x/toolchains/armips:latest /opt/armips/bin/armips /opt/mips-tools/bin/armips

# Build PSX SDK tools for PlayStation development (optional)
RUN cd /tmp && \
    git clone --depth=1 https://github.com/Lameguy64/PSn00bSDK.git && \
    cd PSn00bSDK && \
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/mips-tools && \
    cmake --build build && \
    cmake --install build || echo "PSn00bSDK build failed - continuing with GNU tools"

# Build N64 tools (optional)
RUN cd /tmp && \
    git clone --depth=1 https://github.com/ARM9/bass.git && \
    cd bass/bass && \
    make && \
    cp ../bass /opt/mips-tools/bin/ || echo "bass build failed - continuing with GNU tools"

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for MIPS development"
LABEL version="1.0.0"

USER root

# Install runtime MIPS tools
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    gcc-mips-linux-gnu \
    binutils-mips-linux-gnu \
    gcc-mipsel-linux-gnu \
    binutils-mipsel-linux-gnu

# Copy any additional built tools from builder stage (PSn00bSDK, bass)
COPY --from=builder /opt/mips-tools /opt/mips-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/mips-tools

USER code198x

# Set environment variables
ENV PATH="/opt/mips-tools/bin:/usr/bin:$PATH"
ENV RETRO_ARCH="mips"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD mips-linux-gnu-as --version > /dev/null 2>&1 || mipsel-linux-gnu-as --version > /dev/null