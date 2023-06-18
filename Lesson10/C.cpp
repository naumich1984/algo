// L10, task: C, DS-12 Naumovskiy Alexey
/*
C. Цикл отрицательного веса
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Дан ориентированный граф. Определите, есть ли в нем цикл отрицательного веса, и если да, то выведите его.

Входные данные
Во входном файле в первой строке число N (1 ≤ N ≤ 100) — количество вершин графа. В следующих N строках находится по N чисел — матрица смежности графа. Все веса ребер не превышают по модулю 10 000. Если ребра нет, то соответствующее число равно 100 000.

Выходные данные
В первой строке выходного файла выведите «YES», если цикл существует или «NO» в противном случае. При его наличии выведите во второй строке количество вершин в искомом цикле и в третьей строке — вершины входящие в этот цикл в порядке обхода.
*/
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

class DirGraph {
    const int COLOR_BLACK = 2;
    const int COLOR_GREY = 1;
    const int COLOR_WHITE = 0;
    const int MAX_VERTEX_CNT = 100000;
    bool have_cycle = false;
    int count_vertex;
    int count_edge;
    std::map<int, std::list<int>> map_graph;
    std::vector<int> vector_colors;
    std::vector<int> vector_answers;
    void clear();
    void dfs_topological(std::map<int, std::list<int>>& graph, int vertex, std::vector<int>& answers, std::vector<int>& colors);
    void print_vector(std::vector<int>& my_vector);

public:
    void get_topological_sort();
    void insert_edge(int start_edge, int end_edge);
    DirGraph(int count_vertex, int count_edge);
    ~DirGraph() { clear(); };
};

void DirGraph::insert_edge(int start_edge, int end_edge) {
    map_graph[start_edge].push_back(end_edge);
}

void DirGraph::print_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cout << *it << " ";
    }
}

void DirGraph::clear() {
    vector_answers.clear();
    vector_colors.clear();
    map_graph.clear();
}

void DirGraph::dfs_topological(std::map<int, std::list<int>>& graph, int vertex, std::vector<int>& ans, std::vector<int>& color) {
    if (color[vertex] == COLOR_BLACK) return;
    if (have_cycle) return;
    if (color[vertex] == COLOR_GREY) {
        have_cycle = true;
        return;
    }
    color[vertex] = COLOR_GREY;
    for (int adjacent_vertex : graph[vertex]) {
        dfs_topological(graph, adjacent_vertex, ans, color);
        if (have_cycle) return;
    }
    color[vertex] = COLOR_BLACK;
    ans.push_back(vertex + 1);
}

DirGraph::DirGraph(int count_vertex, int count_edge) {
    this->count_vertex = count_vertex;
    this->count_edge = count_edge;
    vector_colors = std::vector<int>(MAX_VERTEX_CNT, 0);
}

void DirGraph::get_topological_sort() {
    for (int i = 0; i < count_vertex; ++i) {
        dfs_topological(map_graph, i, vector_answers, vector_colors);
    }
    if (!have_cycle) {
        std::reverse(vector_answers.begin(), vector_answers.end());
        print_vector(vector_answers);
    }
    else {
        std::cout << -1;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int count_vertex;
    int count_edge;
    int start_edge;
    int end_edge;
    std::cin >> count_vertex >> count_edge;
    DirGraph directed_graph(count_vertex, count_edge);
    for (int i = 0; i < count_edge; ++i) {
        std::cin >> start_edge >> end_edge;
        start_edge--;
        end_edge--;
        directed_graph.insert_edge(start_edge, end_edge);
    }
    directed_graph.get_topological_sort();
    return 0;
}