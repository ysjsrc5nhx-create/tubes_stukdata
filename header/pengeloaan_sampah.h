#ifndef PENGELOLAAN_SAMPAH_H
#define PENGELOLAAN_SAMPAH_H

#include <string>
using namespace std;

typedef struct Sampah {
    string jenisSampah;
    float berat;        // kilogram
    float hargaPerKg; // harga per kilogram  
    string kategori; 
} Sampah;

typedef struct SampahNode {
    string jenisSampah;
    int hargaPerKg;
    SampahNode* next;
    SampahNode* prev;
} SampahNode;

typedef struct queueNode {
    Sampah data;
    queueNode* next;
} queueNode;


// Pointer queue (global) 
extern queueNode* depan;   // front
extern queueNode* belakang; // rear


// Prototipe fungsi queue
queueNode* createSampah(Sampah S);
void enqueueSampah(Sampah S);
string dequeueSampah();
void tampilQueueSampah();
bool isEmpty();
Sampah inputSampah();
float getHargaPerKgJenis(string kategori, string jenis);

#endif
