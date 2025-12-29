// ...existing code...
#include "header/pelanggan.h"
#include "header/login.h"
#include "header/dataDumy.h"
#include "header/menu.h"
#include <iostream>
using namespace std;

// Definisi variabel global (deklarasi extern ada di header/pelanggan.h)
pelanggan* head = nullptr;
pelanggan* tail = nullptr;


int menuAwal(); // prototipe lokal

int main() {
    // Inisialisasi data sekali saja
    dataDummy(head, tail);

    // Loop utama menu
    while (true) {
        if (menuAwal() == 0) break;
    }

    return 0;
}

// ...existing code...
int menuAwal(){

    cout << "=== Selamat Datang di Sistem Pengelolaan Pelanggan Sampah ===" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Pilih opsi (1-3): ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            login(head);               // gunakan head global
            break;
        case 2:
            registerUser(head, tail);  // gunakan head/tail global
            break;
        case 3:
            cout << "Terima kasih telah menggunakan sistem kami. Sampai jumpa!" << endl;
            return 0;
        default:
            cout << "Opsi tidak valid. Silakan coba lagi." << endl;
    }

    return 0; // kembali ke menu utama
}