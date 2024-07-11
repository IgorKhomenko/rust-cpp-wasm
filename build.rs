// The wasi-sdk does not include libstdc++ or libc++ by default. 
// Instead, it provides the necessary environment for compiling C/C++ code to WebAssembly. 
// We need to ensure that we are correctly configuring the build to use the C++ standard library available in wasi-sdk.
//
//  The cargo:rustc-link-lib=static=c++ and cargo:rustc-link-lib=static=c++abi lines 
// ensure that the static versions of the C++ standard library and C++ ABI library are linked.

use std::env;
use std::path::PathBuf;

fn main() {
    let target = env::var("TARGET").unwrap();

    let mut build = cc::Build::new();
    // build.cpp(true) // this will cause rust-lld: error: unable to find library -lstdc++
    build.file("cpp/my_code.cpp");

    if target.contains("wasm32") {
        let wasi_sdk_path = env::var("WASI_SDK_PATH").expect("WASI_SDK_PATH not set");
        let sysroot = PathBuf::from(&wasi_sdk_path).join("share/wasi-sysroot");
        let include_path = sysroot.join("include");
        let lib_path = sysroot.join("lib/wasm32-wasi");

        // -I (specifies the directories where headers are located)
        build.include(include_path);
        build.include("libsodium/zig-out/include");
        build.include("openssl-wasm/precompiled/include");
        build.include("boost");
        
        build.flag("--sysroot");
        build.flag(sysroot.to_str().unwrap());
        build.flag("-fno-exceptions"); // By adding the -fno-exceptions flag to the cc::Build configuration, you ensure that the C++ code is compiled without exception support, preventing the linker errors related to __cxa_allocate_exception. More info https://github.com/WebAssembly/wasi-sdk?tab=readme-ov-file#notable-limitations

        // -L (specifies the directories where the libraries are located)
        println!("cargo:rustc-link-search=native={}", lib_path.display());
        println!("cargo:rustc-link-search=native={}", "libsodium/zig-out/lib");
        println!("cargo:rustc-link-search=native={}", "openssl-wasm/precompiled/lib");

        // -l (link the libraries)
        println!("cargo:rustc-link-lib=static=c++");
        println!("cargo:rustc-link-lib=static=c++abi");
        println!("cargo:rustc-link-lib=static=sodium"); // Use the static version of libsodium
        println!("cargo:rustc-link-lib=static=ssl"); // Use the static version of ssl
        println!("cargo:rustc-link-lib=static=crypto"); // Use the static version of crypto
    }

    build.compile("my_code");

    println!("cargo:rerun-if-changed=cpp/my_code.cpp");
}

// ~/Downloads/wabt-1.0.35/bin/wasm-objdump -x target/wasm32-wasi/release/my_rust_app.wasm | grep sodium_init
