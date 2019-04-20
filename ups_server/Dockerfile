FROM ubuntu:18.04
RUN apt-get update && apt-get install -y build-essential libpqxx-dev libtbb-dev
RUN mkdir /ups_server
WORKDIR /ups_server
ADD . /ups_server/
