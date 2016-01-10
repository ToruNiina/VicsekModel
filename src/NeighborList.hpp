#ifndef VICSEK_NEIGHBOR_LIST
#define VICSEK_NEIGHBOR_LIST
#include "ParticleManager.hpp"
#include <vector>

namespace vicsek
{
    class NeighborList
    {
        public:
            using iterator = std::vector<uInt>::iterator;
            using const_iterator = std::vector<uInt>::const_iterator;

        public:
            NeighborList(const ParticleSptr& particle,
                         const RegionSptr& region,
                         const ParticleManagerSptr& particle_manager);

            void renew(const RegionSptr& region,
                       const ParticleManagerSptr& particle_manager);

            const uInt get_ownerID() const {return owner;}

            bool empty() const {return neighbors.empty();}
            std::size_t size() const {return particle_size;}
            iterator begin(){return neighbors.begin();}
            iterator end(){return end_of_list;}
            const_iterator cbegin() const {return neighbors.cbegin();}
            const_iterator cend() const
            {return static_cast<const_iterator>(end_of_list);}

        private:

            const uInt owner;
            std::size_t particle_size;
            iterator end_of_list;
            std::vector<uInt> neighbors;
    };

    using NeighborListSptr = std::shared_ptr<NeighborList>;
}
#endif
