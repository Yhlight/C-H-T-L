# Build stage
FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /build

# Copy source code
COPY . .

# Build CHTL
RUN cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build

# Runtime stage
FROM ubuntu:22.04

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Copy built binary and modules
COPY --from=builder /build/build/chtl /usr/local/bin/chtl
COPY --from=builder /build/modules /usr/local/share/chtl/modules

# Set module path environment variable
ENV CHTL_MODULE_PATH=/usr/local/share/chtl/modules

# Create working directory
WORKDIR /workspace

# Set entrypoint
ENTRYPOINT ["chtl"]