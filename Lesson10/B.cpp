// L10, task: B, DS-12 Naumovskiy Alexey
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
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

class RequestsLength {
	const int MAX_REQUEST_CNT = 210;
	std::map<int, std::list<int>> map_graph;
	std::vector<int> vector_used;
	int requests_path_max_length;
	void _dfs(int vertex, int counter);
	void clear();

 public:
	 RequestsLength();
	 ~RequestsLength() { clear(); };
	 void print_requests_path_max_length();
	 void insert_edge(int start_edge, int end_edge);
	 void dfs();
};

void RequestsLength::clear() {
	map_graph.clear();
	vector_used.clear();
}

RequestsLength::RequestsLength() {
	vector_used = std::vector<int>(MAX_REQUEST_CNT, 0);
	requests_path_max_length = 0;
}

void RequestsLength::print_requests_path_max_length() {
	std::cout << requests_path_max_length;
}

void RequestsLength::insert_edge(int start_edge, int end_edge) {
	map_graph[start_edge].push_back(end_edge);
	map_graph[end_edge].push_back(start_edge);
}

void RequestsLength::dfs() {
	_dfs(1, 1); // нас интересует длина цепочики запросов только для Поликарпа
}

void RequestsLength::_dfs(int vertex, int counter) {
	vector_used[vertex] = 1;
	if (1 == map_graph[vertex].size() && counter > requests_path_max_length)
		requests_path_max_length = counter;
	for (auto adjacent_vertex : map_graph[vertex])
		if (0 == vector_used[adjacent_vertex])
			_dfs(adjacent_vertex, counter + 1);
}

int main() {
	int idx = 1;
	int count_requests;
	std::map<std::string, int> map_names;
	std::string to_name, from_name;
	std::cin >> count_requests;
	RequestsLength graph;
	while (count_requests--) {
		std::cin >> to_name;
		std::cin >> from_name >> from_name;
		std::transform(from_name.begin(), from_name.end(), from_name.begin(), [](unsigned char c) { return std::tolower(c); });
		std::transform(to_name.begin(), to_name.end(), to_name.begin(), [](unsigned char c) { return std::tolower(c); });
		if (!map_names.count(from_name)) map_names[from_name] = idx++;
		if (!map_names.count(to_name)) map_names[to_name] = idx++;
		graph.insert_edge(map_names[to_name], map_names[from_name]);
	}
	graph.dfs();
	graph.print_requests_path_max_length();
	map_names.clear();
	return 0;
}



