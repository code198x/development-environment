# WLA-DX Toolchain - Multi-Architecture Assembler Suite
# Supports Game Boy, NES, SNES, SMS, Genesis/Megadrive and more
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Build WLA-DX
RUN cd /tmp && \
    git clone --depth 1 https://github.com/vhelin/wla-dx.git && \
    cd wla-dx && \
    mkdir build && \
    cd build && \
    cmake .. -DCMAKE_INSTALL_PREFIX=/opt/wla-dx && \
    make -j$(nproc) && \
    make install

# Final stage - minimal runtime
FROM ubuntu:24.04 AS runtime

# WLA-DX needs basic runtime libs
RUN apt-get update && apt-get install -y --no-install-recommends \
    libc6 \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /opt/wla-dx /opt/wla-dx

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="WLA-DX multi-architecture assembler suite"

# Set PATH
ENV PATH="/opt/wla-dx/bin:$PATH"

# Default command
CMD ["wla-z80", "--help"]