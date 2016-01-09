#ifndef VICSEK_PARTICLE
#define VICSEK_PARTICLE
#include "Region.hpp"

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
                     const double e);
            ~Particle(){}

            void renew_position(const double mean_angle,
                                const double rnd,
                                const double dt,
                                const RegionSptr& region);
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
}
#endif
