# Mattel Intellivision Development Environment
# Based on CP1610 processor (unique 16-bit processor)
FROM ghcr.io/code198x/code198x-base:latest

LABEL maintainer="code198x"
LABEL description="Mattel Intellivision assembly development environment"
LABEL version="1.0.0"

# Note: CP1610 is a unique processor - will need custom assembler
# For now, using base image until CP1610 assembler is added

# Copy Intellivision-specific resources
COPY --chown=code198x:code198x resources/ /resources/


# Set Intellivision-specific environment
ENV SYSTEM_NAME="Mattel Intellivision"
ENV CPU_ARCH="CP1610"
ENV INTELLIVISION_INCLUDES="/resources/includes"
ENV INTELLIVISION_LIBS="/resources/libs"

WORKDIR /workspace

# Health check - basic for now
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD echo "CP1610 assembler needed" || exit 0

# Default command shows usage
CMD ["sh", "-c", "echo 'Mattel Intellivision Development Environment\\nProcessor: CP1610 (16-bit)\\nNote: CP1610 assembler integration needed'"]