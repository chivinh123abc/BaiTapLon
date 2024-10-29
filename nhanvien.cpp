#include "foundationStruct.cpp"
#pragma once

//
void dinhDangMaNV(char rel[7], int &soThuTuMaNV)
{
    sprintf(rel, "NV-%03d", soThuTuMaNV);
}

NhanVien *newNhanVien(const char maNV[], const char ho[], const char ten[], Phai phai, DanhSachHoaDon ds_hoadon = nullptr)
{
    NhanVien *ds_nhanvien = new NhanVien;
    strcpy(ds_nhanvien->maNV, maNV);
    strcpy(ds_nhanvien->ho, ho);
    strcpy(ds_nhanvien->ten, ten);
    ds_nhanvien->phai = phai;
    ds_nhanvien->position = 0;
    ds_nhanvien->ds_hoadon = ds_hoadon;
    return ds_nhanvien;
};

int soSanhNhanVien(NhanVien *nv1, NhanVien *nv2)
{
    if (strcmp(nv1->ten, nv2->ten) != 0)
    {
        return strcmp(nv1->ten, nv2->ten);
    }
    return strcmp(nv1->ho, nv2->ho);
}

void capNhatGiaTriViTri(DanhSachNhanVien &ds_nv, int &soLuongNV)
{
    for (int i = 0; i < soLuongNV; i++)
    {
        ds_nv[i]->position = i;
    }
}

void insertNhanVienToDSNV(DanhSachNhanVien &ds_nv, NhanVien *nv, int &soLuongNV)
{
    if (soLuongNV >= MAX_NHANVIEN)
    {
        cout << "Danh sach nhan vien da day" << endl;
        return;
    }

    int i = -1;
    for (i = soLuongNV - 1; i >= 0 && (soSanhNhanVien(ds_nv[i], nv) > 0); i--)
    {
        ds_nv[i + 1] = ds_nv[i];
    }
    ds_nv[i + 1] = nv;
    soLuongNV++;
    idNhanVienGlobalCount++;

    capNhatGiaTriViTri(ds_nv, soLuongNV);
}

int searchNhanVienFromDSNV(DanhSachNhanVien ds_nv, const char maNV[], int soLuongNV)
{
    for (int i = 0; i < soLuongNV; i++)
    {
        if (strcmp(ds_nv[i]->maNV, maNV) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool isNhanVienInDSNV(DanhSachNhanVien ds_nv, const char maNV[], int soLuongNV)
{
    for (int i = 0; i < soLuongNV; i++)
    {
        if (strcmp(ds_nv[i]->maNV, maNV) == 0)
        {
            return true;
        }
    }
    return false;
}

void removeNhanVienByMaNV(DanhSachNhanVien &ds_nv, const char maNV[], int &soLuongNV)
{
    if (ds_nv == nullptr || soLuongNV == 0)
    {
        cout << "Danh Sach Nhan Vien Rong Hoac Khong Ton Tai" << endl;
        return;
    }

    int index = searchNhanVienFromDSNV(ds_nv, maNV, soLuongNV);

    if (index == -1)
    {
        cout << "Khong tim thay nhan vien voi MaNV: " << maNV << "\n";
        return;
    }

    for (int i = index; i < soLuongNV - 1; i++)
    {
        ds_nv[i] = ds_nv[i + 1];
    }

    soLuongNV--;
    capNhatGiaTriViTri(ds_nv, soLuongNV);
}

void inDanhSachNhanVien(DanhSachNhanVien ds_nv, int soLuongNV)
{
    if (soLuongNV == 0)
    {
        cout << "Danh Sach Nhan Vien Rong Hoac Khong Ton Tai" << endl;
        return;
    }

    cout << "Danh sach nhan vien theo thu tu ten(ho)" << endl;

    for (int i = 0; i < soLuongNV; i++)
    {
        cout << "maNV: " << ds_nv[i]->maNV
             << ", Ho: " << ds_nv[i]->ho
             << ", Ten: " << ds_nv[i]->ten
             << ", Phai: " << (ds_nv[i]->phai == nam ? "Nam" : "Nu")
             << endl;
    }
}

// int main()
// {
//     DanhSachNhanVien ds_nv;
//     int soLuongNV = 0;

//     cout << "Bat dau" << endl;

//     insertNhanVienToDSNV(ds_nv, newNhanVien("NV001", "Nguyen", "An", nam), soLuongNV);
//     insertNhanVienToDSNV(ds_nv, newNhanVien("NV002", "Tran", "Binh", nu), soLuongNV);
//     insertNhanVienToDSNV(ds_nv, newNhanVien("NV003", "Le", "Cuong", nam), soLuongNV);

//     cout << "Danh sach nhan vien ban dau:" << endl;
//     inDanhSachNhanVien(ds_nv, soLuongNV);

//     removeNhanVienByMaNV(ds_nv, "NV002", soLuongNV);
//     cout << "Danh sach nhan vien sau khi xoa NV002:" << endl;
//     inDanhSachNhanVien(ds_nv, soLuongNV);

//     removeNhanVienByMaNV(ds_nv, "NV004", soLuongNV);

//     for (int i = 0; i < soLuongNV; i++)
//     {
//         delete ds_nv[i];
//     }

//     return 0;
// }
