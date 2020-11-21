/*
k-я имперская порядковая статистика
ограничение по времени на тест1.2 секунд
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Батальон клонов вышел на построение. Все имперцы стали в один ряд и пересчитались: первый, второй, третий, …, n-й. Каждый из них держит в руках бумажку с результатом своего тестирования IQ. Как известно, результатом тестирования IQ является число от 1 до 109.

Периодически к батальону подходит граф Дуко, размахивает мечом и делает запрос: «Если всех клонов с i-го по j-го упорядочить по результату теста, то какое значение будет у клона, стоящем на k-м месте?» — и быстро требует ответ, грозя всю партию пустить в расход. Большая просьба — решите эту задачу и помогите клонам выжить.

Входные данные
В первой строке входного файла содержится целое число n — количество клонов (1≤n≤1000).

Во второй строке содержатся эти n целых чисел, разделённые пробелами. Числа находятся в промежутке от 1 до 109.

В третьей строке содержится число m — количество запросов (1≤m≤105).

Последние m строк содержат запросы в формате «i j k». Гарантируется, что запросы корректны, то есть 1≤i≤j≤n и на отрезке от i-го до j-го элемента включительно есть хотя бы k элементов.

Выходные данные
На каждый запрос выведите единственное число — ответ на запрос.
*/

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void fill_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cin >> *it;
    }
}

void print_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cout << *it << endl;
    }
}

int partition(std::vector<int>& my_vector, int idx_left, int idx_right) {
    //переносим элементы меньше граничного влево, сдвигая позицию последнего меньшего вправо
    int last_value = my_vector[idx_right];
    int idx_new_left = idx_left;
    for (int i = idx_left; i <= idx_right - 1; i++) {
        if (my_vector[i] <= last_value) {
            swap(my_vector[idx_new_left], my_vector[i]);
            idx_new_left++;
        }
    }
    swap(my_vector[idx_new_left], my_vector[idx_right]);
    return idx_new_left;
}

int split(std::vector<int>& my_vector, int idx_left, int idx_right) {
    srand(time(0));
    int vector_len = (idx_right - idx_left + 1);
    int idx_pivot = rand() % vector_len; //рандом в диапазоне длины вектора
    swap(my_vector[idx_left + idx_pivot], my_vector[idx_right]); //меняем новый элемент разделения с последним
    return partition(my_vector, idx_left, idx_right); //чтобы использовать partition 
}

int find_kth(std::vector<int>& my_vector, int idx_left, int idx_right, int idx_k) {
    int vector_len = (idx_right - idx_left + 1);
    if ((idx_k > 0) && (idx_k <= vector_len)) { //проверяем принадлежность к диапазону i и j
        int idx_median = split(my_vector, idx_left, idx_right); // находим рандомную позицию разделения массива
        if ((idx_median - idx_left) == (idx_k - 1)) { //если после разделения позиция совпадает с i + k - значит нашли к-ый
            return my_vector[idx_median];
        }
        if ((idx_median - idx_left) > (idx_k - 1)) { //если позиция разделения больше k, то идем искать вправую часть(от i до разделения)
            return find_kth(my_vector, idx_left, idx_median - 1, idx_k);
        }
        int idx_k_new = idx_k - idx_median + idx_left - 1; //иначе идем искать в левую часть(от разделения до j)
        return find_kth(my_vector, idx_median + 1, idx_right, idx_k_new);
    }
    return -1; //защита от дурака
}

int main() {
    int count_clones;
    int count_requests;
    int idx_left, idx_right, k_element;
    cin >> count_clones;
    std::vector <int> clones_vector(count_clones);
    fill_vector(clones_vector);
    cin >> count_requests;
    for (int i = 0; i < count_requests; i++) {
        vector<int> clones_copy(clones_vector); //для каждого запроса создаем копию эталлонного вектора клонов
        cin >> idx_left >> idx_right >> k_element;
        cout<< find_kth(clones_copy, (idx_left - 1), (idx_right - 1), k_element) << endl;
    }
    return 0;
}
