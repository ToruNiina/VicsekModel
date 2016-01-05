#ifndef VICSEK_REGION
#define VICSEK_REGION
#include "Defs.hpp"
#include "LinearAlgebra.hpp"

namespace vicsek
{
    //Rectangle only
    //periodic boundary
    class Region
    {
        public:
            Region(const double x_max, const double y_max)
                : upper(y_max), lower(0e0), right(x_max), left(0e0),
                  width(x_max), height(y_max)
            {}
            ~Region(){}

            Vector adjacent(const Vector& pos, const Vector& opp)const;
            double min_dist(const Vector& pos, const Vector& opp)const;

            const double upper;
            const double lower;
            const double right;
            const double left;
            const double width;
            const double height;
    };
    using RegionSptr = std::shared_ptr<Region>;

    Vector Region::adjacent(const Vector& pos, const Vector& opp) const
    {
        return Vector(std::array<double, 2>({{
                        std::min(fabs(pos[0] - opp[0]),
                                 fabs(pos[0] - opp[0] - width)),
                        std::min(fabs(pos[1] - opp[1]),
                                 fabs(pos[1] - opp[1] - height))
                     }}));
    }

    double Region::min_dist(const Vector& pos, const Vector& opp) const
    {
        return length(Vector(std::array<double, 2>({{
                        std::min(fabs(pos[0] - opp[0]),
                                 fabs(pos[0] - opp[0] - width)),
                        std::min(fabs(pos[1] - opp[1]),
                                 fabs(pos[1] - opp[1] - height))
                        }})));
    }
}
#endif
