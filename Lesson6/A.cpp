/*
A. Кузнечик собирает монеты
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Кузнечик прыгает по столбикам, расположенным на одной линии на равных расстояниях друг от друга. Столбики имеют порядковые номера от 1 до N. В начале Кузнечик сидит на столбике с номером 1 и хочет добраться до столбика с номером N. Он может прыгнуть вперед на расстояние от 1 до K столбиков, считая от текущего.

На каждом столбике Кузнечик может получить или потерять несколько золотых монет (для каждого столбика это число известно). Определите, как нужно прыгать Кузнечику, чтобы собрать наибольшее количество золотых монет. Учитывайте, что Кузнечик не может прыгать назад.

Входные данные
В первой строке вводятся два натуральных числа: N и K (2 ≤ N, K ≤ 10000), разделённые пробелом. Во второй строке записаны через пробел N - 2 целых числа – количество монет, которое Кузнечик получает на каждом столбике, от 2-го до N - 1-го. Если это число отрицательное, Кузнечик теряет монеты. Гарантируется, что все числа по модулю не превосходят 10 000.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Кузнечик. Во второй строке выводится число прыжков Кузнечика, а в третьей строке – номера всех столбиков, которые посетил Кузнечик (через пробел в порядке возрастания).

Если правильных ответов несколько, выведите любой из них.
*/

// L6, task: A, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

//Заполним массив монет (за первый и последний столб - даем 0 момент)
void fill_vector_monets(std::vector<int>& my_vector) {
    my_vector.push_back(0);
    int buff;
    while (std::cin >> buff) {
        my_vector.push_back(buff);
    }
    my_vector.push_back(0);
}

template<typename T>
void print_data(T my_collection) {
    for (auto it = my_collection.begin(); it != my_collection.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}


/* Профит кузнечика:
Что храним в ДП?        максимальное число момент для каждого столбика
База                    dp[0] = 0
Переход                 наибольший из предыдущих k элементов в dp
                        для i-го столбика смотрим назад на глубину прыжка k и ищем столбик, прыжок 
                        из которого даст максимальное количество монет
Порядок обхода          по возрастанию i
Где ответ?              dp[n]
*/
void get_grasshopper_profit(std::vector<int>& dp, std::vector<int>& monets,
            std::set<int>& points, int pillars_count, int pillar_range) {
    dp[0] = 0; //База - сидя на первом столбике у кузнечика 0 монет
    points.insert(1); //первый столб - исходная точка пути кузнечика
    for (int i = 1; i < pillars_count; i++) { 
        int idx_prev = i - 1;
        int cur_pillar_range = 0;
        if (i - pillar_range > 0) { cur_pillar_range = i - pillar_range; }
        for (int j = cur_pillar_range; j <= (i - 1); ++j) {
            if (dp[j] > dp[idx_prev]) {
                idx_prev = j;
            }
        }
        dp[i] = dp[idx_prev] + monets[i];
        points.insert(idx_prev + 1);
    }
    points.insert(pillars_count); //последний столбик
    std::cout << dp[pillars_count - 1] << "\n";
    std::cout << points.size() - 1 << "\n";
    print_data(points);
}

int main() {
    int pillars_count;
    int pillar_range;
    std::vector<int> monets;
    std::set<int> points;
    std::cin >> pillars_count >> pillar_range;
    std::vector<int> dp(pillars_count);
    fill_vector_monets(monets);
    get_grasshopper_profit(dp, monets, points, pillars_count, pillar_range);
    return 0;
}
