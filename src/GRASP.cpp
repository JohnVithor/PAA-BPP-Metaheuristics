// GRASP.cpp

#include <chrono>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <set>
#include <algorithm>
#include <random>

#include "Solution.hpp"
#include "ProblemInstance.hpp"
#include "LocalSearch.hpp"
#include "GRASP.hpp"

Solution* GRASP::GenerateSolution(const double alpha) {
    std::vector<std::vector<size_t>> items_bins;
    std::vector<size_t> candidates;
    std::vector<size_t> candidates_values;
    std::vector<size_t> lrc;

    size_t* bins_c = new size_t[_problemInstance->GetNumberItems()];
    std::fill_n(bins_c, _problemInstance->GetNumberItems(), 0);

    size_t bins = 0;
    for (size_t i = 0; i < _problemInstance->GetNumberItems(); ++i) {
        candidates.clear();
        candidates_values.clear();
        for (size_t j = 0; j < bins; ++j) {
            if (bins_c[j] + _problemInstance->GetItems()[i] <= _problemInstance->GetBinMaxCapacity()) {
                candidates.push_back(j);
                candidates_values.push_back(_problemInstance->GetBinMaxCapacity()-bins_c[j]);
            }
        }
        if (!candidates.empty()) {
            lrc.clear();
            auto min_max = std::minmax_element(std::begin(candidates_values), std::end(candidates_values));
            for (size_t j = 0; j < candidates.size(); ++j) {
                if (bins_c[candidates[j]] <= *min_max.first + alpha * (*min_max.second - *min_max.first)) {
                    lrc.push_back(candidates[j]);
                }
            }
            size_t selected_bin = _distribuition(_engine) % (lrc.size()+1);
            if (selected_bin == lrc.size()) {
                bins_c[bins] = _problemInstance->GetItems()[i];
                ++bins;
                items_bins.push_back({_problemInstance->GetItems()[i]});
            } else {
                bins_c[lrc[selected_bin]] += _problemInstance->GetItems()[i];
                items_bins[lrc[selected_bin]].push_back(_problemInstance->GetItems()[i]);
            }
        } else {
            bins_c[bins] = _problemInstance->GetItems()[i];
            ++bins;
            items_bins.push_back({_problemInstance->GetItems()[i]});
        }
    }

    Solution* sol = new Solution(_problemInstance->GetNumberItems(), bins, new size_t[_problemInstance->GetNumberItems()]);
    size_t idx = 0;
    for (size_t i = 0; i < items_bins.size(); ++i) {
        for (size_t j = 0; j < items_bins[i].size(); ++j) {
            (*sol)[idx] = items_bins[i][j];
            ++idx;
        }
    }
    delete[] bins_c;
    return sol;
}

Solution* GRASP::Run(Solution *initial_solution, const long max_time_minutes) {
    initial_solution->SetNumberBins( _problemInstance->EvaluateSolution(initial_solution));
    size_t l2 = _problemInstance->GetLowerBoundL2();
    if (initial_solution->GetNumberBins() == l2) {
        return initial_solution;
    }
    _problemInstance->SortItemsDecreasing();
    Solution* best = _seacher->Run(initial_solution, _max_time_searching);
    size_t not_improved_count = 0;
    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    double current_alpha = _start_alpha;
    while (not_improved_count < _max_not_improvements && std::chrono::duration_cast<std::chrono::minutes>(end-begin).count() < max_time_minutes) {
        if (not_improved_count >= _start_increment){
            current_alpha += 0.05;
            current_alpha = std::min(current_alpha, 1.0);
        }
        Solution* current = this->GenerateSolution(current_alpha);
        current = _seacher->Run(current, _max_time_searching);
        if(current->GetNumberBins() < best->GetNumberBins()) {
            delete best;
            if (current->GetNumberBins() == l2) {
                return current;
            }
            best = current;
            not_improved_count = 0;
            current_alpha = _start_alpha;
        } else {
            delete current;
            ++not_improved_count;
        }
        end = std::chrono::steady_clock::now();
    }
    return best;
}