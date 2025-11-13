//
// Created by bambuchachkin on 11/13/25.
//

#ifndef HANDLER_H
#define HANDLER_H

#include "triangle.h"
#include <unordered_map>

class handler {
    int triangle_map_size = 0;
    std::unordered_map<int, triangle&> triangle_map;
public:
    handler();

    void add_triangle(triangle& new_triangle);
    void filter();
};



#endif //HANDLER_H
