#ifndef VICSEK_NEIGHBOR_LIST_HANDLER
#define VICSEK_NEIGHBOR_LIST_HANDLER
#include "NeighborList.hpp"

namespace vicsek
{
    class NeighborListHandler
    {
        public:
            using iterator = std::vector<NeighborListSptr>::iterator;
            using const_iterator = std::vector<NeighborListSptr>::const_iterator;

        public:
            NeighborListHandler(const RegionSptr& region,
                    const ParticleManagerSptr& particle_manager);
            ~NeighborListHandler(){}

            NeighborListSptr find_ID(const uInt id)
            {return neighbor_lists.at(id-1);}

            bool empty() const {return neighbor_lists.empty();}
            std::size_t size() const {return neighbor_lists.size();}
            iterator begin(){return neighbor_lists.begin();}
            iterator end(){return neighbor_lists.end();}
            const_iterator cbegin() const {return neighbor_lists.cbegin();}
            const_iterator cend() const {return neighbor_lists.cend();}

        private:
            std::vector<NeighborListSptr> neighbor_lists;
    };
    using NeighborListHandlerSptr = std::shared_ptr<NeighborListHandler>;

}
#endif
