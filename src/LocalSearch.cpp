// LocalSearch.cpp

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
#include "LocalSearch.hpp"

Solution* LocalSearch::Run(Solution *initial_solution, const long max_time_minutes) {
    initial_solution->SetNumberBins( _problemInstance->EvaluateSolution(initial_solution));
    size_t l2 = _problemInstance->GetLowerBoundL2();
    if (initial_solution->GetNumberBins() == l2) {
        return initial_solution;
    }
    Solution* best = initial_solution;
    bool improved = true;
    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    while (improved && std::chrono::duration_cast<std::chrono::minutes>(end-begin).count() < max_time_minutes) {
        improved = false;
        std::vector<Solution*> neighborhood = (*_neighborhood)(best);
        for (size_t i = 0; i < neighborhood.size(); ++i) {
            size_t bins = _problemInstance->EvaluateSolution(neighborhood[i]);
            if (!improved && bins < best->GetNumberBins()) {
                delete best;
                improved = true;
                best = neighborhood[i];
                best->SetNumberBins(bins);
            } else {
                delete neighborhood[i];
            }
        }
        neighborhood.clear();
        if (best->GetNumberBins() == l2) {
            return best;
        }
        end = std::chrono::steady_clock::now();
    }
    return best;
}
