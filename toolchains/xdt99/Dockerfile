# xdt99 Toolchain Image
# TMS9900 assembler (xas99) for TI-99/4A
# Separated for caching and parallel builds

ARG XDT99_VERSION=latest

# Build stage
FROM ubuntu:24.04 AS builder

# Install Python for xdt99
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install xdt99 tools
# Using --break-system-packages is safe in Docker containers
# Add --no-cache-dir to avoid cache issues and reduce image size
# Use separate RUN commands for better error isolation
RUN python3 -m pip install --break-system-packages --no-cache-dir --upgrade pip

RUN python3 -m pip install --break-system-packages --no-cache-dir xdt99

# Create tools directory and wrapper scripts
RUN mkdir -p /opt/xdt99/bin && \
    # Create wrapper scripts for xdt99 tools
    echo '#!/bin/bash\npython3 -m xdt99.xas99 "$@"' > /opt/xdt99/bin/xas99 && \
    echo '#!/bin/bash\npython3 -m xdt99.xga99 "$@"' > /opt/xdt99/bin/xga99 && \
    echo '#!/bin/bash\npython3 -m xdt99.xbas99 "$@"' > /opt/xdt99/bin/xbas99 && \
    echo '#!/bin/bash\npython3 -m xdt99.xdm99 "$@"' > /opt/xdt99/bin/xdm99 && \
    chmod +x /opt/xdt99/bin/* && \
    # Create version file
    echo "latest" > /opt/xdt99/VERSION

# Test the build
RUN python3 -m xdt99.xas99 --version

# Final stage
FROM ubuntu:24.04 AS runtime

# Runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install xdt99 in runtime
RUN python3 -m pip install --break-system-packages --no-cache-dir xdt99

# Copy wrapper scripts
COPY --from=builder /opt/xdt99 /opt/xdt99

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="xdt99 TMS9900 assembler for TI-99/4A"
LABEL org.opencontainers.image.version="latest"

# Set PATH
ENV PATH="/opt/xdt99/bin:$PATH"

# Health check
RUN xas99 --version

# Default command
CMD ["sh", "-c", "echo 'xdt99 tools: xas99, xga99, xbas99, xdm99'"]