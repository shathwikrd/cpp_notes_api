# Use Ubuntu 24.04 base image
FROM ubuntu:24.04

# Disable interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt update && apt install -y \
    g++ \
    cmake \
    git \
    curl \
    wget \
    unzip \
    pkg-config \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory inside container
WORKDIR /app

# Copy everything to container
COPY . .

# Build the project using CMake
RUN cmake -Bbuild -H. && cmake --build build

# Expose the port your app runs on
EXPOSE 18080

# Start the app
CMD ["./build/cpp_notes_api"]
