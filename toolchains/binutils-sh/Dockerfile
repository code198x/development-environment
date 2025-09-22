# Binutils-SH Toolchain - SuperH Cross-Compiler Tools
FROM ubuntu:24.04 AS builder

# Install pre-built SH4 cross-compiler toolchain from Ubuntu repositories
RUN apt-get update && apt-get install -y \
    binutils-sh4-linux-gnu \
    gcc-sh4-linux-gnu \
    && rm -rf /var/lib/apt/lists/*

# Copy binaries to /opt/binutils-sh for consistency with other toolchains
RUN mkdir -p /opt/binutils-sh/bin && \
    cp /usr/bin/sh4-linux-gnu-* /opt/binutils-sh/bin/ && \
    # Create sh-elf symlinks for compatibility with existing scripts
    cd /opt/binutils-sh/bin && \
    for tool in sh4-linux-gnu-*; do \
        ln -s "$tool" "sh-elf-${tool#sh4-linux-gnu-}" || true; \
    done

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/binutils-sh /opt/binutils-sh