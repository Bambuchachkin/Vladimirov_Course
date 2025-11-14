//
// Created by bambuchachkin on 11/12/25.
//

#include "point.h"

point::point(double x, double y, double z) : p_x(x), p_y(y), p_z(z) {}

std::vector<double> point::get_pos() const {
    return {p_x, p_y, p_z};
}


double point::get_x() const {
    return p_x;
}

double point::get_y() const {
    return p_y;
}

double point::get_z() const {
    return p_z;
}

void point::set_x(double new_x) {
    p_x = new_x;
}

void point::set_y(double new_y) {
    p_x = new_y;
}

void point::set_z(double new_z) {
    p_x = new_z;
}
