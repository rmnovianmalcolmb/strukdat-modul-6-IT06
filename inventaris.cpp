#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class Entity {
public:
    virtual ~Entity() = default;
    virtual void readData() = 0;
    virtual void writeData() = 0;
    virtual void display() = 0;
};

class Product : public Entity {
private:
    vector<int> kodeBarang;
    vector<string> namaBarang;
    vector<int> jumlahBarang;

public:
    Product() {
        readData();
    }

    void readData() override {
        kodeBarang.clear();
        namaBarang.clear();
        jumlahBarang.clear();

        ifstream data;
        string line;

        data.open("kodeBarang.txt");
        while (getline(data, line)) {
            kodeBarang.push_back(stoi(line));
        }
        data.close();

        data.open("namaBarang.txt");
        while (getline(data, line)) {
            namaBarang.push_back(line);
        }
        data.close();

        data.open("jumlahBarang.txt");
        while (getline(data, line)) {
            jumlahBarang.push_back(stoi(line));
        }
        data.close();
    }

    void writeData() override {
        ofstream data;

        data.open("kodeBarang.txt", ios::trunc);
        for (const auto& kode : kodeBarang) {
            data << kode << endl;
        }
        data.close();

        data.open("namaBarang.txt", ios::trunc);
        for (const auto& nama : namaBarang) {
            data << nama << endl;
        }
        data.close();

        data.open("jumlahBarang.txt", ios::trunc);
        for (const auto& jumlah : jumlahBarang) {
            data << jumlah << endl;
        }
        data.close();
    }

    void displayProducts() {
        cout << left << setw(12) << "Kode Barang"
             << left << setw(15) << "Nama Barang"
             << left << setw(8) << "Jumlah Barang"
             << endl;

        for (size_t i = 0; i < kodeBarang.size(); ++i) {
            cout << left << setw(12) << kodeBarang[i]
                 << left << setw(15) << namaBarang[i]
                 << left << setw(8) << jumlahBarang[i]
                 << endl;
        }
    }

    void display() override {
        displayProducts();
    }

    void setKodeBarang(size_t index, int kode) {
        if (index < kodeBarang.size()) {
            kodeBarang[index] = kode;
        }
    }

    void setNamaBarang(size_t index, const string& nama) {
        if (index < namaBarang.size()) {
            namaBarang[index] = nama;
        }
    }

    void setJumlahBarang(size_t index, int jumlah) {
        if (index < jumlahBarang.size()) {
            jumlahBarang[index] = jumlah;
        }
    }

    int getKodeBarang(size_t index) const {
        if (index < kodeBarang.size()) {
            return kodeBarang[index];
        }
        return -1; 
    }

    string getNamaBarang(size_t index) const {
        if (index < namaBarang.size()) {
            return namaBarang[index];
        }
        return ""; 
    }

    int getJumlahBarang(size_t index) const {
        if (index < jumlahBarang.size()) {
            return jumlahBarang[index];
        }
        return -1; 
    }

    size_t getProductCount() const {
        return kodeBarang.size();
    }

    void addProduct(int kode, const string& nama, int jumlah) {
        for (const auto& existingKode : kodeBarang) {
            if (existingKode == kode) {
                cout << "Kode " << kode << " sudah dipakai" << endl;
                return;
            }
        }

        for (const auto& existingNama : namaBarang) {
            if (existingNama == nama) {
                cout << "Nama " << nama << " sudah dipakai" << endl;
                return;
            }
        }

        kodeBarang.push_back(kode);
        namaBarang.push_back(nama);
        jumlahBarang.push_back(jumlah);
        writeData();
    }

    void updateProduct(int kode, int jumlah) {
        for (size_t i = 0; i < kodeBarang.size(); ++i) {
            if (kodeBarang[i] == kode) {
                jumlahBarang[i] = jumlah;
                writeData();
                return;
            }
        }
        cout << "Barang tidak ditemukan" << endl;
    }

    void deleteProduct(int kode) {
        for (size_t i = 0; i < kodeBarang.size(); ++i) {
            if (kodeBarang[i] == kode) {
                kodeBarang.erase(kodeBarang.begin() + i);
                namaBarang.erase(namaBarang.begin() + i);
                jumlahBarang.erase(jumlahBarang.begin() + i);
                writeData();
                return;
            }
        }
        cout << "Barang tidak ditemukan" << endl;
    }

    void updateStock(const string& nama, int jumlah) {
        for (size_t i = 0; i < namaBarang.size(); ++i) {
            if (namaBarang[i] == nama) {
                jumlahBarang[i] += jumlah;
                writeData();
                return;
            }
        }
    }
};

