#include <iostream>
#include <stdio.h>

using namespace std;

struct box{
    int x, y, z, num;
};

/*
2_1. Ящики.

На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0. 
Известно, что их все можно сложить один в один (то есть так, что каждый следующий помещается в предыдущий). 
Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям станут 
строго меньше размеров другого ящика по соответствующим осям. 
Требуется определить, в какой последовательности они будут вложены друг в друга. Вывести номера ящиков.
*/

bool less_box(box left, box right){
    return left.x < right.x;
}

void print(box *data, int n){
    for(int i = 0; i < n; ++i){
        printf("%d ", data[i].num);
    }
}

void heap_make(box *arr, int n){
    for (int i = n/2; i >= 1; --i){
        for (int j = i; j <= n/2;){
            int k = 2*j;
            if (k+1 <= n && less_box(arr[k], arr[k+1])) {
                ++k;
            }
            if (less_box(arr[j], arr[k])) {
                swap(arr[k],arr[j]);
                j = k;
            }
            else {
                break;
            }
        }
    }
}

void heap_pop(box *arr, int n){
    swap(arr[n], arr[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if ( i+1 < n && less_box(arr[i], arr[i+1])) {
            i += 1;
        }
        if (less_box(arr[i/2], arr[i])) {
            swap(arr[i/2], arr[i]);
        }
    }
}

void heap_sort(box *data, int n){
    heap_make(data - 1, n);
    for(int i = 0; i < n; ++i){
        heap_pop(data - 1, n - i);
    }

    print(data, n);
}

void input_box(box *element){

    scanf("%d", &element->x);
    scanf("%d", &element->y);
    scanf("%d", &element->z);
}

void normalize_box(box *el){
    if(el->y < el->z)
        swap(el->y, el->z);
    if(el->x < el->y)
        swap(el->x, el->y);
}



int main()
{
    int count;
    cin >> count;
    box data[count];
    for(int i = 0; i < count; ++i){
        input_box(&data[i]);
        data[i].num = i;
        normalize_box(&data[i]);
    }
    heap_sort(data, count);
    return 0;
}

