// Solution.hpp

#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <cstdlib>
#include <iostream>
#include <algorithm>

class Solution
{
    private:
        size_t _numberItens;
        size_t _numberBins;
        size_t* _itemsOrder;
    public:
        Solution(size_t numberItens, size_t numberBins, size_t* itensOrder)
            : _numberItens(numberItens), _numberBins(numberBins), _itemsOrder(itensOrder)
        {/* Empty */};
        ~Solution() { delete[] _itemsOrder; } ;

        const size_t GetNumberItems() const { return _numberItens; };
        size_t GetNumberBins() { return _numberBins; };
        void SetNumberBins(size_t newNumberBins) { _numberBins = newNumberBins; };
        size_t* GetItemsOrder() { return _itemsOrder; };

        Solution* Copy() const {
            Solution* copy = new Solution(_numberItens, _numberBins, new size_t[_numberItens]);
            std::copy(_itemsOrder, _itemsOrder+_numberItens, copy->_itemsOrder);
            return copy;
        };

        size_t& operator[](size_t idx) { return _itemsOrder[idx]; };
        const size_t& operator[](size_t idx) const { return _itemsOrder[idx]; };

        friend std::ostream& operator<< (std::ostream& stream, const Solution& sol) {
            stream << "Items: " << sol._numberItens << " Bins: " << sol._numberBins << std::endl;
            for (size_t i = 0; i < sol._numberItens; ++i) {
                std::cout << sol[i] << " ";
            }
            stream << std::endl;
            return stream;
        }
};

#endif // _SOLUTION_H_