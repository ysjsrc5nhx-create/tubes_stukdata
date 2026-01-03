#include <iostream>
#include <string>
#include "header/petugas.h"
#include "header/pengeloaan_sampah.h"
#include "header/menu.h"

using namespace std;

// HEAD transaksi
Transaksi* headTransaksi = nullptr;

// ===================================
// MENU KELOLA SAMPAH (BERBASIS TRANSAKSI)
// ===================================
void kelolaSampah() {

        cout << "\n====== KELOLA SAMPAH (MULTI LINKED LIST) ======\n";
        cout << "1. Tambah Sampah ke Transaksi\n";
        cout << "2. Lihat Sampah per Transaksi\n";
        cout << "3. Edit Sampah\n";
        cout << "4. Hapus Sampah\n";
        cout << "5. Kembali\n";
        cout << "Pilih menu: ";
        int pilih;
        cin >> pilih;

        switch (pilih) {
        case 1:
            tambahSampahKeTransaksiMenu();
            kelolaSampah();
            break;
        case 2:
            lihatSampahPerTransaksi();
            kelolaSampah();
            break;
        case 3:
            editSampahTransaksi();
            kelolaSampah();
            break;
        case 4:
            hapusSampahTransaksi();
            kelolaSampah();
            break;
        case 5:
            menuPetugas(nullptr);
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        } 
    } 


Transaksi* cariTransaksiById(string id) {
    Transaksi* t = headTransaksi;
    while (t) {
        if (t->idTransaksi == id)
            return t;
        t = t->next;
    }
    return nullptr;
}


// ====================================================
//           TAMBAH SAMPAH (PAKAI inputSampah())
// ====================================================
void tambahSampahKeTransaksiMenu() {
    if (!headTransaksi) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    string id;
    cout << "Masukkan ID Transaksi: ";
    cin >> id;

    Transaksi* trx = cariTransaksiById(id);
    if (!trx) {
        cout << "Transaksi tidak ditemukan.\n";
        return;
    }

    NodeSampah* node = new NodeSampah;
    node->data = inputSampah();
    node->next = nullptr;

    if (!trx->daftarSampah)
        trx->daftarSampah = node;
    else {
        NodeSampah* temp = trx->daftarSampah;
        while (temp->next)
            temp = temp->next;
        temp->next = node;
    }

    cout << "Sampah berhasil ditambahkan.\n";
}

// ====================================================
//                  EDIT SAMPAH
// ====================================================
void lihatSampahPerTransaksi() {
    if (!headTransaksi) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    string id;
    cout << "Masukkan ID Transaksi: ";
    cin >> id;

    Transaksi* trx = cariTransaksiById(id);
    if (!trx) {
        cout << "Transaksi tidak ditemukan.\n";
        return;
    }

    if (!trx->daftarSampah) {
        cout << "Belum ada sampah pada transaksi ini.\n";
        return;
    }

    NodeSampah* s = trx->daftarSampah;
    int no = 1;

    cout << "\nDaftar Sampah Transaksi " << id << ":\n";

    while (s) {
        cout << no++ << ". "
             << s->data.jenisSampah
             << " | " << s->data.berat << " kg"
             << " | Rp " << s->data.hargaPerKg << endl;

        s = s->next;
    }
}

// ====================================================
//                  HAPUS SAMPAH
// ====================================================
void editSampahTransaksi() {
    string id;
    cout << "Masukkan ID Transaksi: ";
    cin >> id;

    Transaksi* trx = cariTransaksiById(id);
    if (!trx || !trx->daftarSampah) {
        cout << "Data tidak ditemukan.\n";
        return;
    }

    int index;
    cout << "Nomor sampah yang ingin diedit: ";
    cin >> index;

    NodeSampah* cur = trx->daftarSampah;
    int i = 1;

    while (cur && i < index) {
        cur = cur->next;
        i++;
    }

    if (!cur) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    cout << "\nMasukkan data baru:\n";
    cur->data = inputSampah();

    cout << "Data sampah berhasil diperbarui.\n";
}

