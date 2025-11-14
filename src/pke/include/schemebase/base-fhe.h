//==================================================================================
// BSD 2-Clause License
//
// Copyright (c) 2014-2022, NJIT, Duality Technologies Inc. and other contributors
//
// All rights reserved.
//
// Author TPOC: contact@openfhe.org
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==================================================================================

#ifndef LBCRYPTO_CRYPTO_BASE_FHE_H
#define LBCRYPTO_CRYPTO_BASE_FHE_H

// BinFHE removed for CKKS-only build
#include "ciphertext-fwd.h"
#include "cryptocontext-fwd.h"
#include "key/evalkey-fwd.h"
#include "key/keypair.h"
#include "key/privatekey-fwd.h"
#include "utils/exception.h"

#include <map>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

/**
 * @namespace lbcrypto
 * The namespace of lbcrypto
 */
namespace lbcrypto {

/**
 * @brief Abstract interface class for LBC PRE algorithms
 * @tparam Element a ring element.
 */
template <class Element>
class FHEBase {
public:
    virtual ~FHEBase() = default;

    /**
   * Bootstrap functionality:
   * There are three methods that have to be called in this specific order:
   * 1. EvalBootstrapSetup: computes and encodes the coefficients for encoding and
   * decoding and stores the necessary parameters
   * 2. EvalBootstrapKeyGen: computes and stores the keys for rotations and conjugation
   * 3. EvalBootstrap: refreshes the given ciphertext
   */

    /**
   * Sets all parameters for the linear method for the FFT-like method
   *
   * @param levelBudget - vector of budgets for the amount of levels in encoding
   * and decoding
   * @param dim1 - vector of inner dimension in the baby-step giant-step routine
   * for encoding and decoding
   * @param slots - number of slots to be bootstrapped
   * @param correctionFactor - value to rescale message by to improve precision. If set to 0, we use the default logic. This value is only used when NATIVE_SIZE=64
   * @param precompute - flag specifying whether to precompute the plaintexts for encoding and decoding.
   */
    virtual void EvalBootstrapSetup(const CryptoContextImpl<Element>& cc, std::vector<uint32_t> levelBudget,
                                    std::vector<uint32_t> dim1, uint32_t slots, uint32_t correctionFactor,
                                    bool precompute) {
        OPENFHE_THROW("Not supported");
    }

    /**
   * Virtual function to define the generation of all automorphism keys for EvalBT (with FFT evaluation).
   * EvalBTKeyGen uses the baby-step/giant-step strategy.
   *
   * @param privateKey private key.
   * @param slots - number of slots to be bootstrapped
   * @return the dictionary of evaluation key indices.
   */
    virtual std::shared_ptr<std::map<uint32_t, EvalKey<Element>>> EvalBootstrapKeyGen(
        const PrivateKey<Element> privateKey, uint32_t slots) {
        OPENFHE_THROW("Not supported");
    }

    /**
   * Computes the plaintexts for encoding and decoding for both linear and FFT-like methods. Supported in CKKS only.
   *
   * @param slots - number of slots to be bootstrapped
   */
    virtual void EvalBootstrapPrecompute(const CryptoContextImpl<Element>& cc, uint32_t slots) {
        OPENFHE_THROW("Not supported");
    }

    /**
   * Defines the bootstrapping evaluation of ciphertext
   *
   * The flavor of bootstrapping that uses the numIterations and precision parameters is described
   * in the Meta-BTS paper.
   * Source: Bae Y., Cheon J., Cho W., Kim J., and Kim T. META-BTS: Bootstrapping Precision
   * Beyond the Limit. Cryptology ePrint Archive, Report
   * 2022/1167. (https://eprint.iacr.org/2022/1167.pdf)
   *
   * @param ciphertext the input ciphertext.
   * @param numIterations number of iterations to run iterative bootstrapping (Meta-BTS). Increasing the iterations increases the precision of bootstrapping.
   * @param precision precision of initial bootstrapping algorithm. This value is
   * determined by the user experimentally by first running EvalBootstrap with numIterations = 1 and precision = 0 (unused).
   * @return the refreshed ciphertext.
   */
    virtual Ciphertext<Element> EvalBootstrap(ConstCiphertext<Element>& ciphertext, uint32_t numIterations,
                                              uint32_t precision) const {
        OPENFHE_THROW("EvalBootstrap is not implemented for this scheme");
    }