class Loan : public Entity {
private:
    vector<int> kodePinjam;
    vector<int> jumlahPinjam;
    vector<string> namaPinjam;
    vector<string> lamaPinjam;
    vector<string> waktuPinjam;
    vector<string> barangPinjam;
    vector<string> waktuKembali;
    vector<string> status;
    const string belum = "Belum Kembali";
    const string sudah = "Sudah Kembali";

public:
    Loan() {
        readData();
    }

    void readData() override {
        kodePinjam.clear();
        jumlahPinjam.clear();
        namaPinjam.clear();
        lamaPinjam.clear();
        waktuPinjam.clear();
        barangPinjam.clear();
        waktuKembali.clear();
        status.clear();

        ifstream data;
        string line;

        data.open("kodePinjam.txt");
        while (getline(data, line)) {
            kodePinjam.push_back(stoi(line));
        }
        data.close();

        data.open("jumlahPinjam.txt");
        while (getline(data, line)) {
            jumlahPinjam.push_back(stoi(line));
        }
        data.close();

        data.open("namaPinjam.txt");
        while (getline(data, line)) {
            namaPinjam.push_back(line);
        }
        data.close();

        data.open("lamaPinjam.txt");
        while (getline(data, line)) {
            lamaPinjam.push_back(line);
        }
        data.close();

        data.open("waktuPinjam.txt");
        while (getline(data, line)) {
            waktuPinjam.push_back(line);
        }
        data.close();

        data.open("barangPinjam.txt");
        while (getline(data, line)) {
            barangPinjam.push_back(line);
        }
        data.close();

        data.open("status.txt");
        while (getline(data, line)) {
            status.push_back(line);
        }
        data.close();

        data.open("waktuKembali.txt");
        while (getline(data, line)) {
            waktuKembali.push_back(line);
        }
        data.close();
    }

    void writeData() override {
        ofstream data;

        data.open("kodePinjam.txt", ios::trunc);
        for (const auto& kode : kodePinjam) {
            data << kode << endl;
        }
        data.close();

        data.open("jumlahPinjam.txt", ios::trunc);
        for (const auto& jumlah : jumlahPinjam) {
            data << jumlah << endl;
        }
        data.close();

        data.open("namaPinjam.txt", ios::trunc);
        for (const auto& nama : namaPinjam) {
            data << nama << endl;
        }
        data.close();

        data.open("lamaPinjam.txt", ios::trunc);
        for (const auto& lama : lamaPinjam) {
            data << lama << endl;
        }
        data.close();

        data.open("waktuPinjam.txt", ios::trunc);
        for (const auto& waktu : waktuPinjam) {
            data << waktu << endl;
        }
        data.close();

        data.open("barangPinjam.txt", ios::trunc);
        for (const auto& barang : barangPinjam) {
            data << barang << endl;
        }
        data.close();

        data.open("status.txt", ios::trunc);
        for (const auto& stat : status) {
            data << stat << endl;
        }
        data.close();

        data.open("waktuKembali.txt", ios::trunc);
        for (const auto& waktu : waktuKembali) {
            data << waktu << endl;
        }
        data.close();
    }

    void displayLoans() {
        cout << left << setw(12) << "Kode Pinjam    "
             << left << setw(15) << "Nama Peminjam           "
             << left << setw(15) << "Barang           "
             << left << setw(8) << "Jumlah    "
             << left << setw(12) << "Lama Pinjam    "
             << left << setw(15) << "Waktu Pinjam    "
             << left << setw(15) << "Status    "
             << endl;

        for (size_t i = 0; i < kodePinjam.size(); ++i) {
            cout << left << setw(12) << kodePinjam[i] << "   "
                 << left << setw(15) << namaPinjam[i] << "         "
                 << left << setw(15) << barangPinjam[i] << "  "
                 << left << setw(8) << jumlahPinjam[i] << "  "
                 << left << setw(12) << lamaPinjam[i] << "   "
                 << left << setw(15) << waktuPinjam[i] << " "
                 << left << setw(15) << status[i]
                 << endl;
        }
    }

    void display() override {
        displayLoans();
    }

    void setKodePinjam(size_t index, int kode) {
        if (index < kodePinjam.size()) {
            kodePinjam[index] = kode;
        }
    }

    void setJumlahPinjam(size_t index, int jumlah) {
        if (index < jumlahPinjam.size()) {
            jumlahPinjam[index] = jumlah;
        }
    }

