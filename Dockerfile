## Build environment Dockerfile
#> docker build -t mruby-coap-builder .
#> docker run --rm -v ${pwd}:/workspace mruby-coap-builder ruby run_test.rb test
FROM alpine:latest
RUN apk update &&\
    apk add gcc libc-dev git ruby bison libcoap-dev &&\
    rm -rf /var/cache/apk/*
WORKDIR /workspace
