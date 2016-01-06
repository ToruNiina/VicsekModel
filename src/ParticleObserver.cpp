#include "ParticleObserver.hpp"
namespace vicsek
{
    void ParticleObserver::write(const ParticleManagerSptr& particle_manager)
    {
        for(auto iter = particle_manager->begin();
                iter != particle_manager->end(); ++iter)
        {
            const Vector pos = (*iter)->get_position();
            const double theta = (*iter)->get_theta();
            const double v0 = (*iter)->get_v_0();
            const Vector vel =
                Vector(std::array<double,2>(
                            {{v0 * cos(theta), v0 * sin(theta)}}
                            ));

            output << (*iter)->get_ID()       << " "
                   << pos[0] << " " << pos[1] << " "
                   << vel[0] << " " << vel[1] << std::endl;
        }
        output << std::endl;
        output << std::endl;
        return;
    }
}
