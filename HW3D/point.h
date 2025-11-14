//
// Created by bambuchachkin on 11/12/25.
//

#ifndef POINT_H
#define POINT_H
#include <vector>


class point {
    double p_x, p_y, p_z;
public:
    point(double x, double y, double z);

    std::vector<double> get_pos() const;
    double get_x() const;
    double get_y() const;
    double get_z() const;

    void set_x(double new_x);
    void set_y(double new_x);
    void set_z(double new_x);
};



#endif //POINT_H
