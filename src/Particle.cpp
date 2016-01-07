#include "Particle.hpp"

namespace vicsek
{
    uInt Particle::IDgenerator = 0;

    Particle::Particle(const Vector& pos,
                       const double v0,
                       const double th,
                       const double r,
                       const double e)
    : ID(++IDgenerator),
      v_0(v0), R(r), eta(e), theta(th), position(pos)
    {
        assert(-M_PI <= theta && theta <= M_PI);
    }

    void Particle::renew_position(const double mean_angle,
                                  const double rnd,
                                  const double dt,
                                  const RegionSptr& region)
    {
        theta = mean_angle + eta * rnd;

        while(theta < -M_PI)
            theta += 2e0 * M_PI;
        while(theta >= M_PI)
            theta -= 2e0 * M_PI;

        position += v_0 * dt *
            Vector(std::array<double, 2>({{cos(theta), sin(theta)}}));

        if(region->out_of_range(position))
            position = region->put_in_range(position);
        return;
    }

    std::string Particle::dump()
    {
        return std::string("vicsek Particle: position = (")
            + std::to_string(position[0]) + ", "
            + std::to_string(position[1]) + "), v0 = "
            + std::to_string(v_0) + ", eta = "
            + std::to_string(eta) + ", R = " + std::to_string(R);
    }

    std::ostream& operator<<(std::ostream& os, const Particle& p)
    {
        return os << p.get_position()[0] << " " << p.get_position()[1];
    }
}
