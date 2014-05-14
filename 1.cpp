#include <iostream>
#include <vector>
// 1_3. Сортировка пузырьком.
using namespace std;

typedef int* iterator_t;

struct less_t{
    bool operator() (const int &lhs, const int &rhs) const {
        return lhs > rhs;
    }
};

void swap(iterator_t a, iterator_t b){
    iterator_t buf = a;
    a = b;
    b = buf;
}

void sort_(iterator_t begin, size_t size, less_t const &less){
    for(size_t i = 0; i < size - 1; ++i){
        int swapped = 0;
        for(size_t j = 0; j < size - i - 1; ++j){
            if(less(*(begin + j), *(begin + j + 1))){
                swapped = 1;
                swap(begin[j], begin[j + 1]);
            }
        }
        if(!swapped)
            break;
    }
}

int main()
{
    std::vector <int> data;
    less_t less;
    for(;;) {
        int value;
        std::cin >> value;
        if (std::cin.eof()) break;

        data.push_back(value);
    }
    sort_(&data[0], data.size(), less);
    for(size_t i = 0; i < data.size(); i++){
        std::cout << data[i] << endl;
    }
    return 0;
}

