#include <iostream>
#include <cstring>
#include <cmath>
#include "mylib.h"

using namespace std;

const int MAX_NHANVIEN = 500;

//-------PART 1----------------------------------------------------------------
//------Danh Sach Vat Tu------------------------------------------------------------
typedef struct VatTu
{
    char maVT[11];  // Mã vật tư
    char tenVT[51]; // Tên vật tư
    char dVT[21];   // Đơn vị tính
    int soLuongTon; // Số lượng tồn
    VatTu *left;    // Con trỏ trái cho cây nhị phân
    VatTu *right;   // Con trỏ phải cho cây nhị phân
} *DanhSachVatTu;

// Khoi tao danh sach vat tu moi
DanhSachVatTu newDanhSachVatTu(char maVT[], char tenVT[], char dVT[], int soLuongTon)
{
    DanhSachVatTu ds_vattu = new VatTu;
    strcpy(ds_vattu->maVT, maVT);
    strcpy(ds_vattu->tenVT, tenVT);
    strcpy(ds_vattu->dVT, dVT);
    ds_vattu->soLuongTon = soLuongTon;
    ds_vattu->left = nullptr;
    ds_vattu->right = nullptr;
    return ds_vattu;
}

void insertDanhSachVatTu(DanhSachVatTu &root, DanhSachVatTu newVatTu)
{
    if (root == nullptr)
    {
        root = newVatTu;
    }
    else if (strcmp(newVatTu->maVT, root->maVT) < 0)
    {
        insertDanhSachVatTu(root->left, newVatTu);
    }
    else if (strcmp(newVatTu->maVT, root->maVT) > 0)
    {
        insertDanhSachVatTu(root->right, newVatTu);
    }
    else
    {
        cout << "Ma vat tu " << newVatTu->maVT << " da ton tai!" << endl;
    }
}

// Bo sung cho viec tim so nhat cua ham ben phai
void removeCase3(DanhSachVatTu &root, DanhSachVatTu &rp)
{
    if (rp->left != nullptr)
    {
        removeCase3(root, rp->left);
    }
    else
    {
        strcpy(root->maVT, rp->maVT);
        strcpy(root->tenVT, rp->tenVT);
        strcpy(root->dVT, rp->dVT);
        root->soLuongTon = rp->soLuongTon;

        if (rp->right == nullptr)
        {
            delete rp;
        }
        else
        {
            DanhSachVatTu t = rp->right;
            strcpy(rp->maVT, t->maVT);
            strcpy(rp->tenVT, t->tenVT);
            strcpy(rp->dVT, t->dVT);
            rp->soLuongTon = t->soLuongTon;
            rp->right = t->right;
            delete t;
        }
    }
}

void removeFromDanhSachVatTu(char maVT[], DanhSachVatTu &root)
{
    if (root == nullptr)
    {
        cout << "Khong tim thay!!!" << endl;
    }
    else if (strcmp(maVT, root->maVT) < 0)
    {
        removeFromDanhSachVatTu(maVT, root->left);
    }
    else if (strcmp(maVT, root->maVT) > 0)
    {
        removeFromDanhSachVatTu(maVT, root->right);
    }
    else
    {
        DanhSachVatTu rp = root;
        if (rp->right == nullptr)
        {
            root = rp->left;
        }
        else if (rp->left == nullptr)
        {
            root = rp->right;
        }
        else
        {
            removeCase3(root, rp->right);
        }
        // delete rp;
    }
}

void printDanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        printDanhSachVatTu(root->left);
        cout << "Ma Vat Tu: " << root->maVT << ", Ten Vat Tu: " << root->tenVT << ", DVT: " << root->dVT << ", SL ton: " << root->soLuongTon << endl;
        printDanhSachVatTu(root->right);
    }
}

//--------PART 2-------------------------------------------------
//---------Danh Sach Chi Tiet Hoa Don------------------------------------------------
typedef struct CT_HoaDon
{
    char maVT[11];   // Mã vật tư
    int soLuong;     // Số lượng
    float donGia;    // Đơn giá
    float vAT;       // % VAT
    CT_HoaDon *next; // Con trỏ đến chi tiết hóa đơn tiếp theo
} *DanhSach_CT_HoaDon;

// Khoi tao danh sach Chi Tiet Hoa Don moi;

DanhSach_CT_HoaDon newDanhSachCTHoaDon(char maVT[11], int soLuong, float donGia, float vAT)
{
    DanhSach_CT_HoaDon ds_cthoadon = new CT_HoaDon;
    strcpy(ds_cthoadon->maVT, maVT);
    ds_cthoadon->soLuong = soLuong;
    ds_cthoadon->donGia = donGia;
    ds_cthoadon->vAT = vAT;
    ds_cthoadon->next = nullptr;
    return ds_cthoadon;
}

//--------Danh Sach Hoa Don-------------------------------------------------
typedef struct HoaDon
{
    char soHD[21];                   // Số hóa đơn
    char ngayLapHoaDon[21];          // Ngày lập hóa đơn
    char loai;                       // Loại hóa đơn: 'N' (phiếu nhập) hoặc 'X' (phiếu xuất)
    DanhSach_CT_HoaDon ds_ct_hoadon; // Danh sách chi tiết hóa đơn
    HoaDon *next;                    // Con trỏ đến hóa đơn tiếp theo
} *DanhSachHoaDon;

// khoi tao danh sach Hoa Don moi

DanhSachHoaDon newDanhSachHoaDon(char soHD[], char ngayLapHoaDon[21], char loai, DanhSach_CT_HoaDon ds_ct_hoadon)
{
    DanhSachHoaDon ds_hoadon = new HoaDon;
    strcpy(ds_hoadon->soHD, soHD);
    strcpy(ds_hoadon->ngayLapHoaDon, ngayLapHoaDon);
    ds_hoadon->loai = loai;
    ds_hoadon->ds_ct_hoadon = ds_ct_hoadon;
    ds_hoadon->next = nullptr;
    return ds_hoadon;
}

//------Danh Sach Nhan Vien----------------------------------------------------
typedef struct NhanVien
{
    char maNV[21];            // Mã nhân viên
    char ho[11];              // Họ
    char ten[21];             // Tên
    char phai[5];             // Phái (Nam/Nữ)
    DanhSachHoaDon ds_hoadon; // Danh sách hóa đơn
} *DanhSachNhanVien;          // Danh sách nhân viên tối đa 500 người

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

int main()
{
    DanhSachVatTu root = nullptr;

    // Them mot so vat tu vao danh sach
    insertDanhSachVatTu(root, newDanhSachVatTu("VT005", "Vat Tu 5", "Cai", 25));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT002", "Vat Tu 2", "Cai", 20));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT001", "Vat Tu 1", "Cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT003", "Vat Tu 3", "Chiec", 15));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT006", "Vat Tu 6", "Bo", 5));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT007", "Vat Tu 7", "Hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT008", "Vat Tu 8", "Bo", 12));
    insertDanhSachVatTu(root, newDanhSachVatTu("VT004", "Vat Tu 4", "Cai", 18));

    cout << "Danh sach vat tu truoc khi xoa:" << endl;
    printDanhSachVatTu(root);

    // Xoa nut goc (VT005) co ca trai va phai
    removeFromDanhSachVatTu("VT005", root);

    cout << "\nDanh sach vat tu sau khi xoa:" << endl;
    printDanhSachVatTu(root);

    return 0;
}