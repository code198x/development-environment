# ACME Cross-Assembler for Commodore 64
FROM code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore 64 development"
LABEL version="1.0.0"
LABEL system="commodore-64"

USER root

# Build ACME from source
RUN git clone https://github.com/meonwax/acme.git /tmp/acme && \
    cd /tmp/acme/src && \
    make && \
    cp acme /opt/6502-tools/bin/ && \
    rm -rf /tmp/acme

USER retro

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]