// SwapNeighborhood.hpp

#ifndef _SWAP_NEIGHBORHOOD_H_
#define _SWAP_NEIGHBORHOOD_H_

#include <random>

#include "Solution.hpp"
#include "Neighborhood.hpp"

class SwapNeighborhood: public Neighborhood
{
    public:
        virtual std::vector<Solution*> operator()(const Solution *initial_solution) {
            std::vector<Solution*> neighborhood(initial_solution->GetNumberItems());
            for (size_t i = 1; i < initial_solution->GetNumberItems(); ++i) {
                Solution* sol = initial_solution->Copy();
                size_t aux = (*sol)[i-1];
                (*sol)[i-1] = (*sol)[i];
                (*sol)[i] = aux;
                neighborhood[i-1] = sol;
            }
            Solution* sol = initial_solution->Copy();
            size_t aux = (*sol)[0];
            (*sol)[0] = (*sol)[initial_solution->GetNumberItems()-1];
            (*sol)[initial_solution->GetNumberItems()-1] = aux;
            neighborhood[initial_solution->GetNumberItems()-1] = sol;
            return neighborhood;
        }
};

#endif // _SWAP_NEIGHBORHOOD_H_