    void setNamaPinjam(size_t index, const string& nama) {
        if (index < namaPinjam.size()) {
            namaPinjam[index] = nama;
        }
    }

    void setLamaPinjam(size_t index, const string& lama) {
        if (index < lamaPinjam.size()) {
            lamaPinjam[index] = lama;
        }
    }

    void setWaktuPinjam(size_t index, const string& waktu) {
        if (index < waktuPinjam.size()) {
            waktuPinjam[index] = waktu;
        }
    }

    void setBarangPinjam(size_t index, const string& barang) {
        if (index < barangPinjam.size()) {
            barangPinjam[index] = barang;
        }
    }

    void setStatus(size_t index, const string& stat) {
        if (index < status.size()) {
            status[index] = stat;
        }
    }

    void setWaktuKembali(size_t index, const string& waktu) {
        if (index < waktuKembali.size()) {
            waktuKembali[index] = waktu;
        }
    }

    int getKodePinjam(size_t index) const {
        if (index < kodePinjam.size()) {
            return kodePinjam[index];
        }
        return -1; 
    }

    int getJumlahPinjam(size_t index) const {
        if (index < jumlahPinjam.size()) {
            return jumlahPinjam[index];
        }
        return -1;
    }

    string getNamaPinjam(size_t index) const {
        if (index < namaPinjam.size()) {
            return namaPinjam[index];
        }
        return "";
    }

    string getLamaPinjam(size_t index) const {
        if (index < lamaPinjam.size()) {
            return lamaPinjam[index];
        }
        return ""; 
    }

    string getWaktuPinjam(size_t index) const {
        if (index < waktuPinjam.size()) {
            return waktuPinjam[index];
        }
        return ""; 
    }

    string getBarangPinjam(size_t index) const {
        if (index < barangPinjam.size()) {
            return barangPinjam[index];
        }
        return ""; 
    }

    string getStatus(size_t index) const {
        if (index < status.size()) {
            return status[index];
        }
        return ""; 
    }

    string getWaktuKembali(size_t index) const {
        if (index < waktuKembali.size()) {
            return waktuKembali[index];
        }
        return ""; 
    }

    size_t getLoanCount() const {
        return kodePinjam.size();
    }

    void addLoan(const string& nama, const string& barang, int jumlah, const string& lama, Product& product) {
        bool productExists = false;
        for (size_t i = 0; i < product.getProductCount(); ++i) {
            if (product.getNamaBarang(i) == barang) {
                productExists = true;
                if (product.getJumlahBarang(i) - jumlah < 0) {
                    cout << "Jumlah barang tidak cukup" << endl;
                    return;
                }
                break;
            }
        }

        if (!productExists) {
            cout << "Barang tidak ada di daftar produk, pinjam barang dibatalkan" << endl;
            return;
        }

        product.updateStock(barang, -jumlah);

        int kode = getNextKodePinjam();
        kodePinjam.push_back(kode);
        namaPinjam.push_back(nama);
        barangPinjam.push_back(barang);
        jumlahPinjam.push_back(jumlah);
        lamaPinjam.push_back(lama);

        time_t now = time(0);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", localtime(&now));
        waktuPinjam.push_back(string(buffer));

        status.push_back(belum);
        waktuKembali.push_back("-");
        writeData();
    }

    int getNextKodePinjam() {
        if (kodePinjam.empty()) {
            return 1;
        }
        return kodePinjam.back() + 1;
    }

    void updateLoanStatus(int kode, Product& product) {
        for (size_t i = 0; i < kodePinjam.size(); ++i) {
            if (kodePinjam[i] == kode) {
                if (status[i] == sudah) {
                    cout << "Peminjaman dengan kode " << kode << " sudah dikembalikan" << endl;
                    return;
                }
                status[i] = sudah;

                product.updateStock(barangPinjam[i], jumlahPinjam[i]);

                time_t now = time(0);
                char buffer[80];
                strftime(buffer, sizeof(buffer), "%d/%m/%Y", localtime(&now));
                waktuKembali[i] = string(buffer);
                writeData();
                return;
            }
        }
        cout << "Kode peminjaman tidak ditemukan" << endl;
    }

    void deleteLoan(int kode) {
        for (size_t i = 0; i < kodePinjam.size(); ++i) {
            if (kodePinjam[i] == kode) {
                kodePinjam.erase(kodePinjam.begin() + i);
                namaPinjam.erase(namaPinjam.begin() + i);
                barangPinjam.erase(barangPinjam.begin() + i);
                jumlahPinjam.erase(jumlahPinjam.begin() + i);
                lamaPinjam.erase(lamaPinjam.begin() + i);
                waktuPinjam.erase(waktuPinjam.begin() + i);
                status.erase(status.begin() + i);
                waktuKembali.erase(waktuKembali.begin() + i);
                writeData();
                return;
            }
        }
        cout << "Data peminjaman tidak ditemukan" << endl;
    }
};

