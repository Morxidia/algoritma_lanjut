#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <functional>
#include <sstream>
using namespace std;

// header untuk tampilan
#define HEADER_LEN 50
#define NUMBER_LEN 5
#define NAMA_LEN 30
#define GOL_LEN 5
#define AMOUNT_LEN 10


struct donorProfile{
    string name;
    string gol;
    // input the data in milimeter
    int amount; 

    void print(){
        cout << left << setw(NAMA_LEN) << name;
        cout << left << setw(GOL_LEN) << gol;
        cout << right << setw(AMOUNT_LEN) << (to_string(amount) + " ml") << endl;
    }
};

void printData(donorProfile data_profile){
    cout << left << setw(NAMA_LEN) << data_profile.name;
    cout << left << setw(GOL_LEN) << data_profile.gol;
    cout << right << setw(AMOUNT_LEN) << (to_string(data_profile.amount) + " ml") << endl;
}

string replaceChar(string text, char source, char target){
    string newtext = text;
    for(int i = 0; i < text.length(); i ++){
        if(text[i] == source)
            newtext[i] = target;   
    }
    return newtext;
}

string replaceSpacetoUnderscore(string text){
    return replaceChar(text, ' ', '_');
}

string replaceUnderscoretoSpace(string text){
    return replaceChar(text, '_', ' ');
}

string stringTolower(string text){
    for(char& word : text){
        word = (char)tolower(word);
    }
    return text;
}

string stringToupper(string text){
    for(char& word : text){
        word = (char)toupper(word);
    }
    return text;
}

bool checkGolDarah(string gol){
    return (gol == "A" || gol == "B" || gol == "AB" || gol == "O");
}

bool appendToDataFile(const donorProfile &newDonor) {
    ofstream file("./data.txt", ios::app);
    if (file.is_open()) {
        file << replaceSpacetoUnderscore(newDonor.name) << ' ' 
             << newDonor.gol << ' ' 
             << newDonor.amount << endl;
        file.close();
        return true;
    }
    return false;
}

donorProfile *loadData(int *datasize, char separator = '\0'){
    ifstream file("./data.txt");
    donorProfile *dataTemp = new donorProfile[1000];
    string amountTemp = "";
    if(file.is_open()){
        if(separator == '\0'){
            while(file >> dataTemp[*datasize].name >> dataTemp[*datasize].gol >> amountTemp)
            {
                dataTemp[*datasize].name = replaceUnderscoretoSpace(dataTemp[*datasize].name);
                dataTemp[*datasize].amount = stoi(amountTemp);
                (*datasize)++;
            }
        }
        else{
            // use getline radical but work for other separator
            string tempRecord{};
            while(getline(file, tempRecord)){
                if(tempRecord.empty()) {
                    continue;
                };
                stringstream tempField{tempRecord};
                getline(tempField, dataTemp[*datasize].name, separator);
                getline(tempField, dataTemp[*datasize].gol, separator);
                string tempAmount{};
                getline(tempField, tempAmount, separator);
                dataTemp[*datasize].amount = stoi(tempAmount);
                (*datasize)++;
            }
        }
        return dataTemp;
    }
    else{
        delete[] dataTemp;
        *datasize = 0;
        return nullptr;
    }
}

void cetakHeader(){
    cout << string(HEADER_LEN, '_') << endl;
    cout << left << setw(NUMBER_LEN)  << "No"; 
    cout << left << setw(NAMA_LEN) << "Nama"; 
    cout << left << setw(GOL_LEN) << "Gol"; 
    cout << left << setw(AMOUNT_LEN) << "amount" << endl;
    cout << string(HEADER_LEN, '_') << endl;
}

string displayMainMenu() {
    string choice;
    cout << "\n===== MENU UTAMA =====" << endl;
    cout << "1. Tambah Data Pendonor" << endl;
    cout << "2. Lihat Data Pendonor" << endl;
    cout << "3. Cari Data Pendonor" << endl; 
    cout << "4. Simpan & Exit" << endl;
    cout << "Input Pilihan (1-4): ";
    
    cin >> choice;
    cin.ignore();
    return choice;
}

