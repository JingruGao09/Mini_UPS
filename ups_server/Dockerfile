FROM ubuntu:18.04
RUN apt-get update && apt-get install -y build-essential libpqxx-dev libtbb-dev
RUN apt-get update
RUN apt-get install sudo
RUN apt-get update \
&& apt-get install -y \
autoconf \
automake \
libtool \
curl \
make \
g++ \
unzip \
&& apt-get clean
ADD ./protobuf-3.7.1.zip /protobuf-3.7.1.zip
RUN unzip protobuf-3.7.1.zip
WORKDIR /protobuf-3.7.1

RUN ./configure --prefix=/usr
RUN make
RUN make check
RUN make install
RUN ldconfig


RUN mkdir /ups_server
WORKDIR /ups_server
ADD . /ups_server/
