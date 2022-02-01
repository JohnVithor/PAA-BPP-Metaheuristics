// GRASP.hpp

#ifndef _GRASP_H_
#define _GRASP_H_

#include <cstdlib>
#include <random>

#include "Solution.hpp"
#include "ProblemInstance.hpp"
#include "LocalSearch.hpp"

class GRASP
{
    private:
        ProblemInstance* _problemInstance;
        std::default_random_engine _engine;
        LocalSearch* _seacher;
        const size_t _max_time_searching;
        const double _start_alpha;
        const size_t _max_not_improvements;
        const size_t _max_steps;
        const size_t _start_increment;
        std::uniform_int_distribution<size_t> _distribuition;
        std::uniform_real_distribution<double> _realDist;

    public:
        GRASP(ProblemInstance *problemInstance, const size_t seed, LocalSearch* seacher, const size_t max_time_searching, 
        const double alpha, const size_t max_not_improvements, const size_t max_steps, const size_t start_increment)
            : _problemInstance(problemInstance), _engine(seed), _seacher(seacher), _max_time_searching(max_time_searching),
        _start_alpha(alpha), _max_not_improvements(max_not_improvements), _max_steps(max_steps), _start_increment(start_increment)
        {/* Empty */};

        Solution* Run(Solution *initial_solution, const long max_time_minutes);

        Solution* GenerateSolution(const double alpha);
};

#endif // _GRASP_H_