void displayEntity(Entity* entity) {
    entity->display();
}

void menuAwal() {
    cout << "Menu Utama:" << endl;
    cout << "1. Tampilkan Barang" << endl;
    cout << "2. Tambah Barang" << endl;
    cout << "3. Update Barang" << endl;
    cout << "4. Hapus Barang" << endl;
    cout << "5. Tampilkan Pinjaman" << endl;
    cout << "6. Pinjam Barang" << endl;
    cout << "7. Pengembalian Barang" << endl;
    cout << "8. Hapus Pinjaman" << endl;
    cout << "9. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    Product product;
    Loan loan;
    char menu;

    while (true) {
        menuAwal();
        cin >> menu;
        system("cls");

        switch (menu) {
            case '1':
                displayEntity(&product);
                break;
            case '2': {
                displayEntity(&product);
                int kode, jumlah;
                string nama;
                cout << endl << "Masukkan -1 untuk kembali ke menu" << endl;
                cout << "Masukkan kode barang: ";
                cin >> kode;
                if (kode == -1) {
                    system("cls");
                    break;
                }

                cout << "Masukkan nama barang: ";
                cin.ignore();
                getline(cin, nama);
                if (nama == "-1") {
                    system("cls");
                    break;
                }

                cout << "Masukkan jumlah barang: ";
                cin >> jumlah;
                if (jumlah == -1) {
                    system("cls");
                    break;
                }

                product.addProduct(kode, nama, jumlah);
                break;
            }
            case '3': {
                displayEntity(&product);
                int kode, jumlah;
                cout << endl << "Masukkan -1 untuk kembali ke menu" << endl;
                cout << "Masukkan kode barang yang ingin diupdate: ";
                cin >> kode;
                if (kode == -1) {
                    system("cls");
                    break;
                }

                cout << "Masukkan jumlah barang baru: ";
                cin >> jumlah;
                if (jumlah == -1) {
                    system("cls");
                    break;
                }

                product.updateProduct(kode, jumlah);
                break;
            }
            case '4': {
                displayEntity(&product);
                int kode;
                cout << endl << "Masukkan -1 untuk kembali ke menu" << endl;
                cout << "Masukkan kode barang yang ingin dihapus: ";
                cin >> kode;
                if (kode == -1) {
                    system("cls");
                    break;
                }

                product.deleteProduct(kode);
                break;
            }
            case '5':
                loan.display();
                break;
            case '6': {
                product.display();
                string nama, barang, lama;
                int jumlah;
                cout << endl << "Masukkan -1 untuk kembali ke menu" << endl;
                cout << "Masukkan nama peminjam: ";
                cin.ignore();
                getline(cin, nama);
                if (nama == "-1") {
                    system("cls");
                    break;
                }

                cout << "Masukkan nama barang yang akan dipinjam: ";
                getline(cin, barang);
                if (barang == "-1") {
                    system("cls");
                    break;
                }

                cout << "Masukkan jumlah barang yang dipinjam: ";
                cin >> jumlah;
                if (jumlah == -1) {
                    system("cls");
                    break;
                }

                cout << "Masukkan lama pinjaman (hari): ";
                cin >> lama;
                if (lama == "-1") {
                    system("cls");
                    break;
                }

                loan.addLoan(nama, barang, jumlah, lama, product);
                break;
            }
            case '7': {
                loan.display();
                int kode;
                cout << endl << "Masukkan -1 untuk kembali ke menu" << endl;
                cout << "Masukkan kode pinjaman yang ingin dikembalikan: ";
                cin >> kode;
                if (kode == -1) {
                    system("cls");
                    break;
                }

                loan.updateLoanStatus(kode, product);
                break;
            }
            case '8': {
                loan.display();
                int kode;
                cout << endl << "Masukkan -1 untuk kembali ke menu" << endl;
                cout << "Masukkan kode pinjaman yang ingin dihapus: ";
                cin >> kode;
                if (kode == -1) {
                    system("cls");
                    break;
                }

                loan.deleteLoan(kode);
                break;
            }
            case '9':
                return 0;
            default:
                cout << "Menu tidak valid" << endl;
                break;
        }
        cout << endl;
    }

    return 0;
}
