FROM nvidia/cuda:11.8.0-cudnn8-runtime-ubuntu22.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -yq cmake g++ libopencv-dev

WORKDIR /code

