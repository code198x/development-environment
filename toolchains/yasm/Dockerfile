# YASM Toolchain - x86 Assembler
FROM ubuntu:24.04 AS builder

# Install YASM from package - building from source requires Python
RUN apt-get update && apt-get install -y \
    yasm \
    && rm -rf /var/lib/apt/lists/*

# Copy to /opt/yasm for consistency with other toolchains
RUN mkdir -p /opt/yasm/bin && \
    cp /usr/bin/yasm /opt/yasm/bin/

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/yasm /opt/yasm