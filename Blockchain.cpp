

#include "Blockchain.h"
#include "Block.h"

// Construtor inicializando o bloco gênesis e o nível de dificuldade
Blockchain::Blockchain()
{
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 6;
}

// Adiciona um bloco na blockchain e realiza mineração com paralelismo
void Blockchain::AddBlock(Block bNew)
{
    // Hash do bloco anterior é configurado
    bNew.sPrevHash = _GetLastBlock().sHash;
    
    // Minera o novo bloco usando o nível de dificuldade
    bNew.MineBlock(_nDifficulty);

    // Adiciona o bloco minerado à cadeia
    _vChain.push_back(bNew);
}

// Retorna o último bloco da cadeia
Block Blockchain::_GetLastBlock() const
{
    return _vChain.back();
}
"""
