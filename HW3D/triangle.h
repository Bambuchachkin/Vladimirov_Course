//
// Created by bambuchachkin on 11/12/25.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include "point.h"
#include <vector>

class triangle {
    int number;
    static int T_NUMBER;
    point& p1, p2, p3;
    struct box {
        int root_x, root_y, root_z;
        int x_size, y_size, z_size;
    };
    box t_box;
    std::vector<int> possible_neighbors_numbers;
public:
    triangle(point &point_1, point &point_2, point &point_3);

    std::vector<int> get_box();
    void add_possible_neighbor_number(int number);
};



#endif //TRIANGLE_H
