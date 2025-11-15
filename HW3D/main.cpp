#include "handler.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Функция для ввода треугольников с клавиатуры
void input_triangles_from_user(handler& h) {
    int num_triangles;
    std::cout << "Введите количество треугольников: ";
    std::cin >> num_triangles;

    std::cout << "Введите " << num_triangles << " треугольников (по 9 чисел на треугольник):" << std::endl;
    std::cout << "Формат: x1 y1 z1 x2 y2 z2 x3 y3 z3" << std::endl;

    for (int i = 0; i < num_triangles; i++) {
        std::vector<double> coords(9);
        std::cout << "Треугольник " << (i + 1) << ": ";
        for (int j = 0; j < 9; j++) {
            std::cin >> coords[j];
        }
        h.add_triangle(new triangle(coords));
    }
}

// Функция для генерации ГАРАНТИРОВАННО пересекающихся треугольников в группах
void generate_guaranteed_intersecting_groups(handler& h, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Генерация " << count << " ГАРАНТИРОВАННО пересекающихся треугольников в группах..." << std::endl;

    // Создаем небольшое количество групп
    int num_groups = 10;
    int triangles_per_group = count / num_groups;

    std::uniform_real_distribution<> offset_dis(-1.0, 1.0);   // Маленькое случайное смещение
    std::uniform_real_distribution<> size_dis(8.0, 12.0);     // Большие треугольники

    for (int group = 0; group < num_groups; group++) {
        // Центр группы
        double group_center_x = group * 100.0;
        double group_center_y = 50.0;
        double group_center_z = 50.0;

        std::cout << "Группа " << group << " в области X=" << group_center_x << std::endl;

        // Базовый треугольник для группы
        std::vector<double> base_triangle = {
            group_center_x, group_center_y, group_center_z,
            group_center_x + 10.0, group_center_y, group_center_z,
            group_center_x, group_center_y + 10.0, group_center_z
        };
        h.add_triangle(new triangle(base_triangle));

        // Создаем треугольники, которые гарантированно пересекаются с базовым
        for (int i = 1; i < triangles_per_group; i++) {
            double offset_x = offset_dis(gen);
            double offset_y = offset_dis(gen);

            std::vector<double> coords = {
                group_center_x + 5.0 + offset_x, group_center_y + 5.0 + offset_y, group_center_z,
                group_center_x + 15.0 + offset_x, group_center_y + 5.0 + offset_y, group_center_z,
                group_center_x + 5.0 + offset_x, group_center_y + 15.0 + offset_y, group_center_z
            };
            h.add_triangle(new triangle(coords));
        }
    }

    std::cout << "Создано " << num_groups << " групп с гарантированными пересечениями" << std::endl;
}

// Функция для генерации треугольников в ОДНОЙ ПЛОТНОЙ ГРУППЕ
void generate_single_dense_group(handler& h, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Генерация " << count << " треугольников в ОДНОЙ СУПЕР-ПЛОТНОЙ группе..." << std::endl;

    // ОЧЕНЬ маленькая область
    std::uniform_real_distribution<> pos_dis(0.0, 3.0);   // Область 3x3x3
    std::uniform_real_distribution<> size_dis(2.0, 4.0);  // Большие треугольники

    double center_x = 50.0;
    double center_y = 50.0;
    double center_z = 50.0;

    for (int i = 0; i < count; i++) {
        // Все треугольники в ОЧЕНЬ маленькой области
        double x1 = center_x + pos_dis(gen);
        double y1 = center_y + pos_dis(gen);
        double z1 = center_z + pos_dis(gen);

        std::vector<double> coords = {
            x1, y1, z1,
            x1 + size_dis(gen), y1, z1,
            x1, y1 + size_dis(gen), z1
        };
        h.add_triangle(new triangle(coords));
    }

    std::cout << "Все треугольники в одной супер-плотной группе" << std::endl;
}

// Функция для генерации треугольников в ОДНОЙ ПЛОСКОСТИ
void generate_coplanar_triangles(handler& h, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Генерация " << count << " копланарных треугольников..." << std::endl;

    // Все треугольники в плоскости Z=0
    std::uniform_real_distribution<> pos_dis(0.0, 50.0);
    std::uniform_real_distribution<> size_dis(5.0, 20.0);

    for (int i = 0; i < count; i++) {
        double x1 = pos_dis(gen);
        double y1 = pos_dis(gen);

        std::vector<double> coords = {
            x1, y1, 0.0,
            x1 + size_dis(gen), y1, 0.0,
            x1, y1 + size_dis(gen), 0.0
        };
        h.add_triangle(new triangle(coords));
    }

    std::cout << "Все треугольники лежат в плоскости Z=0" << std::endl;
}

