#ifndef VICSEK_NEIGHBOR_LIST_HANDLER
#define VICSEK_NEIGHBOR_LIST_HANDLER
#include "NeighborList.hpp"

namespace vicsek
{
    class NeighborListHandler
    {
        public:
            using iterator = std::vector<NeighborListSptr>::iterator;

        public:
            NeighborListHandler(const RegionSptr& region,
                    const ParticleManagerSptr& particle_manager);
            ~NeighborListHandler(){}

            NeighborListSptr find_ID(const uInt id)
            {return neighbor_lists.at(id-1);}

            bool empty(){return neighbor_lists.empty();}
            std::size_t size(){return neighbor_lists.size();}
            iterator begin(){return neighbor_lists.begin();}
            iterator end(){return neighbor_lists.end();}

        private:
            std::vector<NeighborListSptr> neighbor_lists;
    };
    using NeighborListHandlerSptr = std::shared_ptr<NeighborListHandler>;

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
#endif
