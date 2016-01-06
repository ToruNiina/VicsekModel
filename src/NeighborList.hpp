#ifndef VICSEK_NEIGHBOR_LIST
#define VICSEK_NEIGHBOR_LIST
#include "Defs.hpp"
#include "ParticleManager.hpp"
#include "Region.hpp"
#include <vector>

namespace vicsek
{
    class NeighborList
    {
        public:
            using iterator = std::vector<uInt>::iterator;

        public:
            NeighborList(const ParticleSptr& particle,
                         const RegionSptr& region,
                         const ParticleManagerSptr& particle_manager);

            void renew(const RegionSptr& region,
                       const ParticleManagerSptr& particle_manager);

            const uInt get_ownerID() const {return owner;}

            bool empty(){return neighbors.empty();}
            std::size_t size(){return particle_size;}
            iterator begin(){return neighbors.begin();}
            iterator end(){return end_of_list;}

        private:

            const uInt owner;
            std::size_t particle_size;
            iterator end_of_list;
            std::vector<uInt> neighbors;
    };
    using NeighborListSptr = std::shared_ptr<NeighborList>;

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
#endif
