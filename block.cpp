block_dpcpp_content = """
#include "Block.h"
#include "sha256.h"
#include <CL/sycl.hpp>
#include <iostream>

using namespace sycl;

Block::Block(uint32_t nIndexIn, const std::string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
    _nNonce = 0;
    _tTime = time(nullptr);

    sHash = _CalculateHash();
}

// Função de mineração com paralelização usando DPC++
void Block::MineBlock(uint32_t nDifficulty)
{
    char cstr[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\\0';

    std::string str(cstr);

    // Fila de comandos SYCL
    queue q;

    // Alocação de memória para nonce e hash
    uint64_t nNonce = 0;
    std::string sHash = _CalculateHash();
    bool block_found = false;

    q.submit([&](handler& h) {
        h.parallel_for(range<1>(10000), [=](id<1> i) mutable {
            if (!block_found) {
                uint64_t local_nonce = i[0];
                std::string local_hash = _CalculateHashWithNonce(local_nonce);

                if (local_hash.substr(0, nDifficulty) == str) {
                    nNonce = local_nonce;
                    sHash = local_hash;
                    block_found = true;
                }
            }
        });
    }).wait();

    std::cout << "Block mined: " << sHash << std::endl;
}

std::string Block::_CalculateHash() const
{
    std::stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << _nNonce;

    return sha256(ss.str());
}

// Função auxiliar para calcular o hash com um nonce específico
std::string Block::_CalculateHashWithNonce(uint64_t nonce) const
{
    std::stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << nonce;

    return sha256(ss.str());
}
"""

# Exibindo o código gerado para a versão DPC++ de Block.cpp
block_dpcpp_content
