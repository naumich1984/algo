/*
D. Расстояние по Левенштейну
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Дана текстовая строка. С ней можно выполнять следующие операции:

1. Заменить один символ строки на другой символ.

2. Удалить один произвольный символ.

3. Вставить произвольный символ в произвольное место строки.

Например, при помощи первой операции из строки «СОК» можно получить строку «СУК», при помощи второй операции — строку «ОК», при помощи третьей операции — строку «СТОК».

Минимальное количество таких операций, при помощи которых можно из одной строки получить другую, называется стоимостью редактирования или расстоянием Левенштейна.

Определите расстояние Левенштейна для двух данных строк.

Входные данные
Программа получает на вход две строки, длина каждой из которых не превосходит 1000 символов, строки состоят только из заглавных латинских букв.

Выходные данные
Требуется вывести одно число — расстояние Левенштейна для данных строк.
*/

// L6, task: D, DS-12 Naumovskiy Alexey
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/* Вычисление расстояния Левенштейна между двумя словами аналогично алгоритму нахождения НОП.           
    dp i,j - расстояние между first_word[:i] и second_word[:j]
    dp 0,j = j
    dp 0,i = i
    случаи:
    1) first_word i был удален - dp (i-1),j + 1 
    2) добавить second_word j - dp i,(j-1) + 1
    3) 
        3.1) если  first_word i = second_word j - dp (i-1),(j-1)
        3.2) если  first_word i != second_word j - dp (i-1),(j-1) + 1
    решение: находим min(случай 1), случай 2), случай 3))  - минимальное количество операций для 
    получения из строки first_word строки second_word */
int get_levenshtein_distance(std::string first_word, std::string second_word) {
    int first_word_size = first_word.size();
    std::vector<int> dp(first_word_size + 1);
    for (int i = 0; i <= first_word_size; ++i) { dp[i] = i; }
    for (int j = 1; j <= second_word.size(); ++j) {
        int prev_len = dp[0];
        int prev_len_new = 0;
        dp[0]++;
        for (int i = 1; i <= first_word_size; ++i) {
            prev_len_new = dp[i];
            if (first_word[i - 1] == second_word[j - 1]) {
                dp[i] = prev_len;
            } else {
                dp[i] = std::min(std::min(dp[i - 1], dp[i]), prev_len) + 1;
            }
            prev_len = prev_len_new;
        }
    }
    return dp[first_word_size];
}

int main() {
    std::string first_word;
    std::string  second_word;
    std::getline(std::cin, first_word);
    std::getline(std::cin, second_word);
    std::cout << get_levenshtein_distance(first_word, second_word);
    return 0;
}
