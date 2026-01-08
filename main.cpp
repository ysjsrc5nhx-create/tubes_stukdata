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

   while (true) {
        menuAwal();
    }
    return 0;
}

// ...existing code...
int menuAwal() {
    cout << "=== Selamat Datang di Sistem Pengelolaan Pelanggan Sampah ===" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Pilih opsi (1-3): ";

    int choice;

    if (!(cin >> choice)) {
        cout << "Input tidak valid! Harap masukkan angka 1-3.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return 0; // kembali ke menu
    }

    switch (choice) {
        case 1:
            login(head);
            break;

        case 2:
            registerUser(head, tail);
            break;

        case 3:
            cout << "Terima kasih telah menggunakan sistem kami. Sampai jumpa!" << endl;
            exit(0);

        default:
            cout << "Opsi tidak tersedia! Silakan pilih 1, 2, atau 3.\n";
            break;
    }

    return 0; // kembali ke menu utama
}