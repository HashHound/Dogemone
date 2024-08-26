[![Build](https://github.com/HashHound/Dogemone/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/HashHound/Dogemone/actions/workflows/cmake-multi-platform.yml)
[![Build and Release](https://github.com/HashHound/Dogemone/actions/workflows/buildandrelease.yml/badge.svg)](https://github.com/HashHound/Dogemone/actions/workflows/buildandrelease.yml)


## **Dogemone: The Future of Privacy Coins**

Dogemone is a cutting-edge privacy coin built on the robust Cryptonote protocol, ensuring unparalleled transaction confidentiality and security. With a maximum supply of ~300 million, Dogemone follows a meticulously designed emission curve, providing a predictable and fair distribution over time. The coin leverages the Cryptonight algorithm, known for its Eagleatarian mining capability, promoting decentralization. Dogemone is committed to protecting your financial privacy while maintaining a secure and decentralized network, making it a standout choice in the realm of cryptocurrency. Join us in shaping a future where privacy and security are paramount.

### **Key Features:**
- **Privacy-Focused**: Utilizes Cryptonote protocol for untraceable and unlinkable transactions.
- **Controlled Supply**: Initial Supply is Capped at ~300 million coins with a fair fixed block reward of 57 coins. There is also a tail emission after the initial supply which is 0.3 coins per Block.
- **Efficient Mining**: Cryptonight algorithm ensures equitable mining opportunities.
- **No Premine**: 100% fair launch with no premine.
- **Developer Fee**: 10% of the block reward is allocated to development, taken slowly over time.
- **Difficulty Adjustment**: Adaptive difficulty adjustment every 60 seconds for network stability.
- **Decentralized Network**: Promotes decentralization and security.

Embrace the future of privacy with Dogemone.

## Building Dogemone

### On *nix

Dependencies: GCC 4.7.3 or later, CMake 2.8.6 or later, and Boost 1.55 or later, OpenSSL.

You may download them from:

- https://gcc.gnu.org/
- https://www.cmake.org/
- https://www.boost.org/
- https://www.openssl.org/

Alternatively, it may be possible to install them using a package manager.

To build, change to a directory where this file is located, and run `make`.

or

Run these commands:
```
cd ~
sudo apt-get install build-essential git cmake libboost-all-dev libssl-dev
git clone https://github.com/HashHound/Dogemone.git
cd dogemone
mkdir build
cd build
cmake ..
cd ..
make
```

The resulting executables can be found in `build/release/src`.

**Advanced options:**

* Parallel build: run `make -j<number of threads>` instead of `make`.
* Debug build: run `make build-debug`.
* Test suite: run `make test-release` to run tests in addition to building. Running `make test-debug` will do the same to the debug version.
* Building with Clang: it may be possible to use Clang instead of GCC, but this may not work everywhere. To build, run `export CC=clang CXX=clang++` before running `make`.

### On Windows

# Building Dogemone with MinGW64 on Windows

## Prerequisites

1. **MinGW-w64**: Download and install MinGW-w64 from the official source or use a package manager like MSYS2.
   - [MinGW-w64](https://www.mingw-w64.org/)
   - [MSYS2](https://www.msys2.org/)

2. **CMake**: Install CMake, which is required for configuring the build.
   - [CMake Download](https://cmake.org/download/)

3. **Git**: Install Git to clone the repository.
   - [Git Download](https://git-scm.com/downloads)

4. **Dependencies**: Ensure all necessary dependencies are installed and available for MinGW-w64. Dependencies typically include:
   - Boost
   - OpenSSL
   - Zlib

## Instructions

### 1. Install MSYS2

- Download MSYS2 from [MSYS2's official website](https://www.msys2.org/).
- Follow the installation instructions to install MSYS2 on your Windows machine.
- Once installed, open the MSYS2 MSYS terminal from the Start menu.

### 2. Install MinGW-w64 Toolchain

- Update the package database and install MinGW-w64 toolchain by running the following commands in the MSYS2 terminal:

  ```
  pacman -Syu
  pacman -S mingw-w64-x86_64-toolchain
  pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-git mingw-w64-x86_64-boost mingw-w64-x86_64-openssl mingw-w64-x86_64-zlib
  git clone https://github.com/HashHound/Dogemone.git
  cd Dogemone
  mkdir build
  cd build
  cmake -G "MinGW Makefiles" ..
  mingw32-make
  ```

### Building for macOS

Dependencies: cmake boost and Xcode

Download Xcode from the App store and the Xcode command line tools with `xcode-select --install`
For the other we recommand you to use [Homebrew](https://brew.sh)

Continue with:
```
brew install git cmake boost
git clone https://github.com/HashHound/Dogemone.git
cd Dogemone
cd build
cmake ..
make
```


### Building for Android on Linux

Set up the 32 bit toolchain
Download and extract the Android SDK and NDK
```
android-ndk-r15c/build/tools/make_standalone_toolchain.py --api 21 --stl=libc++ --arch arm --install-dir /opt/android/tool32
```

Download and setup the Boost 1.65.1 source
```
wget https://sourceforge.net/projects/boost/files/boost/1.65.1/boost_1_65_1.tar.bz2/download -O boost_1_65_1.tar.bz2
tar xjf boost_1_65_1.tar.bz2
cd boost_1_65_1
./bootstrap.sh
```
apply patch from external/boost1_65_1/libs/filesystem/src

Build Boost with the 32 bit toolchain
```
export PATH=/opt/android/tool32/arm-linux-androideabi/bin:/opt/android/tool32/bin:$PATH
./b2 abi=aapcs architecture=arm binary-format=elf address-model=32 link=static runtime-link=static --with-chrono --with-date_time --with-filesystem --with-program_options --with-regex --with-serialization --with-system --with-thread --with-context --with-coroutine --with-atomic --build-dir=android32 --stagedir=android32 toolset=clang threading=multi threadapi=pthread target-os=android --reconfigure stage
```

Build Dogemone for 32 bit Android
```
mkdir -p build/release.android32
cd build/release.android32
CC=clang CXX=clang++ cmake -D BUILD_TESTS=OFF -D ARCH="armv7-a" -ldl -D STATIC=ON -D BUILD_64=OFF -D CMAKE_BUILD_TYPE=release -D ANDROID=true -D BUILD_TAG="android" -D BOOST_ROOT=/opt/android/boost_1_65_1 -D BOOST_LIBRARYDIR=/opt/android/boost_1_65_1/android32/lib -D CMAKE_POSITION_INDEPENDENT_CODE:BOOL=true -D BOOST_IGNORE_SYSTEM_PATHS_DEFAULT=ON ../..
make SimpleWallet
```

### Portable and optimized binaries

By default it will compile portable binary, to build optimized for your CPU, run Cmake with flag `-DARCH=native`.

### Socials and Website

Website: https://dogemone.online/

Block Explorer: https://explorer.dogemone.online/

Twitter: https://x.com/ProjectDogemone

Discord: https://discord.com/invite/FMdRT4rjhF
