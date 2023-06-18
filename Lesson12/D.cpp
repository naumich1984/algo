// L12, task: D, DS-12 Naumovskiy Alexey
/*
D. Остовное дерево 2
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Требуется найти в связном графе остовное дерево минимального веса.

Входные данные
Первая строка входного файла содержит два натуральных числа n
 и m
 — количество вершин и ребер графа соответственно. Следующие m
 строк содержат описание ребер по одному на строке. Ребро номер i
 описывается тремя натуральными числами bi
, ei
 и wi
 — номера концов ребра и его вес соответственно (1≤bi,ei≤n
, 0≤wi≤100000
). n≤200000,m≤200000.
Граф является связным.

Выходные данные
Первая строка выходного файла должна содержать одно натуральное число — вес минимального остовного дерева.
*/
#include <iostream>
#include <algorithm>
#include <vector>

struct OneSet {
 public:
    int from;
    int to;
    long long weight;
    friend bool operator<(OneSet from, OneSet to) {
        return from.weight < to.weight;
    }
};

class KruskalMST {
    int count_vertex;
    int count_edge;
    long long min_weight_mst;
    std::vector<OneSet> graph;
    std::vector<int> parent_tree;
    std::vector<int> rank_tree;
    void clear();
    int get(int first_set);
    void join(int first_set, int second_set);

 public:
     KruskalMST(int count_vertex, int count_edge);
     ~KruskalMST() { clear(); };
     void get_kruskal_mst();
     void init_graph();
};

void KruskalMST::clear() {
    graph.clear();
    parent_tree.clear();
    rank_tree.clear();
}

KruskalMST::KruskalMST(int count_vertex, int count_edge) {
    this->count_vertex = count_vertex;
    this->count_edge = count_edge;
    this->min_weight_mst = 0;
    graph = std::vector<OneSet>(count_edge);
    parent_tree = std::vector<int>(count_vertex);
    rank_tree = std::vector<int>(count_vertex);
}

// Kruskal
void KruskalMST::get_kruskal_mst() {
    sort(graph.begin(), graph.end());
    for (int i = 0; i < count_edge; ++i) {
        int from = graph[i].from;
        int to = graph[i].to;
        long long cur_weight = graph[i].weight;
        if (get(to) != get(from)) {
            min_weight_mst += cur_weight;
            join(from, to);
        }
    }
    std::cout << min_weight_mst;
}

void KruskalMST::init_graph() {
    for (int i = 0; i < count_edge; ++i) {
        int from;
        int to;
        long long weight;
        std::cin >> from >> to >> weight;
        from--;
        to--;
        graph[i].from = from;
        graph[i].to = to;
        graph[i].weight = weight;
    }
    for (int i = 0; i < count_vertex; ++i) {
        parent_tree[i] = i;
        rank_tree[i] = i;
    }
}

int KruskalMST::get(int first_set) {
    if (first_set != parent_tree[first_set])
        parent_tree[first_set] = get(parent_tree[first_set]);
    return parent_tree[first_set];
}

void KruskalMST::join(int first_set, int second_set) {
    first_set = get(first_set);
    second_set = get(second_set);
    if (first_set == second_set) return;
    if (rank_tree[first_set] < rank_tree[second_set]) {
        std::swap(first_set, second_set);
    }
    if (rank_tree[first_set] == rank_tree[second_set]) {
        rank_tree[second_set]++;
    }
    parent_tree[second_set] = first_set;
}

int main() {
    int count_vertex;
    int count_edge;
    std::cin >> count_vertex >> count_edge;
    KruskalMST kruskal_mst(count_vertex, count_edge);
    kruskal_mst.init_graph();
    kruskal_mst.get_kruskal_mst();
    return 0;
}

