// L13, task: A, DS-12 Naumovskiy Alexey
/*
A. Очень простой поток
ограничение по времени на тест5 секунд
ограничение по памяти на тест1024 мегабайта
вводстандартный ввод
выводстандартный вывод
Дан неориентированный граф, состоящий из N вершин и M ребер.

У каждого ребра которого есть маленькая пропускная способность. Между любой парой вершин может быть больше одного ребра.

Исток находится в вершине 1, а сток в вершине N. Требуется найти максимальный поток между истоком и стоком.

Входные данные
В первой строке записано натуральное число N — число вершин (2 ≤ N ≤ 100).

Во второй строке записано натуральное число M — число ребер (1 ≤ M ≤ 5000).

Далее в M строках идет описание ребер. Каждое ребро задается тройкой целых чисел Ai, Bi, Ci, где Ai, Bi — номера вершин, которые соединяет ребро (), а Ci (0 ≤ Ci ≤ 20) — пропускная способность этого ребра.

Выходные данные
Выведите максимальный поток между вершинами с номерами 1 и N.
*/
#include <iostream>
#include <vector>
#include <queue>

struct Edge {
    int from;
    int to;
    int capacity;
    int func_thread;
};

class FordFulkerson {
    const int INF = 1000000000;
    int count_vertex;
    int count_edge;
    int s_value;
    int t_value;
    std::vector<std::vector<int>> graph;
    std::vector<int> used;
    std::vector<int> vertex_used;
    std::vector<Edge> edges;
    std::queue<int> queue;
    int push_flow(int u_value, int flow);
    bool bfs();
    void clear();

 public:
     FordFulkerson(int count_vertex, int count_edge);
     ~FordFulkerson() { clear(); }
     int ford_fulkerson();
     void init_graph();
};

FordFulkerson::FordFulkerson(int count_vertex, int count_edge) {
    this->count_vertex = count_vertex;
    this->count_edge = count_edge;
    this->s_value = 0;
    this->t_value = count_vertex - 1;
    this->graph = std::vector<std::vector<int>>(count_vertex);
    this->used = std::vector<int>(count_vertex);
    this->vertex_used = std::vector<int>(count_vertex);
}

void FordFulkerson::clear() {
    graph.clear();
    used.clear();
    vertex_used.clear();
    queue.empty();
    edges.clear();
}

int FordFulkerson::push_flow(int u_value, int flow) {
    if (u_value == t_value || flow == 0) {
        return flow;
    }
    for (; vertex_used[u_value] < graph[u_value].size(); ++vertex_used[u_value]) {
        int num_edge = graph[u_value][vertex_used[u_value]];
        int v_value = edges[num_edge].to;
        if (used[v_value] == used[u_value] + 1) {
            int cur_flow = push_flow(v_value, std::min(flow, edges[num_edge].capacity - edges[num_edge].func_thread));
            if (cur_flow) {
                edges[num_edge].func_thread += cur_flow;
                if (num_edge % 2 == 0) { num_edge++; }
                else { num_edge--; }
                edges[num_edge].func_thread -= cur_flow;
                return cur_flow;
            }
        }
    }
    return 0;
}

bool FordFulkerson::bfs() {
    used.assign(count_vertex, INF);
    used[s_value] = 0;
    queue.push(s_value);
    while (!queue.empty()) {
        int u_value = queue.front();
        queue.pop();
        for (int i = 0; i < graph[u_value].size(); ++i) {
            int num_edge = graph[u_value][i];
            int v_value = edges[num_edge].to;
            if (used[v_value] == INF && edges[num_edge].func_thread < edges[num_edge].capacity) {
                used[v_value] = used[u_value] + 1;
                queue.push(v_value);
            }
        }
    }
    return used[t_value] != INF;
}

int FordFulkerson::ford_fulkerson() {
    int flow = 0;
    while (bfs()) {
        vertex_used.assign(count_vertex, 0);
        int cur_flow = push_flow(s_value, INF);
        while (cur_flow) {
            flow += cur_flow;
            cur_flow = push_flow(s_value, INF);
        }
    }
    return flow;
}

void FordFulkerson::init_graph() {
    for (int i = 0; i < count_edge; ++i) {
        int from, to, capacity;
        std::cin >> from >> to >> capacity;
        from--;
        to--;
        graph[from].push_back(edges.size());
        edges.push_back({ from, to, capacity, 0 });
        graph[to].push_back(edges.size());
        edges.push_back({ to, from, capacity, 0 });
    }
}

int main() {
    int count_vertex, count_edge;
    std::cin >> count_vertex >> count_edge;
    FordFulkerson graph(count_vertex, count_edge);
    graph.init_graph();
    std::cout << graph.ford_fulkerson() << std::endl;
    return 0;
}
