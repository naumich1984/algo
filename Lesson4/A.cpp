/*
A. Минимум на стеке
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Вам требуется реализовать структуру данных, выполняющую следующие операции:

Добавить элемент x в конец структуры.
Удалить последний элемент из структуры.
Выдать минимальный элемент в структуре.
Входные данные
В первой строке входного файла задано одно целое число n — количество операций (1≤n≤106). В следующих n строках заданы сами операции. В i–ой строке число ti — тип операции (1, если операция добавления. 2, если операция удаления. 3, если операция минимума). Если задана операция добавления, то через пробел записано целое число x — элемент, который следует добавить в структуру (−109≤x≤109). Гарантируется, что перед каждой операцией удаления или нахождения минимума структура не пуста.

Выходные данные
Для каждой операции нахождения минимума выведите одно число — минимальный элемент в структуре. Ответы разделяйте переводом строки.
*/


// L4, task: A, DS-12 Naumovskiy Alexey
#include <iostream>
 
//класс Двухсвязный список
template<typename T>
class LinkedList {
    //класс узел списка
    template<typename T>
    class ListNode {
    public:
        T value;
        T min_value; //храним минимальное значение для каждого уровня списка(по факту стека)
        ListNode* next_node;
        ListNode* prev_node;
 
        ListNode(T value = T(), ListNode* next_node = nullptr, ListNode* prev_node = nullptr) {
            this->value = value;
            this->next_node = next_node;
            this->prev_node = prev_node;
        }
    };
 
    int size;
    ListNode<T>* head;
    ListNode<T>* tail;
 
 public:
    LinkedList();
    ~LinkedList();//в деструкторе чистим память
    void push_back(T value); // вставка(использовал в задаче)
    int get_size() { return this->size; } //размер списка
    void pop_front(); //удалить первый(используем для очистки памяти)
    void pop_back(); //удалить последний(использовал в задаче)
    void print_list(); //вывести все элементы списка(для будущих задач)
    T get_min_element(); //минимальный элемент(использовал в задаче)
    void clear(); //очистка памяти
};
 
template<typename T>
LinkedList<T>::LinkedList() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}
 
//деструктор. незабываем чистить память
template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}
 
//вставка в конце списка
//при вставке фиксируем минимальный элемент списка для текущей глубины (это позволит удалять и добавлять сколько хочется)
template<typename T>
void LinkedList<T>::push_back(T value) {
    ListNode<T>* new_node = new ListNode<T>(value);
    if (head == nullptr) {
        new_node->min_value = value; //первый в списке - значит минимальный
        head = new_node;
        tail = head;
    } else {
        tail->next_node = new_node;
        new_node->prev_node = tail;
        this->tail = new_node;
        //определяем минимальный для текущей глубины:
        if (value < new_node->prev_node->min_value) {
            new_node->min_value = value; 
        } else {
            new_node->min_value = new_node->prev_node->min_value; 
        }
    }
    size++;
}
 
//используем для очистки памяти
template<typename T>
void LinkedList<T>::pop_front() {
    if (get_size() > 1) {
        ListNode<T>* old_head = head;
        head = head->next_node;
        head->prev_node = nullptr;
        delete old_head;
    } else {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    size--;
}
 
//Удаление последнего элемента списка
template<typename T>
void LinkedList<T>::pop_back() {
    if (get_size() > 1) {
        ListNode<T>* old_tail = tail; //помещаем указатель на последний элемент списка в темп
        tail = tail->prev_node; //последний элемент заменяем предыдущим
        tail->next_node = nullptr; //следующий элемент для последнего - это null, поэтому зануляем его
        delete old_tail; // удаляем наш темп
    } else { //у нас один элемент в списке. просто удаляем его.
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    size--;
}
 
template<typename T>
void LinkedList<T>::print_list() {
    ListNode<T>* current = this->head;
    for (int i = 0; i < get_size(); ++i) {
        std::cout << current->value << " ";
        current = current->next_node;
    }
    delete current;
}
 
template<typename T>
T LinkedList<T>::get_min_element() {
    return this->tail->min_value;
}
 
template<typename T>
void LinkedList<T>::clear() {
    while (size) {
        pop_front();
    }
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    LinkedList<long long> my_linked_list;
    int count_iter;
    std::cin >> count_iter;
    for (int i = 0; i < count_iter; ++i) {
        int cur_command;
        std::cin >> cur_command;
        if (cur_command == 1) {
            //операция добавления
            long long insert_value;
            std::cin >> insert_value;
            my_linked_list.push_back(insert_value);
        } else if (cur_command == 2) {
            //операця удаления
            my_linked_list.pop_back();
        } else {
            //операция минимума
            std::cout << my_linked_list.get_min_element() << '\n';
        }
    }
    return 0;
}
