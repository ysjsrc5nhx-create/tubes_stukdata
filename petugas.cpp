#include <iostream>
#include <string>
#include "header/petugas.h"
#include "header/pengeloaan_sampah.h"
#include "header/menu.h"

using namespace std;

// ====================================================
//                MENU KELOLA SAMPAH PETUGAS
// ====================================================
void kelolaSampah() {
    int pilih;

    do {
        cout << "\n======== KELOLA SAMPAH ========\n";
        cout << "1. Tambah Sampah\n";
        cout << "2. Lihat Data Sampah\n";
        cout << "3. Edit Data Sampah\n";
        cout << "4. Hapus Data Sampah\n";
        cout << "5. Kembali\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahSampah(); break;
            case 2: lihatSampah(); break;
            case 3: editSampah(); break;
            case 4: hapusSampah(); break;
            case 5: break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 5);
}


// ====================================================
//           TAMBAH SAMPAH (PAKAI inputSampah())
// ====================================================
void tambahSampah() {
    if (jumlahSampah >= 20) {
        cout << "Data penuh! Tidak bisa menambah sampah baru.\n";
        return;
    }

    cout << "\n=== TAMBAH DATA SAMPAH ===\n";
    Sampah S = inputSampah();

    dataSampah[jumlahSampah] = S;
    jumlahSampah++;

    cout << "Data sampah berhasil ditambahkan!\n";
    kelolaSampah();
}


// ====================================================
//                  LIHAT SAMPAH
// ====================================================
void lihatSampah() {
    cout << "\n=== DAFTAR SAMPAH ===\n";

    if (jumlahSampah == 0) {
        cout << "Belum ada data sampah.\n";
        return;
    }

    for (int i = 0; i < jumlahSampah; i++) {
        cout << i+1 << ". Kategori: " << dataSampah[i].kategori << endl;
        cout << "   Jenis   : " << dataSampah[i].jenisSampah << endl;
        cout << "   Berat   : " << dataSampah[i].berat << " kg\n";
        cout << "   Harga/Kg: Rp " << dataSampah[i].hargaPerKg << "\n";
    }
    kelolaSampah();
}


// ====================================================
//                  EDIT SAMPAH
// ====================================================
void editSampah() {
    lihatSampah();

    if (jumlahSampah == 0)
        return;

    int index;
    cout << "\nPilih nomor sampah yang ingin diedit: ";
    cin >> index;

    if (index < 1 || index > jumlahSampah) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    cout << "\n=== EDIT DATA SAMPAH ===\n";
    Sampah S = inputSampah();

    dataSampah[index-1] = S;

    cout << "Data sampah berhasil diperbarui!\n";
    kelolaSampah();
}


// ====================================================
//                  HAPUS SAMPAH
// ====================================================
void hapusSampah() {
    lihatSampah();

    if (jumlahSampah == 0)
        return;

    int index;
    cout << "\nMasukkan nomor sampah yang ingin dihapus: ";
    cin >> index;

    if (index < 1 || index > jumlahSampah) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    for (int i = index - 1; i < jumlahSampah - 1; i++) {
        dataSampah[i] = dataSampah[i+1];
    }

    jumlahSampah--;
    cout << "Data sampah berhasil dihapus!\n";
    kelolaSampah();
}


// ====================================================
//            TAMBAH TRANSAKSI (OTOMATIS HITUNG)
// ====================================================
void tambahTransaksi() {
    if (jumlahTransaksi >= 50) {
        cout << "Data transaksi penuh!\n";
        return;
    }

    cout << "\n=== TAMBAH TRANSAKSI ===\n";

    Transaksi T;

    cout << "Masukkan ID Transaksi: ";
    cin >> T.idTransaksi;

    cout << "Nama Nasabah: ";
    cin.ignore();
    getline(cin, T.namaNasabah);

    Sampah S = inputSampah();

    T.jenisSampah = S.jenisSampah;
    T.berat = S.berat;
    T.totalHarga = S.hargaPerKg * S.berat;

    dataTransaksi[jumlahTransaksi] = T;
    jumlahTransaksi++;

    cout << "Transaksi berhasil ditambahkan!\n";
    laporanTransaksi();
}


// ====================================================
//                   LIHAT TRANSAKSI
// ====================================================
void lihatTransaksi() {
    cout << "\n=== DAFTAR TRANSAKSI ===\n";

    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    for (int i = 0; i < jumlahTransaksi; i++) {
        cout << i+1 << ". ID     : " << dataTransaksi[i].idTransaksi << endl;
        cout << "   Nama   : " << dataTransaksi[i].namaNasabah << endl;
        cout << "   Jenis  : " << dataTransaksi[i].jenisSampah << endl;
        cout << "   Berat  : " << dataTransaksi[i].berat << " kg\n";
        cout << "   Total  : Rp " << dataTransaksi[i].totalHarga << "\n";
    }
    laporanTransaksi();
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
            break;
        case 2:
            tambahTransaksi();
            break;
        case 3:
            break;
        default:
            cout << "Pilihan tidak valid!\n";
    }
}


void menuPetugas(pelanggan* p){

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




