/*
B. Излишне простая сортировка
ограничение по времени на тест2 секунды
ограничение по памяти на тест64 мегабайта
вводстандартный ввод
выводстандартный вывод
Дан небольшой массив целых чисел. Ваша задача — отсортировать его в порядке неубывания.

Входные данные
В первой строке входного файла содержится число N (1 ≤ N ≤ 1000) — количество элементов в массиве. Во второй строке находятся N целых чисел, по модулю не превосходящих 109.

Выходные данные
В выходной файл надо вывести этот же массив в порядке неубывания, между любыми двумя числами должен стоять ровно один пробел.
*/

// L1, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
using namespace std;
 
void FillArray(int *array, const int sizeArr)
{
    for (int i = 0; i < sizeArr; i++)  cin >> array[i];
}
 
void PrintArray(const int *array, const int sizeArr)
{
    for (int i = 0; i < sizeArr; i++) cout << array[i] << " ";
    cout << endl;
}
 
void BubbleSortArray(int *array, const int sizeArr) 
{
    // счетчик перестановок в очередном проходе (если при проходе перестановок не будет - значит массив отсортирован)
    int countBubbles;
    // проход по всему массиву (N-1 шагов)
    for (int i = 0; i < (sizeArr - 1); i++)
    {
        countBubbles = 0;
        // продох до N - i -1 элемента, так как после каждого прохода основного цикла 
        // макс.элемент "вспылвает" в конец массива и до самого конца массива можно не идти
        for (int j = 0; j < (sizeArr - i - 1); j++)
        {
             if (array[j] > array[j + 1])
            {
                //меняем местами("три стакана") если текущий больше следующего
                int tempBuff = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tempBuff;
                countBubbles++;
            }
        }
        //если за очередной проход не было ни одной перестановки - значит массив отсортирован
        // можно прервать выполнение
        if (countBubbles == 0) break;
    }
}
 
int main()
{
    int SIZE_ARR = 0;
    cin >> SIZE_ARR;
    int *my_array = new int[SIZE_ARR];
 
    FillArray(my_array, SIZE_ARR);
    BubbleSortArray(my_array, SIZE_ARR);
    PrintArray(my_array, SIZE_ARR);
    delete[] my_array;
    return 0;
}
 
