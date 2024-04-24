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
    apk add build-base


RUN --mount=type=cache,target=/benchmark \
        git clone https://github.com/google/benchmark.git && \
        cd benchmark && \
        cmake -E make_directory "build" && \
        cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../ && \
        cmake --build "build" --config Release --target install


# Build the C++ program using CMake
RUN mkdir "cmake-build-debug-wsl" && cd cmake-build-debug-wsl && cmake -DCMAKE_BUILD_TYPE=Debug -G 'CodeBlocks - Unix Makefiles' -S . -B .

RUN cmake -B /cmake-build-debug-wsl --target 1_BRC_Benchmark -- -j 6

# Run the program when the container launches
# CMD ["./cmake-build-debug/1brc_cpp"]