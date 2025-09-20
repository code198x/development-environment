# Base image for Z80-family processors
# Uses pre-built toolchain images for fast assembly
FROM ghcr.io/code198x/code198x-base:latest

USER root

# Install runtime dependencies
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Copy pre-built tools from toolchain images
COPY --from=ghcr.io/code198x/toolchains/sjasmplus:v1.20.3 /opt/sjasmplus /opt/z80-tools/sjasmplus
COPY --from=ghcr.io/code198x/toolchains/vasm:v1.9.1 /opt/vasm/bin/vasmz80_oldstyle /opt/z80-tools/bin/vasmz80

# Note: pasmo could be added as another toolchain if needed
# For now, keeping inline build for this smaller tool
RUN cd /tmp && \
    wget -q http://pasmo.speccy.org/bin/pasmo-0.5.5.tar.gz && \
    tar -xzf pasmo-${PASMO_VERSION}.tar.gz && \
    cd pasmo-${PASMO_VERSION} && \
    cp /usr/share/misc/config.guess . && \
    cp /usr/share/misc/config.sub . && \
    ./configure --prefix=/opt/z80-tools && \
    make && make install

# Runtime stage - much smaller
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for Z80 family development"
LABEL version="1.0.0"

USER root

# Copy built tools from builder stage
COPY --from=builder /opt/z80-tools /opt/z80-tools

# Set up directories and permissions
RUN chown -R code198x:code198x /opt/z80-tools

USER code198x

# Set common environment variables for Z80 development
ENV PATH="/opt/z80-tools/bin:$PATH"
ENV RETRO_ARCH="z80"

# Health check to verify assemblers work
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD sjasmplus -h > /dev/null && pasmo --help > /dev/null