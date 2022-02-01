// Selection.hpp

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <random>

#include "Solution.hpp"

class Selection
{
    public:
        virtual Solution* operator()(std::vector<Solution*> solutions) = 0;
};

#endif // _SELECTION_H_
