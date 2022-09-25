FROM ubuntu:22.04

RUN apt-get -y update
RUN apt-get install -y cmake ninja-build git

# Install LLVM 13
RUN apt-get -y install lsb-release wget software-properties-common pkg-config libssl-dev
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 13
RUN rm -f llvm.sh

# Python setup
RUN apt -y install python3-pip
RUN pip3 install tabulate

# ssh setup
WORKDIR /root
RUN mkdir .ssh
RUN touch known_hosts
WORKDIR /
RUN ssh-keyscan github.com >> ~/.ssh/known_hosts

# Install Rust
RUN apt-get install -y curl
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
# RUN source $HOME/.cargo/env
ARG PATH=$PATH:/root/.cargo/bin
ENV PATH=$PATH:/root/.cargo/bin
RUN rustup component add rust-src
RUN apt -y install binaryen
WORKDIR /
RUN cargo install cargo-dylint dylint-link
RUN cargo install --force cargo-contract
RUN rustup update nightly
# RUN rustup target add wasm32-unknown-unknown --toolchain nightly # NEEDED?
RUN rustup component add rust-src --toolchain nightly

# Install Solang
WORKDIR /
RUN mkdir solang
WORKDIR /solang
RUN wget https://github.com/hyperledger-labs/solang/releases/download/v0.1.10/solang-linux-arm64 -O solang
RUN chmod +x solang
ARG PATH=$PATH:/solang
ENV PATH=$PATH:/solang

# Install Typescript
RUN apt -y install curl
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.3/install.sh | bash
WORKDIR /root/.nvm
RUN ./install.sh && chmod +x nvm.sh && ./nvm.sh
RUN echo "[[ -s $HOME/.nvm/nvm.sh ]] && . $HOME/.nvm/nvm.sh" >> $HOME/.bashrc
RUN bash -i -c 'nvm install 17.8.0'
ARG PATH=$PATH:/root/.nvm/versions/node/v17.8.0/bin
ENV PATH=$PATH:/root/.nvm/versions/node/v17.8.0/bin
RUN npm install -g typescript

# Build libBlockchain
WORKDIR /
RUN git clone https://github.com/Veridise/libBlockchain.git
WORKDIR /libBlockchain
ARG LLVM_HOME=/usr/lib/llvm-13
ENV LLVM_HOME=/usr/lib/llvm-13
RUN mkdir cmake-build-debug && \
    cd cmake-build-debug && \
    cmake -GNinja ../ && \
    cmake --build .

# Set up Vanguard
WORKDIR /vanguard
COPY . .

# Fetch Preprocessors
RUN git submodule update --init

# Install Solidity preprocessor
WORKDIR /vanguard/deps/SolidityPreprocessor
RUN npm install
RUN cd src && tsc

# Build libVanguard
WORKDIR /vanguard
ARG Z3_HOME=/z3/build
ENV Z3_HOME=/z3/build
ARG LIBBLOCKCHAIN_HOME=/libBlockchain/cmake-build-debug
ENV LIBBLOCKCHAIN_HOME=/libBlockchain/cmake-build-debug
RUN rm -rf cmake-build-debug
RUN mkdir cmake-build-debug
WORKDIR /vanguard/cmake-build-debug
RUN cmake -GNinja ../
RUN cmake --build .

ARG PATH=$PATH:$LLVM_HOME/bin
ENV PATH=$PATH:$LLVM_HOME/bin
WORKDIR /vanguard

# TODO: use multistage builds to slim down the image? https://docs.docker.com/develop/develop-images/multistage-build/
