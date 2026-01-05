#include "header/pelanggan.h"
#include "header/pengeloaan_sampah.h"
#include "header/petugas.h"
#include "header/menu.h"
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
    cout << "\n===== MENU USER =====\n";
    cout << "Nama: " << p->dataPelanggan.nama << endl;
    cout << "Alamat: " << p->dataPelanggan.alamat << endl;
    cout << "No Telp: " << p->dataPelanggan.no_telp << endl;
    int pilih;
    cout << "1. Tambah Sampah\n";
    cout << "2. Lihat Sampah\n";
    cout << "3. edit sampah \n";
    cout << "4. delete sampah \n";
    cout << "5.back ke menu awal \n";

    cout << "Pilih menu: ";
    cin >> pilih;

    switch (pilih)
    {
    case 1: {
        tambahSampahUser(p);
        menuUser(p);
        break;
    }
    case 2: {
        lihatSampahUser(p);
        menuUser(p);
        break;
    }
    case 3:
        cout << "edit sampah .\n";
        editSampahUser(p);
        menuUser(p);
        break;

    case 4:
        cout << "delete sampah .\n";
        deleteSampahUser(p);
        menuUser(p);
        break;
    case 5:
        cout << "kembali ke menu awal .\n";
        menuAwal();
        break;


    default:
        break;
    }

   

    cout << "=========================\n";
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

    // insert into customer's personal list and get the node
    SampahNode* userNode = insertSampahKePelanggan(p, s);

    // create a new transaksi automatically with status "belum" and link the sampah
    Transaksi* baru = new Transaksi();
    // use global auto-increment transaksiCounter (defined in petugas.cpp)
    baru->idTransaksi = to_string(transaksiCounter++);
    baru->namaNasabah = p->dataPelanggan.nama;
    baru->status = "belum"; // constructor sets this, but keep explicit
    // create a node for this transaction's sampah list
    SampahNode* sn = createNodeSampah(s);
    if (sn) {
        sn->transaksi = baru;
        baru->daftarSampah = sn;
    } else {
        baru->daftarSampah = nullptr;
    }
    // link the user's personal sampah node to this transaksi so status is visible
    if (userNode) {
        userNode->transaksi = baru;
        // debug check
        cout << "[debug] linked userNode to transaksi with status: " << (userNode->transaksi ? userNode->transaksi->status : string("NULL")) << endl;
    }
    baru->next = nullptr;

    // append transaksi to global list
    if (!headTransaksi)
        headTransaksi = baru;
    else {
        Transaksi* t = headTransaksi;
        while (t->next) t = t->next;
        t->next = baru;
    }

    cout << "Sampah berhasil ditambahkan dan transaksi otomatis dibuat (ID: " << baru->idTransaksi << ").\n";
}


Sampah inputSampahuser(pelanggan* p) {
    Sampah S;
    int pilihKategori;

    cout << "\n=== KATEGORI SAMPAH ===\n";
    cout << "1. Organik\n";
    cout << "2. Anorganik\n";
    cout << "Pilihan: ";
    cin >> pilihKategori;

    // KATEGORI ORGANIK
    if (pilihKategori == 1) {
        S.kategori = "Organik";
        cin.ignore();
        cout << "Masukkan jenis sampah organik: ";
        getline(cin, S.jenisSampah);
    }
    // KATEGORI ANORGANIK
    else if (pilihKategori == 2) {
        S.kategori = "Anorganik";

        int pilihJenis;
        cout << "\n=== JENIS SAMPAH ANORGANIK ===\n";
        cout << "1. Plastik\n";
        cout << "2. Kaca\n";
        cout << "3. Logam\n";
        cout << "4. Kertas\n";
        cout << "5. Karet\n";
        cout << "Pilihan: ";
        cin >> pilihJenis;

        switch (pilihJenis) {
            case 1: S.jenisSampah = "Plastik"; break;
            case 2: S.jenisSampah = "Kaca"; break;
            case 3: S.jenisSampah = "Logam"; break;
            case 4: S.jenisSampah = "Kertas"; break;
            case 5: S.jenisSampah = "Karet"; break;
            default: S.jenisSampah = "Tidak diketahui"; break;
        }
    }
    else {
        cout << "Pilihan kategori tidak valid.\n";
        S.kategori = "Tidak valid";
        S.jenisSampah = "Tidak valid";
    }

    cout << "Masukkan berat (kg): ";
    cin >> S.berat;

    S.hargaPerKg = getHargaPerKgJenis(S.kategori, S.jenisSampah);
    cout << "Harga per Kg otomatis: Rp " << S.hargaPerKg << endl;

    return S;
}

