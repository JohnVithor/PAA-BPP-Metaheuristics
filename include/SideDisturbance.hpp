// SideDisturbance.hpp

#ifndef _SIDE_DISTURBANCE_H_
#define _SIDE_DISTURBANCE_H_

#include <random>

#include "Solution.hpp"
#include "Disturbance.hpp"

class SideDisturbance: public Disturbance
{
    private:
        std::default_random_engine _engine;
        std::uniform_real_distribution<double> _distribuition;
    public:
        SideDisturbance(size_t seed) {
            _engine = std::default_random_engine(seed);
            _distribuition = std::uniform_real_distribution<double>(0.0, 1.0);
        };

        virtual Solution* operator()(Solution *sol) {
            double rate = 1.0 / sol->GetNumberItems();
            for (size_t i = 0; i < sol->GetNumberItems(); ++i) {
                if (_distribuition(_engine) < rate) {
                    size_t side = (_distribuition(_engine) < 0.5) ? 1 : -1;
                    size_t aux = (*sol)[i];
                    size_t pos = (i+side) % sol->GetNumberItems();
                    (*sol)[i] = (*sol)[pos];
                    (*sol)[pos] = aux;
                }
            }
            return sol;
        }
};

#endif // _SIDE_DISTURBANCE_H_
