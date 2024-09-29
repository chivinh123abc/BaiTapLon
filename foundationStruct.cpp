#include <iostream>
#include <cstring>
#include <cmath>
#include <string.h>

using namespace std;

//-------PART 1----------------------------------------------------------------
//-------Cau hoi Thi----------------------------------------------------------------
typedef struct CauHoiThi
{
    int id;
    char noiDung[101];
    char A[51];
    char B[51];
    char C[51];
    char D[51];
    char dapAn;
    CauHoiThi *next;
} *DanhSachCauHoiThi;

DanhSachCauHoiThi khoiTaoCauHoiThiMoi(int id, char noiDung[], char A[], char B[], char C[], char D[], char dapAn)
{
    DanhSachCauHoiThi ds_cauhoithi = new CauHoiThi;
    ds_cauhoithi->id = id;
    strcpy(ds_cauhoithi->noiDung, noiDung);
    strcpy(ds_cauhoithi->A, A);
    strcpy(ds_cauhoithi->B, B);
    strcpy(ds_cauhoithi->C, C);
    strcpy(ds_cauhoithi->D, D);
    ds_cauhoithi->dapAn = dapAn;
    ds_cauhoithi->next = nullptr;
    return ds_cauhoithi;
}

//-----Mon Hoc------------------------------------------------------------------
typedef struct MonHoc
{
    char maMH[16];
    char tenMH[51];
    DanhSachCauHoiThi ds_cauhoithi;
    MonHoc *left;
    MonHoc *right;
} *DanhSachMonHoc;

void themMonHoc(DanhSachMonHoc &ds_monhoc)
{
}

//-----PART 2------------------------------------------------------------------
//-----DiemThi------------------------------------------------------------------
typedef struct DiemThi
{
    char maMH[16];
    float diem;
    DiemThi *next;
} DanhSachDiemThi;

//------Sinh vien-----------------------------------------------------------------
typedef struct SinhVien
{
    char maSV[16];
    char ho[20];
    char ten[30];
    char phai[20];
    char password[20];
    DanhSachDiemThi ds_diemthi;
    SinhVien *next;
} *DanhSachSinhVien;

//----Lop-------------------------------------------------------------------
typedef struct Lop
{
    char maLop[16];
    char tenLop[20];
    DanhSachSinhVien ds_sinhvien;
};