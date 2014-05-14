#include <iostream>
#include <malloc.h>
#include <vector>
using namespace std;

/*
3_3. «акраска пр€мой 1.

Ќа числовой пр€мой окрасили N отрезков. »звестны координаты левого и правого концов каждого отрезка (Li и Ri). 
Ќайти длину окрашенной части числовой пр€мой.
*/

struct edge{
    int val;
    bool is_left;
};
struct pnt{
    int x, y;
};

void Merge(struct edge* A, int left, int mid, int right){
    int first = left;
    int second = mid + 1;
    int write = 0;
    struct edge* tmp = new struct edge[right - left + 1];
    while(first <= mid && second <= right){
        if(A[first].val < A[second].val)
            tmp[write++] = A[first++];
        else
            tmp[write++] = A[second++];
    }

    while(second <= right)
        tmp[write++] = A[second++];
    while(first <= mid)
        tmp[write++] = A[first++];

    for(write = 0; write < right-left + 1; write++)
       A[left + write] = tmp[write];
}

void MergeSort(struct edge* A, int left, int right){
    int mid;
    if(left < right){
        mid = (left + right) / 2.0;

        MergeSort(A, left, mid);
        MergeSort(A, mid + 1, right);
        Merge(A, left, mid, right);
    }
}

int input_lines(vector<struct pnt> &in, unsigned int lne_count){
    int buf_value;
    struct pnt buf;
    for(unsigned int i = 0; i < lne_count; ++i){
        cin >> buf_value;
        buf.x = buf_value;
        cin >> buf_value;
        buf.y = buf_value;
        in.push_back(buf);
    }
    return 0;
}

int create_output(std::vector<struct edge> & output, std::vector<struct pnt> input, unsigned int lne_count){
    for(unsigned int i = 0; i < lne_count; ++i){
        output[2 * i].val = input[i].x;
        output[2 * i].is_left = 0;

        output[2 * i + 1].val = input[i].y;
        output[2 * i + 1].is_left = 1;
    }
    return 0;
}

int get_result(struct edge* a, int count){
    int result = 0;
    int flag = 0;
    for(int i = 0; i < count * 2; ++i){
        if(flag && i){
            int buf = a[i].val;
            int buf1 = a[i - 1].val;
            result = result + buf - buf1;
        }
        if(a[i].is_left)
            flag ++;
        else
            flag --;
    }
    return result;
}

int main()
{
    std::vector<struct pnt> in_vec;
    std::vector<struct edge> out_vec;
    struct edge* output;

    struct edge nullEdge;
    nullEdge.is_left = 0;
    nullEdge.val = 0;

    unsigned int lne_count;
    cin >> lne_count;

    out_vec.resize(lne_count*2, nullEdge);
    if(!(output = (struct edge*)malloc(sizeof(struct edge) * lne_count * 2))){
        return -1;
    }

    input_lines(in_vec, lne_count);
	
    create_output(out_vec, in_vec, lne_count);
    for(int i = 0; i < out_vec.size(); ++i){
        output[i] = out_vec[i];
    }

    MergeSort(output, 0, lne_count * 2);
    output++;
	
    int result = get_result(output, lne_count);
    cout << result;
	
    return 0;
}

