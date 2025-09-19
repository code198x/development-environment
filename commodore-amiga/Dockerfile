# VASM for Commodore Amiga
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="VASM assembler for Commodore Amiga development"
LABEL version="1.0.0"
LABEL system="commodore-amiga"

USER root

# Download and build VASM
# Note: Using multiple mirror URLs for reliability
RUN mkdir -p /opt/68000-tools/bin && \
    for url in \
        "http://phoenix.owl.de/tags/vasm1_9.tar.gz" \
        "http://sun.hasenbraten.de/vasm/release/vasm.tar.gz" \
        "https://github.com/mbitsnbites/vasm/archive/refs/heads/master.tar.gz"; do \
        echo "Trying to download from: $url" && \
        curl -L --connect-timeout 10 --retry 3 "$url" -o /tmp/vasm.tar.gz && break || \
        echo "Failed to download from $url, trying next..."; \
    done && \
    cd /tmp && \
    tar -xzf vasm.tar.gz && \
    cd vasm* && \
    make CPU=m68k SYNTAX=mot && \
    cp vasmm68k_mot /opt/68000-tools/bin/ && \
    cp vobjdump /opt/68000-tools/bin/ 2>/dev/null || true && \
    rm -rf /tmp/vasm*

USER retro

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]