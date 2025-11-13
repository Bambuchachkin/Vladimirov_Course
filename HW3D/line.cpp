//
// Created by bambuchachkin on 11/12/25.
//

#include "line.h"

line::line(point &point_1, point &point_2) : p1(point_1), p2(point_2) {
    l = point_2.get_x() - point_1.get_x();
    m = point_2.get_y() - point_1.get_y();
    n = point_2.get_z() - point_1.get_z();
}

std::vector<double> line::get_pos_1() {
    return {p1.get_x(), p1.get_y(), p1.get_z()};
}

std::vector<double> line::get_l_m_n() {
    return {l, m, n};
}

double line::get_x1() const {
    return p1.get_x();
}

double line::get_y1() const {
    return p1.get_y();
}

double line::get_z1() const {
    return p1.get_z();
}

double line::get_l() const {
    return l;
}

double line::get_m() const {
    return m;
}

double line::get_n() const {
    return n;
}

void line::set_l(double new_l) {
    l = new_l;
}

void line::set_m(double new_m) {
    m = new_m;
}

void line::set_n(double new_n) {
    n = new_n;
}
void line::set_p_1_pos(double x, double y, double z) {
    p1.set_x(x);
    p1.set_y(y);
    p1.set_z(z);
    p2.set_x(x+l);
    p2.set_y(y+m);
    p2.set_z(y+m);
}

