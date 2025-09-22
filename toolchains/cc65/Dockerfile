# cc65 Toolchain - 6502 Cross-Compiler Suite
FROM ubuntu:24.04 AS builder

# Install cc65 from Ubuntu package repository
RUN apt-get update && apt-get install -y \
    cc65 \
    cc65-doc \
    && rm -rf /var/lib/apt/lists/*

# Copy to /opt/cc65 for consistency with other toolchains
RUN mkdir -p /opt/cc65/bin /opt/cc65/share && \
    cp -r /usr/bin/cc65 /usr/bin/ca65 /usr/bin/ld65 /usr/bin/ar65 /usr/bin/od65 /usr/bin/sim65 /usr/bin/cl65 /usr/bin/da65 /usr/bin/co65 /usr/bin/grc65 /usr/bin/sp65 /opt/cc65/bin/ 2>/dev/null || true && \
    cp -r /usr/share/cc65 /opt/cc65/share/ 2>/dev/null || true

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/cc65 /opt/cc65