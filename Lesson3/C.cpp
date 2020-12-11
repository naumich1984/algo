/*
C. Квадратный корень и квадратный квадрат
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Найдите такое число x, что , с точностью не менее 6 знаков после точки.

Входные данные
В единственной строке содержится вещественное число 1.0 ≤ C ≤ 1010.

Выходные данные
Выведите одно число — искомый x.
*/

// L3, task: C, DS-12 Naumovskiy Alexey
#include <iostream>
#include <iomanip>
#include <cmath>
 
double f_in(double x_value) {
    return ((pow(x_value, 2) + sqrt(x_value)));
}
 
double bin_search_real(const double CONST, const double EPS) {
    //подбор границ
    double idx_left = -1.0; 
    while (f_in(idx_left) > CONST) { idx_left *= 2.0; }
    double idx_right = 1.0; 
    while (f_in(idx_right) < CONST) { idx_right *= 2.0; }
    //вещественный двоичный поиск:
    int count_iter = 2 * round(log((idx_right/ EPS))); //число итераций
    for (int i = 0; i < count_iter; ++i) {
        double idx_middle = (idx_left + idx_right) / 2.0;
        if (f_in(idx_middle) < CONST) {
            idx_left = idx_middle;
        }
        else {
            idx_right = idx_middle;
        }
    }
    return (idx_right + idx_right) / 2.0;
}
 
int main() {
    const double EPS = pow(10, -6);
    double const_in;
    std::cin  >> const_in;
    std::cout << std::fixed << std::setprecision(6) << bin_search_real(const_in, EPS);
    return 0;
}
