#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <functional>
using namespace std;

// header untuk tampilan
#define HEADER_LEN 120
#define NUMBER_LEN 5
#define NAMA_LEN 30
#define KET_LEN 20
#define POPULASI_LEN 25
#define HABITAT_LEN 40

struct satwa {
    long long populasi;
    string namaHewan;
    string keterangan;
    string habitat;

    void print(int nameField, int ketField, int popField, int habField) {
        cout << left << setw(nameField) << namaHewan;
        cout << left << setw(ketField)  << keterangan;
        cout << left << setw(popField)  << (to_string(populasi) + " ekor");
        cout << left << setw(habField)  << habitat << endl;
    }
};

void printData(satwa data, int nameField, int ketField, int popField, int habField) {
    cout << left << setw(nameField) << data.namaHewan;
    cout << left << setw(ketField)  << data.keterangan;
    cout << left << setw(popField)  << (to_string(data.populasi) + " ekor");
    cout << left << setw(habField)  << data.habitat;
    cout << endl;
}

string replaceChar(string text, char source, char target) {
    string newtext = text;
    for(size_t i = 0; i < text.length(); i++) {
        if(text[i] == source)
            newtext[i] = target;   
    }
    return newtext;
}

string replaceSpacetoUnderscore(string text) {
    return replaceChar(text, ' ', '_');
}

string replaceUnderscoretoSpace(string text) {
    return replaceChar(text, '_', ' ');
}

string stringTolower(string text) {
    for(char& word : text) {
        word = (char)tolower(word);
    }
    return text;
}

string stringToupper(string text) {
    for(char& word : text) {
        word = (char)toupper(word);
    }
    return text;
}

bool appendToDataFile(const satwa &newSatwa) {
    ofstream file("./data.txt", ios::app);
    if (file.is_open()) {
        file << replaceSpacetoUnderscore(newSatwa.namaHewan) << ' ' 
             << replaceSpacetoUnderscore(newSatwa.keterangan) << ' ' 
             << newSatwa.populasi << ' '
             << replaceSpacetoUnderscore(newSatwa.habitat) << endl;
        file.close();
        return true;
    }
    return false;
}

satwa *loadData(int *datasize, char separator = '\0') {
    ifstream file("./data.txt");
    satwa *dataTemp = new satwa[1000];
    string popTemp = "";

    if(!file.is_open()) {
        delete[] dataTemp;
        *datasize = 0;
        return nullptr;
    } else {
        if(separator == '\0'){
            // use my kind of input with default ifstream Behavior
            while(file >> dataTemp[*datasize].namaHewan >> dataTemp[*datasize].keterangan >> popTemp >> dataTemp[*datasize].habitat) {
                dataTemp[*datasize].namaHewan = replaceUnderscoretoSpace(dataTemp[*datasize].namaHewan);
                dataTemp[*datasize].keterangan = replaceUnderscoretoSpace(dataTemp[*datasize].keterangan);
                dataTemp[*datasize].habitat = replaceUnderscoretoSpace(dataTemp[*datasize].habitat);
                dataTemp[*datasize].populasi = stoll(popTemp);
                (*datasize)++;
            }
        }
        else{
            // use getline radical but work for other separator
            string tempRecord{};
            while(getline(file, tempRecord)){
                if(tempRecord.empty()) continue;
                stringstream tempField{tempRecord};
                getline(tempField, dataTemp[*datasize].namaHewan, separator);
                dataTemp[*datasize].namaHewan = replaceUnderscoretoSpace(dataTemp[*datasize].namaHewan );
                getline(tempField, dataTemp[*datasize].keterangan, separator);
                dataTemp[*datasize].keterangan = replaceUnderscoretoSpace(dataTemp[*datasize].keterangan);
                string tempPopulasi{};
                getline(tempField, tempPopulasi, separator);
                dataTemp[*datasize].populasi = stoll(tempPopulasi);
                getline(tempField, dataTemp[*datasize].habitat, separator);
                dataTemp[*datasize].habitat = replaceUnderscoretoSpace(dataTemp[*datasize].habitat);
                (*datasize)++;
            }
        }
        return dataTemp;
    }
}

