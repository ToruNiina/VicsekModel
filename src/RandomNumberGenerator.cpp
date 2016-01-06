#include "RandomNumberGenerator.hpp"

namespace vicsek
{
    double RandomNumberGenerator::get_uniform_dist()
    {
        return uniform(mersenne_twister);
    }

    double RandomNumberGenerator::get_gaussian_dist(const double mean,
                                                    const double sigma)
    {
        return mean + sigma * gaussian(mersenne_twister);
    }

    Vector RandomNumberGenerator::get_random_vector()
    {
        return Vector(std::array<double, 2>({{get_gaussian_dist(),
                                              get_gaussian_dist()}}));
    }

    std::string RandomNumberGenerator::dump() const
    {
        return std::string("RandomNumberGenerator: seed = ") +
               std::to_string(seed);
    }
}
