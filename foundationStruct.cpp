#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
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
    int bf;         // Balance factor
    VatTu *left;
    VatTu *right;
} *DanhSachVatTu;

// Khoi tao danh sach vat tu moi
DanhSachVatTu newDanhSachVatTu(char maVT[], char tenVT[], char dVT[], int soLuongTon)
{
    DanhSachVatTu ds_vattu = new VatTu;
    strcpy(ds_vattu->maVT, maVT);
    strcpy(ds_vattu->tenVT, tenVT);
    strcpy(ds_vattu->dVT, dVT);
    ds_vattu->soLuongTon = soLuongTon;
    ds_vattu->bf = 0;
    ds_vattu->left = nullptr;
    ds_vattu->right = nullptr;
    return ds_vattu;
}

int height(DanhSachVatTu root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int updateBalanceFactor(DanhSachVatTu root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return height(root->left) - height(root->right);
};

// 2 ham rotate la phu nen khong can them tham tri
DanhSachVatTu rotateRight(DanhSachVatTu root)
{
    // xoay ve ben phai thi can cho root lien ket vao ben phai root moi
    // sau do cho phan lien ket ben phai ban dau cua root moi  lien ket vao
    DanhSachVatTu newroot = root->left;
    root->left = newroot->right;
    newroot->right = root;
    root->bf = updateBalanceFactor(root);
    newroot->bf = updateBalanceFactor(newroot);

    return newroot;
};

DanhSachVatTu rotateLeft(DanhSachVatTu root)
{
    DanhSachVatTu newroot = root->right;
    root->right = newroot->left;
    newroot->left = root;
    root->bf = updateBalanceFactor(root);
    newroot->bf = updateBalanceFactor(newroot);

    return newroot;
}

DanhSachVatTu balanceTree(DanhSachVatTu root)
{
    root->bf = updateBalanceFactor(root);

    if (root->bf > 1)
    {
        if (root->left->bf < 0)
        {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }
    else if (root->bf < -1)
    {
        if (root->right->bf > 0)
        {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }
    return root;
}

void insertDanhSachVatTu(DanhSachVatTu &root, DanhSachVatTu newVatTu)
{
    if (root == nullptr)
    {
        root = newVatTu;
    }
    else if (strcmp(newVatTu->tenVT, root->tenVT) < 0)
    {
        insertDanhSachVatTu(root->left, newVatTu);
    }
    else if (strcmp(newVatTu->tenVT, root->tenVT) > 0)
    {
        insertDanhSachVatTu(root->right, newVatTu);
    }
    else
    {
        cout << "Ten vat tu " << newVatTu->tenVT << " da ton tai!" << endl;
        return;
    }

    // can bang sau khi chen
    root = balanceTree(root);
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

void removeFromDanhSachVatTu(char tenVT[], DanhSachVatTu &root)
{
    if (root == nullptr)
    {
        cout << "Khong tim thay!!!" << endl;
    }
    else if (strcmp(tenVT, root->tenVT) < 0)
    {
        removeFromDanhSachVatTu(tenVT, root->left);
    }
    else if (strcmp(tenVT, root->tenVT) > 0)
    {
        removeFromDanhSachVatTu(tenVT, root->right);
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
    }

    if (root != nullptr)
    {
        root = balanceTree(root);
    }
}

DanhSachVatTu searchTenVT_DanhSachVatTu(DanhSachVatTu root, char tenVT[])
{
    DanhSachVatTu current = root;
    while (current != nullptr && (strcmp(current->tenVT, tenVT) != 0))
    {
        if (strcmp(current->tenVT, tenVT) < 0)
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

void preorderTenVT_DanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        cout << root->tenVT << " ";
        preorderTenVT_DanhSachVatTu(root->left);
        preorderTenVT_DanhSachVatTu(root->right);
    }
}

void inorderTenVT_DanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        inorderTenVT_DanhSachVatTu(root->left);
        cout << root->tenVT << " ";
        inorderTenVT_DanhSachVatTu(root->right);
    }
}

void postorderTenVT_DanhSachVatTu(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        postorderTenVT_DanhSachVatTu(root->left);
        postorderTenVT_DanhSachVatTu(root->right);
        cout << root->tenVT << " ";
    }
}

void inDanhSachVatTuTheoTenVT(DanhSachVatTu root)
{
    if (root != nullptr)
    {
        inDanhSachVatTuTheoTenVT(root->left);
        cout << "Ma VT: " << root->maVT << ", Ten vat tu: " << root->tenVT << ", Don vi tinh: " << root->dVT << ", So luong ton: " << root->soLuongTon << endl;
        inDanhSachVatTuTheoTenVT(root->right);
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
// Kiểm tra danh sách chi tiết hóa đơn có rỗng không
bool Empty_CTHD(DanhSach_CT_HoaDon ds_cthoadon)
{
    if (ds_cthoadon == nullptr)
    {
        cout << "Danh sach chi tiet hoa don rong!\n";
        return true;
    }
    return false;
}

//--------Kiểm tra mã vật tư có trùng hay không trong danh sách chi tiết hóa đơn--------- Cần tìm cách sài cho nhiều cái
bool KiemTraMaVT_CTHD(DanhSach_CT_HoaDon ds_cthoadon, const char maVT[11])
{
	if (Empty_CTHD(ds_cthoadon)) return false;
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
//----------Xóa chi tiết hóa đơn theo mã vật tư---------------
bool Xoa_CTHD(DanhSach_CT_HoaDon &ds_cthoadon, const char maVT[11])
{
    if (ds_cthoadon == nullptr)
    {
        cout << "Danh sach chi tiet hoa don rong, khong the xoa!" << endl;
        return false;
    }
    // Nếu node đầu tiên có mã vật tư cần xóa
    if (strcmp(ds_cthoadon->maVT, maVT) == 0)
    {
        DanhSach_CT_HoaDon temp = ds_cthoadon;
        ds_cthoadon = ds_cthoadon->next; // Cập nhật lại đầu danh sách
        delete temp; // Giải phóng bộ nhớ
        cout << "Da xoa chi tiet hoa don co ma vat tu: " << maVT << endl;
        return true;
    }
    // Tìm node có mã vật tư cần xóa
    DanhSach_CT_HoaDon prev = ds_cthoadon;
    DanhSach_CT_HoaDon curr = ds_cthoadon->next;

    while (curr != nullptr)
    {
        if (strcmp(curr->maVT, maVT) == 0)
        {
            prev->next = curr->next; // Bỏ qua node cần xóa
            delete curr; // Giải phóng bộ nhớ
            cout << "Da xoa chi tiet hoa don co ma vat tu: " << maVT << endl;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Khong tim thay chi tiet hoa don co ma vat tu: " << maVT << endl;
    return false; // Không tìm thấy mã vật tư cần xóa
}
//-------------Hàm in danh sách chi tiết hóa đơn---------------
void InChiTietCTHoaDon(CT_HoaDon* ct)
{
    cout << "Ma VT: " << ct->maVT
         << ", So luong: " << ct->soLuong
         << ", Don gia: " << ct->donGia
         << ", VAT: " << ct->vAT << "%" << endl;
}

// Hàm in danh sách chi tiết hóa đơn
void InDanhSachCTHoaDon(DanhSach_CT_HoaDon ds_cthoadon)
{
    if (ds_cthoadon == nullptr)
    {
        cout << "Danh sach chi tiet hoa don rong!" << endl;
        return;
    }

    cout << "Danh sach chi tiet hoa don:" << endl;
    while (ds_cthoadon != nullptr)
    {
        InChiTietCTHoaDon(ds_cthoadon);  // Gọi hàm in chi tiết
        ds_cthoadon = ds_cthoadon->next;
    }
}


//----------Merge Sort------Của Chi tiết hóa đơn-----------------------------------------------
/*Dễ triển khai với danh sách liên kết: Không cần phải truy cập trực tiếp vào các chỉ số (index) như trong mảng. Ta chỉ cần so sánh và hoán đổi con trỏ trong danh sách.
Đơn giản và dễ hiểu: */

// Hàm tìm vị trí giữa của danh sách liên kết
CT_HoaDon* TimViTriGiua(CT_HoaDon* head) {
	
    if (head == nullptr || head->next == nullptr)
        return head;
        
    CT_HoaDon* slow = head;//Con trỏ slow đi từng bước một
    CT_HoaDon* fast = head->next;//Con trỏ fast đi hai bước. Khi fast đến cuối danh sách, slow sẽ nằm ở giữa.

    // Di chuyển fast nhanh hơn slow
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
//------------Merge Sort theo mã vật tư-------------------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo tiêu chí mã vật tư
CT_HoaDon* HopNhatTheoMaVT(CT_HoaDon* trai, CT_HoaDon* phai) {
    // Trường hợp cơ bản
    if (trai == nullptr) return phai;
    if (phai == nullptr) return trai;

    // So sánh mã vật tư và gộp lại
    if (strcmp(trai->maVT, phai->maVT) <= 0) {
        trai->next = HopNhatTheoMaVT(trai->next, phai);
        return trai;
    } else {
        phai->next = HopNhatTheoMaVT(trai, phai->next);
        return phai;
    }
}

CT_HoaDon* MergeSortTheoMaVT(CT_HoaDon* head) {
    // Trường hợp cơ bản: danh sách rỗng hoặc có 1 phần tử
    if (head == nullptr || head->next == nullptr)
        return head;

    // Tìm vị trí giữa của danh sách
    CT_HoaDon* giua = TimViTriGiua(head);
    CT_HoaDon* nuaSau = giua->next;
    giua->next = nullptr; // Chia danh sách

    // Đệ quy gọi MergeSort trên hai nửa
    CT_HoaDon* trai = MergeSortTheoMaVT(head);
    CT_HoaDon* phai = MergeSortTheoMaVT(nuaSau);

    // Gộp hai nửa đã sắp xếp lại với nhau
    return HopNhatTheoMaVT(trai, phai);
}
//------------Merge Sort theo số lượng----------------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo số lượng
CT_HoaDon* HopNhatTheoSoLuong(CT_HoaDon* trai, CT_HoaDon* phai) {
    if (trai == nullptr) return phai;
    if (phai == nullptr) return trai;

    if (trai->soLuong <= phai->soLuong) {
        trai->next = HopNhatTheoSoLuong(trai->next, phai);
        return trai;
    } else {
        phai->next = HopNhatTheoSoLuong(trai, phai->next);
        return phai;
    }
}

CT_HoaDon* MergeSortTheoSoLuong(CT_HoaDon* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon* giua = TimViTriGiua(head);
    CT_HoaDon* nuaSau = giua->next;
    giua->next = nullptr;

    CT_HoaDon* trai = MergeSortTheoSoLuong(head);
    CT_HoaDon* phai = MergeSortTheoSoLuong(nuaSau);

    return HopNhatTheoSoLuong(trai, phai);
}
//----------Merge Sort theo đơn giá-----------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo đơn giá
CT_HoaDon* HopNhatTheoDonGia(CT_HoaDon* trai, CT_HoaDon* phai) {
    if (trai == nullptr) return phai;
    if (phai == nullptr) return trai;

    if (trai->donGia <= phai->donGia) {
        trai->next = HopNhatTheoDonGia(trai->next, phai);
        return trai;
    } else {
        phai->next = HopNhatTheoDonGia(trai, phai->next);
        return phai;
    }
}

CT_HoaDon* MergeSortTheoDonGia(CT_HoaDon* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon* giua = TimViTriGiua(head);
    CT_HoaDon* nuaSau = giua->next;
    giua->next = nullptr;

    CT_HoaDon* trai = MergeSortTheoDonGia(head);
    CT_HoaDon* phai = MergeSortTheoDonGia(nuaSau);

    return HopNhatTheoDonGia(trai, phai);
}

//------------Merge Sort theo VAT--------------------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo VAT
CT_HoaDon* HopNhatTheoVAT(CT_HoaDon* trai, CT_HoaDon* phai) {
    if (trai == nullptr) return phai;
    if (phai == nullptr) return trai;

    if (trai->vAT <= phai->vAT) {
        trai->next = HopNhatTheoVAT(trai->next, phai);
        return trai;
    } else {
        phai->next = HopNhatTheoVAT(trai, phai->next);
        return phai;
    }
}

CT_HoaDon* MergeSortTheoVAT(CT_HoaDon* head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon* giua = TimViTriGiua(head);
    CT_HoaDon* nuaSau = giua->next;
    giua->next = nullptr;

    CT_HoaDon* trai = MergeSortTheoVAT(head);
    CT_HoaDon* phai = MergeSortTheoVAT(nuaSau);

    return HopNhatTheoVAT(trai, phai);
}
//------------Hàm tổng quát sắp xếp theo tiêu chí được chọn----------
DanhSach_CT_HoaDon SapXepDanhSachCTHoaDon(DanhSach_CT_HoaDon ds_cthoadon, int tieuChi)
{
    switch (tieuChi)
    {
        case 1:
            return MergeSortTheoMaVT(ds_cthoadon);
        case 2:
            return MergeSortTheoSoLuong(ds_cthoadon);
        case 3:
            return MergeSortTheoDonGia(ds_cthoadon);
        case 4:
            return MergeSortTheoVAT(ds_cthoadon);
        default:
            cout << "Tieu chi sap xep khong hop le!" << endl;
            return ds_cthoadon;
            //Ví dụ cách sài: ds_cthoadon = SapXepDanhSachCTHoaDon(ds_cthoadon, tieuchi);
    }
}

// Hàm đảo ngược danh sách CT_HoaDon
DanhSach_CT_HoaDon DaoNguocDanhSach(DanhSach_CT_HoaDon head)
{
    DanhSach_CT_HoaDon prev = nullptr;
    DanhSach_CT_HoaDon current = head;
    DanhSach_CT_HoaDon next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev; // Trả về đầu danh sách đã bị đảo ngược
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
    insertDanhSachVatTu(root, newDanhSachVatTu("05", "05", "Cai", 25));
    insertDanhSachVatTu(root, newDanhSachVatTu("04", "04", "Cai", 20));
    insertDanhSachVatTu(root, newDanhSachVatTu("01", "01", "Cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("02", "02", "Cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("10", "10", "Cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("03", "03", "Chiec", 15));
    insertDanhSachVatTu(root, newDanhSachVatTu("06", "06", "Bo", 5));
    insertDanhSachVatTu(root, newDanhSachVatTu("07", "07", "Hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("07", "07", "Hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("08", "08", "Bo", 12));
    insertDanhSachVatTu(root, newDanhSachVatTu("14", "14", "Cai", 18));

    cout << "Danh sach vat tu truoc khi xoa preorder:" << endl;
    preorderTenVT_DanhSachVatTu(root);
    cout << "\nDanh sach vat tu trc khi xoa theo postorder:" << endl;
    postorderTenVT_DanhSachVatTu(root);

    // Xoa nut goc (VT005) co ca trai va phai
    removeFromDanhSachVatTu("05", root);

    cout << "\nDanh sach vat tu sau khi xoa theo preorder:" << endl;
    preorderTenVT_DanhSachVatTu(root);
    cout << "\nDanh sach vat tu sau khi xoa theo inorder:" << endl;
    inorderTenVT_DanhSachVatTu(root);
    cout << "\nDanh sach vat tu sau khi xoa theo ten vt:" << endl;
    inDanhSachVatTuTheoTenVT(root);

    cout << endl;
    cout << root->tenVT << endl;

    return 0;
}
