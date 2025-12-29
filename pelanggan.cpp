#include "header/pelanggan.h"
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
    cout << "3. Kembali\n";
    cout << "Pilih menu: ";
    cin >> pilih;

    switch (pilih)
    {
    case 1: {
        string sampahJenis;
        int sampahHarga;
        cout << "Masukkan jenis sampah: ";
        cin.ignore();
        getline(cin, sampahJenis);
        cout << "Masukkan harga per kg: ";
        cin >> sampahHarga;
        insertSampahKePelanggan(p, sampahJenis, sampahHarga);
         cout << "Sampah berhasil ditambahkan!\n";
         menuUser(p);
         
        break;
    }
    case 2: {
         cout << "===== DAFTAR SAMPAH =====\n";
        SampahNode* s = p->daftarSampah;
        if (!s) {
        cout << "(Belum ada sampah)\n";
        } else {
            while (s != nullptr) {
             cout << "- " << s->jenisSampah
                 << " (" << s->hargaPerKg << " /kg)\n";
                s = s->next;
        }
    }
        break;
    }
    case 3:
        cout << "Kembali ke menu .\n";
        menuAwal();
        break;
    
    default:
        break;
    }

   

    cout << "=========================\n";
}