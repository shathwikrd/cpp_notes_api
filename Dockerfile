FROM ubuntu:24.04

# Install dependencies
RUN apt update && apt install -y \
    g++ \
    cmake \
    git \
    libboost-all-dev \
    nlohmann-json3-dev

# Create app directory
WORKDIR /app

# Copy everything into container
COPY . .

# Create a build directory
RUN mkdir build

# Run cmake inside the build directory
WORKDIR /app/build
RUN cmake .. && make

# Expose the port used by your app
EXPOSE 18080

# Run the compiled binary
CMD ["./cpp_notes_api"]
