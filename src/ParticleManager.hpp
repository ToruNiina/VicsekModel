#ifndef VICSEK_PARTICLE_MANAGER
#define VICSEK_PARTICLE_MANAGER
#include "RandomNumberGenerator.hpp"
#include "Particle.hpp"
#include "Region.hpp"
#include <vector>

namespace vicsek
{
    class ParticleManager
    {
        public:
            using iterator = std::vector<ParticleSptr>::iterator;

        public:
            ParticleManager(const std::size_t num):particle_list(num)
            {}
            ~ParticleManager(){}

            void initialize(const RegionSptr& reg,
                            const double v0,
                            const double R,
                            const double noise,
                            RandomNumberGeneratorSptr& rng);

            ParticleSptr find_ID(const uInt id);

            bool empty(){return particle_list.empty();}
            std::size_t size(){return particle_list.size();}
            iterator begin(){return particle_list.begin();}
            iterator end(){return particle_list.end();}

        private:
            std::vector<ParticleSptr> particle_list;
    };
    using ParticleManagerSptr = std::shared_ptr<ParticleManager>;
}
#endif
