// L14, task: C, DS-12 Naumovskiy Alexey
/*
C. Быстрый поиск подстроки в строке
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Даны строки p и t. Требуется найти все вхождения строки p в строку t в качестве подстроки.

Входные данные
Первая строка входного файла содержит p, вторая — t (1 ≤ |p|, |t| ≤ 106). Строки состоят из букв латинского алфавита.

Выходные данные
В первой строке выведите количество вхождений строки p в строку t. Во второй строке выведите в возрастающем порядке номера символов строки t, с которых начинаются вхождения p. Символы нумеруются с единицы.
*/
#include <iostream>
#include <vector>
#include <string>

class FindAllOccurrence {
    std::string pattern_string;
    std::string text_string;
    std::string kmp_string;
    int size_pattern_string;
    int size_text_string;
    int size_kmp_string;
    std::vector<int> vector_occurrences;
    std::vector<int> vector_prefix;
    void clear();
    void kmp();
    void prefix_func();

 public:
     FindAllOccurrence();
     ~FindAllOccurrence() { clear(); };
     void get_occurrences();
};

void FindAllOccurrence::clear() {
    vector_occurrences.clear();
    vector_prefix.clear();
}

FindAllOccurrence::FindAllOccurrence() {
    std::string pattern_string;
    std::string text_string;
    std::cin >> pattern_string >> text_string;
    this->pattern_string = pattern_string;
    this->text_string = text_string;
    this->size_pattern_string = pattern_string.length();
    this->size_text_string = text_string.length();
    this->kmp_string = pattern_string + "#" + text_string;
    this->size_kmp_string = kmp_string.length();
    vector_prefix = std::vector<int>(size_kmp_string);
}

void FindAllOccurrence::prefix_func() {
    vector_prefix[0] = 0;
    for (int i = 1; i < size_kmp_string; ++i) {
        int j = vector_prefix[i - 1];
        while (j > 0 && kmp_string[i] != kmp_string[j]) {
            j = vector_prefix[j - 1];
        }
        if (kmp_string[i] == kmp_string[j]) {
            ++j;
        };
        vector_prefix[i] = j;
    }
}

void FindAllOccurrence::kmp() {
    prefix_func();
    for (int i = size_pattern_string; i < size_pattern_string + 1 + size_text_string; ++i) {
        if (vector_prefix[i] == size_pattern_string) {
            vector_occurrences.push_back(i - size_pattern_string * 2 + 1);
        }
    }
}

void FindAllOccurrence::get_occurrences() {
    kmp();
    std::cout << vector_occurrences.size() << "\n";
    for (int i = 0; i < vector_occurrences.size(); ++i) {
        std::cout << vector_occurrences[i] << " ";
    }
}

int main() {
    FindAllOccurrence current_search;
    current_search.get_occurrences();
    return 0;
}