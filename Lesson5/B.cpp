/*
B. Map
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Реализуйте ассоциативный массив с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 100000. В каждой строке находится одна из следующих операций:

put x y — поставить в соответствие ключу x значение y. Если ключ уже есть, то значение необходимо изменить.
delete x — удалить ключ x. Если элемента x нет, то ничего делать не надо.
get x — если ключ x есть в ассоциативном массиве, то выведите соответствующее ему значение, иначе выведите «none».
Ключи и значения — строки из латинских букв длинной не более 20 символов.
Выходные данные
Выведите последовательно результат выполнения всех операций get. Следуйте формату выходного файла из примера.
*/

// L5, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <cmath>

class myMap {
    int size_map;
    int tune_p;
    int tune_a;
    //структура для хранения хэш таблицы:
    std::vector<std::vector<std::pair<std::string, std::string>>> my_map;
public:
    myMap(int size_map, int tune_p, int tune_a);
    ~myMap();
    unsigned int hash_function(std::string value);
    void put(std::string  key, std::string value);
    void erase(std::string  key);
    std::string get(std::string  key);
};

myMap::myMap(int size_map, int tune_p, int tune_a) {
    this->size_map = size_map;
    this->tune_p = tune_p;
    this->tune_a = tune_a;
    my_map.reserve(size_map);
    my_map = std::vector<std::vector<std::pair<std::string, std::string>>>(size_map);
}

myMap::~myMap() {
    my_map.clear();
}

//полиномиальная хэш функция:
unsigned int myMap::hash_function(std::string string_value) {
    unsigned int hash_value = 0;
    int string_len = string_value.length();
    int A_pow = pow(tune_a, string_len - 1);
    for (int i = string_len - 1; i >= 0; --i) {
        hash_value = hash_value + ((A_pow * (int)string_value[i]) % tune_p) % size_map;
        A_pow = A_pow / tune_a;
    }
    return (hash_value % tune_p) % size_map;
}

void myMap::put(std::string  key, std::string value) {
    unsigned int idx_hash = hash_function(key);
    for (size_t i = 0; i < my_map[idx_hash].size(); ++i) {
        if (my_map[idx_hash].at(i).first == key) {
            my_map[idx_hash].at(i).second = value;
            return;
        }
    }
    my_map[idx_hash].push_back(std::make_pair(key, value));
}

void myMap::erase(std::string key) {
    unsigned int idx_hash = hash_function(key);
    for (size_t i = 0; i < my_map[idx_hash].size(); ++i) {
        if (my_map[idx_hash].at(i).first == key) {
            my_map[idx_hash].erase(my_map[idx_hash].begin() + i);
            break;
        }
    }
}

std::string myMap::get(std::string key) {
    unsigned int idx_hash = hash_function(key);
    for (size_t i = 0; i < my_map[idx_hash].size(); ++i) {
        if (my_map[idx_hash].at(i).first == key) {
            return my_map[idx_hash].at(i).second;
        }
    }
    return "none";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int MAX_SIZE_SET = 100000;
    int A_TUNE_HASH = 31;
    int P_TUNE_HASH = 100000007;
    myMap my_map(MAX_SIZE_SET, P_TUNE_HASH, A_TUNE_HASH); //создадим хэш таблицу и настроим(хэш функцию) под 100 000 элементов.
    //обработка команд:
    std::string current_command = "";
    std::string key = "";
    std::string value = "";
    while (std::cin >> current_command) {
        if (current_command.compare("put") == 0) {
            std::cin >> key;
            std::cin >> value;
            my_map.put(key, value);
        }
        else if (current_command.compare("get") == 0) {
            std::cin >> key;
            std::cout << my_map.get(key) << "\n";
        }
        else if (current_command.compare("delete") == 0) {
            std::cin >> key;
            my_map.erase(key);
        }
    }
    return 0;
}
