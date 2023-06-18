// L11, task: A, DS-12 Naumovskiy Alexey
/*
A. Приключения шахматного коня
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
На шахматной доске N × N в клетке (x1, y1) стоит голодный шахматный конь. Он хочет попасть в клетку (x2, y2), где растет вкусная шахматная трава. Какое наименьшее количество ходов он должен для этого сделать?

Входные данные
На вход программы поступает пять чисел: N, x1, y1, x2, y2 (5 ≤ N ≤ 20, 1 ≤ x1, y1, x2, y2 ≤ N). Левая верхняя клетка доски имеет координаты (1, 1), правая нижняя — (N, N).

Выходные данные
В первой строке выведите единственное число K — количество посещенных клеток. В каждой из следующих K строк должно быть записано 2 числа — координаты очередной клетки в пути коня.
*/
#include <iostream>
#include <vector>
#include <queue>

class ChessHourse {
    const int CHESS_CELL_EMPTY = 1000000000;
    static const int CNT_OPTIONS_OFFSET = 8;
    const int X_HOURSE_OFFSETS[CNT_OPTIONS_OFFSET] = {-2, -2, -1, -1, 1, 1, 2, 2};
    const int Y_HOURSE_OFFSETS[CNT_OPTIONS_OFFSET] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int size_chess_filed;
    int final_vertex;
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    std::vector<std::vector<int>> chess_graph;
    std::queue<std::pair<int, int>> chess_steps_queue;
    std::vector<std::vector<int>> chess_used_cells;
    std::vector<int> chess_graph_levels;
    std::vector<std::pair<int, int>> chess_graph_coords;
    void clear();
 public:
    ChessHourse(int size_chess_filed, int x_start, int y_start, int x_end, int y_end);
    ~ChessHourse() { clear(); };
    void bfs_chess_hourse();
    void print_count_cells();
    void print_path_cells_coords();
};

void ChessHourse::print_count_cells() {
    std::cout << chess_graph[x_end][y_end] + 1 << std::endl;
}

void ChessHourse::print_path_cells_coords() {
    std::vector<int> chess_hourse_path;
    for (int v = final_vertex; v != -1; v = chess_graph_levels[v])
        chess_hourse_path.push_back(v);
    std::reverse(chess_hourse_path.begin(), chess_hourse_path.end());
    for (int i = 0; i < chess_hourse_path.size(); ++i) {
        std::cout << chess_graph_coords[chess_hourse_path[i]].first << " ";
        std::cout << chess_graph_coords[chess_hourse_path[i]].second << std::endl;
    }
}

ChessHourse::ChessHourse(int size_chess_filed, int x_start, int y_start, int x_end, int y_end) {
    this->size_chess_filed = size_chess_filed;
    this->x_start = x_start;
    this->y_start = y_start;
    this->x_end = x_end;
    this->y_end = y_end;
    this->chess_graph = std::vector<std::vector<int>>(size_chess_filed + 1, std::vector<int>(size_chess_filed + 1));
    this->chess_used_cells = std::vector<std::vector<int>>(size_chess_filed + 1, std::vector<int>(size_chess_filed + 1));
    this->chess_graph_levels = std::vector<int>(size_chess_filed * size_chess_filed, -1);
    this->chess_graph_coords = std::vector<std::pair<int, int>>(size_chess_filed * size_chess_filed);
    for (int i = 0; i <= size_chess_filed; ++i)
        for (int j = 0; j <= size_chess_filed; ++j) chess_graph[i][j] = CHESS_CELL_EMPTY;
}

void ChessHourse::bfs_chess_hourse() {
    chess_graph[x_start][y_start] = 0;
    chess_steps_queue.push(std::make_pair(x_start, y_start));
    chess_graph_coords[0] = std::make_pair(x_start, y_start);
    int level_vertex = 0;
    int idx_vertex = 1;
    while (!chess_steps_queue.empty()) {
        int x_cur = chess_steps_queue.front().first;
        int y_cur = chess_steps_queue.front().second;
        chess_steps_queue.pop();
        for (int k = 0; k < CNT_OPTIONS_OFFSET; ++k) {
            int x_new = x_cur + X_HOURSE_OFFSETS[k];
            int y_new = y_cur + Y_HOURSE_OFFSETS[k];
            if (x_new > 0 && x_new <= size_chess_filed && y_new > 0 && y_new <= size_chess_filed
               && chess_graph[x_new][y_new] > chess_graph[x_cur][y_cur] + 1) {
                if (0 == chess_used_cells[x_new][y_new]) {
                    chess_graph[x_new][y_new] = chess_graph[x_cur][y_cur] + 1;
                    chess_used_cells[x_new][y_new] = 1;
                    chess_steps_queue.push(std::make_pair(x_new, y_new));
                    chess_graph_coords[idx_vertex] = std::make_pair(x_new, y_new);
                    chess_graph_levels[idx_vertex] = level_vertex;
                    if (x_new == x_end && y_new == y_end) {
                        final_vertex = idx_vertex;
                    }
                    idx_vertex++;
                }
            }
        }
        level_vertex++;
    }
}

void ChessHourse::clear() {
    chess_graph.clear();
    chess_used_cells.clear();
    chess_graph_levels.clear();
    chess_graph_coords.clear();
}

int main() {
    int size_chess_filed;
    int x_start, y_start, x_end, y_end;
    std::cin >> size_chess_filed >> x_start >> y_start >> x_end >> y_end;
    ChessHourse chess_hourse(size_chess_filed, x_start, y_start, x_end, y_end);
    chess_hourse.bfs_chess_hourse();
    chess_hourse.print_count_cells();
    chess_hourse.print_path_cells_coords();
    return 0;
}


