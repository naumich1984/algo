/*
D. Количество инверсий
ограничение по времени на тест5 секунд
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Напишите программу, которая для заданного массива A=⟨a1,a2,…,an⟩ находит количество пар (i,j) таких, что i<j и ai>aj.

Входные данные
Первая строка входного файла содержит натуральное число n (1≤n≤500000) — количество элементов массива. Вторая строка содержит n попарно различных элементов массива A (0≤ai≤106).

Выходные данные
В выходной файл выведите одно число — ответ на задачу.*/

// L1, task: D, DS-12 Naumovskiy Alexey
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


void merge(int* array, int idx_left, int idx_middle, int idx_right, long long &invCount)
{
    int i_left = idx_left;
    int j_right = idx_middle +1;
    int idx_all = idx_left;
    int* buff = new int[idx_right + 1];//вспомогательный массив

    while (i_left <= idx_middle && j_right <= idx_right)
    {
        if (array[i_left] < array[j_right])
        {
            buff[idx_all] = array[i_left];
            i_left++;
        }
        else //элемент из левой части больше, чем из правой - значит нужна перестановка
        { 
            buff[idx_all] = array[j_right];
            j_right++;
            invCount += ((long long)idx_middle - (long long)i_left + 1L); //счетчик инверсий
        }
        idx_all++;
    }
    while (i_left <= idx_middle) {
        buff[idx_all] = array[i_left];
        idx_all++;
        i_left++;
    }
    while (j_right <= idx_right) {
        buff[idx_all] = array[j_right];
        idx_all++;
        j_right++;
    }
    for (i_left = idx_left; i_left < idx_all; i_left++)
    {
        array[i_left] = buff[i_left];
    }
        
    delete[] buff;
}

void mergeSortArray(int* array, int idx_left, int idx_right, long long &invCount)
{
    int idx_middle = (idx_left + idx_right) / 2;//середина
    if (idx_right == idx_left) //терминальное условие
    {
        return;
    }
    mergeSortArray(array, idx_left, idx_middle, invCount); //сортируем левую часть(до середины)
    mergeSortArray(array, idx_middle + 1, idx_right, invCount); //сортируем правую часть (от середины)
    merge(array, idx_left, idx_middle, idx_right, invCount);//слияние
}


int main()
{
    int SIZE_ARR = 0;
    long long inversCount = 0;
    cin >> SIZE_ARR;

    int* my_array = new int[SIZE_ARR];
    FillArray(my_array, SIZE_ARR);
    mergeSortArray(my_array, 0, SIZE_ARR - 1, inversCount);
    cout << inversCount;

    delete[]my_array;
}

