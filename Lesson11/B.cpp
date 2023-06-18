/*
B. Кратчайший путь
ограничение по времени на тест2 s.
ограничение по памяти на тест256 MB
вводstandard input
выводstandard output
Дан неориентированный связный взвешенный граф. Найдите кратчайшее расстояние от первой вершины до всех вершин.

Входные данные
В первой строке входного файла два числа: n
 и m
 (2≤n≤30000,1≤m≤400000
), где n
 — количество вершин графа, а m
 — количество ребер.

Следующие m
 строк содержат описание ребер. Каждое ребро задается стартовой вершиной, конечной вершиной и весом ребра. Вес каждого ребра — неотрицательное целое число, не превосходящее 104
.

Выходные данные
Выведите n
 чисел — для каждой вершины кратчайшее расстояние до нее.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <set>

struct NodeGraph {
	int from;
	int to;
	int lenght;
};

class ShortPath {
	int const MAX_VERTEX_CNT = 400000;
	int const MAX_GRAPH_LENGTH = 1000000;
	std::vector<std::vector<NodeGraph>> graph;
	std::vector<int> distances;
	std::vector<int> used_vertex;
	int vertex_count;
	int edge_count;
	void clear();

 public:
	 ShortPath(int vertex_count, int edge_count);
	 ~ShortPath() { clear(); };
	 void algorithm_dijkstra();
	 void fill_graph();
	 void print_distances();
};

void ShortPath::clear() {
	graph.clear();
	distances.clear();
	used_vertex.clear();
}

ShortPath::ShortPath(int vertex_count, int edge_count) {
	this->vertex_count = vertex_count;
	this->edge_count = edge_count;
	graph = std::vector<std::vector<NodeGraph>>(MAX_VERTEX_CNT);
	distances = std::vector<int>(vertex_count, MAX_GRAPH_LENGTH);
	used_vertex = std::vector<int>(vertex_count, 0);
}

void ShortPath::algorithm_dijkstra() {
	int start = graph[0][0].from;
	distances[start] = 0;
	std::set<std::pair<int, int>> unused;
	unused.insert(std::make_pair(0, start));
	for (int i = 0; i < vertex_count; ++i) {
		if (unused.size() == 0) { break; }
		int next = unused.begin()->second;
		unused.erase(unused.begin());
		if (1 == used_vertex[next]) continue;
		for (auto cur_edge : graph[next]) {
			int cur_vertex = cur_edge.to;
			int cur_lenght = cur_edge.lenght;
			if (0 == used_vertex[cur_vertex]) {
				unused.erase(std::make_pair(distances[cur_vertex], cur_vertex));
				distances[cur_vertex] = std::min(distances[cur_vertex], distances[next] + cur_lenght);
				unused.insert(std::make_pair(distances[cur_vertex], cur_vertex));
			}
		}
		used_vertex[next] = 1;
	}
}

void ShortPath::fill_graph() {
	NodeGraph cur_node;
	int start_edge, end_edge, len_edge;
	for (int i = 0; i < edge_count; ++i) {
		std::cin >> start_edge >> end_edge >> len_edge;
		start_edge--;
		end_edge--;
		cur_node.from = start_edge;
		cur_node.to = end_edge;
		cur_node.lenght = len_edge;
		graph[start_edge].push_back(cur_node);
		cur_node.from = end_edge;
		cur_node.to = start_edge;
		cur_node.lenght = len_edge;
		graph[end_edge].push_back(cur_node);
	}
}

void ShortPath::print_distances() {
	for (int i = 0; i < vertex_count; ++i)
		std::cout << distances[i] << " ";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int vertex_count;
	int edge_count;
	std::cin >> vertex_count >> edge_count;
	ShortPath short_paths(vertex_count, edge_count);
	short_paths.fill_graph();
	short_paths.algorithm_dijkstra();
	short_paths.print_distances();
	return 0;
}

