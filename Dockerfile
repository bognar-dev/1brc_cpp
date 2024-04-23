FROM alpine:3.14
LABEL authors="Niklas"


# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
ADD /. /app
# Install Google Benchmark
RUN apk upgrade && \
    apk add cmake && \
    apk add gdb && \
    apk add git && \
    apk add build-base && \
    git clone https://github.com/google/benchmark.git && \
    cd benchmark && \
    cmake -E make_directory "build" && \
    cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../ && \
    cmake --build "build" --config Release --target install

# Build the C++ program using CMake
RUN mkdir cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Debug -G 'CodeBlocks - Unix Makefiles' .. && make

# Run the program when the container launches
CMD ["./cmake-build-debug/1brc_cpp"]