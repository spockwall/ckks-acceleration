CKKS-Acceleration Research Fork
=====================================

**This is a research fork for CKKS acceleration experiments.**

This repository is a simplified, CKKS-only version of OpenFHE, focused on performance optimization and acceleration research for the **CKKS (Cheon-Kim-Kim-Song)** homomorphic encryption scheme.

## About This Fork

- **Purpose**: Research and development of CKKS acceleration techniques
- **Base**: OpenFHE v1.4.2 (CKKS-only build)
- **Focus**: Performance optimization, hardware acceleration, and algorithmic improvements
- **Removed**: BFV, BGV, BinFHE schemes to simplify the codebase for CKKS-specific research

## CKKS Features Included

* Approximate arithmetic over encrypted real/complex numbers
* Homomorphic operations: addition, multiplication, rotation
* Advanced bootstrapping capabilities (simple, iterative, composite scaling)
* Multiparty extensions (Threshold FHE, Interactive bootstrapping, Proxy Re-Encryption)

## Requirements

- **Compiler**: GCC 9+ or Clang 10+
- **CMake**: 3.16.3 or higher
- **OS**: Linux, macOS, or Windows
- **OpenMP**: Recommended for parallelization (optional)

## Quick Start: Build, Run Examples, and Tests

### 1. Build the Library

**Quick build (using Makefile - recommended):**
```bash
make              # Automatically detects OS and builds with optimal settings
make info         # Show available build targets
```

**Alternative: Manual CMake build:**
```bash
mkdir build
cd build
cmake .. -DBUILD_UNITTESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_BENCHMARKS=OFF
make -j$(nproc)  # Linux
make -j$(sysctl -n hw.ncpu)  # macOS
```

**Other Makefile targets:**
```bash
make clean        # Remove build directory
make rebuild      # Clean and rebuild from scratch
make examples     # Build with CKKS examples
make install      # Install libraries system-wide
```

**Build options you can customize:**
- `-DCMAKE_BUILD_TYPE=Release|Debug` - Build type (Release for performance)
- `-DCKKS_M_FACTOR=1` - CKKS multiplication depth factor (default: 1, increase for deeper circuits)
- `-DWITH_NATIVEOPT=ON` - Enable CPU-specific optimizations (`-march=native`)
- `-DWITH_OPENMP=ON|OFF` - Enable/disable OpenMP parallelization
- `-DMATHBACKEND=4` - Math backend (2, 4, or 6)
- `-DNATIVE_SIZE=64` - Native integer size (32, 64, or 128)
- `-DBUILD_SHARED=ON` - Build shared libraries
- `-DBUILD_STATIC=ON` - Build static libraries
- `-DBUILD_EXAMPLES=ON|OFF` - Build example programs
- `-DBUILD_UNITTESTS=ON|OFF` - Build unit tests

### 2. Run Examples

After building, examples are located in `build/bin/examples/`:

```bash
# Run a simple CKKS example
./build/bin/examples/pke/simple-real-numbers

# Run CKKS bootstrapping example
./build/bin/examples/pke/simple-ckks-bootstrapping

# Run advanced real numbers example
./build/bin/examples/pke/advanced-real-numbers

# List all available examples
ls build/bin/examples/pke/
```

### 3. Run Unit Tests

```bash
# Run all unit tests
cd build
make testall

# Or run specific test suites
./unittest/core_tests    # Core functionality tests
./unittest/pke_tests     # PKE/CKKS scheme tests
```

### 4. Install (Optional)

To install the library system-wide:
```bash
cd build
sudo make install  # Installs to /usr/local by default
```

