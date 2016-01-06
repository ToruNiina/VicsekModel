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
}
#endif
