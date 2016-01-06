include_directories("/Users/niina/cpp/math/LinearAlgebra")
add_definitions("-std=c++11 -O3 -Wall")

set (CPP_FILES
    RandomNumberGenerator.cpp Region.cpp
    Particle.cpp ParticleManager.cpp ParticleObserver.cpp
    NeighborList.cpp NeighborListHandler.cpp
    TimeStepper.cpp System.cpp
    )

add_executable(main main.cpp ${CPP_FILES})
