//
// Created by bambuchachkin on 11/13/25.
//

#include "handler.h"
#include <cmath>
#include <iostream>

handler::handler() {}

handler::~handler() {
    for (auto it = triangle_map.begin(); it!=triangle_map.end(); it++) {
        delete it->second;
    }
}


void handler::add_triangle(triangle *new_triangle) {
    triangle_map[triangle_map_size] = new_triangle;
    triangle_map_size++;
}

bool check_box_intersection(const triangle& t_1, const triangle& t_2) {
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
            if (check_box_intersection(*triangle_map[i], *triangle_map[j])) {
                triangle_map[i]->add_possible_neighbor_number(j);
                // triangle_map[j].add_possible_neighbor_number(i); //не нужно тк проверка идет по порядку и номер i проверяется раньше
            }
        }
    }
}

double scalar_product(const std::vector<double>& v1, const std::vector<double>& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

std::vector<double> vector_product(const std::vector<double>& v1, const std::vector<double>& v2) {
    return {
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    };
}

// Функция проецирует треугольник на заданную ось и возвращает интервал проекции
// Вход: треугольник и ось проекции
// Выход: вектор {min_projection, max_projection}
std::vector<double> project_triangle_on_line(const triangle& tr, const std::vector<double>& line) {
    std::vector<std::vector<double>> vertices = tr.get_points();
    double norm = std::sqrt(scalar_product(line, line));
    double min_proj = scalar_product(vertices[0], line) / norm;
    double max_proj = min_proj;
    double proj = 0;

    for (int i = 1; i<3; i++) {
        proj = scalar_product(vertices[i], line) / norm;
        if (proj>max_proj) {
            max_proj = proj;
        } else if (proj<min_proj) {
            min_proj = proj;
        }
    }
    return {min_proj, max_proj};
}

bool check_intervals_intersection(const std::vector<double>& int_1, const std::vector<double>& int_2) {
    double min1 = int_1[0], max1 = int_1[1];
    double min2 = int_2[0], max2 = int_2[1];
    return !(max1 < min2 || max2 < min1);
}

// Функция генерирует все потенциальные разделяющие оси для SAT теста
// Для двух треугольников нужно проверить 11 осей:
// - 2 нормали треугольников
// - 9 осей из векторных произведений ребер
// Вход: два треугольника
// Выход: вектор из 11 осей (единичных векторов)
std::vector<std::vector<double>> get_separating_lines(const triangle& tr_1, const triangle& tr_2) {
    std::vector<std::vector<double>> v_tr_1 = tr_1.get_vectors();
    std::vector<std::vector<double>> v_tr_2 = tr_2.get_vectors();
    std::vector<std::vector<double>> lines = {tr_1.get_normal(), tr_2.get_normal()};
    for (int i =0; i<3; i++) {
        for (int j =0; j<3; j++) {
            lines.push_back(vector_product(v_tr_1[i], v_tr_2[j]));
        }
    }
    return lines;
}

// Основная функция проверки пересечения треугольников методом SAT
bool check_triangles_intersection(const triangle& tr_1, const triangle& tr_2) {
    std::vector<std::vector<double>> lines = get_separating_lines(tr_1, tr_2);
    for (int i = 0; i<lines.size(); i++) {
        if (!check_intervals_intersection(project_triangle_on_line(tr_1, lines[i]),
            project_triangle_on_line(tr_2, lines[i]))) {
            return false;
        }
    }
    return true;
}

void handler::find_intersections() {
    filter();
    std::vector<int> p_neighbors;
    for (int i = 0; i<triangle_map_size; i++) { // для каждого треугольника рассмотрим подозрительных соседей
        p_neighbors = triangle_map[i]->get_p_neighbors();
        for (int j = 0; j<p_neighbors.size(); j++) {
            if (check_triangles_intersection(*triangle_map[i], *triangle_map[p_neighbors[j]])) {
                number_of_triangles_intersections ++;
                numbers_of_intersecting_triangles[i] = 1;
                numbers_of_intersecting_triangles[p_neighbors[j]] = 1;
            }
        }
    }
}
