#ifndef PENGELOLAAN_SAMPAH_H
#define PENGELOLAAN_SAMPAH_H
#include <string>
using namespace std;

struct Transaksi;

typedef struct Sampah {
    string jenisSampah;
    float berat;        // kilogram
    float hargaPerKg; // harga per kilogram  
    string kategori; 
} Sampah;

struct SampahNode {
    Sampah dataSampah;        
    SampahNode* next;
    SampahNode* prev;
    Transaksi* transaksi;     // HANYA 1
};



// Pointer queue (global) 
extern SampahNode* depan;   // front
extern SampahNode* belakang; // rear


// Prototipe fungsi queue
Sampah inputSampah();
float getHargaPerKgJenis(string kategori, string jenis);

#endif
