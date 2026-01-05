#ifndef PETUGAS_H
#define PETUGAS_H

#include <string>
#include "pelanggan.h" // pelanggan.h already includes pengeloaan_sampah.h

using namespace std;




// ================================
// NODE TRANSAKSI (multi link ke sampah)
// ================================
struct Transaksi {
    string idTransaksi;
    string status;    // sudah selesai/belum
    string namaNasabah;

    // hubungan ke list sampah per transaksi
    SampahNode* daftarSampah;

    // next untuk linked list transaksi
    Transaksi* next;

    // konstruktor default: status otomatis "belum"
    Transaksi() : idTransaksi(""), status("belum"), namaNasabah(""), daftarSampah(nullptr), next(nullptr) {}
};


// ================================
// HEAD TRANSAKSI
// ================================
extern Transaksi* headTransaksi;
// global counter for transaksi IDs (auto-increment)
extern int transaksiCounter;

// transaksi
void lihatTransaksi();
void laporanTransaksi();

// ubah status transaksi (mis. menjadi "sudah") berdasarkan ID
void selesaikanTransaksiById();

// util
Transaksi* cariTransaksiById(string id);
// menu petugas
void menuPetugas(pelanggan* p);

#endif
