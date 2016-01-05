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
            std::size_t size(){return neighbors.size();}
            iterator begin(){return neighbors.begin();}
            iterator end(){return neighbors.end();}

        private:
            const uInt owner;
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

        std::size_t index = 0;
        for(auto iter = particle_manager->begin();
                iter != particle_manager->end(); ++iter)
        {// periodic boundary
            if(region->min_dist(position, (*iter)->get_position()) < R)
            {
                neighbors[index] = (*iter)->get_ID();
                ++index;
            }
        }
    }

    void NeighborList::renew(const RegionSptr& region,
                             const ParticleManagerSptr& particle_manager)
    {
        Vector position = particle_manager->find_ID(owner)->get_position();
        double R = particle_manager->find_ID(owner)->get_R();

        std::size_t index = 0;
        neighbors.clear();
        for(auto iter = particle_manager->begin();
                iter != particle_manager->end(); ++iter)
        {
            if(region->min_dist(position, (*iter)->get_position()) < R)
            {
                neighbors[index] = (*iter)->get_ID();
                ++index;
            }
        }
        return;
    }

}
#endif
