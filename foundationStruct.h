#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <iomanip>
#pragma once

using namespace std;

const int MAX_NHANVIEN = 500;
const int MENU_ITEMS = 5;
const int VATTU_ITEMS = 3;
extern int soLuongNhanVienGlobalCount;
extern int SoLuongVatTuGlobalCount;

//-------PART 1----------------------------------------------------------------
//------Danh Sach Vat Tu------------------------------------------------------------
typedef struct VatTu
{
    char maVT[11];  // ma vat tu
    char tenVT[51]; // ten vat tu
    char dVT[11];   // don vi tinh
    int soLuongTon; // so luong ton
    int bf;         // Balance factor
    VatTu *left;
    VatTu *right;
} *DanhSachVatTu;

// Khoi tao danh sach vat tu moi

//------------------PART 2-------------------------------------------------
//---------Danh Sach Chi Tiet Hoa Don------------------------------------------------
typedef struct CT_HoaDon
{
    char maVT[11]; // ma vat tu
    int soLuong;   // so luong
    double donGia; // don gia
    double vAT;    // % VAT
    CT_HoaDon *next;
} *DanhSach_CT_HoaDon;

//--------Danh Sach Hoa Don-------------------------------------------------
typedef enum LoaiHoaDon
{
    n,
    x
} LoaiHoaDon;

struct Date
{
    int day;
    int month;
    int year;
};

typedef struct HoaDon
{
    char soHD[21];
    Date date;
    LoaiHoaDon loai;
    DanhSach_CT_HoaDon ds_ct_hoadon = nullptr;
    HoaDon *next;
} *DanhSachHoaDon;

//------Danh Sach Nhan Vien----------------------------------------------------

typedef enum Phai
{
    nam,
    nu
} Phai;

typedef struct NhanVien
{
    char maNV[11];
    char ho[21];
    char ten[11];
    Phai phai;
    DanhSachHoaDon ds_hoadon = nullptr;
    int position;
} *DanhSachNhanVien[MAX_NHANVIEN];
