FROM --platform=$BUILDPLATFORM alpine:latest

WORKDIR /home

RUN apk add build-base clang texlive-binextra

COPY src src

RUN cd src && make complete && cd .. \
    && mkdir pdf && cp src/*.pdf pdf/ \
    && mkdir c && cp src/*.h src/*.c c/ \
    && rm -rf src