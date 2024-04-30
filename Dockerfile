FROM debian:stable-slim
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        g++-multilib \
        gcc-multilib \
        git \
        libc6-dev \
        libc6-dev-i386 \
        make \
        unzip \
        wget \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install movfuscator
RUN wget https://github.com/xoreaxeaxeax/movfuscator/archive/master.zip \
    && unzip master.zip \
    && cd movfuscator-master \
    && ./build.sh \
    && ./install.sh \
    && cd .. \
    && rm -f master.zip

ENV DEBIAN_FRONTEND=dialog
WORKDIR /

