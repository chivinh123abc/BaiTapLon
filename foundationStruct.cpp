#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
#include "mylib.h"

using namespace std;

const int MAX_NHANVIEN = 500;
const int MENU_ITEMS = 4;

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

char menuName[MENU_ITEMS][51]{
    "1. Them vat tu",
    "2. Xoa vat tu",
    "3. Hieu chinh vat tu",
    "0. Exit"
    //
};

// them/xoa/hieu chinh thong tin vat tu,
// rieng so luong ton chi cho phep nhap khi do la vat tu moi them
void updateMenu(DanhSachVatTu &root)
{
    int choose = -1;
    cout << "---------------------------------------------------" << endl;

    // Hiển thị menu
    for (int i = 0; i < MENU_ITEMS; i++)
    {
        cout << menuName[i] << endl;
    }
    cout << "What you want to do : ";

    bool running = true;

    while (running)
    {
        choose = getch();

        switch (choose)
        {
        case '1':
        {
            cout << endl;
            cout << "Them thong tin vat tu: " << endl;

            char inputMaVT[11];
            int count = 0;
            bool done = false;

            cout << "Nhap ma vat tu (toi da 10 ky tu): ";
            while (!done)
            {
                char ch = getch();

                if (ch == 13 && count > 0)
                {
                    done = true;
                }
                else if (ch == '\b' && count > 0)
                {
                    cout << "\b \b";
                    count--;
                    inputMaVT[count] = '\0';
                }
                else if (isalnum(ch) && count < 10)
                {
                    cout << ch;
                    inputMaVT[count++] = ch;
                }
            }
            inputMaVT[count] = '\0';
            cout << "\nMa vat tu nhap: " << inputMaVT << endl;
            break;
        }
        case '2':
            cout << "Xoa vat tu" << endl;
            break;
        case '3':
            cout << "Hieu chinh vat tu" << endl;
            // Thêm logic hiệu chỉnh vật tư
            break;
        case '0':
            cout << "Thoat chuong trinh" << endl;
            running = false;
            break;
        case 13:
            cout << "Thoat chuong trinh" << endl;
            running = false;
            break;
        default:
            cout << "\nInvalid choice. Please try again." << endl;
            break;
        }

        // Hiển thị lại menu nếu không thoát
        if (running)
        {
            cout << "What you want to do : ";
        }
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

    updateMenu(root);

    return 0;
}