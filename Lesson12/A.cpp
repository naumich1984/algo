// L12, task: A, DS-12 Naumovskiy Alexey
/*
A. Система непересекающихся множеств
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Реализуйте систему непересекающихся множеств. Кроме того, вам нужно будет найти для множества минимум, максимум, и размер.

Изначально каждый элемент находится в своем собственном множестве.

Входные данные
Первая строка ввода содержит целое число n
 — количество элементов в наборе (1≤n≤300000
).

Каждая из следующих строк содержит одну операцию. Существует два типа операций:

union x y: объединить множества, содержащие элементы x и y.
get x: найти множество, содержащее элемент x.
Выходные данные
Для каждой операции get x выведите минимум, максимум и размер множества, содержащего элемент x.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct OneSet {
    int rank;
    int min_element;
    int max_element;
    int count;
};

class DisjointSet {
    int count_sets;
    const int MAX_CNT_OPERATION = 1000000;
    std::vector<int> parent_tree;
    std::vector<OneSet> rank_tree;
    void clear();
    void init_disjoint_set();
    int get(int first_set);

 public:
     DisjointSet(int count_sets);
     ~DisjointSet() { clear(); }
     void join(int first_set, int second_set);
     void print_by_get(int first_set);
};

void DisjointSet::clear() {
    parent_tree.clear();
    rank_tree.clear();
}

void DisjointSet::init_disjoint_set() {
    for (int i = 1; i <= count_sets; ++i) {
        parent_tree[i] = i;
        rank_tree[i].rank = 1;
        rank_tree[i].count = 1;
        rank_tree[i].min_element = i;
        rank_tree[i].max_element = i;
    }
}

DisjointSet::DisjointSet(int count_sets) {
    this->count_sets = count_sets;
    parent_tree = std::vector<int>(MAX_CNT_OPERATION);
    rank_tree = std::vector<OneSet>(MAX_CNT_OPERATION);
    init_disjoint_set();
}

int DisjointSet::get(int first_set) {
    if (parent_tree[first_set] != first_set) {
        parent_tree[first_set] = get(parent_tree[first_set]);
    }
    return parent_tree[first_set];
}

void DisjointSet::print_by_get(int first_set) {
    first_set = get(first_set);
    std::cout << rank_tree[parent_tree[first_set]].min_element << " ";
    std::cout << rank_tree[parent_tree[first_set]].max_element << " ";
    std::cout << rank_tree[parent_tree[first_set]].count << std::endl;
}

void DisjointSet::join(int first_set, int second_set) {
    first_set = get(first_set);
    second_set = get(second_set);
    if (first_set == second_set) return;
    if (rank_tree[first_set].rank > rank_tree[second_set].rank) {
        std::swap(first_set, second_set);
    }
    if (rank_tree[first_set].rank == rank_tree[second_set].rank) {
        rank_tree[second_set].rank++;
    }
    parent_tree[first_set] = second_set;
    rank_tree[second_set].count = rank_tree[second_set].count + rank_tree[first_set].count;
    if (rank_tree[first_set].max_element < rank_tree[second_set].max_element) {
        rank_tree[first_set].max_element = rank_tree[second_set].max_element;
    } else {
        rank_tree[second_set].max_element = rank_tree[first_set].max_element;
    }
    if (rank_tree[first_set].min_element > rank_tree[second_set].min_element) {
        rank_tree[first_set].min_element = rank_tree[second_set].min_element;
    } else {
        rank_tree[second_set].min_element = rank_tree[first_set].min_element;
    }
}

int main() {
    int count_sets;
    std::cin >> count_sets;
    DisjointSet disjoint_set(count_sets);
    int first_set;
    int second_set;
    std::string current_command = "";
    while (std::cin >> current_command) {
        if (current_command.compare("union") == 0) {
            std::cin >> first_set;
            std::cin >> second_set;
            disjoint_set.join(first_set, second_set);
        } else if (current_command.compare("get") == 0) {
            std::cin >> first_set;
            disjoint_set.print_by_get(first_set);
        }
    }
    return 0;
}

