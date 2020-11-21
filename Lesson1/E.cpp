
/*
E. Простая сортировка
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

// L1, task: E, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
using namespace std;

//Для отладки
void RandomFillVector(vector<int>& my_vector)
{
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it)
    {
        *it = rand() % my_vector.size();
    }
}

void FillVector(vector<int>& my_vector)
{
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it)
    {
        cin >> *it;
    }
}

void PrintVector(vector<int>& my_vector)
{
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it)
    {
        cout << *it << " ";
    }
}

void swap(int* valueA, int* valueB)
{
    //три стакана
    int buffPtr = *valueA;
    *valueA = *valueB;
    *valueB = buffPtr;
}
//находим серединную позицию
int Partition(std::vector<int>& array, int idx_left, int idx_right) 
{
    int amid = array[idx_left];
    int idx_lo_mid = idx_left;
    int idx_hi_mid = idx_right;

    while (1) 
    {   //движемся от крайнего левого значения к серединному(пока левое не превысит серединное)
        while (array[idx_lo_mid] < amid) idx_lo_mid++; 
        //движемся от крайнего правого значения к серединному(пока серединное не превысит правое )
        while (array[idx_hi_mid] > amid) idx_hi_mid--; 
        if (idx_lo_mid >= idx_hi_mid)
        {
            return idx_hi_mid; //индекс нового серединного значения
        }
        swap(array[idx_lo_mid], array[idx_hi_mid]); //меньший/равный переносим влево
        //сдвигаем индексы после swap-а
        idx_hi_mid--;
        idx_lo_mid++;
    }
}

void QuickSort(std::vector<int>& array, int idx_left, int idx_right) 
{
    if (idx_left < idx_right) {
        int idx_amid = Partition(array, idx_left, idx_right);
        QuickSort(array, idx_left, idx_amid);
        QuickSort(array, idx_amid + 1, idx_right);
    }
}

int main()
{
    int SIZE_ARR = 0;
    cin >> SIZE_ARR;
    std::vector <int> my_vector(SIZE_ARR);
    FillVector(my_vector);
    QuickSort(my_vector, 0, my_vector.size() - 1);
    PrintVector(my_vector);

    return 0;
}
