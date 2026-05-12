#include <iostream>
#define ASTERISK *
using namespace std;

void outAddPtr(int ASTERISK ASTERISK ptr)
{
    *ptr = (int *)malloc(sizeof(int) * 2);
    // *(*(ptr + 1 ))
    (*ptr)[1] = 5;
    cout << (*ptr)[1] << endl;
}

int main(void)
{
    int ASTERISK p = (int *)malloc(sizeof(int));
    *p = 9;
    outAddPtr(&p);
    cout << p[1] << endl;
    // int a = 5;
    // int *p = &a;

    // increment(&a);
    // cout << *p << endl;

    // buat array dengan pointer??
    // double *arr = (double *)malloc(sizeof(double) * 3);
    // arr[1] = 5.6;
    // cout << arr[1] << endl;

    // char arr[] = "abcdefg";
    // char *pString = arr;
    // char *str = "bvdsg";
    // cout << *(str + 2) << endl;
    // string *p; // harus di isi dengan alamat varible string

    // pointer nyimpen alamat
    // int arr[] = {1, 2, 3};
    // int *pArr = arr;
    // cout << *(pArr + 0) << endl;
    // cout << &pArr << endl;
    // cout << &arr << endl;

    // int x = 5;
    // double b = 5.6;
    // int *p;
    // p = &x;
    // p = (int *)malloc(sizeof(int));
    // *p = 6;
    // cout << "x : " << x << endl;
    // cout << "alamat x : " << &x << endl;
    // cout << "ptr : " << p << endl;
    // cout << "nilai dari alamat ptr : " << *p << endl;
}