// Функция для генерации ГАРАНТИРОВАННО пересекающихся треугольников
void generate_guaranteed_intersecting_triangles(handler& h, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Генерация " << count << " ГАРАНТИРОВАННО пересекающихся треугольников..." << std::endl;

    std::uniform_real_distribution<> offset_dis(-2.0, 2.0);
    std::uniform_real_distribution<> size_dis(8.0, 12.0);

    // Базовый треугольник, с которым будут пересекаться все остальные
    std::vector<double> base_triangle = {10.0, 10.0, 10.0, 20.0, 10.0, 10.0, 10.0, 20.0, 10.0};
    h.add_triangle(new triangle(base_triangle));

    // Создаем треугольники, которые гарантированно пересекаются с базовым
    for (int i = 1; i < count; i++) {
        double offset_x = offset_dis(gen);
        double offset_y = offset_dis(gen);

        std::vector<double> coords = {
            12.0 + offset_x, 12.0 + offset_y, 10.0,
            18.0 + offset_x, 12.0 + offset_y, 10.0,
            12.0 + offset_x, 18.0 + offset_y, 10.0
        };
        h.add_triangle(new triangle(coords));
    }

    std::cout << "Все треугольники гарантированно пересекаются с базовым треугольником" << std::endl;
}

int main() {
    handler h;
    int choice;

    std::cout << "=== ПРОГРАММА ПРОВЕРКИ ПЕРЕСЕЧЕНИЙ ТРЕУГОЛЬНИКОВ ===" << std::endl;
    std::cout << "1. Ввести треугольники с клавиатуры" << std::endl;
    std::cout << "2. Гарантированные пересечения в группах (500 треугольников)" << std::endl;
    std::cout << "3. Одна супер-плотная группа (200 треугольников)" << std::endl;
    std::cout << "4. Копланарные треугольники (300 треугольников)" << std::endl;
    std::cout << "5. Гарантированные пересечения (200 треугольников)" << std::endl;
    std::cout << "Выберите вариант: ";
    std::cin >> choice;

    auto start_time = std::chrono::high_resolution_clock::now();

    switch (choice) {
        case 1:
            input_triangles_from_user(h);
            break;
        case 2:
            generate_guaranteed_intersecting_groups(h, 500);
            break;
        case 3:
            generate_single_dense_group(h, 200);
            break;
        case 4:
            generate_coplanar_triangles(h, 300);
            break;
        case 5:
            generate_guaranteed_intersecting_triangles(h, 200);
            break;
        default:
            std::cout << "Неверный выбор, генерирую гарантированные пересечения" << std::endl;
            generate_guaranteed_intersecting_triangles(h, 100);
            break;
    }

    auto generation_time = std::chrono::high_resolution_clock::now();

    std::cout << "\nНачинаю поиск пересечений..." << std::endl;

    // Замер времени выполнения
    auto find_start = std::chrono::high_resolution_clock::now();
    h.find_intersections();
    auto find_end = std::chrono::high_resolution_clock::now();

    // Вывод результатов
    auto total_end = std::chrono::high_resolution_clock::now();

    // Расчет времени
    auto generation_duration = std::chrono::duration_cast<std::chrono::milliseconds>(generation_time - start_time);
    auto find_duration = std::chrono::duration_cast<std::chrono::milliseconds>(find_end - find_start);
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(total_end - start_time);

    std::cout << "\n=== РЕЗУЛЬТАТЫ ===" << std::endl;
    std::cout << "Всего треугольников: " << h.get_number_of_triangles() << std::endl;

    // Используем вашу функцию для вывода статистики пересечений
    h.print_statistic();

    std::cout << "\n=== ВРЕМЯ ВЫПОЛНЕНИЯ ===" << std::endl;
    std::cout << "Генерация треугольников: " << generation_duration.count() << " мс" << std::endl;
    std::cout << "Поиск пересечений: " << find_duration.count() << " мс" << std::endl;
    std::cout << "Общее время: " << total_duration.count() << " мс" << std::endl;

    return 0;
}