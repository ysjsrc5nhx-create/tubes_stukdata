#ifndef PELANGGAN_H
#define PELANGGAN_H

#include "pengeloaan_sampah.h"

#include <string>
using namespace std;

struct DataUser {
    string nama;
    string alamat;
    string no_telp;
    string username;
    string password;
    string role; // admin, petugas, user
};

struct pelanggan {
    DataUser dataPelanggan;
    pelanggan* next;
    pelanggan* prev;
    SampahNode* daftarSampah; // sublist sampah
};
extern pelanggan* head;
extern pelanggan* tail;



/* =======================
        ADT PELANGGAN
   ======================= */

void createListPelanggan(pelanggan*& head, pelanggan*& tail);
pelanggan* createNodePelanggan(DataUser data);
void insertPelanggan(pelanggan*& head, pelanggan*& tail, DataUser data);
pelanggan* searchPelanggan(pelanggan* head, string username);
void deletePelanggan(pelanggan*& head, pelanggan*& tail, string username);
void printListBertingkat(pelanggan* head);

/* =======================
        ADT SAMPAH
   ======================= */

SampahNode* createNodeSampah(string jenis, int harga);
void insertSampahKePelanggan(pelanggan* p, string jenis, int harga);


/// Implementation of insertSampahKePelanggan
void insertSampahKePelanggan(pelanggan* p, string jenis, int harga);


///menu User
void menuUser(pelanggan* p);
Sampah inputSampahuser(pelanggan* p);
void tambahSampahUser(pelanggan* p);
void lihatSampahUser(pelanggan* p);
void editSampahUser(pelanggan* p);
void deleteSampahUser(pelanggan* p);



#endif
