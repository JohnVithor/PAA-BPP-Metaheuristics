// LocalSearch.hpp

#ifndef _LOCAL_SEARCH_H_
#define _LOCAL_SEARCH_H_

#include <cstdlib>
#include <vector>
#include <random>

#include "Solution.hpp"
#include "ProblemInstance.hpp"
#include "Neighborhood.hpp"
#include "Disturbance.hpp"
#include "Metaheuristic.hpp"

class LocalSearch : public Metaheuristic
{
    private:
        const ProblemInstance* _problemInstance;
        Neighborhood *_neighborhood;

    public:
        LocalSearch(const ProblemInstance *problemInstance, Neighborhood *neighborhood)
            : _problemInstance(problemInstance), _neighborhood(neighborhood)
        {/* Empty */};

        Solution* Run(Solution *initial_solution, const long max_time_minutes);
};

#endif // _LOCAL_SEARCH_H_