#ifndef VICSEK_PARTICLE
#define VICSEK_PARTICLE
#include "Defs.hpp"

namespace vicsek
{
    // Particle must be constructed by ParticleManager
    class Particle
    {
        public:
            Particle(const Vector& pos,
                     const double v0,
                     const double th,
                     const double r,
                     const double e)
            : ID(++IDgenerator),
              v_0(v0), R(r), eta(e), theta(th), position(pos)
            {
                assert(-M_PI <= theta && theta <= M_PI);
            }
            ~Particle(){}

            void renew_position(const double mean_angle, const double rnd);
            std::string dump();

            uInt get_ID() const {return ID;}
            Vector get_position()const{return position;}
            double get_v_0() const {return v_0;}
            double get_theta() const{return theta;}
            double get_R()   const {return R;}
            double get_eta() const {return eta;}

        private:
            static uInt IDgenerator;
            const uInt ID;
            const double v_0; // velocity(immutable)
            const double R;   // sight(immutable)
            const double eta; // noize intensity(immutable)
            double theta;     // direction [-pi, pi)
            Vector position;  // position(cartesian coordinate)
    };
    using ParticleSptr = std::shared_ptr<Particle>;

    uInt Particle::IDgenerator = 0;

    void Particle::renew_position(const double mean_angle, const double rnd)
    {
        theta = mean_angle + eta * rnd;
        while(theta < -M_PI)
            theta += 2e0 * M_PI;
        while(theta >= M_PI)
            theta -= 2e0 * M_PI;

        position +=
            v_0 * Vector(std::array<double, 2>({{cos(theta), sin(theta)}}));
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
#endif
