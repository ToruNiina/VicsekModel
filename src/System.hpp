#ifndef VICSEK_SYSTEM
#define VICSEK_SYSTEM
#include "RandomNumberGenerator.hpp"
#include "NeighborListHandler.hpp"
#include "ParticleManager.hpp"
#include "ParticleObserver.hpp"
#include "TimeStepper.hpp"
#include "Region.hpp"

namespace vicsek
{
    class System
    {
        public:
            System(){}
            ~System(){}

            void init();
            void run();

            void set_seed(const int s)
            {seed = s;}
            void set_maxstep(const uInt max)
            {maxstep = max;}
            void set_neighborlist_renew_step(const uInt nlrnw)
            {nlist_renew_step = nlrnw;}
            void set_observe_step(const uInt obs)
            {observe_step = obs;}
            void set_output_file(const std::string& filename)
            {output_filename = filename;}

            void set_region(const double width, const double height);
            void set_particle_number(const uInt num)
            {particle_number = num;}
            void set_particle_state(const double velocity,
                                    const double sight,
                                    const double noise);

        private:

            int seed = 100;
            uInt maxstep = 1000;
            uInt nlist_renew_step = 1;
            uInt observe_step = 1;
            uInt particle_number = 1000;
            double box_width = 5e1;
            double box_height = 5e1;
            double particle_velocity = 1e0;
            double cutoff_distance = 2.5;
            double noise_intensity = M_PI;
            std::string output_filename = std::string("vicsek.dat");
            RegionSptr region;
            TimeStepperSptr time_stepper;
            ParticleManagerSptr particle_manager;
            ParticleObserverSptr particle_observer;
            NeighborListHandlerSptr neighbor_list_handler;
            RandomNumberGeneratorSptr random_number_generator;
    };
}
#endif