    virtual void EvalFBTSetup(const CryptoContextImpl<Element>& cc, const std::vector<std::complex<double>>& coeffs,
                              uint32_t numSlots, const BigInteger& PIn, const BigInteger& POut, const BigInteger& Bigq,
                              const PublicKey<DCRTPoly>& pubKey, const std::vector<uint32_t>& dim1,
                              const std::vector<uint32_t>& levelBudget, uint32_t lvlsAfterBoot = 0,
                              uint32_t depthLeveledComputation = 0, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }
    virtual void EvalFBTSetup(const CryptoContextImpl<Element>& cc, const std::vector<int64_t>& coeffs,
                              uint32_t numSlots, const BigInteger& PIn, const BigInteger& POut, const BigInteger& Bigq,
                              const PublicKey<DCRTPoly>& pubKey, const std::vector<uint32_t>& dim1,
                              const std::vector<uint32_t>& levelBudget, uint32_t lvlsAfterBoot = 0,
                              uint32_t depthLeveledComputation = 0, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual Ciphertext<Element> EvalFBT(ConstCiphertext<DCRTPoly>& ciphertext,
                                        const std::vector<std::complex<double>>& coeffs, uint32_t digitBitSize,
                                        const BigInteger& initialScaling, uint64_t postScaling,
                                        uint32_t levelToReduce = 0, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }
    virtual Ciphertext<Element> EvalFBT(ConstCiphertext<DCRTPoly>& ciphertext, const std::vector<int64_t>& coeffs,
                                        uint32_t digitBitSize, const BigInteger& initialScaling, uint64_t postScaling,
                                        uint32_t levelToReduce = 0, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual Ciphertext<Element> EvalFBTNoDecoding(ConstCiphertext<DCRTPoly>& ciphertext,
                                                  const std::vector<std::complex<double>>& coeffs,
                                                  uint32_t digitBitSize, const BigInteger& initialScaling,
                                                  size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }
    virtual Ciphertext<Element> EvalFBTNoDecoding(ConstCiphertext<DCRTPoly>& ciphertext,
                                                  const std::vector<int64_t>& coeffs, uint32_t digitBitSize,
                                                  const BigInteger& initialScaling, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual Ciphertext<Element> EvalHomDecoding(ConstCiphertext<DCRTPoly>& ciphertext, uint64_t postScaling,
                                                uint32_t levelToReduce = 0) {
        OPENFHE_THROW("Not supported");
    }

    virtual std::shared_ptr<seriesPowers<DCRTPoly>> EvalMVBPrecompute(ConstCiphertext<DCRTPoly>& ciphertext,
                                                                      const std::vector<std::complex<double>>& coeffs,
                                                                      uint32_t digitBitSize,
                                                                      const BigInteger& initialScaling,
                                                                      size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual std::shared_ptr<seriesPowers<DCRTPoly>> EvalMVBPrecompute(ConstCiphertext<DCRTPoly>& ciphertext,
                                                                      const std::vector<int64_t>& coeffs,
                                                                      uint32_t digitBitSize,
                                                                      const BigInteger& initialScaling,
                                                                      size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual Ciphertext<Element> EvalMVB(const std::shared_ptr<seriesPowers<DCRTPoly>> ciphertexts,
                                        const std::vector<std::complex<double>>& coeffs, uint32_t digitBitSize,
                                        const uint64_t postScaling, uint32_t levelToReduce = 0, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }
    virtual Ciphertext<Element> EvalMVB(const std::shared_ptr<seriesPowers<DCRTPoly>> ciphertexts,
                                        const std::vector<int64_t>& coeffs, uint32_t digitBitSize,
                                        const uint64_t postScaling, uint32_t levelToReduce = 0, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual Ciphertext<Element> EvalMVBNoDecoding(const std::shared_ptr<seriesPowers<DCRTPoly>> ciphertexts,
                                                  const std::vector<std::complex<double>>& coeffs,
                                                  uint32_t digitBitSize, size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }
    virtual Ciphertext<Element> EvalMVBNoDecoding(const std::shared_ptr<seriesPowers<DCRTPoly>> ciphertexts,
                                                  const std::vector<int64_t>& coeffs, uint32_t digitBitSize,
                                                  size_t order = 1) {
        OPENFHE_THROW("Not supported");
    }

    virtual Ciphertext<DCRTPoly> EvalHermiteTrigSeries(ConstCiphertext<DCRTPoly>& ciphertext,
                                                       const std::vector<std::complex<double>>& coefficientsCheb,
                                                       double a, double b,
                                                       const std::vector<std::complex<double>>& coefficientsHerm,
                                                       size_t precomp = 0) {
        OPENFHE_THROW("Not supported");
    }
    virtual Ciphertext<DCRTPoly> EvalHermiteTrigSeries(ConstCiphertext<DCRTPoly>& ciphertext,
                                                       const std::vector<std::complex<double>>& coefficientsCheb,
                                                       double a, double b, const std::vector<int64_t>& coefficientsHerm,
                                                       size_t precomp = 0) {
        OPENFHE_THROW("Not supported");
    }

    /////////////////////////////////////
    // SERIALIZATION
    /////////////////////////////////////

    template <class Archive>
    void save(Archive& ar) const {}

    template <class Archive>
    void load(Archive& ar) {}
};

}  // namespace lbcrypto

#endif