void hapusSampahTransaksi() {
    string id;
    cout << "Masukkan ID Transaksi: ";
    cin >> id;

    Transaksi* trx = cariTransaksiById(id);
    if (!trx || !trx->daftarSampah) {
        cout << "Data tidak ditemukan.\n";
        return;
    }

    int index;
    cout << "Nomor sampah yang ingin dihapus: ";
    cin >> index;

    NodeSampah* curr = trx->daftarSampah;

    if (index == 1) {
        trx->daftarSampah = curr->next;
        delete curr;
        cout << "Sampah berhasil dihapus.\n";
        return;
    }

    NodeSampah* prev = nullptr;
    int i = 1;

    while (curr && i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (!curr) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    prev->next = curr->next;
    delete curr;

    cout << "Sampah berhasil dihapus.\n";
}




// ====================================================
//            TAMBAH TRANSAKSI (OTOMATIS HITUNG)
// ====================================================


void tambahTransaksi() {
    Transaksi* baru = new Transaksi;

    cout << "ID Transaksi : ";
    cin >> baru->idTransaksi;
    cin.ignore();

    cout << "Nama Nasabah : ";
    getline(cin, baru->namaNasabah);

    baru->daftarSampah = nullptr;
    baru->next = nullptr;

    if (!headTransaksi)
        headTransaksi = baru;
    else {
        Transaksi* temp = headTransaksi;
        while (temp->next)
            temp = temp->next;
        temp->next = baru;
    }

    cout << "Transaksi berhasil ditambahkan.\n";
}


// ====================================================
//                   LIHAT TRANSAKSI
// ====================================================

void lihatTransaksi() {
    if (headTransaksi == nullptr) {
        cout << "\nBelum ada transaksi.\n";
        return;
    }

    Transaksi* t = headTransaksi;
    int no = 1;

    while (t != nullptr) {
        cout << "\n====================================\n";
        cout << "Transaksi ke-" << no++ << endl;
        cout << "ID Transaksi   : " << t->idTransaksi << endl;
        cout << "Nama Nasabah   : " << t->namaNasabah << endl;

        // tampilkan daftar sampah
        if (t->daftarSampah == nullptr) {
            cout << "  Tidak ada data sampah.\n";
        } else {
            cout << "  Daftar Sampah:\n";

            NodeSampah* s = t->daftarSampah;
            int i = 1;
            int total = 0;

            while (s != nullptr) {
                int subtotal = s->data.berat * s->data.hargaPerKg;

                cout << "   " << i++ << ". "
                     << s->data.jenisSampah
                     << " | " << s->data.berat << " kg"
                     << " | Rp " << s->data.hargaPerKg
                     << " = Rp " << subtotal
                     << endl;

                total += subtotal;
                s = s->next;
            }

            cout << "  Total Harga Transaksi: Rp " << total << endl;
        }

        t = t->next;
    }
}


void laporanTransaksi() {
    cout << "\n=== LAPORAN TRANSAKSI ===\n";
    cout << "1. Lihat Transaksi\n";
    cout << "2. Tambah Transaksi\n";
    cout << "3. Kembali\n";
    cout << "Pilih menu: ";
    
    int pilihan;
    cin >> pilihan;
    
    switch (pilihan) {
        case 1:
            lihatTransaksi();
            laporanTransaksi();
            break;
        case 2:
            tambahTransaksi();
            laporanTransaksi();
            break;
        case 3:
            menuPetugas(nullptr);
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
    } 
}


void menuPetugas(pelanggan* p) {
    int pilihan;
    cout << "==========================" << endl;
    cout << "      MENU PETUGAS       " << endl;
    cout << "==========================" << endl;
    cout << "1. Kelola Sampah " << endl;
    cout << "2. Laporan Transaksi " << endl;
    cout << "3. Keluar " << endl;
    cout << "==========================" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            kelolaSampah();
            break;
        case 2:
            laporanTransaksi();
            break;
        case 3:
            cout << "Keluar dari menu petugas." << endl;
            menuAwal();
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
    }
}




