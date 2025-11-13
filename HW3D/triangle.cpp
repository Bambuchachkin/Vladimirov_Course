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
    std::vector<double> p_1 = p1.get_pos();
    std::vector<double> p_2 = p2.get_pos();
    std::vector<double> p_3 = p3.get_pos();
    double A = (p_2[1]-p_1[1])*(p_3[2]-p_1[2])-(p_2[2]-p_1[2])*(p_3[1]-p_1[1]);
    double B = (p_2[1]-p_1[1])*(p_3[2]-p_1[2])-(p_2[2]-p_1[2])*(p_3[1]-p_1[1]);
    double C = (p_2[1]-p_1[1])*(p_3[2]-p_1[2])-(p_2[2]-p_1[2])*(p_3[1]-p_1[1]);
    double D = (p_2[1]-p_1[1])*(p_3[2]-p_1[2])-(p_2[2]-p_1[2])*(p_3[1]-p_1[1]);
    plane = {A, B, C, D};
    t_box.root_x = std::min(point_1.get_x(), point_2.get_x(), point_3.get_x());
    t_box.root_y = std::min(point_1.get_y(), point_2.get_y(), point_3.get_y());
    t_box.root_z = std::min(point_1.get_z(), point_2.get_z(), point_3.get_z());
    t_box.x_size = std::max(point_1.get_x(), point_2.get_x(), point_3.get_x()) - t_box.root_x;
    t_box.y_size = std::max(point_1.get_y(), point_2.get_y(), point_3.get_y()) - t_box.root_y;
    t_box.z_size = std::max(point_1.get_z(), point_2.get_z(), point_3.get_z()) - t_box.root_z;
}

std::vector<double> triangle::get_plane() const{
    return plane;
}


std::vector<double> triangle::get_box() const{
    return {t_box.root_x, t_box.root_y, t_box.root_z,
    t_box.x_size, t_box.y_size, t_box.z_size};
}

std::vector<int> triangle::get_p_neighbors() const {
    return  possible_neighbors_numbers;
}

void triangle::add_possible_neighbor_number(int number){
    possible_neighbors_numbers.push_back(number);
}
