// ProblemInstance.cpp

#include "ProblemInstance.hpp"
#include <set>          // set
#include <vector>       // vector
#include <algorithm>    // shuffle, sort
#include <cmath>        // ceil, max
#include <random>       // default_random_engine

size_t ProblemInstance::EvaluateSolution(const Solution *sol) const {
    size_t bins = 1;
    size_t bin_cap = 0;
    for (size_t i = 0; i < sol->GetNumberItems(); ++i) {
        if ((*sol)[i] + bin_cap <= _binMaxCapacity) {
            bin_cap += (*sol)[i];
        } else {
            bin_cap = (*sol)[i];
            ++bins;
        }
    }
    return bins;
}

Solution* ProblemInstance::GenerateRandomSolution(const size_t seed) const {
    Solution* sol = new Solution(_numberItens, 0, new size_t[_numberItens]);
    std::copy(_items, _items+_numberItens, sol->GetItemsOrder());
    std::shuffle(sol->GetItemsOrder(), sol->GetItemsOrder()+_numberItens, std::default_random_engine(seed));
    return sol;
}

Solution* ProblemInstance::GenerateBestFitSolution() const {
    std::vector<std::vector<size_t>> items_bins;
    size_t* bins_c = new size_t[_numberItens];
    std::fill_n(bins_c, _numberItens, 0);

    size_t bins = 0;
    for (size_t i = 0; i < _numberItens; ++i) {
        size_t largest_content_i = _numberItens;
        size_t largest_content = 0;
        for (size_t j = 0; j < bins; ++j) {
            if (bins_c[j] + _items[i] <= _binMaxCapacity && bins_c[j] > largest_content) {
                largest_content_i = j;
                largest_content = bins_c[j];
            }
        }
        if (largest_content_i != _numberItens) {
            bins_c[largest_content_i] += _items[i];
            items_bins[largest_content_i].push_back(_items[i]);
        } else {
            bins_c[bins] = _items[i];
            ++bins;
            items_bins.push_back(std::vector<size_t>({_items[i]}));
        }
    }
    Solution* sol = new Solution(_numberItens, bins, new size_t[_numberItens]);
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

Solution* ProblemInstance::GenerateBestFitDecreasingSolution() const {
    this->SortItemsDecreasing();
    return GenerateBestFitSolution();
}

size_t ProblemInstance::GetLowerBoundLk(const size_t &k) const {
    std::vector<size_t> n1;
    std::vector<size_t> n2;
    long sum_n2 = 0;
    std::vector<size_t> n3;
    long sum_n3 = 0;
    const size_t n1_cut = _binMaxCapacity - k;
    const size_t C_half = _binMaxCapacity / 2;
    for (size_t i = 0; i < _numberItens; ++i){
        if (_items[i] > n1_cut) {
            n1.push_back(_items[i]);
        } else {
            if (_items[i] > C_half) {
                n2.push_back(_items[i]);
                sum_n2 +=_items[i];
            } else {
                if(_items[i] >= k) {
                    n3.push_back(_items[i]);
                    sum_n3 +=_items[i];
                }
            }
        }
    }
    const long last_value = std::max(0.0, std::ceil((sum_n3 - (long)(n2.size()*_binMaxCapacity - sum_n2)) / (double) _binMaxCapacity));
    return n1.size() + n2.size() + last_value;
}

size_t ProblemInstance::GetLowerBoundL2() const {
    std::vector<size_t> n1;
    std::vector<size_t> n2;
    std::set<size_t> distinct_values;
    const size_t C_half = _binMaxCapacity / 2;
    for (size_t i = 0; i < _numberItens; ++i){
        if (_items[i] > C_half) {
            n1.push_back(_items[i]);
        } else {
            distinct_values.insert(_items[i]);
        }
    }
    if (distinct_values.empty()) {
        return n1.size();
    } else {
        size_t result = 0;
        for (auto it = distinct_values.begin(); it != distinct_values.end(); ++it) {
            result = std::max(result, GetLowerBoundLk(*it));
        }
        return result;
    }
}

void ProblemInstance::SortItemsDecreasing() const {
    std::sort(_items, _items+_numberItens, std::greater<size_t>());
}