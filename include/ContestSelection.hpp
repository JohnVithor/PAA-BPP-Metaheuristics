// ContestSelection.hpp

#ifndef _CONTEST_SELECTION_H_
#define _CONTEST_SELECTION_H_

#include <random>

#include "Solution.hpp"
#include "Selection.hpp"

class ContestSelection: public Selection
{
    private:
        size_t _contestSize;
        std::default_random_engine *_engine;
        std::uniform_int_distribution<size_t> *_distribuition;
    public:
        ContestSelection(size_t contestSize, std::default_random_engine *engine, std::uniform_int_distribution<size_t> *distribuition)
                : _contestSize(contestSize), _engine(engine), _distribuition(distribuition)
        {/* Empty */};

        virtual Solution* operator()(std::vector<Solution*> solutions) {
            Solution* winner = solutions[(*_distribuition)(*_engine)];
            size_t current_round = 0;
            while(current_round < _contestSize) {
                Solution* challenger = solutions[(*_distribuition)(*_engine)];
                if (challenger->GetNumberBins() < winner->GetNumberBins()) {
                    winner = challenger;
                }
                ++current_round;
            }
            return winner;
        }
};

#endif // _CONTEST_SELECTION_H_
