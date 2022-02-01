// Disturbance.hpp

#ifndef _DISTURBANCE_H_
#define _DISTURBANCE_H_

#include <random>

#include "Solution.hpp"

class Disturbance
{
    public:
        virtual Solution* operator()(Solution *sol) = 0;
};

#endif // _DISTURBANCE_H_
