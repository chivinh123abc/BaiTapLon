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
            rp->left = t->left;
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

DanhSachVatTu searchMaVT_DanhSachVatTu(DanhSachVatTu root, char maVT[])
{
    DanhSachVatTu current = root;
    while (current != nullptr && (strcmp(current->maVT, maVT) != 0))
    {
        if (strcmp(current->maVT, maVT) < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

void preorderMaVT_DanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        cout << root->maVT << " ";
        preorderMaVT_DanhSachVatTu(root->left);
        preorderMaVT_DanhSachVatTu(root->right);
    }
}

void inorderMaVT_DanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        inorderMaVT_DanhSachVatTu(root->left);
        cout << root->maVT << " ";
        inorderMaVT_DanhSachVatTu(root->right);
    }
}

void postorderMaVT_DanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        postorderMaVT_DanhSachVatTu(root->left);
        postorderMaVT_DanhSachVatTu(root->right);
        cout << root->maVT << " ";
    }
}

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
//--------Kiểm tra mã vật tư có trùng hay không trong danh sách chi tiết hóa đơn--------- Cần tìm cách sài cho nhiều cái
bool KiemTraMaVT_CTHD(DanhSach_CT_HoaDon ds_cthoadon, const char maVT[11])
{
    while (ds_cthoadon != nullptr)
    {
        if (strcmp(ds_cthoadon->maVT, maVT) == 0)
        {
            cout << "Ma vat tu da ton tai trong chi tiet hoa don!" << endl;
            return true; // Mã vật tư đã tồn tại
        }
        ds_cthoadon = ds_cthoadon->next;
    }
    return false; // Mã vật tư không trùng
}
//--------Thêm chi tiết hóa đơn vào danh sách (không trùng mã vật tư)----------
bool Them_CTHD(DanhSach_CT_HoaDon &ds_cthoadon, char maVT[11], int soLuong, float donGia, float vAT)
{
    if (KiemTraMaVT_CTHD(ds_cthoadon, maVT) == true)
    {
        return false; // Không thêm được vì mã vật tư bị trùng
    }

    DanhSach_CT_HoaDon CT_HoaDonMoi = newDanhSachCTHoaDon(maVT, soLuong, donGia, vAT);

    // Thêm chi tiết mới vào đầu danh sách liên kết
    CT_HoaDonMoi->next = ds_cthoadon;
    ds_cthoadon = CT_HoaDonMoi;
    return true; // Thêm thành công
}

//----------Bubble Sort------Của Chi tiết hóa đơn-----------------------------------------------
/*Dễ triển khai với danh sách liên kết: Không cần phải truy cập trực tiếp vào các chỉ số (index) như trong mảng. Ta chỉ cần so sánh và hoán đổi con trỏ trong danh sách.
Đơn giản và dễ hiểu: Dù hiệu quả không cao cho các danh sách lớn, nhưng vì chi tiết hóa đơn thường không nhiều, Bubble Sort vẫn có thể chấp nhận được.*/
// --------- Hàm hoán đổi 2 chi tiết hóa đơn ---------
void HoanDoiChiTietHoaDon(CT_HoaDon *a, CT_HoaDon *b)
{ /*Tại sao lại hoán đổi từng thành phần? Mà không  hóan đổi 2 nodes
trực tiếp vì dslk đơn không quản lí bằng trị số được nên việc hoán đổi rất khó xác định và cho dù có muốn
thì duyệt tới thì cái phần địa chỉ next nó như đuôi rắn cắt ra là nó lấy luôn mấy thằng phía sau đổi tới lui rất phức tạp*/
    swap(a->maVT, b->maVT);
    swap(a->soLuong, b->soLuong);
    swap(a->donGia, b->donGia);
    swap(a->vAT, b->vAT);
}
//------------KT CT_HoaDon co rong khong--------
bool Empty_CTHD(DanhSach_CT_HoaDon ds_cthoadon)
{
    if (ds_cthoadon == nullptr)
        cout << "Danh sach hoa don rong!\n";
    return true;
}
// --------- Sắp xếp nổi bọt theo mã vật tư ---------
void SapXep_CTHD_TheoMaVT(DanhSach_CT_HoaDon &ds_cthoadon)
{
    bool swapped;
    CT_HoaDon *ptr1;           // Tmp ptr
    CT_HoaDon *lptr = nullptr; // last ptr

    // Kiểm tra nếu danh sách rỗng
    if (Empty_CTHD(ds_cthoadon) == true)
        return;
    do
    {
        swapped = false;
        ptr1 = ds_cthoadon;

        while (ptr1->next != lptr)
        {
            // So sánh theo mã vật tư
            if (strcmp(ptr1->maVT, ptr1->next->maVT) > 0)
            {
                HoanDoiChiTietHoaDon(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // Giới hạn lại đoạn đã được sắp xếp
    } while (swapped);
}

// --------- Sắp xếp nổi bọt theo số lượng ---------
void SapXep_CTHD_TheoSoLuong(DanhSach_CT_HoaDon &ds_cthoadon)
{
    bool swapped;
    CT_HoaDon *ptr1;
    CT_HoaDon *lptr = nullptr;

    if (Empty_CTHD(ds_cthoadon) == true)
        return;

    do
    {
        swapped = false;
        ptr1 = ds_cthoadon;

        while (ptr1->next != lptr)
        {
            // So sánh theo số lượng
            if (ptr1->soLuong > ptr1->next->soLuong)
            {
                HoanDoiChiTietHoaDon(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// --------- Sắp xếp nổi bọt theo đơn giá ---------
void SapXep_CTHD_TheoDonGia(DanhSach_CT_HoaDon &ds_cthoadon)
{
    bool swapped;
    CT_HoaDon *ptr1;
    CT_HoaDon *lptr = nullptr;

    if (Empty_CTHD(ds_cthoadon) == true)
        return;

    do
    {
        swapped = false;
        ptr1 = ds_cthoadon;

        while (ptr1->next != lptr)
        {
            // So sánh theo đơn giá
            if (ptr1->donGia > ptr1->next->donGia)
            {
                HoanDoiChiTietHoaDon(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// --------- Sắp xếp nổi bọt theo VAT ---------
void SapXep_CTHD_TheoVAT(DanhSach_CT_HoaDon &ds_cthoadon)
{
    bool swapped;
    CT_HoaDon *ptr1;
    CT_HoaDon *lptr = nullptr;

    if (Empty_CTHD(ds_cthoadon) == true)
        return;

    do
    {
        swapped = false;
        ptr1 = ds_cthoadon;

        while (ptr1->next != lptr)
        {
            // So sánh theo VAT
            if (ptr1->vAT > ptr1->next->vAT)
            {
                HoanDoiChiTietHoaDon(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
//**************************************************************************************

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
    preorderMaVT_DanhSachVatTu(root);

    // Xoa nut goc (VT005) co ca trai va phai
    removeFromDanhSachVatTu("VT005", root);

    cout << "\nDanh sach vat tu sau khi xoa theo preorder:" << endl;
    preorderMaVT_DanhSachVatTu(root);
    cout << "\nDanh sach vat tu sau khi xoa theo inorder:" << endl;
    inorderMaVT_DanhSachVatTu(root);
    cout << "\nDanh sach vat tu sau khi xoa theo postorder:" << endl;
    postorderMaVT_DanhSachVatTu(root);

    return 0;
}