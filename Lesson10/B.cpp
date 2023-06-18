// L10, task: B, DS-12 Naumovskiy Alexey
/*
B. Репосты
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Однажды Поликарп опубликовал в социальной сети смешную картинку с опросом про цвет своего хэндла. Многие из его друзей стали репостить шутку Поликарпа себе в ленту. Некоторые из них репостили репосты и так далее.

Эти события заданы в виде последовательности строк «name1 reposted name2» где name1 — это имя того, кто репостнул, а name2 — имя того, с чей ленты репостнули шутку. Гарантируется, что для каждой строки «name1 reposted name2» пользователь «name1» еще не имел эту шутку в свой ленте, а «name2» уже имел ее в своей ленте к моменту репоста. Поликарп зарегистрирован под именем «Polycarp», и изначально шутка есть только в его ленте.

Поликарп измеряет успешность шутки как длину наибольшей цепочки репостов. Выведите успешность шутки Поликарпа.

Входные данные
В первой строке входных данных записано целое число n (1 ≤ n ≤ 200) — количество репостов. Далее записаны сами репосты в порядке их совершения. Каждый из них записан в отдельной строке и имеет вид «name1 reposted name2». Все имена во входных данных состоят из прописных или строчных латинских букв и/или цифр и имеют длины от 2 до 24 символов включительно.

Известно, что имена пользователей регистронезависимы, то есть два имени, отличающиеся исключительно регистром букв, соответствуют одному и тому же пользователю соцсети.

Выходные данные
Выведите единственное целое число — максимальную длину цепочки репостов.
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



