# FASMARM Toolchain - ARM Assembler (FASM for ARM)
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    git \
    && rm -rf /var/lib/apt/lists/*

# Download and install FASMARM
RUN cd /tmp && \
    git clone --depth 1 https://github.com/jacobly0/fasmarm.git && \
    cd fasmarm && \
    mkdir -p /opt/fasmarm/bin /opt/fasmarm/include && \
    # Copy the pre-built binary
    cp fasmarm /opt/fasmarm/bin/ && \
    # Copy includes
    if [ -d "include" ]; then \
        cp -r include/* /opt/fasmarm/include/; \
    fi && \
    # Copy documentation
    mkdir -p /opt/fasmarm/doc && \
    cp *.txt /opt/fasmarm/doc/ 2>/dev/null || true

# Final stage - minimal runtime
FROM scratch AS runtime
COPY --from=builder /opt/fasmarm /opt/fasmarm