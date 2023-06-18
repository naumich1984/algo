/*
A. Принадлежность точки отрезку
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Входные данные
Шесть чисел — координаты точки и координаты концов отрезка.

Выходные данные
Одна строка YES, если точка принадлежит отрезку, и NO в противном случае.
*/

#include <iostream>
#include <cmath>

class Point {
    double x;
    double y;

public:
    Point() {};
    Point(double x, double y) { this->x = x; this->y = y; };
    ~Point() {};
    double get_x() { return x; };
    double get_y() { return y; };
};

class Vector {
    Point x_point;
    Point y_point;

public:
    double coord_x;
    double coord_y;
    Vector() {};
    Vector(Point x_point, Point y_point) {
        this->x_point = x_point;
        this->y_point = y_point;
        this->coord_x = y_point.get_x() - x_point.get_x();
        this->coord_y = y_point.get_y() - x_point.get_y();
    };
    ~Vector() {};
    double square_lenght();
};

double Vector::square_lenght() {
    return (x_point.get_x() - y_point.get_x()) * (x_point.get_x() - y_point.get_x())
            + (x_point.get_y() - y_point.get_y()) * (x_point.get_y() - y_point.get_y());
}

void read_points(Point &a_point, Point &b_point, Point &c_point) {
    double coord_x, coord_y;
    std::cin >> coord_x >> coord_y;
    a_point = Point(coord_x, coord_y);
    std::cin >> coord_x >> coord_y;
    b_point = Point(coord_x, coord_y);
    std::cin >> coord_x >> coord_y;
    c_point = Point(coord_x, coord_y);
}

bool cross_product(Vector ab, Vector bc, const double EPS) {
    return abs(ab.coord_x * bc.coord_y - ab.coord_y * bc.coord_x) > EPS;
}

double dot_product(Vector ab, Vector bc) {
    return ab.coord_x * bc.coord_x + ab.coord_y * bc.coord_y;
}

void check_inside(Vector vector_segment, Vector vector_check, const double EPS) {
    if (cross_product(vector_check, vector_segment, EPS)) {
        std::cout << "NO" << std::endl;
        return;
    }
    double dotproduct = dot_product(vector_segment, vector_check);
    if (dotproduct < 0) {
        std::cout << "NO" << std::endl;
        return;
    }
    double squared_length = vector_segment.square_lenght();
    if (dotproduct > squared_length) {
        std::cout << "NO" << std::endl;
        return;
    }
    std::cout << "YES" << std::endl;
}

int main() {
    const double EPS = 0.001;
    Point a_point, b_point, c_point;
    read_points(a_point, b_point, c_point);
    check_inside(Vector(b_point, c_point), Vector(b_point, a_point), EPS);
    return 0;
}


