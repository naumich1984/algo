/*
A. Set
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Реализуйте множество с использованием хеш таблицы.

Входные данные
Входной файл содержит описание операций, их количество не превышает 1000000. В каждой строке находится одна из следующих операций:

insert x — добавить элемент x в множество. Если элемент уже есть в множестве, то ничего делать не надо.
delete x — удалить элемент x. Если элемента x нет, то ничего делать не надо.
exists x — если ключ x есть в множестве выведите «true», если нет «false».
В множество помещаются и извлекаются только целые числа, не превышающие по модулю 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists. Следуйте формату выходного файла из примера.
*/

// L5, task: A, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>

class MySet
{   //настройки хэш функции:
    int tune_a;
    int tune_p;
    int tune_m;
    //счетчики:
    int erase_cnt = 0;
    int put_cnt = 0;
    //хэш таблица:
    // 1. если элемент вектора пуст(empty или size == 0) -пустая ячейка хэш таблицы
    // 2. если элемент вектора не пуст и имеет size == 1, то он хранит некое актуальное значение 
    // 3. если элемент вектора не пуст и имеет size == 2, то он хранит некое удаленное значение
    // (второй элемент значения вектора это флаг "гроба")
    std::vector<int>* hash_table;
public:
    MySet(int tune_m, int tune_a, int tune_p);
    ~MySet();
    void put(int value);
    void erase(int value);
    bool exists(int value);
    //хэш функция:
    unsigned int hash_function(int value) {
        return (tune_a * (unsigned int)value) % tune_p % tune_m;
    }
};

MySet::MySet(int tune_m, int tune_a, int tune_p) {
    this->tune_m = tune_m;
    this->tune_a = tune_a;
    this->tune_p = tune_p;
    hash_table = new std::vector<int>[tune_m];
}

MySet::~MySet() {
    hash_table->clear();
    delete hash_table;
}

bool MySet::exists(int value) {
    unsigned int idx = hash_function(value);
    while (!hash_table[idx].empty()) {
        //элемент либо есть/либо был удален(для каждого элемента может быть лишь один "гроб"):
        if (hash_table[idx].size() == 1 && hash_table[idx].at(0) == value) { return true; }
        if (hash_table[idx].size() == 2 && hash_table[idx].at(0) == value) { return false; }
        idx = (idx + 1) % tune_m;
    }
    //либо его нет
    return false;
}

void MySet::put(int value) {
    unsigned int idx = hash_function(value);
    while (!hash_table[idx].empty()) {
        if (hash_table[idx].size() == 1 && hash_table[idx].at(0) == value) { return; } //уже есть в множестве
        if (hash_table[idx].size() == 2 && hash_table[idx].at(0) == value) { //был ранее удален - оживляем
            hash_table[idx].pop_back();
            put_cnt++;
            return;
        }
        idx = (idx + 1) % tune_m;
    }
    hash_table[idx].push_back(value); //ранее не было - добавляем
    put_cnt++;
}

void MySet::erase(int value) {
    unsigned int idx = hash_function(value);
    while (!hash_table[idx].empty()) {
        if (hash_table[idx].size() == 1 && hash_table[idx].at(0) == value) { //нашли удаляем("кладем в гроб")
            hash_table[idx].push_back(-1);
            erase_cnt++;
            put_cnt--;
            break;
        }
        if (hash_table[idx].size() == 2 && hash_table[idx].at(0) == value) break; //уже удален ранее - выходим;
        idx = (idx + 1) % tune_m;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int MAX_SIZE_SET = 1000000;
    int A_TUNE_HASH = 31;
    int P_TUNE_HASH = 1000507;
    MySet my_set(MAX_SIZE_SET, A_TUNE_HASH, P_TUNE_HASH); //создадим хэщ таблицу и настроим(хэш функцию) под 1000 000 элементов.
    //обработка команд:
    std::string current_command = "";
    int command_value = 0;
    while (std::cin >> current_command >> command_value) {
        if (current_command.compare("insert") == 0) {
            my_set.put(command_value);
        }
        else if (current_command.compare("exists") == 0) {
            if (my_set.exists(command_value)) {
                printf("true\n");
            }
            else {
                printf("false\n");
            }
        }
        else if (current_command.compare("delete") == 0) {
            my_set.erase(command_value);
        }
    }
    return 0;
}