void menuTambahData(donorProfile data[], int &datalen) {
    if (datalen >= 1000) {
        cout << "Error: Kapasitas data penuh!" << endl;
        return;
    }
    cout << "\n--- Tambah Data Pendonor ---" << endl;
    cout << "Nama Lengkap       : ";
    getline(cin, data[datalen].name);
    while(true){
        cout << "Golongan Darah(A/B/AB/O): ";
        cin >> data[datalen].gol;
        data[datalen].gol = stringToupper(data[datalen].gol);
        if(!checkGolDarah(data[datalen].gol)){
            continue;
        }
        else{
            break;
        }
    }
    cout << "Jumlah Donor (ml)  : ";
    cin >> data[datalen].amount;
    cin.ignore();

    appendToDataFile(data[datalen]);
    datalen++; 
    cout << "Data berhasil ditambahkan sementara ke memori!" << endl;
}

bool comparator(const donorProfile &a, const donorProfile &b, int field = 1, int order = 1){
    if(field == 1){
        if(order == 2){
            return a.name < b.name;
        }
        else{
            return a.name > b.name;
        }
    }
    else if(field == 2){
        if(order == 2){
            return a.gol < b.gol;
        }
        else{
            return a.gol > b.gol;
        }
    }
    else if(field == 3){
        if(order == 2){
            return a.amount < b.amount;
        }
        else{
            return a.amount > b.amount;
        }
    }
    else{
        return true;
    }
}

