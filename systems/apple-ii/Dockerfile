# Apple II - 6502-based personal computer
FROM ghcr.io/code198x/6502-base:latest

LABEL maintainer="code198x"
LABEL description="cc65 assembler for Apple II development"
LABEL version="1.0.0"
LABEL system="apple-ii"
LABEL year="1977"
LABEL cpu="6502"

# cc65 is included in base image, this adds Apple II specific config
USER code198x

# Set ca65 as the entrypoint for Apple II development
ENTRYPOINT ["ca65"]

# Default command shows version
CMD ["--version"]

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ca65 --version > /dev/null