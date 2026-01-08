#include "header/pelanggan.h"
#include "header/pengeloaan_sampah.h"
#include "header/petugas.h"
#include "header/menu.h"
#include <limits>
#include <cctype>
#include <iostream>
#include <ctime>
using namespace std;
void createListPelanggan(pelanggan*& head, pelanggan*& tail) {
    head = nullptr;
    tail = nullptr;
}

pelanggan* createNodePelanggan(DataUser data) {
    pelanggan* newNode = new pelanggan;
    newNode->dataPelanggan = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    newNode->daftarSampah = nullptr;
    return newNode;
}

void insertPelanggan(pelanggan*& head, pelanggan*& tail, DataUser data) {
    pelanggan* newNode = createNodePelanggan(data);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

pelanggan* searchPelanggan(pelanggan* head, string username) {
    pelanggan* current = head;
    while (current != nullptr) {
        if (current->dataPelanggan.username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void deletePelanggan(pelanggan*& head, pelanggan*& tail, string username) {
    pelanggan* target = searchPelanggan(head, username);
    if (target == nullptr) return; // Not found

    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        head = target->next; // Update head if needed
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    } else {
        tail = target->prev; // Update tail if needed
    }

    delete target;
}

void printListBertingkat(pelanggan* head) {
    pelanggan* currentPelanggan = head;
    while (currentPelanggan != nullptr) {
        cout << "Pelanggan: " << currentPelanggan->dataPelanggan.nama << endl;
        SampahNode* currentSampah = currentPelanggan->daftarSampah;
        while (currentSampah != nullptr) {
            // access Sampah data via dataSampah member of node
            cout << "  Sampah: " << currentSampah->dataSampah.jenisSampah
                 << ", Harga per Kg: " << currentSampah->dataSampah.hargaPerKg << endl;
            currentSampah = currentSampah->next;
        }
        currentPelanggan = currentPelanggan->next;
    }
}

// create node from Sampah object to avoid signature conflicts and match node layout
SampahNode* createNodeSampah(const Sampah& s) {
    SampahNode* newNode = new SampahNode;
    newNode->dataSampah = s;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}
SampahNode* insertSampahKePelanggan(pelanggan* p, const Sampah& s) {
    SampahNode* newNode = createNodeSampah(s);
    if (p->daftarSampah == nullptr) {
        p->daftarSampah = newNode;
    } else {
        SampahNode* current = p->daftarSampah;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
    return newNode;
}


void menuUser(pelanggan* p) {
    cout << "\n===== MENU PELANGGAN =====\n";
    cout << "Nama   : " << p->dataPelanggan.nama << endl;
    cout << "Alamat : " << p->dataPelanggan.alamat << endl;
    cout << "No Telp: " << p->dataPelanggan.no_telp << endl;

    cout << "1. Tambah Sampah\n";
    cout << "2. Lihat Sampah\n";
    cout << "3. Edit Sampah\n";
    cout << "4. Delete Sampah\n";
    cout << "5. Back ke Menu Awal\n";
    cout << "Pilih menu (1-5): ";

    int pilih;

    if (!(cin >> pilih)) {
        cout << "Input tidak valid! Harap masukkan ANGKA 1-5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        menuUser(p);
        return;
    }

    if (pilih < 1 || pilih > 5) {
        cout << "Pilihan tidak tersedia! Pilih angka 1-5.\n";
        menuUser(p);
        return;
    }

    switch (pilih) {
        case 1:
            tambahSampahUser(p);
            break;
        case 2:
            lihatSampahUser(p);
            break;
        case 3:
            editSampahUser(p);
            break;
        case 4:
            deleteSampahUser(p);
            break;
        case 5:
            cout << "Kembali ke menu awal.\n";
            menuAwal();
            return;
    }

    menuUser(p); // tampilkan ulang menu setelah aksi
}
void editSampahUser(pelanggan* p) {
    if (!p->daftarSampah) {
        cout << "Belum ada sampah.\n";
        return;
    }

    int index = 1;
    SampahNode* curr = p->daftarSampah;

    cout << "\nDaftar Sampah:\n";
    while (curr) {
        cout << index++ << ". " << curr->dataSampah.jenisSampah << endl;
        curr = curr->next;
    }

    cout << "Pilih nomor sampah: ";
    int pilih;
    cin >> pilih;

    curr = p->daftarSampah;
    int i = 1;
    while (curr && i < pilih) {
        curr = curr->next;
        i++;
    }

    if (!curr) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    cout << "Masukkan data baru:\n";
    Sampah s = inputSampahuser(p);

    curr->dataSampah.jenisSampah = s.jenisSampah;
    curr->dataSampah.hargaPerKg  = s.hargaPerKg;

    cout << "Data berhasil diperbarui.\n";
}

void deleteSampahUser(pelanggan* p) {
    if (!p->daftarSampah) {
        cout << "Belum ada sampah.\n";
        return;
    }

    int index = 1;
    SampahNode* curr = p->daftarSampah;

    cout << "\nDaftar Sampah:\n";
    while (curr) {
        cout << index++ << ". " << curr->dataSampah.jenisSampah << endl;
        curr = curr->next;
    }

    cout << "Pilih nomor yang ingin dihapus: ";
    int pilih;
    cin >> pilih;

    curr = p->daftarSampah;
    int i = 1;
    while (curr && i < pilih) {
        curr = curr->next;
        i++;
    }

    if (!curr) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    if (curr->prev)
        curr->prev->next = curr->next;
    else
        p->daftarSampah = curr->next;

    if (curr->next)
        curr->next->prev = curr->prev;

    delete curr;

    cout << "Sampah berhasil dihapus.\n";
}




void lihatSampahUser(pelanggan* p) {
    cout << "\n=== DAFTAR SAMPAH ANDA ===\n";
    SampahNode* current = p->daftarSampah;

    if (current == nullptr) {
        cout << "Anda belum memiliki sampah yang terdaftar.\n";
        return;
    }

    int i = 1;
    while (current != nullptr) {
        cout << i << ". Jenis Sampah: " << current->dataSampah.jenisSampah << ", Harga per Kg: " << current->dataSampah.hargaPerKg;
        if (current->transaksi != nullptr) {
            cout << ", Status Transaksi: " << current->transaksi->status;
        }
        cout << endl;
        current = current->next;
        i++;
    }
}


void tambahSampahUser(pelanggan* p) {
    Sampah s = inputSampahuser(p);

    // masukkan sampah ke daftar sampah milik pelanggan dan ambil node-nya
    SampahNode* userNode = insertSampahKePelanggan(p, s);

    // buat transaksi baru secara otomatis dengan status "belum"
    Transaksi* baru = new Transaksi();

    // gunakan auto-increment 
    baru->idTransaksi = to_string(transaksiCounter++);
    baru->namaNasabah = p->dataPelanggan.nama;
    baru->status = "belum"; // set status awal transaksi

    // buat node sampah untuk daftar sampah pada transaksi
    SampahNode* sn = createNodeSampah(s);
    if (sn) {
        sn->transaksi = baru;
        baru->daftarSampah = sn;
    } else {
        baru->daftarSampah = nullptr;
    }

    // hubungkan node sampah milik pelanggan ke transaksi
    // agar status transaksi bisa dilihat dari data sampah pelanggan
    if (userNode) {
        userNode->transaksi = baru;

        // debug: memastikan node pelanggan berhasil terhubung ke transaksi
        cout << "[debug] linked userNode to transaksi with status: "
             << (userNode->transaksi ? userNode->transaksi->status : string("NULL")) << endl;
    }

    baru->next = nullptr;

    // tambahkan transaksi ke linked list transaksi global
    if (!headTransaksi)
        headTransaksi = baru;
    else {
        Transaksi* t = headTransaksi;
        while (t->next) t = t->next;
        t->next = baru;
    }

    // tampilkan pesan bahwa sampah dan transaksi berhasil dibuat
    cout << "Sampah berhasil ditambahkan dan transaksi otomatis dibuat (ID: "
         << baru->idTransaksi << ").\n";
}


Sampah inputSampahuser(pelanggan* p) {
    Sampah S;
    int pilihKategori;

    while (true) {
        cout << "\n=== KATEGORI SAMPAH ===\n";
        cout << "1. Organik\n";
        cout << "2. Anorganik\n";
        cout << "Pilihan (1-2): ";

        if (!(cin >> pilihKategori)) {
            cout << "Input tidak valid! Harap masukkan angka 1 atau 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (pilihKategori < 1 || pilihKategori > 2) {
            cout << "Pilihan kategori tidak tersedia!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    if (pilihKategori == 1) {
        S.kategori = "Organik";
        cout << "Masukkan jenis sampah organik: ";
        getline(cin, S.jenisSampah);
    }

    else {
        S.kategori = "Anorganik";
        int pilihJenis;

        while (true) {
            cout << "\n=== JENIS SAMPAH ANORGANIK ===\n";
            cout << "1. Plastik\n";
            cout << "2. Kaca\n";
            cout << "3. Logam\n";
            cout << "4. Kertas\n";
            cout << "5. Karet\n";
            cout << "Pilihan (1-5): ";

            if (!(cin >> pilihJenis)) {
                cout << "Input tidak valid! Harap masukkan angka 1-5.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (pilihJenis < 1 || pilihJenis > 5) {
                cout << "Pilihan jenis tidak tersedia!\n";
                continue;
            }

            break;
        }

        switch (pilihJenis) {
            case 1: S.jenisSampah = "Plastik"; break;
            case 2: S.jenisSampah = "Kaca"; break;
            case 3: S.jenisSampah = "Logam"; break;
            case 4: S.jenisSampah = "Kertas"; break;
            case 5: S.jenisSampah = "Karet"; break;
        }
    }

    while (true) {
        cout << "Masukkan berat (kg): ";

        if (!(cin >> S.berat)) {
            cout << "Berat harus berupa angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (S.berat <= 0) {
            cout << "Berat harus lebih dari 0 kg!\n";
            continue;
        }

        break;
    }

    // ================= HARGA =================
    S.hargaPerKg = getHargaPerKgJenis(S.kategori, S.jenisSampah);
    cout << "Harga per Kg otomatis: Rp " << S.hargaPerKg << endl;

    return S;
}

