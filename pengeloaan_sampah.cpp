#include "header/pengeloaan_sampah.h"
#include "header/pelanggan.h"
#include <iostream>
using namespace std;

// =====================
// INPUT SAMPAH (MENU KATEGORI)
// =====================
Sampah inputSampah() {
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

// ===================== Titik pengumpulan RW =====================

titikpengumpulan* headRW = NULL;

void tambahRW() {
    titikpengumpulan* T = new titikpengumpulan;

    cin.ignore();
    cout << "\n=== TAMBAH TITIK PENGUMPULAN RW ===\n";

    cout << "Masukkan nomor RW (contoh: RW 01)1: ";
    getline(cin, T->RW);

    cout << "Masukkan alamat titik pengumpulan: ";
    getline(cin, T->alamat);

    T->next = NULL;

    // Jika list masih kosong
    if (headRW == NULL) {
        headRW = T;
    } else {
        // tambah di akhir
        titikpengumpulan* temp = headRW;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = T;
    }

    cout << "RW berhasil ditambahkan!\n";
}



void tampilRW() {
    cout << "\n=== DAFTAR TITIK PENGUMPULAN RW ===\n";

    if (headRW == NULL) {
        cout << "Belum ada titik pengumpulan.\n";
        return;
    }

    titikpengumpulan* temp = headRW;
    int nomor = 1;

    while (temp != NULL) {
        cout << nomor++ << ". RW : " << temp->RW << endl;
        cout << "   Alamat : " << temp->alamat << endl;
        temp = temp->next;
    }
}

void editRW() {
    if (headRW == NULL) {
        cout << "Data kosong.\n";
        return;
    }

    string cariRW;
    cout << "Masukkan RW yang ingin diedit: ";
    cin.ignore();
    getline(cin, cariRW);

    titikpengumpulan* temp = headRW;

    while (temp != NULL) {
        if (temp->RW == cariRW) {
            cout << "Masukkan RW baru: ";
            getline(cin, temp->RW);

            cout << "Masukkan alamat baru: ";
            getline(cin, temp->alamat);

            cout << "Data berhasil diedit.\n";
            return;
        }
        temp = temp->next;
    }

    cout << "RW tidak ditemukan.\n";
}

void hapusRW(string rw) {
    if (headRW == NULL) {
        cout << "Data kosong.\n";
        return;
    }

    titikpengumpulan* temp = headRW;
    titikpengumpulan* prev = NULL;

    // Jika yang dihapus adalah head
    if (temp != NULL && temp->RW == rw) {
        headRW = temp->next;
        delete temp;
        cout << "RW berhasil dihapus.\n";
        return;
    }

    // Mencari RW yang akan dihapus
    while (temp != NULL && temp->RW != rw) {
        prev = temp;
        temp = temp->next;
    }

    // Jika RW tidak ditemukan
    if (temp == NULL) {
        cout << "RW tidak ditemukan.\n";
        return;
    }

    // Menghapus node
    prev->next = temp->next;
    delete temp;
    cout << "RW berhasil dihapus.\n";
}

float getHargaPerKgJenis(string kategori, string jenis) {
    // ✅ Harga SAMPAH ORGANIK (lebih murah)
    if (kategori == "Organik") {
        return 1000;   // harga organik flat
    }

    // ✅ Harga SAMPAH ANORGANIK (beda tiap jenis)
    else if (kategori == "Anorganik") {
        if (jenis == "Plastik") return 4000;
        if (jenis == "Kaca")    return 3000;
        if (jenis == "Logam")   return 8000;  // paling mahal
        if (jenis == "Kertas")  return 2500;
        if (jenis == "Karet")   return 3500;

        return 2000; // default jika jenis tidak dikenali
    }

    return 0; // kategori tidak valid
}
