#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
/*
4_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/
using namespace std;

int partition(vector<int> &mas, int left, int right) {

    // Выбор произвольного элемента массива и обмен
    if (left!=right)
        swap(mas[left + rand() % (right - left)], mas[left]);
    int x = mas[left];

    // два счетчика справа
    int i = right+1;
    for (int j = right; j >= left; j--) {
        if (mas[j] >= x)
            swap(mas[--i],mas[j]);
    }
    return i;
}

int get_kth(vector<int> & arr, const int kth, int left, int right) {
    srand(time(NULL));
    while(1) {
        int pos = partition(arr, left, right);
//        cout << pos;

        if (pos < kth)
            left = pos + 1;
        else if (pos > kth)
            right = pos - 1;
        else
            return arr[kth];
    }
}

int main() {
    int len, kth;
    cin >> len >> kth;

    vector<int> array;
    int item;
    for (int i = 0; i < len; ++i) {
        cin >> item;
        array.push_back(item);
    }

    cout << get_kth(array, kth, 0, len - 1);

    return 0;
}

