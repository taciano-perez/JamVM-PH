FROM ubuntu:14.04
MAINTAINER Taciano Perez <taciano.perez@hp.com>
ENV http_proxy 'http://web-proxy.atl.hp.com:8088'
RUN apt-get update && apt-get install -y build-essential openjdk-7-jdk zlib1g-dev libffi-dev git pkg-config autoconf man-db zip
COPY src/ /src/
RUN ls -la /src/*
RUN cd /src/classpath; sh compile.sh
RUN git clone https://github.com/pmem/nvml.git; cd nvml; git checkout tags/1.1; make; sudo make install
RUN cd /src/jamvm/jamvm-1.5.4; sh compile.sh