FROM mrkloan/alpine-gcc:latest
MAINTAINER Valentin Fries <contact@fries.io>

COPY . /src

RUN cd /src &&\
    make

ENTRYPOINT ["/src/bin/htcpcp", "-a", "127.0.0.1", "-p", "8080"]