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
    std::unordered_map<int, int> numbers_of_intersecting_triangles = 0;
    std::unordered_map<int, triangle&> triangle_map;
public:
    handler();

    void add_triangle(triangle& new_triangle);
    void filter();
    void find_intersections();
};



#endif //HANDLER_H