Or install to a custom location:
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/your/custom/path
make install
```

## Upstream Resources

 * [OpenFHE documentation](https://openfhe-development.readthedocs.io/en/latest/)
 * [Design paper for OpenFHE](https://eprint.iacr.org/2022/915)
 * [OpenFHE website](https://openfhe.org)
 * [BSD 2-Clause License](LICENSE)

## Project Architecture

### Directory Structure

```
ckks-acceleration/
├── src/
│   ├── core/              # Core math and lattice operations
│   │   ├── include/       # Public headers (math backends, lattices, utilities)
│   │   └── lib/           # Implementation files
│   └── pke/               # Public Key Encryption (CKKS scheme)
│       ├── include/       # CKKS headers
│       │   ├── scheme/ckksrns/     # CKKS-RNS implementation
│       │   ├── schemebase/         # Base classes for all schemes
│       │   └── keyswitch/          # Key switching techniques
│       ├── lib/           # CKKS implementation
│       ├── examples/      # CKKS usage examples
│       └── unittest/      # Unit tests (disabled in this build)
├── third-party/           # External dependencies
│   ├── cereal/           # Serialization library
│   ├── google-test/      # Testing framework
│   └── google-benchmark/ # Benchmarking framework
├── build/                 # Build output directory (created by CMake)
│   └── lib/              # Compiled libraries (libOPENFHEcore, libOPENFHEpke)
└── CMakeLists.txt        # Main build configuration
```

### Key Components

#### 1. **Core Library (`src/core/`)**
Provides fundamental mathematical operations for FHE:
- **Math backends**: Multiple precision integer arithmetic (MATHBACKEND 2, 4, or 6)
- **Lattice operations**: Polynomial rings, NTT/FFT operations
- **Utilities**: Random number generation, serialization, exception handling
- **Configuration**: Build-time configuration via `config_core.h`

#### 2. **PKE/CKKS Library (`src/pke/`)**
Implements the CKKS homomorphic encryption scheme:
- **CKKS-RNS implementation** (`scheme/ckksrns/`):
  - Parameter generation
  - Encryption/Decryption
  - Homomorphic operations (Add, Mult, Rotate, Bootstrap)
  - Advanced operations (polynomial evaluation, Chebyshev/Hermite series)
- **Key management** (`key/`): Public/private keys, evaluation keys, rotation keys
- **Key switching** (`keyswitch/`): Hybrid, BV, and RNS key switching techniques
- **Base classes** (`schemebase/`): Abstract interfaces for PKE, SHE, FHE features

#### 3. **Removed Components (CKKS-Only Build)**
The following were removed from the original OpenFHE to simplify this research fork:
- **BFV/BGV schemes**: Integer-based FHE schemes
- **BinFHE/FHEW**: Boolean circuit FHE schemes
- **Scheme switching**: CKKS ↔ FHEW conversion (commented out in `base-fhe.h`, `base-scheme.h`, `cryptocontext.h`)

### How It Works

#### Build System (CMake)
1. **Configuration** (`CMakeLists.txt`):
   - Detects platform (macOS/Linux/Windows)
   - Configures compiler flags and optimization levels
   - Sets CKKS parameters (CKKS_M_FACTOR, MATHBACKEND, NATIVE_SIZE)
   - Generates `config_core.h` from `configure/config_core.in`

2. **Compilation**:
   - Builds `libOPENFHEcore.dylib` (core math library)
   - Builds `libOPENFHEpke.dylib` (CKKS library, depends on core)

3. **Key Build Options**:
   - `CKKS_M_FACTOR`: Multiplication depth scaling factor (default: 1)
   - `MATHBACKEND`: Integer backend (2=NTL, 4=native, 6=NTL+GMP)
   - `NATIVE_SIZE`: Native integer width (64 or 128 bits)
   - `WITH_OPENMP`: Enable parallel computation
   - `WITH_NATIVEOPT`: Enable `-march=native` CPU optimizations

#### CKKS Workflow

```
1. Parameter Generation (ckksrns-parametergeneration.cpp)
   └─> Set ring dimension, modulus chain, scaling factor

2. Key Generation (ckksrns-pke.cpp)
   └─> Generate public/private key pair

3. Encoding (encoding/encodings.cpp)
   └─> Encode real/complex numbers into plaintext polynomials

4. Encryption (ckksrns-pke.cpp)
   └─> Encrypt plaintext → ciphertext

5. Homomorphic Operations (ckksrns-leveledshe.cpp, ckksrns-advancedshe.cpp)
   ├─> EvalAdd: Addition
   ├─> EvalMult: Multiplication (with rescaling)
   ├─> EvalRotate: Slot rotation
   └─> EvalBootstrap: Refresh ciphertext (ckksrns-fhe.cpp)

6. Decryption (ckksrns-pke.cpp)
   └─> Decrypt ciphertext → plaintext

7. Decoding (encoding/encodings.cpp)
   └─> Decode plaintext polynomial → real/complex numbers
