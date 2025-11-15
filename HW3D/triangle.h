//
// Created by bambuchachkin on 11/12/25.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "line.h"
#include "point.h"
#include <vector>

class triangle {
    int number;
    static int T_NUMBER;
    std::vector<double> p1, p2, p3;
    // point p1, p2, p3;
    struct box {
        double root_x, root_y, root_z;
        double x_size, y_size, z_size;
    };
    box t_box;
    // std::vector<double> plane; // Ax + By + Cz + D = 0
    std::vector<double> normal;
    std::vector<std::vector<double>> vectors; //p1-p2, p2-p3, p3-p1
    std::vector<int> possible_neighbors_numbers;
public:
    // triangle(const point &point_1, const point &point_2, const point &point_3);
    triangle(std::vector<double> nine_numbers);

    std::vector<std::vector<double>> get_vectors() const;
    std::vector<std::vector<double>> get_points() const;
    // std::vector<double> get_plane() const;
    std::vector<double> get_normal() const;
    std::vector<double> get_box() const;
    std::vector<int> get_p_neighbors() const;

    void add_possible_neighbor_number(int number);
};



#endif //TRIANGLE_H
