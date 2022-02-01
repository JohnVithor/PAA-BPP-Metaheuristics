// Genetic.hpp

#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <cstdlib>
#include <vector>
#include <random>

#include "Solution.hpp"
#include "ProblemInstance.hpp"
#include "Disturbance.hpp"
#include "CrossOver.hpp"
#include "Selection.hpp"

class Genetic
{
    private:
        const ProblemInstance* _problemInstance;
        std::default_random_engine _engine;
        Disturbance *_mutation;
        double _mutationRate;
        CrossOver *_crossOver;
        double _crossRate;
        Selection *_selection;
        const size_t _epochs;
        const size_t _size;
        std::uniform_int_distribution<size_t> _distribuition;
        std::uniform_real_distribution<double> _realDist;

    public:
        Genetic(const ProblemInstance *problemInstance, size_t seed, 
                Disturbance *mutation, double mutationRate, 
                CrossOver *crossOver, double crossRate,
                Selection *selection, const size_t epochs, const size_t size)
            : _problemInstance(problemInstance), _engine(seed),
              _mutation(mutation), _mutationRate(mutationRate),
              _crossOver(crossOver), _crossRate(crossRate),
              _selection(selection), _epochs(epochs), _size(size)
        {/* Empty */};

        Solution* Run(Solution *initial_solution, const long max_time_minutes);
};

#endif // _GENETIC_H_