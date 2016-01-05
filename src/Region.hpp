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

            bool out_of_range(const Vector& pos);
            Vector put_in_range(const Vector& pos);

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

    bool Region::out_of_range(const Vector& pos)
    {
        return !( (left <= pos[0] && pos[0] < right) &&
                 (lower <= pos[1] && pos[1] < upper));
    }

    Vector Region::put_in_range(const Vector& pos)
    {
        double pos_x = pos[0];
        while(pos_x < left)
            pos_x += width;
        while(right <= pos_x)
            pos_x -= width;

        double pos_y = pos[1];
        while(pos_y < lower)
            pos_y += height;
        while(upper <= pos_y)
            pos_y -= height;

        Vector retval = Vector(std::array<double, 2>({{pos_x, pos_y}}));
        if(out_of_range(retval))
            throw std::logic_error("Region:internal error");

        return retval;
    }
}
#endif
