#ifndef LOGIN_H
#define LOGIN_H

#include "pelanggan.h"
#include <string>
using namespace std;

void login(pelanggan* head);
string registerUser(pelanggan*& head, pelanggan*& tail);
void menuPetugas(pelanggan* p);

#endif
