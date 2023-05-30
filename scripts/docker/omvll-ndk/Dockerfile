FROM ubuntu:22.04
LABEL maintainer="weliveindetail <stefan.graenitz@gmail.com>"

RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
        llvm-14-tools python3-pip clang-14 libc++-14-dev libc++abi-14-dev cmake ninja-build git && \
    apt clean autoclean && apt autoremove --yes

RUN python3 -m pip install lit && \
        lit --version

RUN git config --global --add safe.directory /o-mvll

RUN apt update && DEBIAN_FRONTEND=noninteractive apt install -y --no-install-recommends \
        zlib1g-dev

RUN mkdir -p /test-deps/bin && cd /usr/lib/llvm-14/bin && cp FileCheck count not /test-deps/bin/. && cd /

# Copy in llvm-config from a local resource

# Copy in test dependencies from a local resource
# FIXME: Once we update the deps-package, these must be included
COPY llvm-config /test-deps/bin
COPY clang /test-deps/bin
RUN ln -s /test-deps/bin/clang /test-deps/bin/clang++
