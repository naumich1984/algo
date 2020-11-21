/*
см. F.pdf
*/

// L1, task: F, DS-12 Naumovskiy Alexey
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
 
using namespace std;
int romanToarab(string romanDigit) 
{
    map<char, int> dictRomanArabic = { {'I', 1}, {'V', 5},{'X', 10},{'L', 50},
    {'C', 100},{'D', 500},{'M', 1000} };
 
    int arabic = 0;
    for (int i = 0; i < romanDigit.length(); i++) 
    {
        if (dictRomanArabic[romanDigit[i + 1]] <= dictRomanArabic[romanDigit[i]])
        {
            arabic += dictRomanArabic[romanDigit[i]];
        }
        else
        {
            arabic -= dictRomanArabic[romanDigit[i]];
        }
    }
    return arabic;
}
 
bool compar(string a, string b) 
{
    return romanToarab(a) < romanToarab(b);
}
 
int main()
{
    int N = 0;
    string KingName = "";
    string KingNumber = "";
    // словарь для хранения цифр(массив на случай одинаковых имен) королей.
    map <string, vector<string>> dictKingNum;
 
    cin >> N;
    //50(max) по условию задачи. Отдельно(для удобства их сортировки) храним имена
    string KingNames[50]; 
    for (int i = 0; i < N; i++) 
    {
        cin >> KingName >> KingNumber;
        KingNames[i] = KingName;
        dictKingNum[KingName].push_back(KingNumber);
        //поддерживаем цифры королей с одинаковыми именами в порядке возрастания
        sort(dictKingNum[KingName].begin(), dictKingNum[KingName].end(), compar);
    }
 
    //сортируем имена королей в лексикографическом порядке
    sort(KingNames, KingNames+N);
 
    string prev = ""; //будем отслеживаем предыдущее имя - для борьбы с дубликатами имен
    for (auto now : KingNames)
    {   
        if (now.compare(prev) == 0) continue;
        //для каждого короля выводим все цифры в порядке возрастания
        for (std::vector<string>::iterator  it = dictKingNum[now].begin(); it != dictKingNum[now].end(); ++it)
        {
            cout << now <<" "<< *it <<endl;
        }
        prev = now;
    }
}
 
