FROM        debian:stable-slim
LABEL       PROJECT="Task1" \
            VERSION="1.0"   \
            AUTHOR="suyuti"
MAINTAINER  suyuti "mehmet.dindar@gmail.com"

WORKDIR     /tmp
RUN         apt update

RUN         apt -y install libapr1 libapr1-dev
RUN         apt -y --no-install-recommends install \
            build-essential \
            cmake \
            gdb \
            wget \
            clang \
            libgtest-dev 

WORKDIR     /src
COPY        /src/CMakeLists.txt /src/main.cpp ./

