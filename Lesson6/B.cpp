/*
B. Черепаха и монеты
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Черепаха хочет переползти из левого верхнего угла поля размером N на M клеток (2 ≤ N, M ≤ 1000) в правый нижний. За один шаг она может переместиться на соседнюю клетку вправо или на соседнюю клетку вниз. Кроме того, проходя через каждую клетку, Черепаха получает (или теряет) несколько золотых монет (это число известно для каждой клетки).

Определите, какое максимальное количество монет может собрать Черепаха по пути и как ей нужно идти для этого.

Входные данные
В первой строке вводятся два натуральных числа: N и M (2 ≤ N, M ≤ 1000), разделённые пробелом. В каждой из следующих N строк записаны через пробел по M чисел aij(|aij| ≤ 10), которые обозначают количество монет, получаемых Черепашкой при проходе через каждую клетку. Если это число отрицательное, Черепашка теряет монеты.

Выходные данные
В первой строке программа должна вывести наибольшее количество монет, которое может собрать Черепаха. Во второй строке без пробелов выводятся команды, которые нужно выполнить Черепахе: буква 'R' (от слова right) обозначает шаг вправо, а буква 'D' (от слова down) – шаг вниз.
*/

// L6, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void clear(std::vector<std::vector<int>>& dp, std::vector<std::vector<int>>& coins) {
    dp.clear();
    coins.clear();
}

void read_coins_matrix(std::vector<std::vector<int>>& coins, int width_matrix, int height_matrix) {
    for (int i = 0; i < width_matrix; i++) {
        for (int j = 0; j < height_matrix; j++) {
            int cur_coins;
            std::cin >> cur_coins;
            coins[i][j] = cur_coins;
        }
    }
}

//Восстанавливаем путь черепахи по матрице DP (идем сверху вниз):
void print_path(std::vector<std::vector<int>>& dp, int width_matrix, int height_matrix) {
    std::string str_path = "";
    for (int i = width_matrix - 1; i >= 0;) {
        for (int j = height_matrix - 1; j >= 0;) {
            if (i == 0 && j == 0) break;
            if (i == 0) { 
                str_path = str_path + "R"; 
                j--; 
                continue; 
            }
            if (j == 0) { 
                str_path = str_path + "D"; 
                j = 0; i--;  
                continue; 
            }
            if (dp[i][j - 1] > dp[i - 1][j]) {
                str_path = str_path + "R"; 
                j--; 
                continue;
            } else {
                str_path = str_path + "D"; 
                i--; 
                continue;
            }
        }
        if (i == 0) break;
    }
    std::reverse(str_path.begin(), str_path.end());
    std::cout << str_path;
}

//Передвижение черепахи:
/*
(реализован алгоритм из лекции - для этого доработана загрузка данных см. read_coins_matrix )
Что храним в DP         dp[i][j] ─ максимальное число монет на пути в клетку (i, j)
База                    dp[0][0] = coins[0][0]
Переход                 dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + coins[i][j]
                        dp[i][j] = dp[i-1][j] + coins[i][j], если j = 0 
                        dp[i][j] = dp[i][j-1]+apples[i][j], если i = 0 
Порядок обхода          По возрастанию i, По возрастанию j
Где ответ?              dp[n][m] - максимальное количество монет
                        по матрице dp[i][j] - можно восстановить путь
*/
void move_turtle(std::vector<std::vector<int>>& dp, std::vector<std::vector<int>>& coins,
                int width_matrix, int height_matrix) {
    dp[0][0] = coins[0][0];
    for (int i = 0; i < width_matrix; i++) {
        for (int j = 0; j < height_matrix; j++) {
            if (i == 0 && j > 0) {
                dp[i][j] = dp[i][j - 1] + coins[i][j];
            }
            if (i > 0 && j == 0) {
                dp[i][j] = dp[i - 1][j] + coins[i][j];
            }
            if (i > 0 && j > 0) {
                int max_v = 0;
                if (dp[i][j - 1] >= dp[i - 1][j]) {
                    max_v = dp[i][j - 1];
                } else {
                    max_v = dp[i - 1][j];
                }
                dp[i][j] = max_v + coins[i][j];
            }
        }
    }
    std::cout << dp[width_matrix - 1][height_matrix - 1] << "\n";
}

int main() {
    int width_matrix;
    int height_matrix;
    std::cin >> width_matrix >> height_matrix;
    std::vector<std::vector<int>> dp(width_matrix, std::vector<int>(height_matrix, -100));
    std::vector<std::vector<int>> coins(width_matrix, std::vector<int>(height_matrix, -100));
    read_coins_matrix(coins, width_matrix, height_matrix);
    move_turtle(dp, coins, width_matrix, height_matrix);
    print_path(dp, width_matrix, height_matrix);
    clear(dp, coins);
    return 0;
}
