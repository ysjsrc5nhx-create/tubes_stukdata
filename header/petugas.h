#ifndef PETUGAS_H
#define PETUGAS_H

#include <string>
#include "pengeloaan_sampah.h"
#include "pelanggan.h"

using namespace std;

// ================================
// NODE SAMPAH (linked list)
// ================================
struct NodeSampah {
    Sampah data;
    NodeSampah* next;
};

// ================================
// NODE TRANSAKSI (multi link ke sampah)
// ================================
struct Transaksi {
    string idTransaksi;
    string namaNasabah;

    NodeSampah* daftarSampah; // relasi ke banyak sampah
    Transaksi* next;          // linked list transaksi
};


// ================================
// HEAD TRANSAKSI
// ================================
extern Transaksi* headTransaksi;

// transaksi
void tambahTransaksi();
void lihatTransaksi();
void laporanTransaksi();

// kelola sampah per transaksi
void tambahSampahKeTransaksiMenu();
void lihatSampahPerTransaksi();
void editSampahTransaksi();
void hapusSampahTransaksi();
void kelolaSampah();


// util
Transaksi* cariTransaksiById(string id);
// menu petugas
void menuPetugas(pelanggan* p);

#endif
