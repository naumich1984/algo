// L10, task: A, DS-12 Naumovskiy Alexey
/*
A. Компоненты связности
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Дан неориентированный граф. Требуется выделить компоненты связности в нем.

Входные данные
Первая строка входного файла содержит два натуральных числа n
 и m
 — количество вершин и ребер графа соответственно (1≤n≤100000
, 0≤m≤200000
).

Следующие m
 строк содержат описание ребер по одному на строке. Ребро номер i
 описывается двумя натуральными числами bi
, ei
 — номерами концов ребра (1≤bi,ei≤n
). Допускаются петли и параллельные ребра.

Выходные данные
В первой строке выходного файла выведите целое число k
 — количество компонент связности графа. Во второй строке выведите n
 натуральных чисел a1,a1,…,an
, не превосходящих k
, где ai
 — номер компоненты связности, которой принадлежит i
-я вершина.
*/
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
 
class UndirGraph {
    const int DEFAULT_COLOR = 0;
    const int MAX_VERTEX_CNT = 200000;
    int count_vertex;
    int count_edge;
    int count_connectivity = 0;
    std::vector<std::list<int>> map_graph;
    std::vector<int> vector_colors;
    void clear();
    void dfs(int  vertex, int cur_color);
    void print_colors_vector();
 
public:
    UndirGraph(int count_vertex, int count_edge);
    ~UndirGraph() { clear(); };
    void get_count_connectivity();
    void insert_edge(int start_edge, int end_edge);
};
 
void UndirGraph::clear() {
    vector_colors.clear();
    map_graph.clear();
}
 
void UndirGraph::dfs(int vertex, int cur_color) {
    vector_colors[vertex] = cur_color;
    for (int next_vertex : map_graph[vertex]) {
        if (DEFAULT_COLOR == vector_colors[next_vertex]) {
            dfs(next_vertex, cur_color);
        }
    }
}
 
UndirGraph::UndirGraph(int count_vertex, int count_edge) {
    this->count_vertex = count_vertex;
    this->count_edge = count_edge;
    this->vector_colors = std::vector<int>(count_vertex);
    this->map_graph = std::vector<std::list<int>>(MAX_VERTEX_CNT);
}
 
void UndirGraph::print_colors_vector() {
    for (std::vector<int>::iterator it = vector_colors.begin(); it != vector_colors.end(); ++it) {
        std::cout << *it << " ";
    }
}
 
void UndirGraph::get_count_connectivity() {
    for (int i = 0; i < count_vertex; ++i) {
        if (DEFAULT_COLOR == vector_colors[i]) {
            count_connectivity++;
            dfs(i, count_connectivity);
        }
    }
    std::cout << count_connectivity << std::endl;
    print_colors_vector();
}
 
void UndirGraph::insert_edge(int start_edge, int end_edge) {
    map_graph[start_edge].push_back(end_edge);
    map_graph[end_edge].push_back(start_edge);
}
 
int main() {
    int count_vertex;
    int count_edge;
    int start_edge;
    int end_edge;
    std::cin >> count_vertex >> count_edge;
    UndirGraph undirected_graph(count_vertex, count_edge);
    for (int i = 0; i < count_edge; ++i) {
        std::cin >> start_edge >> end_edge;
        start_edge--;
        end_edge--;
        undirected_graph.insert_edge(start_edge, end_edge);
    }
    undirected_graph.get_count_connectivity();
    return 0;
}