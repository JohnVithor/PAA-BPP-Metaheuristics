// MetaHeuristic.hpp

#ifndef _METAHEURISTIC_H_
#define _METAHEURISTIC_H_

#include "Solution.hpp"

class MetaHeuristic
{
    public:
        virtual Solution* Run(Solution *initial_solution, const long max_time_minutes) = 0;
}

#endif // _METAHEURISTIC_H_