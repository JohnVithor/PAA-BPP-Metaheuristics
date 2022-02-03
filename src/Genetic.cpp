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

        for (size_t i = 1; i < _size; ++i) {
            delete population[i];
            new_population[i]->SetNumberBins(_problemInstance->EvaluateSolution(new_population[i]));
            population[i] = new_population[i];
            if (population[i]->GetNumberBins() < pop_best->GetNumberBins()) {
                pop_best = population[i]->Copy();
            }
        }

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
