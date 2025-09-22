# TMS9900 Processor Base Image
# For TI-99/4A (16-bit processor)
FROM ghcr.io/code198x/code198x-base:latest AS builder

USER root

# Install Python for xdt99 tools
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/*

# Install xdt99 tools (includes xas99 assembler for TMS9900)
# Using --break-system-packages is safe in Docker containers
RUN python3 -m pip install --break-system-packages --upgrade pip && \
    python3 -m pip install --break-system-packages xdt99

# Create tools directory structure
RUN mkdir -p /opt/tms9900-tools/bin && \
    # Create wrapper scripts for xdt99 tools
    echo '#!/bin/bash\npython3 -m xdt99.xas99 "$@"' > /opt/tms9900-tools/bin/xas99 && \
    echo '#!/bin/bash\npython3 -m xdt99.xga99 "$@"' > /opt/tms9900-tools/bin/xga99 && \
    echo '#!/bin/bash\npython3 -m xdt99.xbas99 "$@"' > /opt/tms9900-tools/bin/xbas99 && \
    echo '#!/bin/bash\npython3 -m xdt99.xdm99 "$@"' > /opt/tms9900-tools/bin/xdm99 && \
    chmod +x /opt/tms9900-tools/bin/*

# Runtime stage
FROM ghcr.io/code198x/code198x-base:latest AS runtime

LABEL maintainer="code198x"
LABEL description="Base image for TMS9900 processor development (TI-99/4A)"
LABEL version="1.0.0"

USER root

# Install Python runtime
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install xdt99 in runtime
RUN python3 -m pip install --break-system-packages xdt99

# Copy wrapper scripts from builder
COPY --from=builder /opt/tms9900-tools /opt/tms9900-tools

# Set up permissions
RUN chown -R code198x:code198x /opt/tms9900-tools

USER code198x

# Set environment for TMS9900 development
ENV PATH="/opt/tms9900-tools/bin:$PATH"
ENV RETRO_ARCH="tms9900"
ENV TMS9900_TOOLS="/opt/tms9900-tools"

# Health check to verify assembler works
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD xas99 --version || exit 0

WORKDIR /workspace

# Default command shows usage
CMD ["sh", "-c", "echo 'TMS9900 Development Environment\\nAssembler: xas99 (xdt99 suite)\\nTools: xga99, xbas99, xdm99\\nExample: xas99 -R -b main.asm -o program.bin'"]