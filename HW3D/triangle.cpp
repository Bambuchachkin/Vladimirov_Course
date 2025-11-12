//
// Created by bambuchachkin on 11/12/25.
//

#include "triangle.h"
#include <algorithm>

int triangle::T_NUMBER = 0;

triangle::triangle(point &point_1, point &point_2, point &point_3) {
    number = T_NUMBER;
    T_NUMBER++;
    p1 = point_1;
    p2 = point_2;
    p3 = point_3;
    t_box.root_x = std::min(point_1.get_x(), point_2.get_x(), point_3.get_x());
    t_box.root_y = std::min(point_1.get_y(), point_2.get_y(), point_3.get_y());
    t_box.root_z = std::min(point_1.get_z(), point_2.get_z(), point_3.get_z());
    t_box.x_size = std::max(point_1.get_x(), point_2.get_x(), point_3.get_x()) - t_box.root_x;
    t_box.y_size = std::max(point_1.get_y(), point_2.get_y(), point_3.get_y()) - t_box.root_y;
    t_box.z_size = std::max(point_1.get_z(), point_2.get_z(), point_3.get_z()) - t_box.root_z;
}
