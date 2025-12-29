#include "header/pelanggan.h"
#include "header/login.h"
#include "header/petugas.h"
#include <iostream>
using namespace std;

// Define global variables
tipeJumlahSampah jumlahSampah = 0;
Sampah dataSampah[20];

tipeJumlahTransaksi jumlahTransaksi = 0;
Transaksi dataTransaksi[50];

void dataDummy(pelanggan*& head, pelanggan*& tail) {

    createListPelanggan(head, tail);

    // ============================
    // Data User Dummy
    // ============================
    DataUser u1 = {"Alice", "Wonderland", "0811111111", "alice", "pass1", "user"};
    DataUser u2 = {"Bob", "Builder Street", "0822222222", "bob", "pass2", "user"};
    DataUser u3 = {"Charlie", "Chocolate Factory", "0833333333", "charlie", "pass3", "petugas"};
    DataUser u4 = {"Admin", "Admin Street", "0844444444", "admin", "adminpass", "admin"};

    insertPelanggan(head, tail, u1);
    insertPelanggan(head, tail, u2);
    insertPelanggan(head, tail, u3);
    insertPelanggan(head, tail, u4);
   
    

    // Charlie (petugas) tidak punya sampah
}
