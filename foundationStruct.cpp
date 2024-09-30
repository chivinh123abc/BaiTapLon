#include <iostream>
#include <cstring>
#include <cmath>
#include <string.h>
#include <mylib.h>

using namespace std;

//-------PART 1----------------------------------------------------------------
//------Danh Sach Vat Tu------------------------------------------------------------
typedef struct VatTu
{
    char maVT[11];
    char tenVT[51];
    char dVT[21]; // DonViTinh
    VatTu *left;
    VatTu *right;
};