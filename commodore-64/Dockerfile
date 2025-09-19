# ACME Cross-Assembler for Commodore 64
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="ACME assembler for Commodore 64 development"
LABEL version="1.0.0"
LABEL system="commodore-64"

# ACME assembler is now included in the base image
# This image just provides C64-specific configuration

USER code198x

# Set ACME as the entrypoint
ENTRYPOINT ["acme"]

# Default command shows help
CMD ["--help"]