#ifndef VICSEK_TIME_STEPPER
#define VICSEK_TIME_STEPPER
#include "NeighborListHandler.hpp"

namespace vicsek
{
    class TimeStepper
    {
        public:
            TimeStepper(){}
            ~TimeStepper(){}

            void set_dt(const double delta_t){dt = delta_t;}

            void move_particle(const RegionSptr& region,
                    const ParticleManagerSptr& particle_manager,
                    const NeighborListHandlerSptr& neighbor_list_handler,
                    const RandomNumberGeneratorSptr& rng);

            void renew_neighborlist(const RegionSptr& region,
                    const ParticleManagerSptr& particle_manager,
                    const NeighborListHandlerSptr& neighbor_list_handler);

        private:
            double dt = 0.1;
    };
    using TimeStepperSptr = std::shared_ptr<TimeStepper>;
}
#endif
