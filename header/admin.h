#ifndef ADMIN_H
#define ADMIN_H
#include "pelanggan.h"
#include <string>
using namespace std;
void adminListUser(pelanggan* head);
void adminTambahUser(pelanggan*& head, pelanggan*& tail);
void adminEditUser(pelanggan* head);
void adminHapusUser(pelanggan*& head);

void adminMenu(pelanggan*& head, pelanggan*& tail);



#endif