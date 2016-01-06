#include "NeighborList.hpp"

namespace vicsek
{
    NeighborList::NeighborList(const ParticleSptr& particle,
                               const RegionSptr& region,
                               const ParticleManagerSptr& particle_manager)
        : owner(particle->get_ID()),
          neighbors(particle_manager->size())
    {
        Vector position = particle->get_position();
        double R = particle->get_R();

        particle_size = 0;
        end_of_list = neighbors.begin();
        for(auto iter = particle_manager->begin();
                iter != particle_manager->end(); ++iter)
        {// periodic boundary
            if(region->min_dist(position, (*iter)->get_position()) < R)
            {
                neighbors[particle_size] = (*iter)->get_ID();
                ++particle_size;
                ++end_of_list;
            }
        }
    }

    void NeighborList::renew(const RegionSptr& region,
                             const ParticleManagerSptr& particle_manager)
    {
        Vector position = particle_manager->find_ID(owner)->get_position();
        double R = particle_manager->find_ID(owner)->get_R();

        neighbors.clear();

        particle_size = 0;
        end_of_list = neighbors.begin();
        for(auto iter = particle_manager->begin();
                iter != particle_manager->end(); ++iter)
        {
            if(region->min_dist(position, (*iter)->get_position()) < R)
            {
                neighbors[particle_size] = (*iter)->get_ID();
                ++particle_size;
                ++end_of_list;
            }
        }
        return;
    }
}
