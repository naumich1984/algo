/*
C. Простая сортировка
ограничение по времени на тест2 секунды
ограничение по памяти на тест64 мегабайта
вводстандартный ввод
выводстандартный вывод
Дан массив целых чисел. Ваша задача — отсортировать его в порядке неубывания.

Входные данные
В первой строке входного файла содержится число N (1 ≤ N ≤ 100 000) — количество элементов в массиве. Во второй строке находятся N целых чисел, по модулю не превосходящих 109.

Выходные данные
В выходной файл надо вывести этот же массив в порядке неубывания, между любыми двумя числами должен стоять ровно один пробел.
*/

// L1, task: C, DS-12 Naumovskiy Alexey
#include <iostream>
using namespace std;

void FillArray(int* array, const int sizeArr)
{
    for (int i = 0; i < sizeArr; i++)  cin >> array[i];
}

void PrintArray(const int* array, const int sizeArr)
{
    for (int i = 0; i < sizeArr; i++) cout << array[i] << " ";
    cout << endl;
}

void merge(int *array, int idx_left, int idx_middle, int idx_right)
{
    int i, j;
    int* buff = new int[idx_right + 1]{};//вспомогательный массив
    for (i = idx_middle + 1; i > idx_left; i--) buff[i - 1] = array[i - 1];
    for (j = idx_middle; j < idx_right; j++)
    {
        buff[idx_right + idx_middle - j] = array[j + 1];
    }
    for (int k = idx_left; k <= idx_right; k++)//сливаем части в одну (минимальный первым)
        if (buff[j] < buff[i])
            array[k] = buff[j--];
        else
            array[k] = buff[i++];
    
    delete[] buff;
}

void mergeSortArray(int* array, int idx_left, int idx_right)
{
    int idx_middle = (idx_left + idx_right) / 2;//середина
    if (idx_right == idx_left) //терминальное условие
    {
        return;
    }
    mergeSortArray(array, idx_left, idx_middle); //сортируем левую часть(до середины)
    mergeSortArray(array, idx_middle + 1, idx_right); //сортируем правую часть (от середины)
    merge(array, idx_left, idx_middle, idx_right);//слияние
}


int main()
{
    int SIZE_ARR = 0;
    cin >> SIZE_ARR;
    int* my_array = new int[SIZE_ARR];
    FillArray(my_array, SIZE_ARR);
    mergeSortArray(my_array, 0, SIZE_ARR-1);
    PrintArray(my_array, SIZE_ARR);
    
    delete[]my_array;
}

