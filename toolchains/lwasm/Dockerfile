# LWASM Toolchain - 6809 Assembler
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    && rm -rf /var/lib/apt/lists/*

# Build from GitHub repository as lwtools.ca is unreliable
# Use -fcommon to fix multiple definition errors with modern GCC
RUN cd /tmp && \
    git clone --depth 1 https://github.com/jmatzen/LWTools.git && \
    cd LWTools && \
    make CFLAGS="-O2 -fcommon" && \
    mkdir -p /opt/lwasm/bin && \
    cp lwasm/lwasm lwlink/lwlink lwar/lwar lwlink/lwobjdump /opt/lwasm/bin/ || true

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/lwasm /opt/lwasm