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
            uInt maxstep = 100;
            uInt nlist_renew_step = 1;
            uInt observe_step = 1;
            uInt particle_number = 1000;
            double box_width = 1e2;
            double box_height = 1e2;
            double particle_velocity = 1e0;
            double cutoff_distance = 5e0;
            double noise_intensity = M_PI / 4e0;
            std::string output_filename = std::string("vicsek.dat");
            RegionSptr region;
            TimeStepperSptr time_stepper;
            ParticleManagerSptr particle_manager;
            ParticleObserverSptr particle_observer;
            NeighborListHandlerSptr neighbor_list_handler;
            RandomNumberGeneratorSptr random_number_generator;
    };

    void System::init()
    {
        random_number_generator =
            RandomNumberGeneratorSptr(new RandomNumberGenerator(seed));

        region =
            RegionSptr(new Region(box_width, box_height));

        particle_manager =
            ParticleManagerSptr(new ParticleManager(particle_number));
        particle_manager->initialize(region,
                particle_velocity,
                cutoff_distance,
                noise_intensity,
                random_number_generator
                );

        particle_observer =
            ParticleObserverSptr(new ParticleObserver(output_filename));

        neighbor_list_handler =
            NeighborListHandlerSptr(
                    new NeighborListHandler(region, particle_manager)
                    );

        time_stepper = TimeStepperSptr(new TimeStepper());

        std::cout << "system initialized" << std::endl;
        return;
    }

    void System::run()
    {
        particle_observer->write(particle_manager);
        for(uInt timestep = 0; timestep < maxstep; ++timestep)
        {
            time_stepper->move_particle(region,
                    particle_manager,
                    neighbor_list_handler,
                    random_number_generator
                );

            if(timestep % nlist_renew_step == 0)
                time_stepper->renew_neighborlist(region,
                        particle_manager,
                        neighbor_list_handler
                    );
            if(timestep % observe_step == 0)
                particle_observer->write(particle_manager);

            if(timestep % (maxstep / 10) == 0)
                std::cout << "progress: " << timestep / (maxstep / 100) << "%."
                          << std::endl;
        }
        return;
    }

    void System::set_region(const double width, const double height)
    {
        box_width = width;
        box_height = height;
        return;
    }

    void System::set_particle_state(const double velocity,
                                    const double sight,
                                    const double noise)
    {
        particle_velocity = velocity;
        cutoff_distance = sight;
        noise_intensity = noise;
        return;
    }
}
#endif
