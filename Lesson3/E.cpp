/*
E. Очень Легкая Задача
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Сегодня утром жюри решило добавить в вариант олимпиады еще одну, Очень Легкую Задачу. Ответственный секретарь Оргкомитета напечатал ее условие в одном экземпляре, и теперь ему нужно до начала олимпиады успеть сделать еще n копий. В его распоряжении имеются два ксерокса, один из которых копирует лист за x секунд, а другой — за y. (Разрешается использовать как один ксерокс, так и оба одновременно. Можно копировать не только с оригинала, но и с копии.) Помогите ему выяснить, какое минимальное время для этого потребуется.

Входные данные
На вход программы поступают три натуральных числа n, x и y, разделенные пробелом (1 ≤ n ≤ 2·108, 1 ≤ x, y ≤ 10).

Выходные данные
Выведите одно число — минимальное время в секундах, необходимое для получения n копий.
*/

// L3, task: E, DS-12 Naumovskiy Alexey
#include <iostream>
#include <cmath>
#include <algorithm>
 
//определяем количество копий при заданном кол-ве секунд и сравниваем с требуемым количеством копий:
bool f_in(long long speed1, long long speed2, long long count_copies, long long seconds) {
    return ((1 + (seconds / speed1 + seconds / speed2)) < count_copies);
}
//бинарный поиск по ответу
void bin_search(long long speed1, long long speed2, long long count_copies) {
    long long idx_left = 0;
    long long idx_right = count_copies * std::max(speed1, speed2);
    long long idx_middle;
    while (idx_right - idx_left > 0) {
        idx_middle = (idx_right + idx_left) / 2;
        if (f_in(speed1, speed2, count_copies, idx_middle)) { //если для текущего времени количество копий меньше требуемого
            idx_left = idx_middle + 1; //то продолжаем искать в правой части со следующего
        }
        else { // если для текущего времени кол-во копий больше требуемого, то продолжаем искать в левой части
            idx_right = idx_middle;
        }
    }
    std::cout << idx_right + std::min(speed1, speed2);
}
 
int main() {
    long long count_copies, speed1, speed2;
    std::cin >> count_copies >> speed1 >> speed2;
    bin_search(speed1, speed2, count_copies);
    return 0;
}
 
