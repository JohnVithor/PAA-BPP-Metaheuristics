// IteratedLocalSearch.hpp

#ifndef _ITERATED_LOCAL_SEARCH_H_
#define _ITERATED_LOCAL_SEARCH_H_

#include <cstdlib>
#include <vector>
#include <random>

#include "Solution.hpp"
#include "ProblemInstance.hpp"
#include "Neighborhood.hpp"
#include "Disturbance.hpp"
#include "Metaheuristic.hpp"

class IteratedLocalSearch : public Metaheuristic
{
    private:
        const ProblemInstance* _problemInstance;
        Neighborhood *_neighborhood;
        Disturbance *_disturbance;
        const size_t _disturbance_rounds;
        const size_t _max_not_improvements;

    public:
        IteratedLocalSearch(const ProblemInstance *problemInstance, Neighborhood *neighborhood, Disturbance *disturbance, const size_t disturbance_rounds, const size_t max_not_improvements)
            : _problemInstance(problemInstance), _neighborhood(neighborhood), _disturbance(disturbance), _disturbance_rounds(disturbance_rounds), _max_not_improvements(max_not_improvements)
        {/* Empty */};

        Solution* Run(Solution *initial_solution, const long max_time_minutes);
};

#endif // _ITERATED_LOCAL_SEARCH_H_