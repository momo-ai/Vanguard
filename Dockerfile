FROM ubuntu:22.04

WORKDIR /vanguard

COPY . .

RUN apt -y update

# Install LLVM 13
RUN apt -y install lsb-release wget software-properties-common pkg-config libssl-dev emacs
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 13
RUN rm -f llvm.sh

# Install Z3
WORKDIR /
RUN apt -y install git
WORKDIR /root
RUN mkdir .ssh
RUN touch known_hosts
WORKDIR /
RUN ssh-keyscan github.com >> ~/.ssh/known_hosts
RUN git clone https://github.com/Z3Prover/z3.git
WORKDIR /z3
RUN apt -y install cmake build-essential
RUN mkdir build
WORKDIR /z3/build
RUN cmake -G "Unix Makefiles" ../
RUN make -j4

# Build libBlockchain
WORKDIR /
RUN git clone https://github.com/Veridise/libBlockchain.git
WORKDIR /libBlockchain
ARG LLVM_HOME=/usr/lib/llvm-13
ENV LLVM_HOME=/usr/lib/llvm-13
RUN mkdir cmake-build-debug
WORKDIR /libBlockchain/cmake-build-debug
RUN cmake -G "Unix Makefiles" ../
RUN make

# Fetch Preprocessors
WORKDIR /vanguard
RUN git submodule update --init

# Install Typescript
WORKDIR /vanguard/deps/SolidityPreprocessor/src
RUN apt -y install curl
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.3/install.sh | bash
WORKDIR /root/.nvm
RUN ./install.sh
RUN chmod +x nvm.sh
RUN ./nvm.sh
RUN echo "[[ -s $HOME/.nvm/nvm.sh ]] && . $HOME/.nvm/nvm.sh" >> $HOME/.bashrc
WORKDIR /vanguard/deps/SolidityPreprocessor/src
RUN bash -i -c 'nvm install 17.8.0'
ARG PATH=$PATH:/root/.nvm/versions/node/v17.8.0/bin
ENV PATH=$PATH:/root/.nvm/versions/node/v17.8.0/bin
RUN npm install -g typescript
RUN npm install --save solc-typed-ast
RUN tsc

# Build libVanguard
WORKDIR /vanguard
ARG Z3_HOME=/z3/build
ENV Z3_HOME=/z3/build
ARG LIBBLOCKCHAIN_HOME=/libBlockchain/cmake-build-debug
ENV LIBBLOCKCHAIN_HOME=/libBlockchain/cmake-build-debug
RUN rm -rf cmake-build-debug
RUN mkdir cmake-build-debug
WORKDIR /vanguard/cmake-build-debug
RUN cmake -G "Unix Makefiles" ../
RUN make

# Python setup
RUN apt -y install python3-pip
RUN pip3 install tabulate

# Install Rust
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
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
RUN rustup component add rust-src --toolchain nightly-aarch64-unknown-linux-gnu

# Install Solang
WORKDIR /
RUN mkdir solang
WORKDIR /solang
RUN wget https://github.com/hyperledger-labs/solang/releases/download/v0.1.10/solang-linux-arm64 -O solang
RUN chmod +x solang
ARG PATH=$PATH:/solang
ENV PATH=$PATH:/solang
ARG PATH=$PATH:$LLVM_HOME/bin
ENV PATH=$PATH:$LLVM_HOME/bin

WORKDIR /vanguard
