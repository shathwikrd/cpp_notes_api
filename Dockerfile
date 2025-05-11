FROM gcc:12

# Install CMake and other tools
RUN apt-get update && \
    apt-get install -y cmake git wget && \
    apt-get clean

# Copy project
WORKDIR /app
COPY . .

# Build
RUN cmake . && make

# Expose port and run
EXPOSE 18080
CMD ["./crow_api"]
