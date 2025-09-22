# ACME Toolchain - Multi-platform 6502/6510/65816 Cross Assembler
FROM ubuntu:24.04 AS builder

# Install ACME from Ubuntu package repository
# Version 0.97 includes MEGA65 (45GS02) support
RUN apt-get update && apt-get install -y \
    acme \
    && rm -rf /var/lib/apt/lists/*

# Copy to /opt/acme for consistency with other toolchains
RUN mkdir -p /opt/acme/bin && \
    cp /usr/bin/acme /opt/acme/bin/ && \
    # Copy library files if they exist
    mkdir -p /opt/acme/lib && \
    cp -r /usr/share/acme/* /opt/acme/lib/ 2>/dev/null || true

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/acme /opt/acme