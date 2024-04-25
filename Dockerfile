FROM alpine:3.14
LABEL authors="Niklas" name="benchmark"

# Install Google Benchmark
RUN apk upgrade && \
    apk add cmake && \
    apk add gdb && \
    apk add git && \
    apk add build-base && \
    apk add linux-headers && \
    git clone https://github.com/google/benchmark.git && \
    cd benchmark && \
    cmake -E make_directory "build" && \
    cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../ && \
    cmake --build "build" --config Release --target install

COPY . /project

# define working directory from container
WORKDIR /build

# compile with CMake
RUN cmake ../project && cmake --build .

# run executable (name has to match with CMakeLists.txt file)
CMD [ "/bin/sh", "/project/benchmark.sh" ]