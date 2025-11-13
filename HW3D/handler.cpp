//
// Created by bambuchachkin on 11/13/25.
//

#include "handler.h"

handler::handler() {}

void handler::add_triangle(triangle &new_triangle) {
    triangle_map[triangle_map_size] = new_triangle;
    triangle_map_size++;
}

bool check_box_intersection(triangle& t_1, triangle& t_2) {
    std::vector<int> box_1 = t_1.get_box();
    std::vector<int> box_2 = t_2.get_box();
    if ((box_1[0]-box_2[3] <= box_2[0]) && (box_2[0] <= box_1[0]+box_1[3])) {
        if ((box_1[1]-box_2[4] <= box_2[1]) && (box_2[1] <= box_1[1]+box_1[4])) {
            if ((box_1[2]-box_2[5] <= box_2[2]) && (box_2[2] <= box_1[2]+box_1[5])) {
                return true;
            }
        }
    }
    return false;
}

void handler::filter() {
    for (int i = 0; i<triangle_map_size-1; i++) {
        for (int j = i+1; j<triangle_map_size; j++) {
            if (check_box_intersection(triangle_map[i], triangle_map[j])) {
                triangle_map[i].add_possible_neighbor_number(j);
                triangle_map[j].add_possible_neighbor_number(i);
            }
        }
    }
}
