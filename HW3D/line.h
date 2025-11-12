//
// Created by bambuchachkin on 11/12/25.
//

#ifndef LINE_H
#define LINE_H

#include "point.h"

class line {
    point& p1, p2; // p_1 = (x1, y1, z1)
    int l, m, n; // x = x1+lt, y = y1+mt, z = z1+nt
public:
    line(point &point_1, point &point_2);
    int get_x1() const;
    int get_y1() const;
    int get_z1() const;
    int get_l() const;
    int get_m() const;
    int get_n() const;
};



#endif //LINE_H
