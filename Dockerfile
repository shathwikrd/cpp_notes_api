# Use official C++ image
FROM gcc:13

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    git \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Set workdir
WORKDIR /app

# Copy files
COPY . .

# Install crow and nlohmann/json headers
RUN mkdir -p /usr/local/include/crow && \
    wget https://raw.githubusercontent.com/CrowCpp/crow/master/include/crow.h -O /usr/local/include/crow/crow.h && \
    wget https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp -O /usr/local/include/nlohmann/json.hpp


# Build
RUN cmake . && make

# Expose port
EXPOSE 18080

# Run the app
CMD ["./crow_api"]
