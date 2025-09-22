# Binutils-SH Toolchain - SuperH Cross-Compiler Tools
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    texinfo \
    && rm -rf /var/lib/apt/lists/*

# Build binutils for SuperH targets (SH-2, SH-4)
ARG BINUTILS_VERSION=2.42
RUN cd /tmp && \
    wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz && \
    tar -xzf binutils-${BINUTILS_VERSION}.tar.gz && \
    cd binutils-${BINUTILS_VERSION} && \
    mkdir build && cd build && \
    ../configure \
        --prefix=/opt/binutils-sh \
        --target=sh-elf \
        --disable-nls \
        --disable-werror \
        --with-sysroot && \
    make -j$(nproc) && \
    make install && \
    cd / && rm -rf /tmp/binutils-*

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/binutils-sh /opt/binutils-sh