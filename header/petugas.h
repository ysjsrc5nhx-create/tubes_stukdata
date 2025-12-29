#ifndef PETUGAS_H
#define PETUGAS_H
#include "pengeloaan_sampah.h"
#include "pelanggan.h"

#include <string>
using namespace std;

// ================================
// FITUR PETUGAS - SAMPAH
// ================================

typedef int tipeJumlahSampah;
typedef int tipeJumlahTransaksi;

extern tipeJumlahSampah jumlahSampah;
extern Sampah dataSampah[20];

void kelolaSampah();
void tambahSampah();
void lihatSampah();
void editSampah();
void hapusSampah();


// ================================
// FITUR PETUGAS - TRANSAKSI
// ================================

struct Transaksi {
    string idTransaksi;
    string namaNasabah;
    string jenisSampah;
    float berat;
    int totalHarga;
};

extern tipeJumlahTransaksi jumlahTransaksi;
extern Transaksi dataTransaksi[50];
void laporanTransaksi();
void tambahTransaksi();
void lihatTransaksi();
void menuPetugas(pelanggan* p);

#endif
