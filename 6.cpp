#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
/*
6_1. MSD для строк.

Дан массив строк. Количество строк не больше 105. 
Отсортировать массив методом поразрядной сортировки MSD по символам. 
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
*/
using namespace std;

struct StringNode{
    const char *str; //указатель на строку
    StringNode *next;
};

StringNode *strMSD(StringNode *pList, unsigned int iDigit )
{

    const int iRange = 256;

  //массив bucket-ов (под-списков)
    StringNode *buckets[iRange];
    memset(buckets, 0, sizeof(buckets) );

    StringNode **ppNextItem[iRange];
    for (int i = 0; i < iRange; i++)
        ppNextItem[i] = &buckets[i];


    while (pList)
    {
        StringNode* temp = pList;
        pList=pList->next;

        temp->next=NULL;

        unsigned char c = (unsigned char)temp->str[iDigit];
        *ppNextItem[c]=temp;
        ppNextItem[c]=&temp->next;
    }


    StringNode* pResult = NULL;
    StringNode** ppNext = &pResult;


    *ppNext = buckets[0];
    while (*ppNext)
        ppNext = &((*ppNext)->next);

    for (int i = 1; i < iRange; i++)
    {
        if ( !buckets[i] )
        continue;

        if (buckets[i]->next == NULL)
            *ppNext = buckets[i];
        else
            *ppNext = strMSD(buckets[i], iDigit + 1);

        while (*ppNext)
            ppNext=&((*ppNext)->next);
    }

    return pResult;
}

int main()
{
    vector<string> strVec;
    string str;

    for(;str != "end";) {
        std::cin >> str;
        if (std::cin.eof()) break;
        strVec.push_back(str);
    }

    StringNode* pList = NULL;
    StringNode** ppCurr = &pList;
    for ( unsigned int i=0 ; i<strVec.size(); i++) {
        *ppCurr = new StringNode();
        (*ppCurr )->str = strVec[i].c_str();
        (*ppCurr )->next = NULL;
        ppCurr = &(*ppCurr)->next;
    }

    pList = strMSD(pList, 0);

    while(pList)
    {
        std::cout << pList->str;
        std::cout << endl;
        StringNode* tmp = pList;
        pList = pList->next;
        delete tmp;
    }
    return 0;
}
