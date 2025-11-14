//
// Created by bambuchachkin on 11/13/25.
//

#include "handler.h"
#include <cmath>
#include <iostream>

handler::handler() {}

void handler::add_triangle(triangle &new_triangle) {
    triangle_map[triangle_map_size] = new_triangle;
    triangle_map_size++;
}

bool check_box_intersection(triangle& t_1, triangle& t_2) {
    std::vector<double> box_1 = t_1.get_box();
    std::vector<double> box_2 = t_2.get_box();
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
                // triangle_map[j].add_possible_neighbor_number(i); //не нужно тк проверка идет по порядку и номер i проверяется раньше
            }
        }
    }
}

double scalar_product(const std::vector<double>& v1, const std::vector<double>& v2) const {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

std::vector<double> vector_product(const std::vector<double>& v1, const std::vector<double>& v2) const {
    return {
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    };
}

double handler::modul_of_vector(const std::vector<double>& v) const {
    return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

// Функция проецирует треугольник на заданную ось и возвращает интервал проекции
// Вход: треугольник и ось проекции (единичный вектор)
// Выход: вектор {min_projection, max_projection}
std::vector<double> handler::projectTriangleOnAxis(const triangle& tri, const std::vector<double>& axis) const {
    // Получаем bounding box треугольника
    std::vector<double> box = tri.get_box();

    // Создаем 8 вершин bounding box'а
    std::vector<std::vector<double>> vertices = {
        {box[0], box[1], box[2]},                      // min corner
        {box[0] + box[3], box[1], box[2]},            // min_x + size_x
        {box[0], box[1] + box[4], box[2]},            // min_y + size_y
        {box[0], box[1], box[2] + box[5]},            // min_z + size_z
        {box[0] + box[3], box[1] + box[4], box[2]},   // min_x + size_x, min_y + size_y
        {box[0] + box[3], box[1], box[2] + box[5]},   // min_x + size_x, min_z + size_z
        {box[0], box[1] + box[4], box[2] + box[5]},   // min_y + size_y, min_z + size_z
        {box[0] + box[3], box[1] + box[4], box[2] + box[5]} // max corner
    };

    // Инициализируем min и max значения
    double min_proj = std::numeric_limits<double>::max();
    double max_proj = std::numeric_limits<double>::lowest();

    // Проецируем каждую вершину на ось и находим min/max
    for (const auto& vertex : vertices) {
        double projection = dotProduct(vertex, axis);
        if (projection < min_proj) min_proj = projection;
        if (projection > max_proj) max_proj = projection;
    }

    return {min_proj, max_proj};
}

bool check_triangles_intersection(triangle& tr_1, triangle& tr_2) {
    return false;
}
void handler::find_intersections() {
    std::vector<int> p_neighbors;
    for (int i = 0; i<triangle_map_size; i++) { // для каждого треугольника рассмотрим подозрительных соседей
        p_neighbors = triangle_map[i].get_p_neighbors();
        for (int j = 0; j<p_neighbors.size(); j++) {
            if (check_box_intersection(triangle_map[i], triangle_map[j])) {
                number_of_triangles_intersections ++;
                numbers_of_intersecting_triangles[i] = 1;
                numbers_of_intersecting_triangles[j] = 1;
            }
        }
    }
}
