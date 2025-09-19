# SjASMPlus for ZX Spectrum
FROM ghcr.io/code198x/z80-base:latest

LABEL maintainer="code198x"
LABEL description="SjASMPlus assembler for ZX Spectrum development"
LABEL version="1.0.0"
LABEL system="sinclair-zx-spectrum"

# sjasmplus is now included in the base image
# This image provides ZX Spectrum specific configuration

USER code198x

# Set sjasmplus as the entrypoint
ENTRYPOINT ["sjasmplus"]

# Default command shows help
CMD ["--help"]