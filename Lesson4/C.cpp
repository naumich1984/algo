/*
C. Реализуйте очередь
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Для каждой операции изъятия элемента выведите ее результат.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. Команда — это либо "+ N", либо "-". Команда "+ N" означает добавление в очередь числа N, по модулю не превышающего 109. Команда "-" означает изъятие элемента из очереди.

Входные данные
В первой строке содержится количество команд — m (1⩽m⩽105). В последующих строках содержатся команды, по одной в каждой строке.

Выходные данные
Выведите числа, которые удаляются из очереди, по одному в каждой строке. Гарантируется, что изъятий из пустой очереди не производится.
*/

// L4, task: C, DS-12 Naumovskiy Alexey
#include <iostream>
#include <string>

//Класс циклическая очередь(на саморасширяющимся массиве)
template<typename T>
class CycleQueue {
    int begin;
    int end;
    int capacity;
    T* elements;
 public:
    CycleQueue();
    explicit CycleQueue(int capacity);
    ~CycleQueue();
    void push_back(T value);
    int get_size();
    void ensure_capacity();
    void pop_front();
    int front();
    void decrease_capacity();
    void print();
    int get_capacity();
};

template<typename T>
CycleQueue<T>::CycleQueue() {
    begin = -1;
    end = -1;
    capacity = 4;
    elements = new T[capacity];
}

template<typename T>
CycleQueue<T>::CycleQueue(int capacity) {
    begin = -1;
    end = -1;
    this->capacity = capacity;
    elements = new T[capacity];
}

//Деструктор. чистим память
template<typename T>
CycleQueue<T>::~CycleQueue() {
    delete[] this->elements;
    this->elements = nullptr;
}

//вставка в конец. при достижении capacity - вызываем для ensure_capacity расширения
template<typename T>
void CycleQueue<T>::push_back(T value) {
    if (begin == -1) { begin = 0; }
    end = (end + 1) % capacity;
    elements[end] = value;
    if (capacity == get_size()) { ensure_capacity(); }
}

template<typename T>
int CycleQueue<T>::get_size() {
    if (begin < end) {
        return (end - begin + 1);
    } else if (begin > end) {
        return (end % capacity + (capacity - begin) + 1);
    } else if (begin == -1) {
        return 0;
    } else {
        return 1;
    }
}

//метод расширения массива. Увеличиваем capacity двое, переносим элементы, чистим память
template<typename T>
void CycleQueue<T>::ensure_capacity() {
    T* new_elements = new T[capacity * 2];
    int i, new_idx = 0;
    for (i = begin; i != end; i = (i + 1) % capacity) {
        new_elements[new_idx++] = elements[i];
    }
    new_elements[new_idx] = elements[i];
    capacity = capacity * 2;
    begin = 0;
    end = new_idx;
    delete[] elements;
    elements = new_elements;
    new_elements = nullptr;
}

//удаляем первый. при уменьшении до capacity / 4 - вызываем decrease_capacity для сжатия
template<typename T>
void CycleQueue<T>::pop_front() {
    if (begin == end + 1 || end == begin) {
        begin = -1;
        end = -1;
    } else {
        begin = (begin + 1) % capacity;
        if (get_size() == capacity / 4) { decrease_capacity(); }
    }
}

//получаем значение первого
template<typename T>
int CycleQueue<T>::front() {
    return elements[begin];
}

//метод сжатия массива. Уменьшаем массив в 2 раза,переносим элементы, чистим память.
template<typename T>
void CycleQueue<T>::decrease_capacity() {
    T* new_elements = new T[capacity / 2];
    int i, new_idx = 0;
    for (i = begin; i != end; i = (i + 1) % capacity) {
        new_elements[new_idx++] = elements[i];
    }
    new_elements[new_idx] = elements[i];
    capacity = capacity / 2;
    begin = 0;
    end = new_idx;
    delete[] elements;
    elements = new_elements;
    new_elements = nullptr;
}

template<typename T>
void CycleQueue<T>::print() {
    if (begin == -1) { 
        std::cout << "~empty~"; 
    } else {
        int i;
        for (i = begin; i != end; i = (i + 1) % capacity) {
            std::cout << elements[i] << " ";
        }
        std::cout << elements[i] << " ";
    }
}

template<typename T>
int CycleQueue<T>::get_capacity() {
    return capacity;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    CycleQueue<int> cycle_queue;
    int count_requests;
    std::cin >> count_requests;
    for (int i = 0; i < count_requests; i++) {
        std::string current_command;
        std::cin >> current_command;
        if (current_command[0] == '+') {
            int new_value;
            std::cin >> new_value;
            cycle_queue.push_back(new_value);
        } else {
            std::cout << cycle_queue.front() << "\n";
            cycle_queue.pop_front();
        }
    }
    return 0;
}

