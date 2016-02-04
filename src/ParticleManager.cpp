#include "ParticleManager.hpp"

namespace vicsek
{
    void ParticleManager::initialize(const RegionSptr& reg,
                                     const double v0,
                                     const double R,
                                     const double noise,
                                     RandomNumberGeneratorSptr& rng)
    {
        const double width = reg->width;
        const double height = reg->height;
        for(auto iter = particle_list.begin(); iter != particle_list.end();
                ++iter)
        {
            double theta = (2e0 * rng->get_uniform_dist() - 1e0) * M_PI;
            Vector pos = std::array<double, 2>({{
                width * rng->get_uniform_dist(),
                height * rng->get_uniform_dist(),
            }});
            *iter = ParticleSptr(new Particle(pos, v0, theta, R, noise));
        }
    }

    ParticleSptr ParticleManager::find_ID(const uInt id)
    {
        return particle_list.at(id - 1);
    }
}
