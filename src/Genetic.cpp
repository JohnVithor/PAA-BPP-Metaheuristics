// Genetic.cpp

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
#include "Disturbance.hpp"
#include "CrossOver.hpp"
#include "Genetic.hpp"

Solution* Genetic::Run(Solution *initial_solution, const long max_time_minutes) {
    initial_solution->SetNumberBins( _problemInstance->EvaluateSolution(initial_solution));
    size_t l2 = _problemInstance->GetLowerBoundL2();
    if (initial_solution->GetNumberBins() == l2) {
        return initial_solution;
    }
    Solution* best = initial_solution;
    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::vector<Solution*> population(_size);
    for (size_t i = 0; i < _size-(_size/10); ++i) {
        population[i] = _problemInstance->GenerateRandomSolution(_distribuition(_engine));
        population[i]->SetNumberBins(_problemInstance->EvaluateSolution(population[i]));
    }
    for (size_t i = _size-(_size/10); i < _size; ++i) {
        population[i] = best->Copy();
    }
    size_t current_epoch = 0;
    while (current_epoch < _epochs && std::chrono::duration_cast<std::chrono::minutes>(end-begin).count() < max_time_minutes) {
        std::vector<Solution*> new_population(_size);
        for (size_t i = 0; i < _size; ++i) {
            Solution* s1 = population[i];
            Solution* s2 = (*_selection)(population);
            Solution* child;
            if (_realDist(_engine) < _crossRate) {
                child = (*_crossOver)(s1, s2);
            } else {
                child = (s1->GetNumberBins() < s2->GetNumberBins()) ? s1->Copy() : s2->Copy();
            }
            if (_realDist(_engine) < _mutationRate) {
                child = (*_mutation)(child);
            }
            new_population[i] = child;
        }
        delete population[0];
        new_population[0]->SetNumberBins(_problemInstance->EvaluateSolution(new_population[0]));
        population[0] = new_population[0];
        Solution* pop_best = population[0];

        std::vector<size_t> migration(_size/10);
        size_t current_max = 0;
        for (size_t i = 1; i < _size; ++i) {
            delete population[i];
            new_population[i]->SetNumberBins(_problemInstance->EvaluateSolution(new_population[i]));
            population[i] = new_population[i];
            if (population[i]->GetNumberBins() < pop_best->GetNumberBins()) {
                pop_best = population[i]->Copy();
            } else {
                if (migration.size() < _size/10) {
                    migration.push_back(i);
                    if (population[i]->GetNumberBins() > current_max) {
                        current_max = population[i]->GetNumberBins();
                    }
                } else {
                    if (population[i]->GetNumberBins() > current_max) {
                        size_t max = 0;
                        size_t p_max = current_max;
                        for (size_t j = 1; j < migration.size(); ++j) {
                            if (population[j]->GetNumberBins() > population[migration[max]]->GetNumberBins()) {
                                p_max = population[migration[max]]->GetNumberBins();
                                max = j;
                            } else {
                                if (population[j]->GetNumberBins() == population[migration[max]]->GetNumberBins()){
                                    p_max = population[migration[max]]->GetNumberBins();
                                }
                            }
                        }
                        migration.at(max) = i;
                        current_max = p_max;
                    }
                }
            }
        }

        for (size_t i = 0; i < migration.size(); ++i) {
            population[migration[i]] = _problemInstance->GenerateRandomSolution(_distribuition(_engine));
            population[migration[i]]->SetNumberBins(_problemInstance->EvaluateSolution(population[migration[i]]));
        }
        migration.clear();

        if (pop_best->GetNumberBins() < best->GetNumberBins()) {
            delete best;
            best = pop_best->Copy();
        }
        if (best->GetNumberBins() == l2) {
            for (size_t i = 0; i < _size; ++i) {
                delete population[i];
            }
            return best;
        }
        ++current_epoch;
        end = std::chrono::steady_clock::now();
    }
    for (size_t i = 0; i < _size; ++i) {
        delete population[i];
    }
    return best;
}
