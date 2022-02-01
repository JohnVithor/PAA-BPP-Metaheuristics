// ProblemInstance.hpp

#ifndef _PROBLEM_INSTANCE_H_
#define _PROBLEM_INSTANCE_H_

#include <cstdlib>
#include "Solution.hpp"

class ProblemInstance
{
    private:
        const size_t _binMaxCapacity;
        const size_t _numberItens;
        size_t* _items;

        size_t GetLowerBoundLk(const size_t &k) const;
    
    public:
        ProblemInstance(size_t binMaxCapacity, size_t numberItens, size_t* items)
            : _binMaxCapacity(binMaxCapacity), _numberItens(numberItens), _items(items)
        {/* Empty */};
        ~ProblemInstance() { delete[] _items; };

        const size_t GetBinMaxCapacity() { return _binMaxCapacity; };
        const size_t GetNumberItems() { return _numberItens; };
        const size_t* GetItems() { return _items; };

        const size_t& operator[](size_t idx) const { return _items[idx]; };

        size_t EvaluateSolution(const Solution *sol) const;
        Solution* GenerateRandomSolution(const size_t seed) const;
        Solution* GenerateBestFitSolution() const;
        Solution* GenerateBestFitDecreasingSolution() const;
        size_t GetLowerBoundL2() const;
        void SortItemsDecreasing() const;
};

#endif // _PROBLEM_INSTANCE_H_