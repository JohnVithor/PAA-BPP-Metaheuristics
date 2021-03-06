// driver.cpp

#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <set>
#include <stack>
#include <algorithm>
#include <random>

#include "Solution.hpp"
#include "ProblemInstance.hpp"
#include "SwapDisturbance.hpp"
#include "SideDisturbance.hpp"
#include "RandomCutCrossOver.hpp"
#include "ContestSelection.hpp"
#include "Genetic.hpp"

int main(int argc, char const *argv[]) {
    if (argc != 10) {
        std::cout << "O programa deve receber o caminho para arquivo com os dados da instância." << std::endl;
        std::cout << "A seed para realizar o shuffle dos elementos antes de aplicar o algoritmo escolhido (Os items já estão ordenados nos arquivos)" << std::endl;
        std::cout << "Em seguida o tempo máximo em minutos que o programa pode executar até encontrar o resultado ótimo" << std::endl;

        std::cout << "Então os parametros para o algoritmo genético:" << std::endl;
        std::cout << "Número de participantes do torneio de seleção para o cruzamento" << std::endl;
        std::cout << "Taxa de mutação seguida da taxa de cruzamento, entre 0 e 1" << std::endl;
        std::cout << "Número de épocas (iterações do algoritmo) e tamanho da população" << std::endl;

        std::cout << "E por fim o nível de detalhe a ser informado na saida padrão sobre os resultados obtidos (0-3)" << std::endl;
        std::cout << "0 - Apenas a quantidade de bins usada e o tempo em nanosegundos" << std::endl;
        std::cout << "1 - O anterior e o tempo em segundos" << std::endl;
        std::cout << "2 - O anterior e o tempo em minutos" << std::endl;
        std::cout << "3 - O anterior e em qual bin cada item foi empacotado além da capacidade de cada bin" << std::endl;
        exit(1);
    }
    std::ifstream fileSource(argv[1]);
    size_t N = 0;
    size_t C = 0;
    size_t* items = nullptr;
    if (!fileSource) {
        std::cerr << "Erro: Arquivo não pode ser aberto - " << argv[1] << std::endl;
        return 1;
    } else {
        fileSource >> N;
        fileSource >> C;
        items = new size_t[N];
        for (size_t i = 0; i < N; ++i)
        {
            fileSource >> items[i];
        }
        fileSource.close();
    }
    size_t seed = std::strtoul(argv[2], nullptr, 10);
    std::default_random_engine* dre = new std::default_random_engine(seed);
    std::uniform_int_distribution<size_t>* uid = new std::uniform_int_distribution<size_t>(0, N);

    std::shuffle(items, items+N, *dre);
    const long int max_time_min = std::strtoul(argv[3], nullptr, 10);
    if (!(max_time_min > 0)) {
        std::cout << "O tempo máximo em minutos deve ser maior que 0" << std::endl;
        return 1;
    }

    size_t contest_size = std::strtoul(argv[4], nullptr, 10);
    double mutation_rate = std::strtod(argv[5], nullptr);
    double cross_rate = std::strtod(argv[6], nullptr);
    size_t n_epochs = std::strtoul(argv[7], nullptr, 10);
    size_t population_size = std::strtoul(argv[8], nullptr, 10);

    const long detail_level = std::strtol(argv[9], nullptr, 10);
    if (!(detail_level > -1 && detail_level < 4)) {
        std::cout << "O nível de detalhe deve ser qualquer inteiro entre {0,1,2,3}" << std::endl;
        return 1;
    }
    ProblemInstance instance(C, N, items);
    SideDisturbance disturbance((*uid)(*dre));
    RandomCutCrossOver cross(dre, uid);
    ContestSelection selection(contest_size, dre, uid);
    Genetic search(&instance, (*uid)(*dre), &disturbance, mutation_rate, &cross, cross_rate, &selection, n_epochs, population_size);

    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    Solution* sol = search.Run(instance.GenerateBestFitDecreasingSolution(), max_time_min);

    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "Número de bins: " << sol->GetNumberBins() << std::endl;
    std::cout << "Tempo em nanosegundos: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
    if (detail_level > 0) {
        std::cout << "Tempo em segundos: " << std::chrono::duration_cast<std::chrono::seconds>(end-begin).count() << std::endl;    
        if (detail_level > 1) {
            std::cout << "Tempo em minutos: " << std::chrono::duration_cast<std::chrono::minutes>(end-begin).count() << std::endl;
            if (detail_level > 2) {
                std::cout << std::left;
                size_t bin = 1;
                size_t bin_cap = 0;
                std::cout << "Bin 1 possui os itens:" << std::endl;
                for (size_t i = 0; i < sol->GetNumberItems(); ++i) {
                    if ((*sol)[i] + bin_cap <= instance.GetBinMaxCapacity()) {
                        bin_cap += (*sol)[i];
                        std::cout << (*sol)[i] << " ";
                    } else {
                        bin_cap = (*sol)[i];
                        ++bin;
                        std::cout << std::endl << "Bin " << bin << " possui os itens:" << std::endl;
                        std::cout << (*sol)[i] << " ";
                    }
                }
                std::cout << std::endl << "Capacidade por bin: " << C << std::endl;
            }
        }
    }
    delete sol;
    delete dre;
    delete uid;
    return 0;
}