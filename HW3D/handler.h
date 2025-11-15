//
// Created by bambuchachkin on 11/13/25.
//

#ifndef HANDLER_H
#define HANDLER_H

#include "triangle.h"
#include <unordered_map>

class handler {
    int triangle_map_size = 0;
    int number_of_triangles_intersections = 0;
    int potencial_intersections = 0;
    std::unordered_map<int, int> numbers_of_intersecting_triangles;
    std::unordered_map<int, triangle*> triangle_map;

    bool check_box_intersection(const triangle& t_1, const triangle& t_2);
public:
    handler();
    ~handler();

    void add_triangle(triangle* new_triangle);
    void filter();
    void find_intersections();

    void print_statistic() const;
    int get_number_of_triangles() const;
};



#endif //HANDLER_H
