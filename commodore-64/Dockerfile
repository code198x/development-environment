# ACME Cross-Assembler for Commodore 64
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore 64 development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Build ACME from source
RUN git clone https://github.com/meonwax/acme.git /tmp/acme && \
    cd /tmp/acme/src && \
    make && \
    make install && \
    rm -rf /tmp/acme

# Create workspace directory
WORKDIR /workspace

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]