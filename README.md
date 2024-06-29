# Overview

A rust project with C++ code compatible with wasm. Uses libsodium.

## Prerequisites 


1. Download and install `wasi-sdk` from the official [GitHub repository](https://github.com/WebAssembly/wasi-sdk/releases). Choose the appropriate version for your system.
2. After downloading, extract the `wasi-sdk` package and set up the environment variables:
```
export WASI_SDK_PATH=~/Downloads/wasi-sdk-22.0
export PATH=$WASI_SDK_PATH/bin:$PATH
```
3. You may also need to install `rustup`
4. Run `sh prepare-sodium.sh` to prepare `libsodium` for wasm env. You may need to install `zig` in advance.

## Build

```
cargo build --target=wasm32-wasi --release
```

## Run 

```
wasmedge --reactor target/wasm32-wasi/release/my_rust_app.wasm test
```

This should print the following:

```
[test] Hello from Rust
[hello] Hello, World from C++! (std::cout)
[hello] Hello World from C++! (printf)
The sodium is initialized!
sodium randombytes: 714298213
```
