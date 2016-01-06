#include "System.hpp"

namespace vicsek
{
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
