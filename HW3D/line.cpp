//
// Created by bambuchachkin on 11/12/25.
//

#include "line.h"

line::line(point &point_1, point &point_2) {
    p1 = point_1;
    p2 = point_2;
    l = point_2.get_x() - point_1.get_x();
    m = point_2.get_y() - point_1.get_y();
    n = point_2.get_z() - point_1.get_z();
}

std::vector<int> line::get_pos_1() {
    return {p1.get_x(), p1.get_y(), p1.get_z()};
}

std::vector<int> line::get_l_m_n() {
    return {l, m, n};
}

int line::get_x1() const {
    return p1.get_x();
}

int line::get_y1() const {
    return p1.get_y();
}

int line::get_z1() const {
    return p1.get_z();
}

int line::get_l() const {
    return l;
}

int line::get_m() const {
    return m;
}

int line::get_n() const {
    return n;
}
