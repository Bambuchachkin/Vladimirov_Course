//
// Created by bambuchachkin on 11/13/25.
//

#include "handler.h"
#include <cmath>

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
                triangle_map[j].add_possible_neighbor_number(i);
            }
        }
    }
}

point find_point_on_intersection_line(const std::vector<double>& plane1,
                                     const std::vector<double>& plane2) {
    double A1 = plane1[0], B1 = plane1[1], C1 = plane1[2], D1 = plane1[3];
    double A2 = plane2[0], B2 = plane2[1], C2 = plane2[2], D2 = plane2[3];
    // Пытаемся найти точку, фиксируя одну координату
    double det = A1 * B2 - A2 * B1;
    if (std::abs(det) > 1e-10) {
        double z = 0;
        double x = (B1 * (-D2) - B2 * (-D1)) / det;
        double y = (A2 * (-D1) - A1 * (-D2)) / det;
        return point(x, y, z);
    }
    else {
        // Если определитель близок к нулю, пробуем y = 0
        det = A1 * C2 - A2 * C1;
        if (std::abs(det) > 1e-10) {
            double y = 0;
            double x = (C1 * (-D2) - C2 * (-D1)) / det;
            double z = (A2 * (-D1) - A1 * (-D2)) / det;
            return point(x, y, z);
        }
        else {
            // Пробуем x = 0
            det = B1 * C2 - B2 * C1;
            if (std::abs(det) > 1e-10) {
                double x = 0;
                double y = (C1 * (-D2) - C2 * (-D1)) / det;
                double z = (B2 * (-D1) - B1 * (-D2)) / det;
                return point(x, y, z);
            }
            else {
                // Плоскости параллельны или совпадают
                return point(NAN, NAN, NAN);
            }
        }
    }
}

point find_lines_intersection(const line& line1, const line& line2) {
    // line1: x = x1 + l1*t, y = y1 + m1*t, z = z1 + n1*t
    // line2: x = x2 + l2*s, y = y2 + m2*s, z = z2 + n2*s
    double x1 = line1.get_x1(), y1 = line1.get_y1(), z1 = line1.get_z1();
    double l1 = line1.get_l(), m1 = line1.get_m(), n1 = line1.get_n();
    double x2 = line2.get_x1(), y2 = line2.get_y1(), z2 = line2.get_z1();
    double l2 = line2.get_l(), m2 = line2.get_m(), n2 = line2.get_n();
    double det = l1 * (-m2) - (-l2) * m1;  // Определитель матрицы коэффициентов
    if (std::abs(det) < 1e-10) {
        // Прямые параллельны или совпадают в плоскости XY
        // Проверяем третье уравнение
        det = l1 * (-n2) - (-l2) * n1;
        if (std::abs(det) < 1e-10) {
            // Прямые параллельны
            return point(NAN, NAN, NAN);
        }
        // Решаем используя x и z координаты
        // x1 + l1*t = x2 + l2*s  => l1*t - l2*s = x2 - x1
        // z1 + n1*t = z2 + n2*s  => n1*t - n2*s = z2 - z1
        double A = l1, B = -l2, C = x2 - x1;
        double D = n1, E = -n2, F = z2 - z1;
        det = A * E - B * D;
        if (std::abs(det) < 1e-10) {
            return point(NAN, NAN, NAN);
        }
        double t = (C * E - B * F) / det;
        double s = (A * F - C * D) / det;
        // Проверяем согласованность по y координате
        double y_intersect1 = y1 + m1 * t;
        double y_intersect2 = y2 + m2 * s;
        if (std::abs(y_intersect1 - y_intersect2) > 1e-10) {
            // Прямые скрещиваются
            return point(NAN, NAN, NAN);
        }
        double x = x1 + l1 * t;
        double y = y1 + m1 * t;
        double z = z1 + n1 * t;
        return point(x, y, z);
    }
    else {
        // Решаем систему для t и s
        double t = ((x2 - x1) * (-m2) - (y2 - y1) * (-l2)) / det;
        double s = (l1 * (y2 - y1) - m1 * (x2 - x1)) / det;
        // Проверяем согласованность по z координате
        double z_intersect1 = z1 + n1 * t;
        double z_intersect2 = z2 + n2 * s;
        if (std::abs(z_intersect1 - z_intersect2) > 1e-10) {
            // Прямые скрещиваются
            return point(NAN, NAN, NAN);
        }
        double x = x1 + l1 * t;
        double y = y1 + m1 * t;
        double z = z1 + n1 * t;
        return point(x, y, z);
    }
}

void handler::find_intersections() {
    line intersection_line(NAN, NAN);
    point inter_1_tr_1_and_line(NAN, NAN);
    point inter_2_tr_1_and_line(NAN, NAN);
    point inter_1_tr_2_and_line(NAN, NAN);
    point inter_2_tr_2_and_line(NAN, NAN);
    std::vector<double> plane_1;
    std::vector<double> plane_2;
    std::vector<int> p_neighbors;
    for (int i = 0; i<triangle_map_size; i++) { // для каждого треугольника рассмотри подозрительных соседей
        plane_1 = triangle_map[i].get_plane();
        p_neighbors = triangle_map[i].get_p_neighbors();
        for (int j = 0; j<p_neighbors.size(); j++) {
            plane_2 = triangle_map[p_neighbors[j]].get_plane();
            intersection_line.set_l(plane_1[1]*plane_2[2]-plane_1[2]*plane_2[1]); // находим прямую по которой пересекаются плоскости треугольников
            intersection_line.set_m(plane_1[2]*plane_2[0]-plane_1[0]*plane_2[2]);
            intersection_line.set_n(plane_1[0]*plane_2[1]-plane_1[1]*plane_2[0]);
            point p_1 = find_point_on_intersection_line(plane_1, plane_2);
            intersection_line.set_p_1_pos(p_1.get_x(), p_1.get_y(), p_1.get_z());


        }
    }
}
