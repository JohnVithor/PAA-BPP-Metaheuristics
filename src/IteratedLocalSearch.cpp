// IteratedLocalSearch.cpp

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
#include "Neighborhood.hpp"
#include "Disturbance.hpp"
#include "IteratedLocalSearch.hpp"


Solution* IteratedLocalSearch::Run(Solution *initial_solution, const long max_time_minutes) {
    initial_solution->SetNumberBins(_problemInstance->EvaluateSolution(initial_solution));
    size_t l2 = _problemInstance->GetLowerBoundL2();
    if (initial_solution->GetNumberBins() == l2) {
        return initial_solution;
    }
    Solution* best = initial_solution->Copy();
    Solution* current = initial_solution;
    size_t not_improved_count = 0;
    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    while (not_improved_count < _max_not_improvements && std::chrono::duration_cast<std::chrono::minutes>(end-begin).count() < max_time_minutes) {
        bool improved = true;
        while (improved) {
            improved = false;
            std::vector<Solution*> neighborhood = (*_neighborhood)(current);
            for (size_t i = 0; i < neighborhood.size(); ++i) {
                size_t bins = _problemInstance->EvaluateSolution(neighborhood[i]);
                if (bins < current->GetNumberBins()) {
                    delete current;
                    improved = true;
                    current = neighborhood[i];
                    current->SetNumberBins(bins);
                } else {
                    delete neighborhood[i];
                }
            }
        }
        if(current->GetNumberBins() < best->GetNumberBins()) {
            delete best;
            if (current->GetNumberBins() == l2) {
                return current;
            }
            best = current->Copy();
            not_improved_count = 0;
        } else {
            ++not_improved_count;
        }
        size_t p = 0;
        while (p < _disturbance_rounds) {
            current = (*_disturbance)(current);
            ++p;
        }
        end = std::chrono::steady_clock::now();
    }
    delete current;
    return best;
}
