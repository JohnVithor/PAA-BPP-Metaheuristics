// Neighborhood.hpp

#ifndef _NEIGHBORHOOD_H_
#define _NEIGHBORHOOD_H_

#include <random>

#include "Solution.hpp"

class Neighborhood
{
    public:
        virtual std::vector<Solution*> operator()(const Solution *initial_solution) = 0;
};

#endif // _NEIGHBORHOOD_H_
