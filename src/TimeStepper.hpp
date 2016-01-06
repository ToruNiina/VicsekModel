#ifndef VICSEK_TIME_STEPPER
#define VICSEK_TIME_STEPPER
#include "RandomNumberGenerator.hpp"
#include "NeighborListHandler.hpp"
#include "ParticleManager.hpp"
#include "Region.hpp"

namespace vicsek
{
    class TimeStepper
    {
        public:
            TimeStepper(){}
            ~TimeStepper(){}

            void move_particle(const RegionSptr& region,
                    const ParticleManagerSptr& particle_manager,
                    const NeighborListHandlerSptr& neighbor_list_handler,
                    const RandomNumberGeneratorSptr& rng);

            void renew_neighborlist(const RegionSptr& region,
                    const ParticleManagerSptr& particle_manager,
                    const NeighborListHandlerSptr& neighbor_list_handler);
    };
    using TimeStepperSptr = std::shared_ptr<TimeStepper>;
}
#endif