```

#### Important Files for Research

- **CKKS multiplication**: `src/pke/lib/scheme/ckksrns/ckksrns-leveledshe.cpp`
- **Bootstrapping**: `src/pke/lib/scheme/ckksrns/ckksrns-fhe.cpp`
- **NTT operations**: `src/core/lib/lattice/hal/default/lat-backend-default.cpp`
- **Parameter generation**: `src/pke/lib/scheme/ckksrns/ckksrns-parametergeneration.cpp`
- **CKKS encoding**: `src/pke/lib/encoding/encodings.cpp`

### Acceleration Opportunities

For CKKS acceleration research, focus on:
1. **NTT/FFT operations** (most computational cost)
2. **Modular arithmetic** (large integer operations)
3. **Key switching** (automorphism, relinearization)
4. **Bootstrapping** (homomorphic decoding/encoding)
5. **Parallelization** (slot-level, operation-level)

## CKKS Code Examples

Example source files are in `src/pke/examples/`. After building, executables are in `build/bin/examples/pke/`.

### 1. Basic CKKS Examples
- [Simple Real Numbers](src/pke/examples/simple-real-numbers.cpp) - Introduction to CKKS
- [Simple Real Numbers with Serialization](src/pke/examples/simple-real-numbers-serial.cpp)
- [Advanced Real Numbers](src/pke/examples/advanced-real-numbers.cpp)
- [High-Precision CKKS (128-bit)](src/pke/examples/advanced-real-numbers-128.cpp)
- [Simple Complex Numbers](src/pke/examples/simple-complex-numbers.cpp)

### 2. Bootstrapping Examples
- [Simple CKKS Bootstrapping](src/pke/examples/simple-ckks-bootstrapping.cpp)
- [Advanced CKKS Bootstrapping](src/pke/examples/advanced-ckks-bootstrapping.cpp)
- [Iterative Bootstrapping](src/pke/examples/iterative-ckks-bootstrapping.cpp)
- [Composite Scaling Bootstrapping](src/pke/examples/simple-ckks-bootstrapping-composite-scaling.cpp)

### 3. Advanced Operations
- [Function Evaluation](src/pke/examples/function-evaluation.cpp)
- [Functional Bootstrapping for CKKS](src/pke/examples/functional-bootstrapping-ckks.cpp)
- [Inner Product Operations](src/pke/examples/inner-product.cpp)
- [CKKS Noise Flooding](src/pke/examples/ckks-noise-flooding.cpp)

### 4. Threshold/Multiparty FHE
- [Threshold FHE for CKKS](src/pke/examples/threshold-fhe.cpp)
- [Interactive Bootstrapping (2-party)](src/pke/examples/interactive-bootstrapping.cpp)
- [Multiparty Interactive Bootstrapping](src/pke/examples/tckks-interactive-mp-bootstrapping.cpp)
- [Proxy Re-Encryption](src/pke/examples/pre-buffer.cpp)

## API Documentation

- [PKE CryptoContext API (CKKS)](https://openfhe-development.readthedocs.io/en/latest/api/classlbcrypto_1_1CryptoContextImpl.html)
- [CryptoContext Parameters for CKKS](https://github.com/openfheorg/openfhe-development/blob/main/src/pke/examples#description-of-the-cryptocontext-parameters-and-their-restrictions)

## How to Cite OpenFHE

To cite OpenFHE in academic papers, please use the following BibTeX entry (updated version)

```
@misc{OpenFHE,
      author = {Ahmad Al Badawi and Andreea Alexandru and Jack Bates and Flavio Bergamaschi and David Bruce Cousins and Saroja Erabelli and Nicholas Genise and Shai Halevi and Hamish Hunt and Andrey Kim and Yongwoo Lee and Zeyu Liu and Daniele Micciancio and Carlo Pascoe and Yuriy Polyakov and Ian Quah and Saraswathy R.V. and Kurt Rohloff and Jonathan Saylor and Dmitriy Suponitsky and Matthew Triplett and Vinod Vaikuntanathan and Vincent Zucca},
      title = {{OpenFHE}: Open-Source Fully Homomorphic Encryption Library},
      howpublished = {Cryptology ePrint Archive, Paper 2022/915},
      year = {2022},
      note = {\url{https://eprint.iacr.org/2022/915}},
      url = {https://eprint.iacr.org/2022/915}
}
```
or, alternatively (original WAHC@CCS'22 version),
```
@inproceedings{10.1145/3560827.3563379,
      author = {Al Badawi, Ahmad and Bates, Jack and Bergamaschi, Flavio and Cousins, David Bruce and Erabelli, Saroja and Genise, Nicholas and Halevi, Shai and Hunt, Hamish and Kim, Andrey and Lee, Yongwoo and Liu, Zeyu and Micciancio, Daniele and Quah, Ian and Polyakov, Yuriy and R.V., Saraswathy and Rohloff, Kurt and Saylor, Jonathan and Suponitsky, Dmitriy and Triplett, Matthew and Vaikuntanathan, Vinod and Zucca, Vincent},
      title = {OpenFHE: Open-Source Fully Homomorphic Encryption Library},
      year = {2022},
      publisher = {Association for Computing Machinery},
      address = {New York, NY, USA},
      url = {https://doi.org/10.1145/3560827.3563379},
      doi = {10.1145/3560827.3563379},
      booktitle = {Proceedings of the 10th Workshop on Encrypted Computing \& Applied Homomorphic Cryptography},
      pages = {53-63},
      numpages = {11},
      location = {Los Angeles, CA, USA},
      series = {WAHC'22}
}
```

## Acknowledgments ##

Distribution Statement "A" (Approved for Public Release, Distribution Unlimited). This work is supported in part by DARPA through HR0011-21-9-0003 and HR0011-20-9-0102. The views, opinions, and/or findings expressed are those of the author(s) and should not be interpreted as representing the official views or policies of the Department of Defense or the U.S. Government.
