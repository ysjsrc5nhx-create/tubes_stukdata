#include "header/login.h"
#include "header/admin.h"
#include "header/pelanggan.h"
#include "header/petugas.h"
#include "header/menu.h"
#include <iostream>
using namespace std;

void login(pelanggan* head) {
    cout << "==========================\n";
    cout << "          LOGIN           \n";
    cout << "==========================\n";

    string username, password;

    // pastikan buffer bersih
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Masukkan username: ";
    getline(cin, username);

    cout << "Masukkan password: ";
    getline(cin, password);

    cout << "==========================\n";

    if (username.empty() || password.empty()) {
        cout << "Login gagal: Username dan password tidak boleh kosong.\n";
        return;
    }

    // cari user di linked list
    pelanggan* userNode = searchPelanggan(head, username);

    if (userNode == nullptr) {
        cout << "Login gagal: Username tidak ditemukan.\n";
        return;
    }

    if (password != userNode->dataPelanggan.password) {
        cout << "Login gagal: Password salah.\n";
        return;
    }

    cout << "Login berhasil! Selamat datang, "
         << userNode->dataPelanggan.nama << endl;

    // cek role
    if (userNode->dataPelanggan.role == "user") {
        menuUser(userNode);
    }
    else if (userNode->dataPelanggan.role == "petugas") {
        menuPetugas(userNode);
    }
    else if (userNode->dataPelanggan.role == "admin") {
        adminMenu(head, tail);
    }
    else {
        cout << "Role tidak dikenali.\n";
    }
}


string registerUser(pelanggan*& head, pelanggan*& tail) {
    DataUser newUser;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // ================= NAMA =================
    while (true) {
        cout << "Masukkan nama: ";
        getline(cin, newUser.nama);

        if (newUser.nama.empty()) {
            cout << "Nama tidak boleh kosong!\n";
        } else {
            break;
        }
    }

    // ================= ALAMAT =================
    while (true) {
        cout << "Masukkan alamat: ";
        getline(cin, newUser.alamat);

        if (newUser.alamat.empty()) {
            cout << "Alamat tidak boleh kosong!\n";
        } else {
            break;
        }
    }

    // ================= NO TELP =================
    while (true) {
        cout << "Masukkan no_telp: ";
        getline(cin, newUser.no_telp);

        bool valid = true;
        if (newUser.no_telp.empty()) valid = false;

        for (char c : newUser.no_telp) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "No telp harus berupa angka dan tidak boleh kosong!\n";
        } else {
            break;
        }
    }

    // ================= USERNAME =================
    while (true) {
        cout << "Masukkan username: ";
        getline(cin, newUser.username);

        if (newUser.username.empty()) {
            cout << "Username tidak boleh kosong!\n";
            continue;
        }

        // cek username unik
        if (searchPelanggan(head, newUser.username) != nullptr) {
            cout << "Username sudah digunakan! Pilih username lain.\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "Masukkan password: ";
        getline(cin, newUser.password);

        if (newUser.password.length() < 4) {
            cout << "Password minimal 4 karakter!\n";
        } else {
            break;
        }
    }

    newUser.role = "user"; // default role

    insertPelanggan(head, tail, newUser);

    cout << "Registrasi berhasil! Silakan login dengan akun Anda.\n";

    return newUser.username;
}