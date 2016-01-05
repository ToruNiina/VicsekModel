#ifndef VICSEK_RANDOM_NUMBER_GENERATOR
#define VICSEK_RANDOM_NUMBER_GENERATOR
#include <random>
#include <string>
#include "Defs.hpp"

namespace vicsek
{
    class RandomNumberGenerator
    {
        public:
            RandomNumberGenerator(const int s)
                : seed(s), mersenne_twister(s), gaussian(0e0,1e0)
            {}
            ~RandomNumberGenerator(){}

            double get_uniform_dist();
            double get_gaussian_dist(const double mean = 0e0,
                                     const double sigma = 1e0);
            Vector get_random_vector();

            std::string dump() const;
            int get_seed() const {return seed;}

        private:
            const int seed;
            std::mt19937 mersenne_twister;
            std::uniform_real_distribution<> uniform;
            std::normal_distribution<> gaussian;
    };

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

    using RandomNumberGeneratorSptr = std::shared_ptr<RandomNumberGenerator>;
}
#endif