donorProfile* sortDataBubble(donorProfile data[], int datalen, int field, int order){
    donorProfile* tempData = new donorProfile[datalen];
    bool swapped;
    for (int i = 0; i < datalen; i++){
        tempData[i] = data[i];
    }
    for (int i = 0; i < datalen - 1; i++) {
        swapped = false;
        for (int j = 0; j < datalen - i - 1; j++) {
            if (comparator(tempData[j], tempData[j + 1], field, order)) {
                donorProfile temp = tempData[j];
                tempData[j] = tempData[j + 1];
                tempData[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped){
            break;
        }
    }
    return tempData;
}

int partition(donorProfile data_profile[], int left, int right, function<bool (const donorProfile&, const donorProfile&)> comparator){
    donorProfile pivot = data_profile[right];
    int i = left - 1;

    for (int j = left; j < right; j++)
    {
        if (comparator(data_profile[j], pivot)){
            i++;
            donorProfile temp = data_profile[i];
            data_profile[i] = data_profile[j];
            data_profile[j] = temp;
        }
    }
    data_profile[right] = data_profile[i + 1];
    data_profile[i + 1] = pivot;
    return (i + 1);
}

void sortDataQuick(donorProfile data_profile[], int left, int right, function<bool (const donorProfile&, const donorProfile&)> comparator){
    if(left < right){
        int partitionResult = partition(data_profile, left, right, comparator);
        sortDataQuick(data_profile, left, partitionResult - 1, comparator);
        sortDataQuick(data_profile, partitionResult + 1, right, comparator);
    }
}

void menuLihatData(donorProfile data_profile[], int datalen) {
    if (datalen == 0) {
        cout << "\n[ Data Kosong - Tidak ada data untuk diurutkan ]" << endl;
        return;
    }
    string tempChoice;
    int fieldChoice, orderChoice;
    cout << "\n--- Urutkan Data Berdasarkan Field ---" << endl;
    cout << "1. Nama Lengkap" << endl;
    cout << "2. Golongan Darah" << endl;
    cout << "3. Jumlah Donor (ml)" << endl;
    cout << "4. default" << endl;
    cout << "Pilih Field (1-4): ";
    getline(cin, tempChoice);
    try
    {
        fieldChoice = stoi(tempChoice);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    

    if (fieldChoice < 1 || fieldChoice > 4) {
        cout << "Pilihan field tidak valid!" << endl;
        return;
    }

    if(fieldChoice == 4){
        cetakHeader();
        for (int i = 0; i < datalen; i++) {
            cout << setw(NUMBER_LEN) << (i + 1);
            printData(data_profile[i]);
        }
        cout << string(HEADER_LEN, '_') << endl;
        return;
    }

    cout << "\nTipe Urutan:" << endl;
    cout << "1. Terkecil ke Terbesar (Ascending)" << endl;
    cout << "2. Terbesar ke Terkecil (Descending)" << endl;
    cout << "Pilih Tipe (1-2): ";
    getline(cin, tempChoice);
    try
    {
        orderChoice = stoi(tempChoice);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    if (orderChoice < 1 || orderChoice > 2) {
        cout << "Pilihan tipe urutan tidak valid!" << endl;
        return;
    }

    function<bool(const donorProfile&, const donorProfile&)> comp;

    if (fieldChoice == 1) {
        comp = (orderChoice == 1) ? [](const donorProfile& a, const donorProfile& b) { return a.name > b.name; }
                                 : [](const donorProfile& a, const donorProfile& b) { return a.name < b.name; };
    } 
    else if (fieldChoice == 2) {
        comp = (orderChoice == 1) ? [](const donorProfile& a, const donorProfile& b) { return a.gol > b.gol; }
                                 : [](const donorProfile& a, const donorProfile& b) { return a.gol < b.gol; };
    } 
    else if (fieldChoice == 3) {
        comp = (orderChoice == 1) ? [](const donorProfile& a, const donorProfile& b) { return a.amount > b.amount; }
                                 : [](const donorProfile& a, const donorProfile& b) { return a.amount < b.amount; };
    }

    // uncomment for using bubble sort
    // donorProfile* sortedData = sortDataBubble(data_profile, datalen, fieldChoice, orderChoice);

    // menggunakan QuickSort but using functional library, use the bubble sort for no abstraction
    donorProfile* quickSortResult = new donorProfile[datalen];
    for (int i = 0; i < datalen; i++) {
        quickSortResult[i] = data_profile[i];
    }
    sortDataQuick(quickSortResult, 0, datalen-1, comp);
    
    cetakHeader();
    for (int i = 0; i < datalen; i++) {
        cout << setw(5) << (i + 1);
        printData(quickSortResult[i]);
    }
    cout << string(HEADER_LEN, '_') << endl;

    // delete[] sortedData;
    delete[] quickSortResult;
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

void menuCariData(donorProfile data[], int datalen) {
    if (datalen == 0) {
        cout << "\n[ Data Kosong - Tidak ada data untuk dicari ]" << endl;
        return;
    }
    string tempChoice;
    int searchChoice;
    cout << "\n--- Cari Data Pendonor ---" << endl;
    cout << "1. Cari berdasarkan Nama" << endl;
    cout << "2. Cari berdasarkan Golongan Darah" << endl;
    cout << "Pilih Metode Pencarian (1-2): ";
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

    if (searchChoice < 1 || searchChoice > 2) {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }

    string keyword;
    cout << "Masukkan kata kunci pencarian: ";
    getline(cin, keyword);
    
    string lowerKeyword = stringTolower(keyword);

    bool found = false;

    // Cetak header tabel terlebih dahulu
    cout << "\n=== HASIL PENCARIAN ===" << endl;
    cetakHeader();
    int matchCount = 1;
    for (int i = 0; i < datalen; i++) {
        string targetText = (searchChoice == 1) ? data[i].name : data[i].gol;
        string lowerTarget = stringTolower(targetText);
        
        // use this for use find method, really reccomend
        // size_t posisi = lowerTarget.find(lowerKeyword);
        bool kondisi = contains(lowerTarget, lowerKeyword);
        if (kondisi/*posisi < lowerTarget.length()*/) {
            cout << setw(5) << matchCount;
            printData(data[i]);
            matchCount++;
            found = true;
        }
    }
    cout << string(HEADER_LEN, '_') << endl;

    if (!found) {
        cout << "[ Data tidak ditemukan dengan kata kunci: \"" << keyword << "\" ]" << endl;
    }
}

// IDK why I use this
void menuExit(donorProfile data_profile[], int datalen, bool *isRunning) {
    cout << "\nMenyimpan data ke file..." << endl;
    ofstream file("./data.txt", ios::trunc);
    if (file.is_open()) {
        for(size_t i{0}; i < datalen; ++i){
            file << replaceSpacetoUnderscore(data_profile[i].name) << ' ' 
             << data_profile[i].gol << ' ' 
             << data_profile[i].amount << endl;
        }
    }
    file.close();
    *isRunning = false;
}

int main(){
    int datalen = 0;
    int actualChoice;
    string userChoice;
    donorProfile* data = loadData(&datalen);
    string input;
    if (data == nullptr) {
        data = new donorProfile[1000];
    }
    bool isRunning = true;
    while (isRunning) {
        userChoice = displayMainMenu();
        try
        {
            actualChoice = stoi(userChoice);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            actualChoice = -1;
        }
        
        switch (actualChoice) {
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
            default:
                cout << "Pilihan tidak valid! Masukkan angka 1 sampai 4." << endl;
                break;
        }
    }
    delete[] data;
    return 0;
}