// Computing intersection points among curves using the sweep line.
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arr_polyline_traits_2.h>
#include <CGAL/Sweep_line_2_algorithms.h>
#include <vector>
#include <list>

#include "cgal_intersection.h"

typedef CGAL::Cartesian<double>                    Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel>              Segment_traits;
typedef CGAL::Arr_polyline_traits_2<Segment_traits>     Traits;
typedef Traits::Point_2                                 Point;
typedef Traits::Curve_2                                 Polyline;

extern "C" int find_intersections_of_curves(
    coordinate *curve_1, long curve_1_size,
    coordinate *curve_2, long curve_2_size,
    coordinate *intersections, int max_num_of_intersections)
{

    std::vector<Point> points_1(curve_1_size);
    for (long i_1 = 0; i_1 < curve_1_size; i_1++)
        points_1[i_1] = Point(curve_1[i_1].x, curve_1[i_1].y);
    Polyline  polyline_1(points_1.begin(), points_1.end());

    std::vector<Point> points_2(curve_2_size);
    for (long i_2 = 0; i_2 < curve_2_size; i_2++)
        points_2[i_2] = Point(curve_2[i_2].x, curve_2[i_2].y);
    Polyline  polyline_2(points_2.begin(), points_2.end());

    Polyline polylines[] = {polyline_1, polyline_2};
    std::list<Point> intersection_points;
    CGAL::compute_intersection_points(polylines, polylines + 2,
                                      std::back_inserter(intersection_points));

    int num_of_intersections = intersection_points.size();
    Point intersection_point;
    for (int j = 0; j < num_of_intersections; j++){
        if (j == max_num_of_intersections)
            break;
        intersection_point = intersection_points.front();
        intersections[j].x = intersection_point.x();
        intersections[j].y = intersection_point.y();
        intersection_points.pop_front();
    }

    return num_of_intersections;
}