//
// Created by bambuchachkin on 11/12/25.
//

#ifndef LINE_H
#define LINE_H

#include "point.h"
#include <vector>

class line {
    point& p1, p2; // p_1 = (x1, y1, z1)
    // std::vector<int> p_1;
    // std::vector<int> p_2;
    double l, m, n; // x = x1+lt, y = y1+mt, z = z1+nt
public:
    line(point &point_1, point &point_2);

    std::vector<double> get_pos_1();
    std::vector<double> get_l_m_n();
    double get_x1() const;
    double get_y1() const;
    double get_z1() const;
    double get_l() const;
    double get_m() const;
    double get_n() const;

    void set_l(double new_l);
    void set_m(double new_m);
    void set_n(double new_n);
    void set_p_1_pos(double x, double y, double z);
};



#endif //LINE_H
