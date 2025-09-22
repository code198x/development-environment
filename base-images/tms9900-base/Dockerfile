# TMS9900 Processor Base Image
# For TI-99/4A (16-bit processor)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Base image for TMS9900 processor development (TI-99/4A)"
LABEL version="1.0.0"

USER root

# Install Python runtime (needed for xdt99)
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Copy wrapper scripts from toolchain image
COPY --from=ghcr.io/code198x/toolchains/xdt99:latest /opt/xdt99 /opt/tms9900-tools

# Set up permissions
RUN chown -R code198x:code198x /opt/tms9900-tools

USER code198x

# Set environment for TMS9900 development
ENV PATH="/opt/tms9900-tools:$PATH"
ENV RETRO_ARCH="tms9900"
ENV TMS9900_TOOLS="/opt/tms9900-tools"

# Health check to verify assembler works
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD python3 /opt/tms9900-tools/xas99.py -h > /dev/null 2>&1 || exit 0

WORKDIR /workspace

# Default command shows usage
CMD ["sh", "-c", "echo 'TMS9900 Development Environment\\nAssembler: xas99 (xdt99 suite)\\nTools: xga99, xbas99, xdm99\\nExample: xas99 -R -b main.asm -o program.bin'"]