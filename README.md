OpenFHE-CKKS - CKKS-Only Build of OpenFHE Library
=====================================

**This is a simplified, CKKS-only version of OpenFHE.**

Fully Homomorphic Encryption (FHE) is a powerful cryptographic primitive that enables performing computations over encrypted data without having access to the secret key.

This build includes only the **CKKS (Cheon-Kim-Kim-Song) scheme** for real and complex number arithmetic, featuring:
  * Approximate arithmetic over encrypted real/complex numbers
  * Homomorphic operations: addition, multiplication, rotation
  * Advanced bootstrapping capabilities (simple, iterative, composite scaling)
  * Multiparty extensions:
    - Threshold FHE for CKKS
    - Interactive bootstrapping for Threshold CKKS
    - Proxy Re-Encryption for CKKS

**Removed schemes:** BFV (integer), BGV (integer), BinFHE/FHEW/TFHE (boolean circuits), and scheme-switching capabilities have been removed to simplify the codebase.

OpenFHE supports any GNU C++ compiler version 9 or above and clang C++ compiler version 10 or above. To achieve the best runtime performance, we recommend following the
guidelines outlined in [building OpenFHE for best performance](https://github.com/openfheorg/openfhe-development/blob/main/docs/static_docs/Best_Performance.md).

## Links and Resources

 * [OpenFHE documentation](https://openfhe-development.readthedocs.io/en/latest/)
 * [Design paper for OpenFHE](https://eprint.iacr.org/2022/915)
 * [OpenFHE website](https://openfhe.org)
 * [Community forum for OpenFHE](https://openfhe.discourse.group/)
 * [OpenFHE Release Notes](https://github.com/openfheorg/openfhe-development/blob/main/docs/static_docs/Release_Notes.md)
 * [Quickstart](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/quickstart.html)
 * [BSD 2-Clause License](LICENSE)
 * [Contributing to OpenFHE](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/contributing/contributing.html)
 * [OpenFHE Governance](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/misc/governance.html)
 * [Openfhe-development Github Issues](https://github.com/openfheorg/openfhe-development/issues)
 * To report security vulnerabilities, please email us at contact@openfhe.org


## Installation

Refer to our General Installation Information: [readthedocs](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/installation.html) for more information

Or refer to the following for your specific operating system:

- [Linux](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/linux.html)

- [MacOS](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/macos.html)

- [Windows](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/windows.html)


## CKKS Code Examples

To get familiar with the CKKS API, we recommend looking at the following examples:

   1. **Basic CKKS Examples:**
       1. [Simple Real Numbers](src/pke/examples/simple-real-numbers.cpp) - Introduction to CKKS
       2. [Simple Real Numbers with Serialization](src/pke/examples/simple-real-numbers-serial.cpp)
       3. [Advanced Real Numbers](src/pke/examples/advanced-real-numbers.cpp)
       4. [High-Precision CKKS (128-bit)](src/pke/examples/advanced-real-numbers-128.cpp)
       5. [Simple Complex Numbers](src/pke/examples/simple-complex-numbers.cpp)

   2. **Bootstrapping Examples:**
       1. [Simple CKKS Bootstrapping](src/pke/examples/simple-ckks-bootstrapping.cpp)
       2. [Advanced CKKS Bootstrapping](src/pke/examples/advanced-ckks-bootstrapping.cpp)
       3. [Iterative Bootstrapping](src/pke/examples/iterative-ckks-bootstrapping.cpp)
       4. [Composite Scaling Bootstrapping](src/pke/examples/simple-ckks-bootstrapping-composite-scaling.cpp)

   3. **Advanced Operations:**
       1. [Function Evaluation](src/pke/examples/function-evaluation.cpp)
       2. [Functional Bootstrapping for CKKS](src/pke/examples/functional-bootstrapping-ckks.cpp)
       3. [Inner Product Operations](src/pke/examples/inner-product.cpp)
       4. [CKKS Noise Flooding](src/pke/examples/ckks-noise-flooding.cpp)

   4. **Threshold/Multiparty FHE:**
       1. [Threshold FHE for CKKS](src/pke/examples/threshold-fhe.cpp)
       2. [Interactive Bootstrapping (2-party)](src/pke/examples/interactive-bootstrapping.cpp)
       3. [Multiparty Interactive Bootstrapping](src/pke/examples/tckks-interactive-mp-bootstrapping.cpp)
       4. [Proxy Re-Encryption](src/pke/examples/pre-buffer.cpp)

## Main API

- [PKE CryptoContext API (CKKS)](https://openfhe-development.readthedocs.io/en/latest/api/classlbcrypto_1_1CryptoContextImpl.html)
- [Description of CryptoContext Parameters for CKKS](https://github.com/openfheorg/openfhe-development/blob/main/src/pke/examples#description-of-the-cryptocontext-parameters-and-their-restrictions)

## Code of Conduct

In the interest of fostering an open and welcoming environment, we as contributors and maintainers pledge to making
participation in our project and our community a harassment-free experience for everyone, regardless of age, body size,
disability, ethnicity, sex characteristics, gender identity and expression, level of experience, education,
socio-economic status, nationality, personal appearance, race, religion, or sexual identity and orientation.


OpenFHE is a community-driven open source project developed by a diverse group of
[contributors](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/misc/contributors.html). The OpenFHE leadership has made a strong commitment to creating an open,
inclusive, and positive community. Please read our
[Code of Conduct](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/misc/code_of_conduct.html?highlight=code%20of%20) for guidance on how to interact with others in a way that
makes our community thrive.

## Call for Contributions

We welcome all contributions including but not limited to:

- [reporting issues](https://github.com/openfheorg/openfhe-development/issues)
- addressing [bugs](https://github.com/openfheorg/openfhe-development/issues) big or small. We label issues to help you filter them to your skill level.
- documentation changes
- talks and seminars using OpenFHE

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