int displayMainMenu() {
    int choice;
    cout << "\n===== MENU UTAMA DATA SATWA =====" << endl;
    cout << "1. Tambah Data Satwa" << endl;
    cout << "2. Lihat & Urutkan Data Satwa" << endl;
    cout << "3. Cari Data Satwa" << endl; 
    cout << "4. Simpan & Exit" << endl;
    cout << "Input Pilihan (1-4): ";
    
    if (!(cin >> choice)) {
        cout << "Input harus berupa angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return -1; 
    }
    cin.ignore();
    return choice;
}

void menuTambahData(satwa data[], int &datalen) {
    if (datalen >= 1000) {
        cout << "Error: Kapasitas data penuh!" << endl;
        return;
    }
    cout << "\n--- Tambah Data Satwa Baru ---" << endl;
    cout << "Nama Hewan           : ";
    getline(cin, data[datalen].namaHewan);
    cout << "Populasi (Angka)     : ";
    cin >> data[datalen].populasi;
    cin.ignore();

    if (data[datalen].populasi == 0) {
        data[datalen].keterangan = "PUNAH";
    } 
    else if (data[datalen].populasi < 100) {
        data[datalen].keterangan = "DILINDUNGI";
    } 
    else if (data[datalen].populasi < 1000) {
        data[datalen].keterangan = "LANGKA";
    } 
    else if (data[datalen].populasi < 1000000) {
        data[datalen].keterangan = "TIDAK DILINDUNGI";
    } 
    else {
        data[datalen].keterangan = "MELIMPAH";
    }

    cout << "Habitat              : ";
    getline(cin, data[datalen].habitat);
    
    
    if(appendToDataFile(data[datalen])){
        cout << "Data satwa berhasil disimpan permanen ke berkas!" << endl;
        datalen++; 
    }
    else{
        cerr << "data gagal dimasukan" << endl;
    }
}

bool comparator(const satwa &a, const satwa &b, int field = 1, int order = 1){
    if(field == 1){
        if(order == 2){
            return a.populasi < b.populasi;
        }
        else{
            return a.populasi > b.populasi;
        }
    }
    else if(field == 2){
        if(order == 2){
            return a.namaHewan < b.namaHewan;
        }
        else{
            return a.namaHewan > b.namaHewan;
        }
    }
    else if(field == 3){
        if(order == 2){
            return a.habitat < b.habitat;
        }
        else{
            return a.habitat > b.habitat;
        }
    }
    else{
        return true;
    }
}

