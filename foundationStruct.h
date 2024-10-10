#ifndef FOUNDATIONSTRUCT_H
#define FOUNDATIONSTRUCT_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include <fstream>

using namespace std;

const int MAX_NHANVIEN = 500;
const int MENU_ITEMS = 5;
const int VATTU_ITEMS = 3;
extern int idGlobalCount;

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
    float donGia;  // don gia
    float vAT;     // % VAT
    CT_HoaDon *next;
} *DanhSach_CT_HoaDon;

//--------Danh Sach Hoa Don-------------------------------------------------
typedef enum LoaiHoaDon
{
    n,
    x
} LoaiHoaDon;

typedef struct HoaDon
{
    char soHD[21];                   // Số hóa đơn
    char ngayLapHoaDon[21];          // Ngày lập hóa đơn
    LoaiHoaDon loai;                 // Loại hóa đơn: 'N' (phiếu nhập) hoặc 'X' (phiếu xuất)
    DanhSach_CT_HoaDon ds_ct_hoadon; // Danh sách chi tiết hóa đơn
    HoaDon *next;                    // Con trỏ đến hóa đơn tiếp theo
} *DanhSachHoaDon;

//------Danh Sach Nhan Vien----------------------------------------------------
typedef struct NhanVien
{
    char maNV[21];            // Mã nhân viên
    char ho[11];              // Họ
    char ten[21];             // Tên
    char phai[5];             // Phái (Nam/Nữ)
    DanhSachHoaDon ds_hoadon; // Danh sách hóa đơn
    int position;             // so thu tu SV cua danh sach
    NhanVien *node[MAX_NHANVIEN];
} *DanhSachNhanVien;

#endif
