FROM ubuntu:24.04

LABEL maintainer="Code Like It's 198x"
LABEL description="Commodore 64 development environment with ACME assembler"

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    make \
    && rm -rf /var/lib/apt/lists/*

# Build and install ACME
RUN git clone https://github.com/meonwax/acme.git /tmp/acme && \
    cd /tmp/acme/src && \
    make && \
    make install && \
    rm -rf /tmp/acme

# Create workspace directory
WORKDIR /workspace

# Add helper scripts
COPY scripts/build.sh /usr/local/bin/build-c64
RUN chmod +x /usr/local/bin/build-c64

# Set up example Makefile template
COPY templates/Makefile.c64 /usr/local/share/templates/Makefile

# Default command
CMD ["/bin/bash"]