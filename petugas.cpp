#include <iostream>
#include <string>
#include "header/petugas.h"
#include "header/pengeloaan_sampah.h"
#include "header/menu.h"

using namespace std;

// HEAD transaksi
Transaksi* headTransaksi = nullptr;
// global transaksi counter (start from 1)
int transaksiCounter = 1;


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
            cout << "Status         : " << t->status << endl;

        // tampilkan daftar sampah
        if (t->daftarSampah == nullptr) {
            cout << "  Tidak ada data sampah.\n";
        } else {
            cout << "  Daftar Sampah:\n";

            SampahNode* s = t->daftarSampah;
            int i = 1;
            int total = 0;

            while (s != nullptr) {
                int subtotal = s->dataSampah.berat * s->dataSampah.hargaPerKg;

                cout << "   " << i++ << ". "
                     << s->dataSampah.jenisSampah
                     << " | " << s->dataSampah.berat << " kg"
                     << " | Rp " << s->dataSampah.hargaPerKg
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
    cout << "2. Tandai Transaksi Selesai (by ID)\n";
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
            selesaikanTransaksiById();
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
// ===================================================
//                    SELESAIKAN TRANSAKSI
// ===================================================

// ubah status transaksi menjadi "sudah" berdasarkan ID
void selesaikanTransaksiById() {
    if (!headTransaksi) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    string id;
    cout << "Masukkan ID Transaksi yang ingin diselesaikan: ";
    cin >> id;
    // Search the transaksi list here to avoid potential linkage issues
    Transaksi* cur = headTransaksi;
    while (cur) {
        if (cur->idTransaksi == id) break;
        cur = cur->next;
    }

    if (!cur) {
        cout << "Transaksi dengan ID '" << id << "' tidak ditemukan.\n";
        return;
    }

    if (cur->status == "sudah") {
        cout << "Transaksi sudah berstatus 'sudah'.\n";
        return;
    }

    cur->status = "sudah";
    cout << "Status transaksi (ID: " << id << ") berhasil diubah menjadi 'sudah'.\n";
}


void menuPetugas(pelanggan* p) {
    int pilihan;
    cout << "==========================" << endl;
    cout << "      MENU PETUGAS       " << endl;
    cout << "==========================" << endl;
    cout << "1. Laporan Transaksi " << endl;
    cout << "2. Keluar " << endl;
    cout << "==========================" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            laporanTransaksi();
            break;
        case 2:
            cout << "Keluar dari menu petugas." << endl;
            menuAwal();
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
    }
}




