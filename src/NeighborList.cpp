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
        for(auto iter = particle_manager->cbegin();
                iter != particle_manager->cend(); ++iter)
        {// periodic boundary
            if(region->min_dist(position, (*iter)->get_position()) < R)
            {
                neighbors[particle_size] = (*iter)->get_ID();
                ++particle_size;
                ++end_of_list;
            }
        }
//         cend_of_list = end_of_list;
    }

    void NeighborList::renew(const RegionSptr& region,
                             const ParticleManagerSptr& particle_manager)
    {
        const Vector position = particle_manager->find_ID(owner)->get_position();
        const double R = particle_manager->find_ID(owner)->get_R();

        neighbors.clear();

        particle_size = 0;
        end_of_list = neighbors.begin();
        for(auto iter = particle_manager->cbegin();
                iter != particle_manager->cend(); ++iter)
        {
            const std::array<Vector, 9>
                periodic_copies(region->periodic_1st((*iter)->get_position()));

            for(auto periodic_iter = periodic_copies.cbegin();
                    periodic_iter != periodic_copies.cend(); ++periodic_iter)
            {
                if(length(position - *periodic_iter) < R)
                {
                    // if the particle's periodic boundary copy is near,
                    // add the particle into neighbors several times.
                    neighbors[particle_size] = (*iter)->get_ID();
                    ++particle_size;
                    ++end_of_list;
                }
            }
        }
//         cend_of_list = end_of_list;
        return;
    }
}
