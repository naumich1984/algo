/*
B. Постфиксная запись
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
В постфиксной записи (или обратной польской записи) операция записывается после двух операндов. Например, сумма двух чисел A и B записывается как A B +. Запись B C + D * обозначает привычное нам (B + C) * D, а запись A B C + D * + означает A + (B + C) * D. Достоинство постфиксной записи в том, что она не требует скобок и дополнительных соглашений о приоритете операторов для своего чтения.

Дано выражение в обратной польской записи. Определите его значение.

Входные данные
В единственной строке записано выражение в постфиксной записи, содержащее однозначные числа и операции +, -, *. Строка содержит не более 100 чисел и операций.

Выходные данные
Необходимо вывести значение записанного выражения. Гарантируется, что результат выражения, а также результаты всех промежуточных вычислений по модулю меньше 231.
*/

// L4, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
#include <string>
 
//Класс саморасширяющийся массив(Надежный массив)
template<typename T>
class SafeArray {
    int size;
    int capacity;
    T *elements;
 public:
     SafeArray();
     explicit SafeArray(int capacity);
     ~SafeArray();
     T get_element(T pos);
     void push_back(T value);
     int get_size();
     void ensure_capacity();
     T pop_back();
     void decrease_capacity();
};
 
template<typename T>
SafeArray<T>::SafeArray() {
    size = 0;
    capacity = 3;
    elements = new T[capacity];
}
 
template<typename T>
SafeArray<T>::SafeArray(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    elements = new T[capacity];
}
 
template<typename T>
SafeArray<T>::~SafeArray() {
    delete[] this->elements;
    this->elements = nullptr;
}
 
template<typename T>
T SafeArray<T>::get_element(T pos) {
    if (pos < 0 || pos >= size) return NULL;
    else {
        return *(this->elements + pos);
    }
}
 
template<typename T>
void SafeArray<T>::push_back(T value) {
    if (size + 1 > capacity) { ensure_capacity(); }
    elements[size] = value;
    size++;
}
 
template<typename T>
int SafeArray<T>::get_size() {
    return size;
}
 
//метод расширения массива. Увеличиваем capacity двое, переносим элементы, чистим память
template<typename T>
void SafeArray<T>::ensure_capacity() {
    capacity = capacity * 2;
    T *new_elements = new T[capacity];
    for (int i = 0; i < size; ++i) {
        new_elements[i] = elements[i];
    }
    delete [] elements;
    elements = new_elements;
    new_elements = nullptr;
}
 
template<typename T>
T SafeArray<T>::pop_back() {
    T buff = elements[size - 1];
    elements[size - 1] = NULL;
    size--;
    if (size == capacity / 4) { decrease_capacity(); }
    return buff;
}
 
//метод сжатия массива. Уменьшаем массив в 2 раза,переносим элементы, чистим память.
template<typename T>
void SafeArray<T>::decrease_capacity() {
    capacity = capacity / 2;
    T* new_elements = new T[capacity];
    for (int i = 0; i < size; ++i) {
        new_elements[i] = elements[i];
    }
    delete[] elements;
    elements = new_elements;
    new_elements = nullptr;
}
 
//проверка на однозначные числа
bool is_digit(char check_char) {
    return (static_cast<int>(check_char) - '0' >= 0 && static_cast<int>(check_char) - '0' <= 9);
}
 
int main() {
    SafeArray<int> digits_stack;
    int operand1, operand2, intermediate_value = 0;
    std::string str_expression;
    std::getline(std::cin, str_expression);
    for (int i = 0; i < str_expression.length(); ++i) {
        if (str_expression[i] == ' ') continue;
        if (is_digit(str_expression[i])) {
            digits_stack.push_back(str_expression[i] - '0');
        } else {
            operand2 = digits_stack.pop_back();
            operand1 = digits_stack.pop_back();
            switch (str_expression[i]) {
            case '+': intermediate_value = operand1 + operand2; break;
            case '-': intermediate_value = operand1 - operand2; break;
            case '*': intermediate_value = operand1 * operand2; break;
            }
            digits_stack.push_back(intermediate_value);
        }
    }
    std::cout << digits_stack.pop_back();
    return 0;
}
