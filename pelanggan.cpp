#include "header/pelanggan.h"
#include "header/pengeloaan_sampah.h"
#include "header/petugas.h"
#include "header/menu.h"
#include <iostream>
using namespace std;
void createListPelanggan(pelanggan*& head, pelanggan*& tail) {
    head = nullptr;
    tail = nullptr;
}

pelanggan* createNodePelanggan(DataUser data) {
    pelanggan* newNode = new pelanggan;
    newNode->dataPelanggan = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    newNode->daftarSampah = nullptr;
    return newNode;
}

void insertPelanggan(pelanggan*& head, pelanggan*& tail, DataUser data) {
    pelanggan* newNode = createNodePelanggan(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

pelanggan* searchPelanggan(pelanggan* head, string username) {
    pelanggan* current = head;
    while (current != nullptr) {
        if (current->dataPelanggan.username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void deletePelanggan(pelanggan*& head, pelanggan*& tail, string username) {
    pelanggan* target = searchPelanggan(head, username);
    if (target == nullptr) return; // Not found

    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        head = target->next; // Update head if needed
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    } else {
        tail = target->prev; // Update tail if needed
    }

    delete target;
}

void printListBertingkat(pelanggan* head) {
    pelanggan* currentPelanggan = head;
    while (currentPelanggan != nullptr) {
        cout << "Pelanggan: " << currentPelanggan->dataPelanggan.nama << endl;
        SampahNode* currentSampah = currentPelanggan->daftarSampah;
        while (currentSampah != nullptr) {
            cout << "  Sampah: " << currentSampah->jenisSampah 
                 << ", Harga per Kg: " << currentSampah->hargaPerKg << endl;
            currentSampah = currentSampah->next;
        }
        currentPelanggan = currentPelanggan->next;
    }
}

SampahNode* createNodeSampah(string jenis, int harga) {
    SampahNode* newNode = new SampahNode;
    newNode->jenisSampah = jenis;
    newNode->hargaPerKg = harga;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}
void insertSampahKePelanggan(pelanggan* p, string jenis, int harga) {
    SampahNode* newNode = createNodeSampah(jenis, harga);
    if (p->daftarSampah == nullptr) {
        p->daftarSampah = newNode;
    } else {
        SampahNode* current = p->daftarSampah;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}


void menuUser(pelanggan* p) {
    cout << "\n===== MENU USER =====\n";
    cout << "Nama: " << p->dataPelanggan.nama << endl;
    cout << "Alamat: " << p->dataPelanggan.alamat << endl;
    cout << "No Telp: " << p->dataPelanggan.no_telp << endl;
    int pilih;
    cout << "1. Tambah Sampah\n";
    cout << "2. Lihat Sampah\n";
    cout << "3. Logout\n";
    cout << "Pilih menu: ";
    cin >> pilih;

    switch (pilih)
    {
    case 1: {
        tambahSampahUser(p);
        menuUser(p);
        
         
        break;
    }
    case 2: {
        lihatSampahUser(p);
        menuUser(p);
        break;
    }
    case 3:
        cout << "Kembali Menu Awal .\n";
        menuAwal();
        break;
    
    default:
        break;
    }

   

    cout << "=========================\n";
}
void lihatSampahUser(pelanggan* p) {
    cout << "\n=== DAFTAR SAMPAH ANDA ===\n";
    SampahNode* current = p->daftarSampah;

    if (current == nullptr) {
        cout << "Anda belum memiliki sampah yang terdaftar.\n";
        return;
    }

    int i = 1;
    while (current != nullptr) {
        cout << i << ". Jenis Sampah: " << current->jenisSampah << ", Harga per Kg: " << current->hargaPerKg << endl;
        current = current->next;
        i++;
    }
}


void tambahSampahUser(pelanggan* p) {
     if (jumlahSampah >= 20) {
        cout << "Data penuh! Tidak bisa menambah sampah baru.\n";
        return;
    }

    cout << "\n=== TAMBAH DATA SAMPAH ===\n";
    Sampah S = inputSampahuser(p);

    dataSampah[jumlahSampah] = S;
    jumlahSampah++;

    insertSampahKePelanggan(p, S.jenisSampah, S.hargaPerKg);

    cout << "Data sampah berhasil ditambahkan!\n";
    menuUser(p);
}

Sampah inputSampahuser(pelanggan* p) {
    Sampah S;
    int pilihKategori;

    cout << "\n=== KATEGORI SAMPAH ===\n";
    cout << "1. Organik\n";
    cout << "2. Anorganik\n";
    cout << "Pilihan: ";
    cin >> pilihKategori;

    // KATEGORI ORGANIK
    if (pilihKategori == 1) {
        S.kategori = "Organik";
        cin.ignore();
        cout << "Masukkan jenis sampah organik: ";
        getline(cin, S.jenisSampah);
    }
    // KATEGORI ANORGANIK
    else if (pilihKategori == 2) {
        S.kategori = "Anorganik";

        int pilihJenis;
        cout << "\n=== JENIS SAMPAH ANORGANIK ===\n";
        cout << "1. Plastik\n";
        cout << "2. Kaca\n";
        cout << "3. Logam\n";
        cout << "4. Kertas\n";
        cout << "5. Karet\n";
        cout << "Pilihan: ";
        cin >> pilihJenis;

        switch (pilihJenis) {
            case 1: S.jenisSampah = "Plastik"; break;
            case 2: S.jenisSampah = "Kaca"; break;
            case 3: S.jenisSampah = "Logam"; break;
            case 4: S.jenisSampah = "Kertas"; break;
            case 5: S.jenisSampah = "Karet"; break;
            default: S.jenisSampah = "Tidak diketahui"; break;
        }
    }
    else {
        cout << "Pilihan kategori tidak valid.\n";
        S.kategori = "Tidak valid";
        S.jenisSampah = "Tidak valid";
    }

    cout << "Masukkan berat (kg): ";
    cin >> S.berat;

    S.hargaPerKg = getHargaPerKgJenis(S.kategori, S.jenisSampah);
    cout << "Harga per Kg otomatis: Rp " << S.hargaPerKg << endl;

    return S;
}

