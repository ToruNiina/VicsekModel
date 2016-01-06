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

    void TimeStepper::move_particle(const RegionSptr& region,
            const ParticleManagerSptr& particle_manager,
            const NeighborListHandlerSptr& neighbor_list_handler,
            const RandomNumberGeneratorSptr& rng)
    {
        std::vector<double> mean_theta_list(particle_manager->size());

        auto mean_theta_iter = mean_theta_list.begin();
        for(auto iter = particle_manager->begin();
                iter !=particle_manager->end(); ++iter)
        {
            NeighborListSptr nlist =
                neighbor_list_handler->find_ID((*iter)->get_ID());

            int neighbor_num = 0;
            double sum_theta(0e0);
            for(auto niter = nlist->begin(); niter != nlist->end(); ++niter)
            {
                sum_theta += particle_manager->find_ID(*niter)->get_theta();
                ++neighbor_num;
            }
            *mean_theta_iter = sum_theta / static_cast<double>(neighbor_num);

            ++mean_theta_iter;
        }

        mean_theta_iter = mean_theta_list.begin();
        for(auto iter = particle_manager->begin();
                iter !=particle_manager->end(); ++iter)
        {
            double rand = rng->get_uniform_dist();
            (*iter)->renew_position(*mean_theta_iter, rand, region);
            ++mean_theta_iter;
        }
 
        return;
    }

    void TimeStepper::renew_neighborlist(const RegionSptr& region,
            const ParticleManagerSptr& particle_manager,
            const NeighborListHandlerSptr& neighbor_list_handler)
    {
        for(auto iter = neighbor_list_handler->begin();
                iter != neighbor_list_handler->end(); ++iter)
        {
            (*iter)->renew(region, particle_manager);
        }
    }
}
#endif
