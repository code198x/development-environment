# VASM for Commodore Amiga
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="VASM assembler for Commodore Amiga development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Download and build VASM
RUN curl -L http://phoenix.owl.de/tags/vasm1_9.tar.gz -o /tmp/vasm.tar.gz && \
    cd /tmp && \
    tar -xzf vasm.tar.gz && \
    cd vasm && \
    make CPU=m68k SYNTAX=mot && \
    cp vasmm68k_mot /usr/local/bin/ && \
    cp vobjdump /usr/local/bin/ && \
    rm -rf /tmp/vasm*

# Create workspace directory
WORKDIR /workspace

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]