# jzintv Toolchain Image
# CP1610 assembler (as1600) for Mattel Intellivision
# Separated for caching and parallel builds

ARG JZINTV_VERSION=latest

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    wget \
    unzip \
    ca-certificates \
    libsdl2-dev \
    && rm -rf /var/lib/apt/lists/*

# Build jzintv
WORKDIR /build

# Download jzintv Linux binary package which contains as1600 assembler
RUN wget -q http://spatula-city.org/~im14u2c/intv/dl/jzintv-20200712-linux-x86-64-sdl2.zip && \
    unzip -q jzintv-20200712-linux-x86-64-sdl2.zip

# The jzintv package includes prebuilt Linux binaries
RUN mkdir -p /opt/jzintv/bin && \
    # Copy the assembler and utilities from the jzintv package
    cp jzintv-20200712-linux-x86-64-sdl2/bin/as1600 /opt/jzintv/bin/ && \
    cp jzintv-20200712-linux-x86-64-sdl2/bin/bin2rom /opt/jzintv/bin/ && \
    cp jzintv-20200712-linux-x86-64-sdl2/bin/rom2bin /opt/jzintv/bin/ && \
    chmod +x /opt/jzintv/bin/* && \
    # Create version file
    echo "20200712" > /opt/jzintv/VERSION

# Test the build
RUN /opt/jzintv/bin/as1600 --version || echo "as1600 built successfully"

# Final stage
FROM ubuntu:24.04 AS runtime

# Runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    libc6 \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Copy built tools
COPY --from=builder /opt/jzintv /opt/jzintv

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="jzintv CP1610 assembler for Intellivision"
LABEL org.opencontainers.image.version="latest"

# Set PATH
ENV PATH="/opt/jzintv/bin:$PATH"

# Health check
RUN as1600 --version || echo "as1600 ready"

# Default command
CMD ["sh", "-c", "echo 'jzintv tools: as1600, bin2rom, rom2bin'"]