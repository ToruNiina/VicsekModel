#include "NeighborListHandler.hpp"

namespace vicsek
{
    NeighborListHandler::NeighborListHandler(const RegionSptr& region,
                        const ParticleManagerSptr& particle_manager)
        :neighbor_lists(particle_manager->size())
    {
        std::size_t index = 0;
        for(auto iter = particle_manager->begin();
                iter != particle_manager->end();
                ++iter)
        {
            neighbor_lists[index] = 
                NeighborListSptr(
                        new NeighborList(*iter, region, particle_manager)
                        );
            ++index;
        }
    }
}
