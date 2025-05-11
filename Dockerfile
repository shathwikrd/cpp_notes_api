FROM ubuntu:24.04

# Install required packages
RUN apt update && apt install -y \
    g++ \
    cmake \
    libboost-all-dev \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Manually install nlohmann/json (header-only)
RUN curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp -o /usr/local/include/json.hpp

# Install Crow (header-only)
RUN git clone https://github.com/CrowCpp/crow.git && \
    cd crow && mkdir build && cd build && cmake .. && make && make install

# Copy your code
WORKDIR /app
COPY . .

# Build your project
RUN cmake . && make

# Expose port
EXPOSE 18080

# Run the API
CMD ["./api"]
