#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <unordered_set>
using namespace std;

struct Product
{
    string nama;
    double weight;
    string productId;

    void print()
    {
        cout << "Nama\t: " << nama << "\nID\t: " << productId  << fixed << setprecision(2) << "\nWeight\t: " << weight << " kg" << endl;
    }
};

extern string randName[100];
Product *GenRandProduct(int size);
void printArray(Product Array[], int size);
bool checkSortIdAsc(const Product arr[], int size);
bool checkSortIdDsc(const Product arr[], int size);

/*
    Change the code below to complete the test
*/

void yourSortHere(/*Change parameter as desire*/){
    /* Function body */
}

/*
    change above code to complete the test
*/

int main(void)
{
    // ubah ukuran list product disini, tidak boleh lebih dari 100
    int sizeProduct = 10;

    Product *Array = GenRandProduct(sizeProduct);
    cout << "Data sebelum di sorting" << endl;
    printArray(Array, sizeProduct);
    
    // call you sorting function
    yourSortHere();
    
    cout << "Data setelah di sorting" << endl;
    printArray(Array, sizeProduct);

    cout << "Data sudah tersorting? : " << (checkSortIdAsc(Array, sizeProduct)? "sudah" : "belum") << endl;

    delete[] Array;
    return 0;
}

/*
    do not change the code below, it is used to generate random Product data for testing the sorting algorithm
*/

int GenRandNum(int start, int end)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(start, end);
    return dist(mt);
}

double randFloat(int start, int end)
{
  static std::random_device rd;
  static std::mt19937 mt(rd());
  std::uniform_real_distribution<> dist(start, end);
  return dist(mt);
}

bool checkSortIdAsc(const Product arr[], int size){
    for(int i=0; i < size-1 ; i++){
        if(arr[i].productId > arr[i+1].productId){
            return false;
        }
    }
    return true;

}

bool checkSortIdDsc(const Product arr[], int size){
    for(int i=0; i < size-1 ; i++){
        if(arr[i].productId < arr[i+1].productId){
            return false;
        }
    }
    return true;
}

Product *GenRandProduct(int size)
{
    int totalNames = sizeof(randName) / sizeof(randName[0]);

    if (size > totalNames)
    {
        throw invalid_argument("Size must be less than or equal to the number of unique products available.");
    }

    unordered_set<int> uniqueIDs;
    unordered_set<int> uniqueIndexes;
    Product *Array = new Product[size];
    for (int i = 0; i < size; i++)
    {
        int currentID;
        int currentNameIndex;
        do
        {
            currentID = GenRandNum(100, (totalNames*2)+100);
            currentNameIndex = GenRandNum(0, totalNames - 1);
        } while (uniqueIDs.find(currentID) != uniqueIDs.end() || uniqueIndexes.find(currentNameIndex) != uniqueIndexes.end());
        uniqueIDs.insert(currentID);
        uniqueIndexes.insert(currentNameIndex);

        ostringstream oss;
        oss << "ID-TK01-" << setfill('0') << setw(3) << currentID;
        Array[i].nama = randName[currentNameIndex];
        Array[i].weight = randFloat(1, 10);
        Array[i].productId = oss.str();
    }
    return Array;
}

void printArray(Product Array[], int size)
{
    cout << "Daftar Product:\n";
    cout << "---------------------------------\n";
    for (int i = 0; i < size; i++)
    {
        Array[i].print();
        cout << "---------------------------------\n";
    }
}

string randName[100] = {
    "Beras Setra Ramos", "Minyak Goreng Sawit", "Gula Pasir Kristal", "Garam Dapur Beriodium", "Susu Kental Manis",
        "Kopi Bubuk Arabika", "Teh Celup Melati", "Mie Instan Rasa Ayam Bawang", "Telur Ayam Negeri", "Sabun Mandi Cair 450ml",
        "Shampoo Anti Ketombe", "Pasta Gigi Herbal", "Sikat Gigi Soft", "Deterjen Bubuk Premium", "Pembersih Lantai Karbol",
        "Tisu Wajah 250 sheets", "Pembalut Wanita Wing", "Popok Bayi Ukuran M", "Bedak Bayi Wangi", "Minyak Kayu Putih 120ml",
        "Biskuit Gandum Utuh", "Cokelat Batangan Almond", "Keripik Singkong Pedas", "Kacang Goreng Asin", "Air Mineral 600ml",
        "Jus Jeruk Kemasan", "Minuman Bersoda 1.5L", "Kecap Manis Botol", "Saus Sambal Ekstra Pedas", "Mentega Margarin Serbaguna",
        "Tepung Terigu Protein Sedang", "Sabun Cuci Piring Jeruk Nipis", "Pewangi Pakaian Konsentrat", "Obat Nyamuk Semprot", "Lampu LED 10 Watt",
        "Baterai AA Isi 4", "Kipas Angin Meja", "Rice Cooker Digital", "Blender Jus Buah", "Setrika Listrik Otomatis",
        "Televisi LED 32 Inci", "Smartphone Android 128GB", "Laptop Core i5 8GB", "Mouse Wireless Ergonomis", "Keyboard Mechanical Blue Switch",
        "Headset Gaming Stereo", "Powerbank 10000mAh", "Kabel Data Type-C Fast Charge", "Speaker Bluetooth Portable", "Jam Tangan Digital Sport",
        "Sepatu Lari Pria", "Sandal Jepit Karet", "Kaus Polos Cotton Combed", "Celana Jeans Denim", "Jaket Hoodie Fleece",
        "Tas Ransel Sekolah", "Dompet Kulit Sapi", "Topi Baseball Polos", "Kaos Kaki Semata Kaki", "Ikat Pinggang Kulit",
        "Buku Tulis A5 Isi 38", "Pulpen Gel Hitam 0.5mm", "Pensil 2B Ujian", "Penghapus Putih Bersih", "Penggaris Besi 30cm",
        "Map Dokumen Plastik", "Stapler Kecil HD-10", "Gunting Kertas Stainless", "Lem Kertas Cair", "Kalkulator Ilmiah",
        "Panci Stainless Steel 20cm", "Wajan Anti Lengket Teflon", "Pisau Dapur Set", "Talenan Kayu Jati", "Piring Keramik Putih",
        "Gelas Kaca Bening", "Sendok Makan Stainless", "Garpu Makan Stainless", "Botol Minum Tumblr 500ml", "Kotak Makan Siang BPA Free",
        "Sabun Cuci Muka Pria", "Krim Pelembab Wajah", "Sunscreen SPF 50 PA+++", "Parfum Maskulin 100ml", "Lipstik Matte Tahan Lama",
        "Masker Wajah Sheet Mask", "Hand Cream Wangi Bunga", "Vitamin C 500mg Isi 30", "Plester Luka Transparan", "Antiseptik Cair 95ml",
        "Helm Motor SNI Full Face", "Oli Mesin Motor Matic", "Ban Dalam Sepeda 26 Inci", "Pompa Angin Manual", "Kunci Inggris 10 Inci",
        "Obeng Plus Minus Magnetic", "Palu Kambing Baja", "Gergaji Kayu Tajam", "Meteran Gulung 5 Meter", "Senter LED Rechargeable"
};