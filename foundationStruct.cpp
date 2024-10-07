#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include "mylib.h"
#include <fstream>

using namespace std;

const int MAX_NHANVIEN = 500;
const int MENU_ITEMS = 5;
const int VATTU_ITEMS = 3;
int idGlobalCount = 1;

//-------PART 1----------------------------------------------------------------
//------Danh Sach Vat Tu------------------------------------------------------------
typedef struct VatTu
{
    char maVT[11];  // Mã vật tư
    char tenVT[51]; // Tên vật tư
    char dVT[11];   // Đơn vị tính
    int soLuongTon; // Số lượng tồn
    int bf;         // Balance factor
    VatTu *left;
    VatTu *right;
} *DanhSachVatTu;

// Khoi tao danh sach vat tu moi

//------------------PART 2-------------------------------------------------
//---------Danh Sach Chi Tiet Hoa Don------------------------------------------------
typedef struct CT_HoaDon
{
    char maVT[11];   // Mã vật tư
    int soLuong;     // Số lượng
    float donGia;    // Đơn giá
    float vAT;       // % VAT
    CT_HoaDon *next; // Con trỏ đến chi tiết hóa đơn tiếp theo
} *DanhSach_CT_HoaDon;

//--------Danh Sach Hoa Don-------------------------------------------------
typedef struct HoaDon
{
    char soHD[21];                   // Số hóa đơn
    char ngayLapHoaDon[21];          // Ngày lập hóa đơn
    char loai;                       // Loại hóa đơn: 'N' (phiếu nhập) hoặc 'X' (phiếu xuất)
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
    int pos;                  // so SV cua danh sach
    NhanVien *node[MAX_NHANVIEN];
} *DanhSachNhanVien; // Danh sách nhân viên tối đa 500 người
