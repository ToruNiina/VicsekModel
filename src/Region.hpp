#ifndef VICSEK_REGION
#define VICSEK_REGION
#include "Defs.hpp"

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
}
#endif
