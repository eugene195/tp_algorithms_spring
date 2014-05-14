#include <iostream>
#include <malloc.h>
#include "math.h"
using namespace std;


void inline swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


void heap_make(int *arr, int n){
    for (int i = n/2; i >= 1; --i){
        for (int j = i; j <= n/2;){
            int k = 2*j;
            if (k+1 <= n && (arr[k] < arr[k+1])) {
                ++k;
            }
            if (arr[j] < arr[k]) {
                swap(arr, k, j);
                j = k;
            }
            else {
                break;
            }
        }
    }
}

void heap_pop(int *arr, int n){
    swap(arr[n], arr[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if ( i+1 < n && (arr[i] < arr[i+1])) {
            i += 1;
        }
        if (arr[i/2] < arr[i]) {
            swap(arr, i/2, i);
        }
    }
}

void heap_sort(int *data, int n){
    heap_make(data - 1, n);
    for(int i = 0; i < n; ++i){
        heap_pop(data - 1, n - i);
    }
}

void quickSort(int a[], int left, int right, int parts, int depth)
{
    int len = right - left;
    if(len <= 0)
        return;
    if(depth <= 0){
        heap_sort((a + left),  right-left+1 );
        return;
    }
    if (len < 33) { // insertion sort for tiny array
        for (int i = left + 1; i <= right; i++) {
            for (int j = i; j > left && a[j] < a[j - 1]; j--) {
                swap(a, j, j - 1);
            }
        }
        return;
    }
    // Three-part
    int third = len / parts;

    // "medians"
    int m1 = left  + third;
    int m2 = right - third;

    if (m1 <= left) {
        m1 = left + 1;
    }
    if (m2 >= right) {
        m2 = right - 1;
    }
    if (a[m1] < a[m2]) {
        swap(a, m1, left);
        swap(a, m2, right);
    }
    else {
        swap(a, m1, right);
        swap(a, m2, left);
    }
    // pivots
    int pivot1 = a[left];
    int pivot2 = a[right];

    // pointers
    int less  = left  + 1;
    int great = right - 1;

    // sorting
    for (int k = less; k <= great; k++) {
        if (a[k] < pivot1) {
            swap(a, k, less++);
        }
        else if (a[k] > pivot2) {
            while (k < great && a[great] > pivot2) {
                great--;
            }
            swap(a, k, great--);

            if (a[k] < pivot1) {
                swap(a, k, less++);
            }
        }
    }
    // swaps
    int dist = great - less;

    if (dist < 13) {
       parts++;
    }
    swap(a, less  - 1, left);
    swap(a, great + 1, right);

            // subarrays
    quickSort(a, left,   less - 2, parts, depth - 1);
    quickSort(a, great + 2, right, parts, depth - 1);

            // equal elements
    if (dist > len - 13 && pivot1 != pivot2) {
        for (int k = less; k <= great; k++) {
            if (a[k] == pivot1) {
                swap(a, k, less++);
            }
            else if (a[k] == pivot2) {
                swap(a, k, great--);

                if (a[k] == pivot1) {
                    swap(a, k, less++);
                }
            }
        }
    }
            // subarray
    if (pivot1 < pivot2) {
        quickSort(a, less, great, parts, depth - 1);
    }
}

int main()
{
    int *a = (int *)malloc(sizeof(int) * 25000000);
    int i = 0;
    for(;;) {
        int val;
        scanf("%d", &val);
        if(feof(stdin))
            break;
        a[i++] = val;
    }

    quickSort(a, 0, i-1, 3, (int(2*log(i)/0.30102999566398119521)));
    for(int j = 9; j < i; j+=10){
            printf("%d ", a[j]);
    }
    return 0;
}
