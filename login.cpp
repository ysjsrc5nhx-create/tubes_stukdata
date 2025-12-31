#include "header/login.h"
#include "header/admin.h"
#include "header/pelanggan.h"
#include "header/petugas.h"
#include "header/menu.h"
#include <iostream>
using namespace std;

void login(pelanggan* head) {
    cout << "==========================" << endl;
    cout << "          LOGIN           " << endl;
    cout << "==========================" << endl;

    string username, password;

    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    cout << "==========================" << endl;

    // cari user di linked list
    pelanggan* userNode = searchPelanggan(head, username);

    if (userNode == NULL) {
        cout << "Login gagal: Username tidak ditemukan." << endl;
        return;
    }

    if (password != userNode->dataPelanggan.password) {
        cout << "Login gagal: Password salah." << endl;
        return;
    }

    // Jika lolos username & password
    cout << "Login berhasil! Selamat datang, " << userNode->dataPelanggan.nama << endl;

    // Cek role
    if (userNode->dataPelanggan.role == "user") {
        menuUser(userNode);
    } else if (userNode->dataPelanggan.role == "petugas") {
        menuPetugas(userNode);
    } else if (userNode->dataPelanggan.role == "admin") {
        adminMenu(head, tail);
    } else {
        cout << "Role tidak dikenali." << endl;
    }
}


string registerUser(pelanggan*& head, pelanggan*& tail) {
    DataUser newUser;
    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, newUser.nama);
    cout << "Masukkan alamat: ";
    getline(cin, newUser.alamat);
    cout << "Masukkan no_telp: ";
    getline(cin, newUser.no_telp);
    cout << "Masukkan username: ";
    getline(cin, newUser.username);
    cout << "Masukkan password: ";
    getline(cin, newUser.password);
    newUser.role = "user"; // Default role is user

    insertPelanggan(head, tail, newUser);
    cout << "Registrasi berhasil! Silakan login dengan username dan password Anda." << endl;
    return newUser.username;
}