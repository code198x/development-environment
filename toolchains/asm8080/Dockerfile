# ASM8080 Toolchain - Intel 8080 Assembler
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    autoconf \
    automake \
    libtool \
    && rm -rf /var/lib/apt/lists/*

RUN cd /tmp && \
    git clone --depth 1 https://github.com/begoon/asm8080.git && \
    cd asm8080 && \
    chmod +x autogen.sh && \
    ./autogen.sh && \
    ./configure --prefix=/opt/asm8080 && \
    make -j$(nproc) && \
    make install

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/asm8080 /opt/asm8080