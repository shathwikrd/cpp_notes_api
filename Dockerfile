FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y g++ cmake git libssl-dev

# Copy source code
WORKDIR /app
COPY . .

# Build the project
RUN cmake . && make

# Expose the port Render expects
EXPOSE 10000

# Run the app (update port if needed)
CMD ./cpp_notes_api
