#include "foundationStruct.cpp"

//
DanhSachNhanVien newDanhSachNhanVien(char maNV[], char ho[], char ten[], char phai[5], DanhSachHoaDon ds_hoadon)
{
    DanhSachNhanVien ds_nhanvien = new NhanVien;
    strcpy(ds_nhanvien->maNV, maNV);
    strcpy(ds_nhanvien->ho, ho);
    strcpy(ds_nhanvien->ten, ten);
    strcpy(ds_nhanvien->phai, phai);
    ds_nhanvien->ds_hoadon = ds_hoadon;
    return ds_nhanvien;
};

// Khai báo mảng con trỏ cho danh sách nhân viên
DanhSachNhanVien dsNhanVien[MAX_NHANVIEN];