satwa* sortDataBubbble(satwa data_hewan[], int datalen, int field, int order) {
    satwa* tempData = new satwa[datalen];
    bool swapped;
    for (int i = 0; i < datalen; i++) {
        tempData[i] = data_hewan[i];
    }
    for (int i = 0; i < datalen - 1; i++) {
        swapped = false;
        for (int j = 0; j < datalen - i - 1; j++) {
            if (comparator(tempData[j], tempData[j + 1], field, order)) {
                satwa temp = tempData[j];
                tempData[j] = tempData[j + 1];
                tempData[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return tempData;
}

int partition(satwa data_hewan[], int left, int right, function<bool (const satwa&, const satwa&)> comparator){
    satwa pivot = data_hewan[right];
    int i = left - 1;

    for (int j = left; j < right; j++)
    {
        if (comparator(data_hewan[j], pivot)){
            i++;
            satwa temp = data_hewan[i];
            data_hewan[i] = data_hewan[j];
            data_hewan[j] = temp;
        }
    }
    data_hewan[right] = data_hewan[i + 1];
    data_hewan[i + 1] = pivot;
    return (i + 1);
}

void sortDataQuick(satwa data_hewan[], int left, int right, function<bool (const satwa&, const satwa&)> comparator){
    if(left < right){
        int partitionResult = partition(data_hewan, left, right, comparator);
        sortDataQuick(data_hewan, left, partitionResult - 1, comparator);
        sortDataQuick(data_hewan, partitionResult + 1, right, comparator);
    }
}

void menuLihatData(satwa data_hewan[], int datalen) {
    if (datalen == 0) {
        cout << "\n[ Data Kosong - Tidak ada satwa untuk ditampilkan ]" << endl;
        return;
    }
    string inputChoice;
    int fieldChoice, orderChoice;

    cout << "\n--- Pengaturan Tampilan Pengurutan Satwa ---" << endl;
    cout << "1. Urutkan berdasarkan Populasi" << endl;
    cout << "2. Urutkan berdasarkan Nama Hewan" << endl;
    cout << "3. Urutkan berdasarkan Habitat" << endl;
    cout << "5. Tanpa Pengurutan (Default)" << endl;
    cout << "Pilih Opsi (1-4): ";
    getline(cin, inputChoice);
    try
    {
        fieldChoice = stoi(inputChoice);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    

    if (fieldChoice < 1 || fieldChoice > 5 ) {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    if(fieldChoice == 5) {
        cout << "\n" << string(HEADER_LEN, '_') << endl;
        cout << left << setw(NUMBER_LEN)  << "No" << setw(NAMA_LEN) << "Nama Hewan" << setw(KET_LEN) << "Keterangan" << setw(POPULASI_LEN) << "Populasi" << setw(HABITAT_LEN) << "Habitat" << endl;
        cout << string(HEADER_LEN, '_') << endl;
        for (int i = 0; i < datalen; i++) {
            cout << left << setw(NUMBER_LEN) << (i + 1);
            printData(data_hewan[i], NAMA_LEN, KET_LEN, POPULASI_LEN, HABITAT_LEN);
        }
        cout << string(HEADER_LEN, '_') << endl;
        return;
    }
    else{

        cout << "\nTipe Urutan:" << endl;
        cout << "1. Terkecil ke Terbesar (Ascending)" << endl;
        cout << "2. Terbesar ke Terkecil (Descending)" << endl;
        cout << "Pilih Tipe (1-2): ";
        getline(cin, inputChoice);
        try
        {
            orderChoice = stoi(inputChoice);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        if (orderChoice < 1 || orderChoice > 2) {
            cout << "Pilihan tipe tidak valid!" << endl;
            return;
        }
    
        // for quicksort only
        function<bool(const satwa&, const satwa&)> comp;
        if (fieldChoice == 1) {
            comp = (orderChoice == 1) ? [](const satwa& a, const satwa& b) { return a.populasi < b.populasi; } : [](const satwa& a, const satwa& b) { return a.populasi > b.populasi; };
        } 
        else if (fieldChoice == 2) {
            comp = (orderChoice == 1) ? [](const satwa& a, const satwa& b) { return a.namaHewan < b.namaHewan; } : [](const satwa& a, const satwa& b) { return a.namaHewan > b.namaHewan; };
        } 
        else if (fieldChoice == 3) {
            comp = (orderChoice == 1) ? [](const satwa& a, const satwa& b) { return a.habitat < b.habitat; } : [](const satwa& a, const satwa& b) { return a.habitat > b.habitat; };
        }
    
        // menggunakan QuickSort but using functional library, use the bubble sort for no abstraction
        satwa* quickSortResult = new satwa[datalen];
        for (int i = 0; i < datalen; i++) {
            quickSortResult[i] = data_hewan[i];
        }
        sortDataQuick(quickSortResult, 0, datalen-1, comp);
        
        // menggunakan Bubble sort
        // satwa* sortedData = sortDataBubbble(data_hewan, datalen, fieldChoice, orderChoice);
    

        cout << "\n" << string(HEADER_LEN, '_') << endl;
        cout << left << setw(NUMBER_LEN)  << "No" << setw(NAMA_LEN) << "Nama Hewan" << setw(KET_LEN) << "Keterangan" << setw(POPULASI_LEN) << "Populasi" << setw(HABITAT_LEN) << "Habitat" << endl;
        cout << string(HEADER_LEN, '_') << endl;
        for (int i = 0; i < datalen; i++) {
            cout << left << setw(5) << (i + 1);
            // printData(sortedData[i], NAMA_LEN, KET_LEN, POPULASI_LEN, HABITAT_LEN);
            printData(quickSortResult[i], NAMA_LEN, KET_LEN, POPULASI_LEN, HABITAT_LEN);
        }
        cout << string(HEADER_LEN, '_') << endl;
        // delete[] sortedData;
        delete[] quickSortResult;
    }
}

// I Discover 3 algorithm just to make this possible but endup using the naive or brute force one
// just use find method
bool contains(const string& text, const string& keyword) {
    if (keyword.empty()) return true;
    if (text.length() < keyword.length()) return false;

    for (size_t i = 0; i <= text.length() - keyword.length(); i++) {
        size_t j = 0;
        while (j < keyword.length() && text[i + j] == keyword[j]) {
            j++;
        }
        if (j == keyword.length()) return true;
    }
    return false;
}

void menuCariData(satwa data[], int datalen) {
    bool found = false;
    int searchChoice;
    string tempChoice;
    if (datalen == 0) {
        cout << "\n[ Data Kosong - Tidak ada data untuk dicari ]" << endl;
        return;
    }

    cout << "\n--- Cari Data Satwa ---" << endl;
    cout << "1. Cari berdasarkan Nama Hewan" << endl;
    cout << "2. Cari berdasarkan Habitat" << endl;
    cout << "Pilih Metode (1-2): ";
    getline(cin, tempChoice);
    try
    {
        searchChoice = stoi(tempChoice);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    if(searchChoice < 1 || searchChoice > 2) {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    string keyword;
    cout << "Masukkan kata kunci pencarian: ";
    getline(cin, keyword);

    if(keyword == ""){
        cout << "Empty Keyword" << endl;
        return;
    }

    string lowerKeyword = stringTolower(keyword);
    

    cout << "\n=== HASIL PENCARIAN SATWA ===" << endl;
    cout << string(HEADER_LEN, '_') << endl;
    cout << left << setw(NUMBER_LEN)  << "No" << setw(NAMA_LEN) << "Nama Hewan" << setw(KET_LEN) << "Keterangan" << setw(POPULASI_LEN) << "Populasi" << setw(HABITAT_LEN) << "Habitat" << endl;
    cout << string(HEADER_LEN, '_') << endl;

    int matchCount = 1;
    for (int i = 0; i < datalen; i++) {
        string targetText = (searchChoice == 1) ? data[i].namaHewan : data[i].habitat;
        string lowerTarget = stringTolower(targetText);
        
        // use find but cahnge the if condition statement
        // size_t posisi = lowerTarget.find(lowerKeyword);

        bool kondisi = contains(lowerTarget, lowerKeyword);;

        // change here
        if (kondisi/*posisi < lowerTarget.length()*/) {
            cout << left << setw(5) << matchCount;
            printData(data[i], NAMA_LEN, KET_LEN, POPULASI_LEN, HABITAT_LEN);
            matchCount++;
            found = true;
        }
    }
    cout << string(HEADER_LEN, '_') << endl;

    if (!found) {
        cout << "[ Data satwa tidak ditemukan dengan kata kunci: \"" << keyword << "\" ]" << endl;
    }
}

void menuExit(satwa data[], int datalen, bool *isRunning) {
    cout << "\nPerubahan telah tersimpan otomatis di berkas data.txt." << endl;
    cout << "Keluar dari program manajemen satwa." << endl;
    *isRunning = false;
}

int main() {
    int datalen = 0;
    satwa* data = loadData(&datalen);
    
    if (data == nullptr) {
        data = new satwa[1000];
    }
    
    bool isRunning = true;
    while (isRunning) {
        int userChoice = displayMainMenu();
        switch (userChoice) {
            case 1:
                menuTambahData(data, datalen); 
                break;
            case 2:
                menuLihatData(data, datalen);  
                break;
            case 3:
                menuCariData(data, datalen);
                break;
            case 4:
                menuExit(data, datalen, &isRunning);
                break;
            case -1:
                break;
            default:
                cout << "Pilihan tidak valid! Masukkan angka 1 sampai 4." << endl;
                break;
        }
    }
    delete[] data;
    return 0;
}

