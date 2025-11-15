//
// Created by bambuchachkin on 11/12/25.
//

#include "triangle.h"
#include <algorithm>
#include <complex>

int triangle::T_NUMBER = 0;

// triangle::triangle(const point &point_1, const point &point_2, const point &point_3) : p1(point_1), p2(point_2), p3(point_3) {
//     number = T_NUMBER;
//     T_NUMBER++;
//     std::vector<double> p_1 = p1.get_pos();
//     std::vector<double> p_2 = p2.get_pos();
//     std::vector<double> p_3 = p3.get_pos();
//     double A = (p_2[1]-p_1[1])*(p_3[2]-p_1[2])-(p_2[2]-p_1[2])*(p_3[1]-p_1[1]);
//     double B = (p_2[2]-p_1[2])*(p_3[0]-p_1[0])-(p_2[0]-p_1[0])*(p_3[2]-p_1[2]);
//     double C = (p_2[0]-p_1[0])*(p_3[1]-p_1[1])-(p_2[1]-p_1[1])*(p_3[0]-p_1[0]);
//     // double D = (p_2[1]-p_1[1])*(p_3[2]-p_1[2])-(p_2[2]-p_1[2])*(p_3[1]-p_1[1]);
//     // plane = {A, B, C, D};
//     normal = {A, B, C};
//     t_box.root_x = std::min({point_1.get_x(), point_2.get_x(), point_3.get_x()});
//     t_box.root_y = std::min({point_1.get_y(), point_2.get_y(), point_3.get_y()});
//     t_box.root_z = std::min({point_1.get_z(), point_2.get_z(), point_3.get_z()});
//     t_box.x_size = std::max({point_1.get_x(), point_2.get_x(), point_3.get_x()}) - t_box.root_x;
//     t_box.y_size = std::max({point_1.get_y(), point_2.get_y(), point_3.get_y()}) - t_box.root_y;
//     t_box.z_size = std::max({point_1.get_z(), point_2.get_z(), point_3.get_z()}) - t_box.root_z;
//     vectors = {{p_1[0]-p_2[0], p_1[1]-p_2[1], p_1[2]-p_2[2]},
//                 {p_2[0]-p_3[0], p_2[1]-p_3[1], p_2[2]-p_3[2]},
//                 {p_3[0]-p_1[0], p_3[1]-p_1[1], p_3[2]-p_1[2]}};
// }

triangle::triangle(std::vector<double> nine_numbers) {
    p1 = {nine_numbers[0], nine_numbers[1], nine_numbers[2]};
    p2 = {nine_numbers[3], nine_numbers[4], nine_numbers[5]};
    p3 = {nine_numbers[6], nine_numbers[7], nine_numbers[8]};
    number = T_NUMBER;
    T_NUMBER++;
    double A = (p2[1]-p1[1])*(p3[2]-p1[2])-(p2[2]-p1[2])*(p3[1]-p1[1]);
    double B = (p2[2]-p1[2])*(p3[0]-p1[0])-(p2[0]-p1[0])*(p3[2]-p1[2]);
    double C = (p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0]);
    normal = {A, B, C};
    t_box.root_x = std::min({p1[0], p2[0], p3[0]});
    t_box.root_y = std::min({p1[1], p2[1], p3[1]});
    t_box.root_z = std::min({p1[2], p2[2], p3[2]});
    t_box.x_size = std::max({p1[0], p2[0], p3[0]}) - t_box.root_x;
    t_box.y_size = std::max({p1[1], p2[1], p3[1]}) - t_box.root_y;
    t_box.z_size = std::max({p1[2], p2[2], p3[2]}) - t_box.root_z;
    vectors = {{p1[0]-p2[0], p1[1]-p2[1], p1[2]-p2[2]},
                {p2[0]-p3[0], p2[1]-p3[1], p2[2]-p3[2]},
                {p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2]}};
}

std::vector<std::vector<double>> triangle::get_vectors() const {
    return vectors;
}

std::vector<std::vector<double>>  triangle::get_points() const {
    return {p1, p2, p3};
}

// std::vector<double> triangle::get_plane() const{
    // return plane;
// }

std::vector<double> triangle::get_normal() const{
    return {normal};
}

std::vector<double> triangle::get_box() const{
    return {t_box.root_x, t_box.root_y, t_box.root_z,
    t_box.x_size, t_box.y_size, t_box.z_size};
}

std::vector<int> triangle::get_p_neighbors() const {
    return  possible_neighbors_numbers;
}

void triangle::add_possible_neighbor_number(const int number){
    possible_neighbors_numbers.push_back(number);
}
