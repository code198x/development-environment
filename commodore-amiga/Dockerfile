# VASM for Commodore Amiga
FROM ghcr.io/code198x/68000-base:latest

LABEL maintainer="code198x"
LABEL description="VASM assembler for Commodore Amiga development"
LABEL version="1.0.0"
LABEL system="commodore-amiga"

# VASM is now included in the base image
# This image provides Amiga-specific configuration

USER code198x

# Set vasm as the entrypoint
ENTRYPOINT ["vasmm68k_mot"]

# Default command shows help
CMD ["-help"]