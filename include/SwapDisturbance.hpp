// SwapDisturbance.hpp

#ifndef _SWAP_DISTURBANCE_H_
#define _SWAP_DISTURBANCE_H_

#include <random>

#include "Solution.hpp"
#include "Disturbance.hpp"

class SwapDisturbance: public Disturbance
{
    private:
        std::default_random_engine *_engine;
        std::uniform_int_distribution<size_t> *_distribuition;
    public:
        SwapDisturbance(std::default_random_engine *engine, std::uniform_int_distribution<size_t> *distribuition)
                : _engine(engine), _distribuition(distribuition)
        {/* Empty */};

        virtual Solution* operator()(Solution *sol) {
            size_t i = (*_distribuition)(*_engine);
            size_t j = (*_distribuition)(*_engine);
            size_t val = (*sol)[i];
            (*sol)[i] = (*sol)[j];
            (*sol)[j] = val;
            return sol;
        }
};

#endif // _SWAP_DISTURBANCE_H_
