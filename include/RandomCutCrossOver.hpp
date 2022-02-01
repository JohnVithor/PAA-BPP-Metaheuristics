// RandomCutCrossOver.hpp

#ifndef _RANDOM_CUT_CROSS_OVER_H_
#define _RANDOM_CUT_CROSS_OVER_H_

#include <random>
#include <set>

#include "Solution.hpp"
#include "CrossOver.hpp"

class RandomCutCrossOver : public CrossOver
{
    private:
        std::default_random_engine *_engine;
        std::uniform_int_distribution<size_t> *_distribuition;
    public:
        RandomCutCrossOver(std::default_random_engine *engine, std::uniform_int_distribution<size_t> *distribuition)
                : _engine(engine), _distribuition(distribuition)
        {/* Empty */};

        virtual Solution* operator()(Solution *sol1, Solution *sol2) {
            std::multiset<size_t, std::greater<size_t>> bag;          
            Solution* child = sol1->Copy();
            size_t pos = (*_distribuition)(*_engine);

            for (size_t i = pos; i < child->GetNumberItems(); ++i) {
                bag.insert((*sol1)[i]);
            }
            size_t i = pos;
            for (size_t j = 0; j < child->GetNumberItems(); ++j) {
                auto it = bag.find((*sol2)[j]);
                if (it != bag.end()) {
                    bag.erase(it);
                    (*child)[i] = *it;
                    ++i;
                }
            }
            return child;
        };
};

#endif // _RANDOM_CUT_CROSS_OVER_H_
