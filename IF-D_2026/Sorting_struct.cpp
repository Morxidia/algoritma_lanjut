#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <functional>
using namespace std;

struct Mahasiswa
{
    string nama;
    string ID;
    void print()
    {
        cout << "Nama\t: " << nama << "\nID\t: " << ID << endl;
    }
};

extern string randName[100];
Mahasiswa *GenRandUsers(int size);
int GenRand(int start, int end);
void printArray(Mahasiswa *Array, int size);

/*
    Change the code below to complete the test
*/

int partition(Mahasiswa Arr[], int low, int high)
{
    int pivot = high;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (Arr[j].ID <= Arr[pivot].ID)
        {
            i++;
            Mahasiswa temp = Arr[i];
            Arr[i] = Arr[j];
            Arr[j] = temp;
        }
    }
    Mahasiswa temp = Arr[i + 1];
    Arr[i + 1] = Arr[pivot];
    Arr[pivot] = temp;
    return (i + 1);
}

void Quicksort(Mahasiswa Arr[], int low, int high)
{
    if (low < high)
    {
        int indexPivot = partition(Arr, low, high);
        Quicksort(Arr, low, indexPivot - 1);
        Quicksort(Arr, indexPivot + 1, high);
    }
}
/*
    change above code to complete the test
*/

int main(void)
{
    int sizeMahasiswa = 20;
    Mahasiswa *Array = GenRandUsers(sizeMahasiswa);
    cout << "Array sebelum : " << endl;
    printArray(Array, sizeMahasiswa);

    Quicksort(Array, 0, sizeMahasiswa - 1);

    // this should not be allowed
    cout << "Array setelah : " << endl;
    printArray(Array, sizeMahasiswa);
    delete[] Array;
    return 0;
}

/*
    do not change the code below, it is used to generate random Mahasiswa data for testing the sorting algorithm
*/
int GenRand(int start, int end)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(start, end);
    return dist(mt);
}

Mahasiswa *GenRandUsers(int size)
{
    int totalNames = sizeof(randName) / sizeof(randName[0]);

    if (size > totalNames || size > 255)
    {
        throw invalid_argument("Size must be less than or equal to the number of unique names and IDs available.");
    }

    int start = 1;
    int end = 255;
    unordered_set<int> uniqueIDs;
    unordered_set<int> uniqueIndexes;
    Mahasiswa *Array = new Mahasiswa[size];
    for (int i = 0; i < size; i++)
    {
        int currentID;
        int currentNameIndex;
        do
        {
            currentID = GenRand(start, end);
            currentNameIndex = GenRand(0, totalNames - 1);
        } while (uniqueIDs.find(currentID) != uniqueIDs.end() || uniqueIndexes.find(currentNameIndex) != uniqueIndexes.end());
        uniqueIDs.insert(currentID);
        uniqueIndexes.insert(currentNameIndex);

        ostringstream oss;
        oss << "123250" << setfill('0') << setw(3) << currentID;
        Array[i].nama = randName[currentNameIndex];
        Array[i].ID = oss.str();
    }
    return Array;
}

void printArray(Mahasiswa *Array, int size)
{
    cout << "Daftar Mahasiswa:\n";
    cout << "---------------------------------\n";
    for (int i = 0; i < size; i++)
    {
        Array[i].print();
        cout << "---------------------------------\n";
    }
}

string randName[100] = {
    "Aditya Saputra", "Ahmad Fauzi", "Andi Wijaya", "Anisa Putri", "Arianto Nugroho",
    "Bambang Hermanto", "Budi Santoso", "Citra Lestari", "Dewi Sartika", "Dian Prasetyo",
    "Eka Ramadhan", "Endang Sulastri", "Fajar Hidayat", "Farida Utami", "Gita Permata",
    "Hadi Kusuma", "Hafiz Pratama", "Indah Cahyani", "Irfan Hakim", "Joko Susilo",
    "Kartika Sari", "Kurniawan Dwi", "Larasati Putri", "Lukman Hakim", "Maya Indah",
    "Muhammad Rizky", "Nadia Safira", "Nur Hasanah", "Oki Setiawan", "Putu Gede",
    "Ratih Purwasih", "Reza Rahadian", "Siti Aminah", "Slamet Riyadi", "Tri Wahyuni",
    "Utami Ningsih", "Vina Panduwinata", "Wahyu Hidayat", "Yanto Basna", "Zulkifli Lubis",
    "Agus Setiawan", "Bayu Pamungkas", "Chandra Kirana", "Dedi Mulyadi", "Eko Prasetyo",
    "Fitriani Bakri", "Guntur Romli", "Hendra Gunawan", "Intan Permatasari", "Jajang Mulyana",
    "Kiki Amalia", "Lutfi Alwi", "Maman Abdurrahman", "Nina Marlina", "Oman Rachman",
    "Puji Astuti", "Qori Sandioriva", "Rendra Karno", "Santi Widiyanti", "Taufik Hidayat",
    "Ujang Hermawan", "Vera Feriska", "Wawan Ridwan", "Xena Gabriella", "Yayan Ruhian",
    "Zainal Abidin", "Asep Sunandar", "Beni Irawan", "Cecep Rahman", "Dadan Hamdani",
    "Encep Nurjaman", "Feri Irawan", "Gani Wardhana", "Heryanto Putra", "Iwan Fals",
    "Junaedi Sitorus", "Kusnadi Wijaya", "Lilis Surjani", "Mulyadi Jaya", "Nanang Iskandar",
    "Onny Sastro", "Pipit Fitriani", "Rahmat Hidayat", "Soleh Solihun", "Tatang Sutarma",
    "Umar Bakri", "Vicky Prasetyo", "Wati Setiawati", "Yuni Shara", "Zaki Iskandar",
    "Ade Irma", "Bagas Adi", "Cici Paramida", "Dodo Zakaria", "Euis Dahlia",
    "Fanny Fadillah", "Ginanjar Saputra", "Hesti Purwadinata", "Imas Masitoh", "Jajang C. Noer"};