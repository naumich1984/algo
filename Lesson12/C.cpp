// L12, task: C, DS-12 Naumovskiy Alexey
/*
C. Остовное дерево
ограничение по времени на тест8 секунд
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Даны точки на плоскости, являющиеся вершинами полного графа. Вес ребра равен расстоянию между точками, соответствующими концам этого ребра. Требуется в этом графе найти остовное дерево минимального веса.

Входные данные
Первая строка входного файла содержит натуральное число n
 — количество вершин графа (1≤n≤10000
). Каждая из следующих n
 строк содержит два целых числа xi
, yi
  — координаты i
-й вершины (−10000≤xi,yi≤10000
). Никакие две точки не совпадают.

Выходные данные
Первая строка выходного файла должна содержать одно вещественное число — вес минимального остовного дерева.
*/
#include <iostream>
#include <vector>
#include <cmath>

class PrimMST {
    const int INF = 1000000;
    int count_vertex;
    double weight_mst;
    std::vector<std::pair<int, int>> graph;
    std::vector<bool> used; //вкючена ли вершина в остов 
    std::vector<int> edges_ends;
    std::vector<double> edges_min_values; //веса наименьшего допустимого ребра для каждой вершины
    void clear();
    double get_segment_length(int first_vertex, int second_vertex);

public:
    PrimMST(int count_vertex);
    ~PrimMST() { clear(); };
    void init_graph();
    void get_mst();
};

void PrimMST::clear() {
    graph.clear();
    used.clear();
    edges_ends.clear();
    edges_min_values.clear();
}

double PrimMST::get_segment_length(int first_vertex, int second_vertex) {
    if (first_vertex == second_vertex) return INF;
    std::pair<int, int> from = graph[first_vertex];
    std::pair<int, int> to = graph[second_vertex];
    double segment_length = sqrt((to.first - from.first) * (to.first - from.first) + (to.second - from.second) * (to.second - from.second));
    return segment_length;
}

PrimMST::PrimMST(int count_vertex) {
    this->count_vertex = count_vertex;
    this->weight_mst = 0;
    used = std::vector<bool>(count_vertex);
    edges_ends = std::vector<int>(count_vertex, -1);
    edges_min_values = std::vector<double>(count_vertex, INF);
    edges_min_values[0] = 0;
}

void PrimMST::init_graph() {
    for (int i = 0; i < count_vertex; ++i) {
        int x_coordinate;
        int y_coordinate;
        std::cin >> x_coordinate >> y_coordinate;
        graph.push_back(std::make_pair(x_coordinate, y_coordinate));
    }
}

void PrimMST::get_mst() {
    for (int i = 0; i < count_vertex; ++i) {
        int from = -1;
        for (int j = 0; j < count_vertex; ++j) {
            if (!used[j] && (edges_min_values[j] < edges_min_values[from] || -1 == from)) {
                from = j;
            }
        }
        used[from] = true;
        if (edges_ends[from] != -1) {
            weight_mst += (get_segment_length(from, edges_ends[from]));
        }
        for (int to = 0; to < count_vertex; ++to) {
            double cur_length = get_segment_length(from, to);
            if (cur_length < edges_min_values[to]) {
                edges_min_values[to] = cur_length;
                edges_ends[to] = from;
            }
        }
    }
    std::cout << weight_mst;
}

int main() {
    int count_vertex;
    std::cin >> count_vertex;
    PrimMST prim_graph(count_vertex);
    prim_graph.init_graph();
    prim_graph.get_mst();
    return 0;
}
