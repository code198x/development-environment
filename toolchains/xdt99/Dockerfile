# xdt99 Toolchain Image
# TMS9900 assembler (xas99) for TI-99/4A
# Separated for caching and parallel builds

ARG XDT99_VERSION=3.6.5

# Build stage
FROM ubuntu:24.04 AS builder

# Install Python and tools for xdt99
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    wget \
    tar \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Download and install xdt99 from GitHub
# xdt99 is not available on PyPI, must be downloaded from GitHub
# Using latest stable version
RUN mkdir -p /opt/xdt99 && \
    wget https://github.com/endlos99/xdt99/archive/refs/tags/3.6.5.tar.gz && \
    tar xzf 3.6.5.tar.gz && \
    mv xdt99-3.6.5/* /opt/xdt99/ && \
    rm -rf 3.6.5.tar.gz xdt99-3.6.5

# Make xdt99 tools executable
RUN chmod +x /opt/xdt99/*.py && \
    echo "3.6.5" > /opt/xdt99/VERSION

# Test the build
RUN python3 /opt/xdt99/xas99.py -h > /dev/null 2>&1

# Final stage
FROM ubuntu:24.04 AS runtime

# Runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Copy wrapper scripts
COPY --from=builder /opt/xdt99 /opt/xdt99

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="xdt99 TMS9900 assembler for TI-99/4A"
LABEL org.opencontainers.image.version="3.6.5"

# Set PATH
ENV PATH="/opt/xdt99:$PATH"

# Health check
RUN python3 /opt/xdt99/xas99.py -h > /dev/null 2>&1 && echo "xas99 ready"

# Default command
CMD ["sh", "-c", "echo 'xdt99 tools: xas99, xga99, xbas99, xdm99'"]