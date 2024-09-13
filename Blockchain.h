
#ifndef TESTCHAIN_BLOCK_H
#define TESTCHAIN_BLOCK_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include <CL/sycl.hpp>

using namespace std;
using namespace sycl;

class Block {
public:
    string sHash;
    string sPrevHash;

    Block(uint32_t nIndexIn, const string &sDataIn);

    void MineBlock(uint32_t nDifficulty);

private:
    uint32_t _nIndex;
    uint32_t _nNonce;
    string _sData;
    time_t _tTime;

    string _CalculateHash() const;
    string _CalculateHashWithNonce(uint64_t nonce) const;
};

#endif //TESTCHAIN_BLOCK_H
"""

# Exibindo o conteúdo atualizado de Block.h para DPC++
block_h_dpcpp_content
