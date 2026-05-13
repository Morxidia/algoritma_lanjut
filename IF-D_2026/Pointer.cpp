#include <iostream>
using namespace std;

int *arrOfrRange(int a, int b)
{
    int size = b - a;
    int *ptr = (int *)malloc(sizeof(int) * size);
    for (int i = a; i < b; i++)
    {
        *(ptr + i) = i;
    }
    return ptr;
}

int main(void)
{
    int *arr = arrOfrRange(1, 5);

    for (int i = 1; i < 5; i++)
    {
        cout << *(arr + i) << endl;
    }

    // // (label_data *)malloc(sizeof(tipe_data) * berapa_kotak)
    // int *ptr = (int *)malloc(sizeof(int));
    // *ptr = 5;
    // changePtr(&ptr);
    // cout << *ptr << endl;

    // char kata[] = "katakata";
    // char *ptr = "katakata";

    // int angka[] = {1, 2, 3, 5};

    // int *ptr = angka;

    // cout << angka << endl;
    // cout << ptr << endl;
    // cout << 2[ptr] << endl;
    // cout << *(2 + ptr) << endl;

    // char *ptr = kata;
    // cout << ptr << endl;
    // int a = 9;
    // int *ptr = &a;
    // ptr += 4;
    // *ptr += 4;
    // cout << *ptr << endl;
    // cout << a << endl;

    // int a = 6;      // 4 byte
    // double b = 8.6; // 8 byte
    // int *ptr = &a;  // bisa menyimpan alamat dengan label apapun
    // sebuah variable pointer itu ukuran pasti 8 byte

    // int *ptr = nullptr /* kosong */;

    // int x = 6;
    // int *ptr = &x;
    // cout << *ptr << endl;
    // cout << *(&x) << endl;
    // cout << ptr << endl;
    // cout << &ptr << endl;
}