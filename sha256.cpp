sha256_dpcpp_content = """
#include <cstring>
#include <fstream>
#include "sha256.h"
#include <CL/sycl.hpp>

using namespace sycl;

// Constantes do algoritmo SHA256
const unsigned int SHA256::sha256_k[64] = {
    // constantes pré-definidas aqui
};

// Função transformada usando SYCL para paralelizar o processo
void SHA256::transform(const unsigned char *message, unsigned int block_nb)
{
    uint32 w[64];
    uint32 wv[8];
    uint32 t1, t2;
    const unsigned char *sub_block;

    // Criando fila de comandos SYCL
    queue q;

    // Processando os blocos de dados com paralelismo
    q.submit([&](handler& h) {
        h.parallel_for(range<1>(block_nb), [=](id<1> i) mutable {
            int block_idx = i[0];
            sub_block = message + (block_idx << 6);

            // Processamento dos primeiros 16 valores do bloco
            for (int j = 0; j < 16; j++) {
                SHA2_PACK32(&sub_block[j << 2], &w[j]);
            }

            // Processamento dos valores restantes
            for (int j = 16; j < 64; j++) {
                w[j] = SHA256_F4(w[j - 2]) + w[j - 7] + SHA256_F3(w[j - 15]) + w[j - 16];
            }

            // Transformação dos valores
            for (int j = 0; j < 8; j++) {
                wv[j] = m_h[j];
            }

            for (int j = 0; j < 64; j++) {
                t1 = wv[7] + SHA256_F2(wv[4]) + SHA256_CH(wv[4], wv[5], wv[6]) + sha256_k[j] + w[j];
                t2 = SHA256_F1(wv[0]) + SHA256_MAJ(wv[0], wv[1], wv[2]);
                wv[7] = wv[6];
                wv[6] = wv[5];
                wv[5] = wv[4];
                wv[4] = wv[3] + t1;
                wv[3] = wv[2];
                wv[2] = wv[1];
                wv[1] = wv[0];
                wv[0] = t1 + t2;
            }
        });
    }).wait();

    // Atualizando o estado do hash final
    for (int i = 0; i < 8; i++) {
        m_h[i] += wv[i];
    }
}
"""

# Exibindo o código gerado para a versão DPC++ de sha256.cpp
sha256_dpcpp_content
