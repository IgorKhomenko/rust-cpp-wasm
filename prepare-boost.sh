#rm -rf boost
git clone --recursive https://github.com/boostorg/boost.git
cd boost
./bootstrap.sh
./b2 headers # generate headers
./b2 toolset=clang --with-system --with-filesystem # build

# boost-array/precompiled/include will contain headers
# boost-array/precompiled/lib will contain binaries