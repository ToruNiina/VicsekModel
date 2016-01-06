#ifndef VICSEK_PARTICLE_OBSERVER
#define VICSEK_PARTICLE_OBSERVER
#include "ParticleManager.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace vicsek
{
    class ParticleObserver
    {
        public:

            ParticleObserver(const std::string& filename)
                :output(filename)
            {}

            ~ParticleObserver()
            {
                output.close();
            }

            void write(const ParticleManagerSptr& particle_manager);
    
        private:
            std::ofstream output;
    };
    using ParticleObserverSptr = std::shared_ptr<ParticleObserver>;

}
#endif
