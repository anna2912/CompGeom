#include "geom/primitives/point.h"
#include <algorithm>
#include <math.h>

namespace geom {
namespace algorithms {
namespace point_in_poly {

    using geom::structures::point_type;

    bool BinarySearch(std::vector <point_type> vertices, point_type pt, bool newPts);
    bool CrossingNumber(std::vector <point_type> vertices, point_type pt);
    bool noSelfCrossings(std::vector <point_type> vertices);
    bool isConvex(std::vector <point_type> vertices);

}}}
