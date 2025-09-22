# ASL Toolchain - Alfred Arnold's Macro Assembler
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Build ASL assembler - use a working template and override arch-specific flags
RUN cd /tmp && \
    wget -q http://john.ccac.rwth-aachen.de:8000/ftp/as/source/c_version/asl-current.tar.gz && \
    tar -xzf asl-current.tar.gz && \
    cd asl-* && \
    cp Makefile.def-samples/Makefile.def-unknown-linux Makefile.def && \
    sed -i 's|-march=[^ ]*||g' Makefile.def && \
    sed -i 's|-mtune=[^ ]*||g' Makefile.def && \
    sed -i 's|BINDIR = /usr/local/bin|BINDIR = /opt/asl/bin|' Makefile.def && \
    sed -i 's|INCDIR = /usr/local/include/asl|INCDIR = /opt/asl/include|' Makefile.def && \
    sed -i 's|MANDIR = /usr/local/man|MANDIR = /opt/asl/man|' Makefile.def && \
    sed -i 's|DOCDIR = /usr/local/doc/asl|DOCDIR = /opt/asl/doc|' Makefile.def && \
    make -j$(nproc) binaries && \
    mkdir -p /opt/asl/bin /opt/asl/include && \
    cp asl p2hex p2bin pbind plist alink /opt/asl/bin/ && \
    cp *.msg /opt/asl/include/ 2>/dev/null || true

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/asl /opt/asl