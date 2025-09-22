# NASM Toolchain - x86 Assembler
FROM ubuntu:24.04 AS builder

# Install NASM from Ubuntu package repository
RUN apt-get update && apt-get install -y \
    nasm \
    && rm -rf /var/lib/apt/lists/*

# Copy to /opt/nasm for consistency with other toolchains
RUN mkdir -p /opt/nasm/bin && \
    cp /usr/bin/nasm /usr/bin/ndisasm /opt/nasm/bin/ 2>/dev/null || true

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/nasm /opt/nasm