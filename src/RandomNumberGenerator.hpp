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
    using RandomNumberGeneratorSptr = std::shared_ptr<RandomNumberGenerator>;
}
#endif
