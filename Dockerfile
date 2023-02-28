FROM nvidia/cuda:11.8.0-cudnn8-runtime-ubuntu22.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -yq wget unzip cmake g++ libopencv-dev

RUN wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.13.1%2Bcpu.zip --directory-prefix include/

RUN unzip include/libtorch-cxx11-abi-shared-with-deps-1.13.1+cpu.zip

RUN wget https://thor.robots.ox.ac.uk/~vgg/data/pets/images.tar.gz --directory-prefix data/

RUN tar -xf data/images.tar.gz

WORKDIR /code

