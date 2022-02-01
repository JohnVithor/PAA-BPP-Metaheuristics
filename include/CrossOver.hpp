// CrossOver.hpp

#ifndef _CROSS_OVER_H_
#define _CROSS_OVER_H_

#include <random>

#include "Solution.hpp"

class CrossOver
{
    public:
        virtual Solution* operator()(Solution *sol1, Solution *sol2) = 0;
};

#endif // _CROSS_OVER_H_
