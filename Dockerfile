# 1. Base image
FROM ubuntu:24.04

# 2. Install build deps
RUN apt-get update && apt-get install -y \
    g++ \
    libboost-all-dev \
    libnlohmann-json-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# 3. Grab Crow headers
RUN git clone https://github.com/CrowCpp/Crow.git /usr/src/crow
ENV CPLUS_INCLUDE_PATH=/usr/src/crow/include

# 4. Copy your code
WORKDIR /app
COPY . .

# 5. Compile
RUN g++ -std=c++17 main.cpp -o cpp_notes_api -pthread -lboost_system

# 6. Expose port & run
EXPOSE 18080
CMD ["./cpp_notes_api"]
