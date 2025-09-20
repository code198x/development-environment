# vasm Toolchain Image
# Multi-target assembler supporting 68000, Z80, 6502, and more
# Separated for caching and parallel builds

ARG VASM_VERSION=1.9.1

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build vasm
ARG VASM_VERSION
WORKDIR /build

# Clone vasm source from GitHub mirror
RUN git clone --depth=1 https://github.com/dbuchwald/vasm.git

# Build multiple CPU targets
WORKDIR /build/vasm

# Build for 68000 (Amiga, Atari ST)
RUN make CPU=m68k SYNTAX=mot && \
    mkdir -p /opt/vasm/bin && \
    cp vasmm68k_mot /opt/vasm/bin/ && \
    cp vobjdump /opt/vasm/bin/vobjdump_m68k && \
    make clean

# Build for Z80 (if needed for some systems)
RUN make CPU=z80 SYNTAX=oldstyle && \
    cp vasmz80_oldstyle /opt/vasm/bin/ && \
    make clean

# Build for 6502 (alternative to cc65/acme)
RUN make CPU=6502 SYNTAX=oldstyle && \
    cp vasm6502_oldstyle /opt/vasm/bin/ && \
    make clean

# Create version file
RUN echo "${VASM_VERSION}" > /opt/vasm/VERSION

# Test the builds (vasm shows version in error messages)
RUN /opt/vasm/bin/vasmm68k_mot 2>&1 | head -5 || true && \
    /opt/vasm/bin/vasmz80_oldstyle 2>&1 | head -5 || true && \
    /opt/vasm/bin/vasm6502_oldstyle 2>&1 | head -5 || true

# Final stage
FROM ubuntu:24.04 AS runtime

# Runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    libc6 \
    && rm -rf /var/lib/apt/lists/*

# Copy built tools
COPY --from=builder /opt/vasm /opt/vasm

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="vasm multi-target assembler"
LABEL org.opencontainers.image.version="${VASM_VERSION}"

# Set PATH
ENV PATH="/opt/vasm/bin:$PATH"

# Health check
RUN vasmm68k_mot 2>&1 | head -1 || true

# Default command (shows help and version info)
CMD ["vasmm68k_mot"]