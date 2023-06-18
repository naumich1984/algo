// L12, task: B, DS-12 Naumovskiy Alexey
/*
B. Подсчет опыта
ограничение по времени на тест2 секунды
ограничение по памяти на тест64 мегабайта
вводстандартный ввод
выводстандартный вывод
В очередной онлайн игре игроки, как обычно, сражаются с монстрами и набирают опыт. Для того, чтобы сражаться с монстрами, они объединяются в кланы. После победы над монстром, всем участникам клана, победившего его, добавляется одинаковое число единиц опыта. Особенностью этой игры является то, что кланы никогда не распадаются и из клана нельзя выйти. Единственная доступная операция — объединение двух кланов в один.

Поскольку игроков стало уже много, вам поручили написать систему учета текущего опыта игроков.

Входные данные
В первой строке входного файла содержатся числа n (1 ≤ n ≤ 200000) и m 1 ≤ m ≤ 200000 — число зарегистрированных игроков и число запросов.

В следующих m строках содержатся описания запросов. Запросы бывают трех типов:

join X Y — объединить кланы, в которые входят игроки X и Y (если они уже в одном клане, то ничего не меняется).
add X V — добавить V единиц опыта всем участникам клана, в который входит игрок X (1 ≤ V ≤ 100).
get X — вывести текущий опыт игрока X.
Изначально у всех игроков 0 опыта и каждый из них состоит в клане, состоящим из него одного.

Выходные данные
Для каждого запроса get X выведите текущий опыт игрока X.
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
    graph = std::vector<std::pair<int, int>>(count_vertex);
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


