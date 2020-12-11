/*
D. Веревочки
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
С утра шел дождь, и ничего не предвещало беды. Но к обеду выглянуло солнце, и в лагерь заглянула СЭС. Пройдя по всем домикам и корпусам, СЭС вынесла следующий вердикт: бельевые веревки в жилых домиках не удовлетворяют нормам СЭС. Как выяснилось, в каждом домике должно быть ровно по одной бельевой веревке, и все веревки должны иметь одинаковую длину. В лагере имеется N бельевых веревок и K домиков. Чтобы лагерь не закрыли, требуется так нарезать данные веревки, чтобы среди получившихся веревочек было K одинаковой длины. Размер штрафа обратно пропорционален длине бельевых веревок, которые будут развешены в домиках. Поэтому начальство лагеря стремиться максимизировать длину этих веревочек.

Входные данные
В первой строке заданы два числа — N и K (1 ≤ N, K ≤ 10001). Далее в каждой из последующих N строк записано по одному числу — длине очередной бельевой веревки. Длина веревки задана в сантиметрах. Все длины лежат в интервале от 1 сантиметра до 100 километров включительно.

Выходные данные
В выходной файл следует вывести одно целое число — максимальную длину веревочек, удовлетворяющую условию, в сантиметрах. В случае, если лагерь закроют, выведите 0.
*/

// L3, task: D, DS-12 Naumovskiy Alexey
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
 
void fill_vector(std::vector<long long>& my_vector) {
    for (std::vector<long long>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cin >> *it;
    }
}
 
long long f_rope_check(std::vector<long long>& my_vector, long long rope_length) {
    int k_sum = 0;
    for (size_t i = 0; i < my_vector.size(); ++i) {
        k_sum += (my_vector[i] / rope_length);
    }
    return k_sum;
}
 
int main() {
    long long count_ropes;
    long long count_houses;
    std::cin >> count_ropes >> count_houses;
    std::vector <long long> my_vector(count_ropes); 
    fill_vector(my_vector);
    //Если домов 0, то ничего считать не нужно
    if (count_houses == 0) {
        std::cout << 0;
        return 0;
    }
    //упорядочиваем массив веревок по их длинам
    sort(my_vector.begin(), my_vector.end());
    long long left_value = 1;
    long long right_value = my_vector[count_ropes - 1];
    //двоичный поиск:
    while (right_value - left_value > 1)
    {
        long long middle_value = (right_value + left_value) / 2;
        if (f_rope_check(my_vector, middle_value) < count_houses)
            right_value = middle_value;
        else
            left_value = middle_value;
    }
    //проверка частных/граничных случаев(выглядит неочень - надеюсь успею переделать):
    const long long R_VALUE = f_rope_check(my_vector, right_value);
    const long long L_VALUE = f_rope_check(my_vector, left_value);
    if (R_VALUE == count_houses) { std::cout << right_value; return 0;}
    else if (L_VALUE == count_houses) { std::cout << left_value; return 0;}
    if (L_VALUE < count_houses) {
        if (R_VALUE < count_houses) std::cout << 0;
        return 0;
    }
    if (right_value == left_value) { std::cout << right_value; return 0; }
    if (L_VALUE > count_houses) {
        if (R_VALUE > count_houses) { std::cout << right_value; return 0; }
        else if (R_VALUE <= count_houses) { std::cout << left_value; return 0; }
    }
    if (R_VALUE > count_houses) {
        if (L_VALUE > count_houses) { std::cout << left_value; return 0; }
        else if (L_VALUE <= count_houses) { std::cout << right_value; return 0; }
        return 0;
    }
    return 0;
}
