/*
C. Наибольшая возрастающая подпоследовательность
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Пусть a1, a2, ..., an — числовая последовательность. Длина последовательности — это количество элементов этой последовательности. Последовательность ai1, ai2, ..., aik называется подпоследовательностью последовательности a, если 1 ≤ i1 < i2 < ... < ik ≤ n. Последовательность a называется возрастающей, если a1 < a2 < ... < an.

Вам дана последовательность, содержащая n целых чисел. Найдите ее самую длинную возрастающую подпоследовательность.

Входные данные
В первой строке задано одно число n (1 ≤ n ≤ 2000) — длина подпоследовательности. В следующей строке задано n целых чисел ai ( - 109 ≤ ai ≤ 109) — элементы последовательности.

Выходные данные
В первой строке выведите число k — длину наибольшей возрастающей подпоследовательности. В следующей строке выведите k чисел — саму подпоследовательность.
*/

// L6, task: C, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <algorithm>

void clear(std::vector<int>& sequence, std::vector<int>& subsequence, std::vector<int>& dp, std::vector<int>& history) {
    dp.clear();
    sequence.clear();
    subsequence.clear();
    history.clear();
}

void print_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cout << *it << " ";
    }
}

void fill_vector(std::vector<int>& my_vector) {
    int buff;
    while (std::cin >> buff) {
        my_vector.push_back(buff);
    }
}

std::pair<int, int> find_pair_max_subsequence_and_pos(std::vector<int>& sequence, std::vector<int>& dp, 
                                    std::vector<int>& history, int len_sequence, const int SMALL_INF) {
    for (int i = 0; i < len_sequence; ++i) {
        dp[i] = 1;
        history[i] = SMALL_INF;
        for (int j = 0; j <= i - 1; ++j) {
            if ((sequence[j] < sequence[i]) && (dp[j] + 1 > dp[i])) {
                dp[i] = dp[j] + 1;
                history[i] = j;
            }
        }
    }
    std::vector<int>::iterator max_dp = std::max_element(dp.begin(), dp.end());
    int pos_subsequence = std::distance(std::begin(dp), max_dp);
    return std::make_pair(*max_dp, pos_subsequence);
}

int main() {
    int const SMALL_INF = -2000000000;
    int len_sequence;
    std::cin >> len_sequence;
    std::vector<int> sequence;
    fill_vector(sequence);
    std::vector<int> dp(len_sequence);
    std::vector<int> history(len_sequence);
    std::vector<int> subsequence;
    std::pair<int, int> max_dp_with_pos = find_pair_max_subsequence_and_pos(sequence, dp, history, len_sequence, SMALL_INF);
    std::cout << max_dp_with_pos.first << "\n";
    int pos_subsequence = max_dp_with_pos.second;
    while (pos_subsequence != SMALL_INF) {
        subsequence.push_back(sequence[pos_subsequence]);
        pos_subsequence = history[pos_subsequence];
    }
    std::reverse(subsequence.begin(), subsequence.end());
    print_vector(subsequence);
    clear(sequence, subsequence, dp, history);
    return 0;
}
