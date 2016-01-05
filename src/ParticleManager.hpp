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
                            const RandomNumberGeneratorSptr& rng);

            ParticleSptr find_ID(const uInt id);
            const std::vector<ParticleSptr>& get_list(){return particle_list;}

            bool empty(){return particle_list.empty();}
            std::size_t size(){return particle_list.size();}
            iterator begin(){return particle_list.begin();}
            iterator end(){return particle_list.end();}

        private:
            std::vector<ParticleSptr> particle_list;
    };
    using ParticleManagerSptr = std::shared_ptr<ParticleManager>;

    void ParticleManager::initialize(const RegionSptr& reg,
                                     const double v0,
                                     const double R,
                                     const double noise,
                                     const RandomNumberGeneratorSptr& rng)
    {
        double width = reg->right - reg->left;
        double height = reg->upper - reg->lower;
        for(auto iter = particle_list.begin(); iter != particle_list.end();
                ++iter)
        {
            double theta = rng->get_uniform_dist();
            Vector pos = std::array<double, 2>{
                width * rng->get_uniform_dist(),
                height * rng->get_uniform_dist(),
            };
            *iter = ParticleSptr(new Particle(pos, v0, theta, R, noise));
        }
    }

    ParticleSptr ParticleManager::find_ID(const uInt id)
    {
        return particle_list.at(id - 1);
    }
}
#endif
