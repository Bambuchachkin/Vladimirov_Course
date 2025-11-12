//
// Created by bambuchachkin on 11/12/25.
//

#include "point.h"

point::point(int x, int y, int z) : p_x(x), p_y(y), p_z(z) {}

int point::get_x() const {
    return p_x;
}

int point::get_y() const {
    return p_y;
}

int point::get_z() const {
    return p_z;
}
