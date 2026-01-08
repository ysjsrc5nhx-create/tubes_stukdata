#include "header/admin.h"
#include "header/pelanggan.h"
#include "header/petugas.h"
#include "header/menu.h"
#include <iostream>
using namespace std;

void adminListUser(pelanggan* head) {
    cout << "==========================" << endl;
    cout << "       DAFTAR USER        " << endl;
    cout << "==========================" << endl;

    pelanggan* current = head;
    if (current == NULL) {
        cout << "Tidak ada user terdaftar." << endl;
        return;
    }

    while (current != NULL) {
        cout << "Nama: " << current->dataPelanggan.nama << endl;
        cout << "Alamat: " << current->dataPelanggan.alamat << endl;
        cout << "No Telp: " << current->dataPelanggan.no_telp << endl;
        cout << "Username: " << current->dataPelanggan.username << endl;
        cout << "Role: " << current->dataPelanggan.role << endl;
        cout << "--------------------------" << endl;
        current = current->next;
    }
}

void adminTambahUser(pelanggan*& head, pelanggan*& tail) {
    DataUser newUser;
     cout << "\n===== TAMBAH USER / PETUGAS =====\n";
    cout << "Username : "; cin >> newUser.username;
    cout << "Password : "; cin >> newUser.password;
    cout << "Nama     : "; cin >> newUser.nama;
    cout << "Alamat   : "; cin >> newUser.alamat;
    cout << "No Telp  : "; cin >> newUser.no_telp;
    cout << "Role (user/petugas): "; cin >> newUser.role;

    insertPelanggan(head, tail, newUser);
    cout << "User berhasil ditambahkan." << endl;
}

void adminEditUser(pelanggan* head) {
    string username;
    cout << "\n===== EDIT USER / PETUGAS =====\n";
    cout << "Masukkan username yang akan diedit: ";
    cin >> username;

    pelanggan* current = head;
    while (current != nullptr) {
        if (current->dataPelanggan.username == username) {
            cout << "Mengedit data untuk user: " << username << endl;
            cout << "Nama (" << current->dataPelanggan.nama << "): "; cin >> current->dataPelanggan.nama;
            cout << "Alamat (" << current->dataPelanggan.alamat << "): "; cin >> current->dataPelanggan.alamat;
            cout << "No Telp (" << current->dataPelanggan.no_telp << "): "; cin >> current->dataPelanggan.no_telp;
            cout << "Password (" << current->dataPelanggan.password << "): "; cin >> current->dataPelanggan.password;
            cout << "Role (" << current->dataPelanggan.role << "): "; cin >> current->dataPelanggan.role;
            cout << "Data user berhasil diperbarui." << endl;
            return;
        }
        current = current->next;
    }
    cout << "User dengan username " << username << " tidak ditemukan." << endl;
}

void adminHapusUser(pelanggan*& head) {
    string username;
    cout << "\n===== HAPUS USER / PETUGAS =====\n";
    cout << "Masukkan username yang akan dihapus: ";
    cin >> username;

    pelanggan* current = head;
    pelanggan* target = nullptr;

    while (current != nullptr) {
        if (current->dataPelanggan.username == username) {
            target = current;
            break;
        }
        current = current->next;
    }

    if (target == nullptr) {
        cout << "User dengan username " << username << " tidak ditemukan." << endl;
        return;
    }

    // Hapus node dari linked list
    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        head = target->next; // Update head if needed
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    }

    delete target;
    cout << "User dengan username " << username << " telah dihapus." << endl;
}

void adminMenu(pelanggan*& head, pelanggan*& tail) {
    int choice;
    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. List User/Petugas\n";
        cout << "2. Tambah User/Petugas\n";
        cout << "3. Edit User/Petugas\n";
        cout << "4. Hapus User/Petugas\n";
        cout << "5. cari user \n";
        cout << "6. Liat Semua List Transaksi\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        if (!(cin >> choice)) {
        cout << "Input tidak valid! Harap masukkan ANGKA 1-5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        adminMenu(head, tail);
        return;
     }

        switch (choice) {
            case 1:
                adminListUser(head);
                break;
            case 2:
                adminTambahUser(head, tail);
                break;
            case 3:
                adminEditUser(head);
                break;
            case 4:
                adminHapusUser(head);
                break;
            case 5:
                adminSearchUserByNama(head);
                break;
            case 6:
                adminLihatSemuaTransaksi();
                break;
            case 7:
                cout << "Keluar dari menu admin.\n";
                menuAwal();
                break;    
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 7);
}

void adminSearchUserByNama(pelanggan* head) {
    string nama;
    cout << "\n===== SEARCH USER BY NAMA =====\n";
    cout << "Masukkan nama yang dicari: ";
    cin.ignore();
    getline(cin, nama);


    pelanggan* current = head;
    bool ditemukan = false;

    while (current != nullptr) {
        if (current->dataPelanggan.username == nama) {
            cout << "\n--- USER DITEMUKAN ---\n";
            cout << "Nama     : " << current->dataPelanggan.nama << endl;
            cout << "Alamat   : " << current->dataPelanggan.alamat << endl;
            cout << "No Telp  : " << current->dataPelanggan.no_telp << endl;
            cout << "Username : " << current->dataPelanggan.username << endl;
            cout << "Role     : " << current->dataPelanggan.role << endl;
            cout << "----------------------\n";
            ditemukan = true;
        }
        current = current->next;
    }

    if (!ditemukan) {
        cout << "User dengan nama \"" << nama << "\" tidak ditemukan.\n";
    }
}

void adminLihatSemuaTransaksi() {
    cout << "\n===== SEMUA TRANSAKSI =====\n";
    lihatTransaksi();
}