#include "Region.hpp"

namespace vicsek
{
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

    std::array<Vector, 8> Region::periodic_1st(const Vector& opp) const
    {/* 8 1 2 *
      * 7 0 3 *
      * 6 5 4 */
        std::array<Vector, 8> retval;
        for(int i(1); i < 9; ++i)
        {
            const double Xpos
                = ((2 <= i && i <= 4) ? opp[0] + width :
                        (6 <= i && i <= 8) ? opp[0] - width : opp[0]);
            const double Ypos
                = ((i == 1 || i == 2 || i == 8) ? opp[1] + height :
                        (4 <= i && i <= 6) ? opp[1] - height : opp[1]);
            retval.at(i-1) = (Vector(std::array<double, 2>({{Xpos, Ypos}})));
        }

        return retval;
    }

    bool Region::out_of_range(const Vector& pos)
    {
        return !(( left <= pos[0] && pos[0] < right) &&
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
            throw std::logic_error("Region:internal error. x = "
                    + std::to_string(pos_x) + ", y = "
                    + std::to_string(pos_y) + " and region is "
                    + std::to_string(left) + " < x < "
                    + std::to_string(right) + ", "
                    + std::to_string(lower) + " < y < "
                    + std::to_string(upper));

        return retval;
    }

}
