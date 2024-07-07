rm -rf openssl-wasm
git clone git@github.com:jedisct1/openssl-wasm.git --recursive
cd openssl-wasm
./patch.sh
./build.sh

# openssl-wasm/precompiled/include will contain headers
# openssl-wasm/precompiled/lib will contain binaries