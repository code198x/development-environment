# cc65 Toolchain Image
# Builds the cc65 suite (C compiler, ca65 assembler, ld65 linker, etc.)
# This is separated to enable caching and parallel builds

ARG CC65_VERSION=V2.19

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build cc65
ARG CC65_VERSION
WORKDIR /build

# Download and extract
RUN wget -q https://github.com/cc65/cc65/archive/refs/tags/${CC65_VERSION}.tar.gz && \
    tar -xzf ${CC65_VERSION}.tar.gz && \
    rm ${CC65_VERSION}.tar.gz

# Build with parallel make for speed
RUN cd cc65-* && \
    make -j$(nproc) PREFIX=/opt/cc65 && \
    make install PREFIX=/opt/cc65 && \
    # Create version file for tracking
    echo "${CC65_VERSION}" > /opt/cc65/VERSION

# Test the build
RUN /opt/cc65/bin/cc65 --version && \
    /opt/cc65/bin/ca65 --version && \
    /opt/cc65/bin/ld65 --version

# Final stage - minimal image with just the tools
FROM ubuntu:24.04 AS runtime

# Install only runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    libc6 \
    && rm -rf /var/lib/apt/lists/*

# Copy the built tools
COPY --from=builder /opt/cc65 /opt/cc65

# Add labels for tracking
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="cc65 toolchain for 6502 development"
LABEL org.opencontainers.image.version="V2.19"

# Set PATH for convenience (though base images will handle this)
ENV PATH="/opt/cc65/bin:$PATH"

# Health check
RUN cc65 --version && ca65 --version && ld65 --version

# Default to just showing version
CMD ["cc65", "--version"]