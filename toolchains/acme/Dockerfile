# ACME Toolchain Image
# Builds the ACME cross-assembler for 6502 development
# Separated for caching and parallel builds

ARG ACME_VERSION=0.97.0

# Build stage
FROM ubuntu:24.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build ACME
ARG ACME_VERSION
WORKDIR /build

# Clone and build from GitHub
RUN git clone --depth=1 https://github.com/meonwax/acme.git && \
    cd acme/src && \
    make && \
    mkdir -p /opt/acme/bin && \
    cp acme /opt/acme/bin/ && \
    # Include library files
    mkdir -p /opt/acme/lib && \
    cp -r ../ACME_Lib/* /opt/acme/lib/ 2>/dev/null || true && \
    # Create version file
    echo "latest" > /opt/acme/VERSION

# Test the build
RUN /opt/acme/bin/acme --version

# Final stage - minimal image
FROM ubuntu:24.04 AS runtime

# No special runtime dependencies for ACME
RUN apt-get update && apt-get install -y --no-install-recommends \
    libc6 \
    && rm -rf /var/lib/apt/lists/*

# Copy the built tool
COPY --from=builder /opt/acme /opt/acme

# Add labels
LABEL org.opencontainers.image.source="https://github.com/code198x/development-environment"
LABEL org.opencontainers.image.description="ACME assembler for 6502 development"
LABEL org.opencontainers.image.version="${ACME_VERSION}"

# Set PATH
ENV PATH="/opt/acme/bin:$PATH"

# Health check
RUN acme --version

# Default command
CMD ["acme", "--version"]