#include "foundationStruct.cpp"
#pragma once
#include "vattu.cpp"

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
    if (Empty_CTHD(ds_cthoadon))
        return false;
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
        return false;
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
        delete temp;                     // Giải phóng bộ nhớ
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
            delete curr;             // Giải phóng bộ nhớ
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
void InChiTietCTHoaDon(CT_HoaDon *ct)
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
        InChiTietCTHoaDon(ds_cthoadon);
        ds_cthoadon = ds_cthoadon->next;
    }
}

//----------Merge Sort------Của Chi tiết hóa đơn-----------------------------------------------
/*Dễ triển khai với danh sách liên kết: Không cần phải truy cập trực tiếp vào các chỉ số (index) như trong mảng. Ta chỉ cần so sánh và hoán đổi con trỏ trong danh sách.
Đơn giản và dễ hiểu: */

// Hàm tìm vị trí giữa của danh sách liên kết
CT_HoaDon *TimViTriGiua(CT_HoaDon *head)
{

    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon *slow = head;       // Con trỏ slow đi từng bước một
    CT_HoaDon *fast = head->next; // Con trỏ fast đi hai bước. Khi fast đến cuối danh sách, slow sẽ nằm ở giữa.

    // Di chuyển fast nhanh hơn slow
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
//------------Merge Sort theo mã vật tư-------------------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo tiêu chí mã vật tư
CT_HoaDon *HopNhatTheoMaVT(CT_HoaDon *trai, CT_HoaDon *phai)
{
    // Trường hợp cơ bản
    if (trai == nullptr)
        return phai;
    if (phai == nullptr)
        return trai;

    // So sánh mã vật tư và gộp lại
    if (strcmp(trai->maVT, phai->maVT) <= 0)
    {
        trai->next = HopNhatTheoMaVT(trai->next, phai);
        return trai;
    }
    else
    {
        phai->next = HopNhatTheoMaVT(trai, phai->next);
        return phai;
    }
}

CT_HoaDon *MergeSortTheoMaVT(CT_HoaDon *head)
{
    // Trường hợp cơ bản: danh sách rỗng hoặc có 1 phần tử
    if (head == nullptr || head->next == nullptr)
        return head;

    // Tìm vị trí giữa của danh sách
    CT_HoaDon *giua = TimViTriGiua(head);
    CT_HoaDon *nuaSau = giua->next;
    giua->next = nullptr; // Chia danh sách

    // Đệ quy gọi MergeSort trên hai nửa
    CT_HoaDon *trai = MergeSortTheoMaVT(head);
    CT_HoaDon *phai = MergeSortTheoMaVT(nuaSau);

    // Gộp hai nửa đã sắp xếp lại với nhau
    return HopNhatTheoMaVT(trai, phai);
}
//------------Merge Sort theo số lượng----------------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo số lượng
CT_HoaDon *HopNhatTheoSoLuong(CT_HoaDon *trai, CT_HoaDon *phai)
{
    if (trai == nullptr)
        return phai;
    if (phai == nullptr)
        return trai;

    if (trai->soLuong <= phai->soLuong)
    {
        trai->next = HopNhatTheoSoLuong(trai->next, phai);
        return trai;
    }
    else
    {
        phai->next = HopNhatTheoSoLuong(trai, phai->next);
        return phai;
    }
}

CT_HoaDon *MergeSortTheoSoLuong(CT_HoaDon *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon *giua = TimViTriGiua(head);
    CT_HoaDon *nuaSau = giua->next;
    giua->next = nullptr;

    CT_HoaDon *trai = MergeSortTheoSoLuong(head);
    CT_HoaDon *phai = MergeSortTheoSoLuong(nuaSau);

    return HopNhatTheoSoLuong(trai, phai);
}
//----------Merge Sort theo đơn giá-----------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo đơn giá
CT_HoaDon *HopNhatTheoDonGia(CT_HoaDon *trai, CT_HoaDon *phai)
{
    if (trai == nullptr)
        return phai;
    if (phai == nullptr)
        return trai;

    if (trai->donGia <= phai->donGia)
    {
        trai->next = HopNhatTheoDonGia(trai->next, phai);
        return trai;
    }
    else
    {
        phai->next = HopNhatTheoDonGia(trai, phai->next);
        return phai;
    }
}

CT_HoaDon *MergeSortTheoDonGia(CT_HoaDon *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon *giua = TimViTriGiua(head);
    CT_HoaDon *nuaSau = giua->next;
    giua->next = nullptr;

    CT_HoaDon *trai = MergeSortTheoDonGia(head);
    CT_HoaDon *phai = MergeSortTheoDonGia(nuaSau);

    return HopNhatTheoDonGia(trai, phai);
}

//------------Merge Sort theo VAT--------------------
// Hàm hợp nhất (merge) hai danh sách đã sắp xếp theo VAT
CT_HoaDon *HopNhatTheoVAT(CT_HoaDon *trai, CT_HoaDon *phai)
{
    if (trai == nullptr)
        return phai;
    if (phai == nullptr)
        return trai;

    if (trai->vAT <= phai->vAT)
    {
        trai->next = HopNhatTheoVAT(trai->next, phai);
        return trai;
    }
    else
    {
        phai->next = HopNhatTheoVAT(trai, phai->next);
        return phai;
    }
}

CT_HoaDon *MergeSortTheoVAT(CT_HoaDon *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    CT_HoaDon *giua = TimViTriGiua(head);
    CT_HoaDon *nuaSau = giua->next;
    giua->next = nullptr;

    CT_HoaDon *trai = MergeSortTheoVAT(head);
    CT_HoaDon *phai = MergeSortTheoVAT(nuaSau);

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

//-------------******************************************************************************************************************-------------------------------------------------------------------------------------------------------------------
// khoi tao danh sach Hoa Don moi

DanhSachHoaDon newHoaDon(char soHD[], Date date, LoaiHoaDon loai, DanhSach_CT_HoaDon ds_ct_hoadon)
{
    DanhSachHoaDon ds_hoadon = new HoaDon;
    strcpy(ds_hoadon->soHD, soHD);
    ds_hoadon->date = date;
    ds_hoadon->loai = loai;
    ds_hoadon->ds_ct_hoadon = ds_ct_hoadon;
    ds_hoadon->next = nullptr;
    return ds_hoadon;
}

void dinhDangSoHoaDon(char rel[21], int &soThuTuSoHD)
{
    sprintf(rel, "hd-%07d", soThuTuSoHD);
}

DanhSachHoaDon InsertHoaDonVaoDSHD(DanhSachHoaDon &First, HoaDon *hd)
{
    if (First == nullptr)
    {
        First = hd;
    }
    else
    {
        if (hd->soHD < First->soHD)
        {
            hd->next = First;
            First = hd;
        }
        else
        {
            HoaDon *current = First;
            HoaDon *prev = nullptr;
            while (current != nullptr && current->soHD < hd->soHD)
            {
                prev = current;
                current = current->next;
            }
            //
            prev->next = hd;
            hd->next = current;
        }
    }
    return First;
}

DanhSachHoaDon RemoveHoaDonTheoSoHD(DanhSachHoaDon &First, char soHD[])
{
    HoaDon *current = First;
    HoaDon *prev = nullptr;

    while (current != nullptr && (strcmp(current->soHD, soHD) != 0))
    {
        prev = current;
        current = current->next;
    }
    if (current == nullptr)
    {
        cout << "SoHD khong ton tai trong DanhSach";
    }
    else
    {
        if (current == First)
        {
            First = First->next;
        }
        else
        {
            prev->next = current->next;
        }

        delete current;
    }
    return First;
}

DanhSachHoaDon LapHoaDon(DanhSachHoaDon &First, char soHD[], Date date, LoaiHoaDon loai, DanhSach_CT_HoaDon ds_ct_hoadon)
{
    if (loai == n || loai == x)
    {
        InsertHoaDonVaoDSHD(First, newHoaDon(soHD, date, loai, ds_ct_hoadon));
    }
    else
    {
        cout << "Loai hoa don khong hop le!" << endl;
    }
    return First;
}

// luu y sau khi confirm hoa don chan chac dc nhap
// thi phai dung lenh nay de cap nhat vat tu
// QUAN TRONG!!!QUAN TRONG!!!QUANTRONG
// QUAN TRONG!!!QUAN TRONG!!!QUANTRONG
// QUAN TRONG!!!QUAN TRONG!!!QUANTRONG
void CapNhatVatTuKhiNhapXuatHoaDon(DanhSachVatTu &root, DanhSachHoaDon &hd)
{
    if (hd == nullptr)
    {
        return;
    }
    if (hd->loai == n)
    {
        DanhSach_CT_HoaDon current = hd->ds_ct_hoadon;
        while (current != nullptr)
        {
            if (!isContainMaVT_DanhSachVatTu(root, current->maVT))
            {
                DanhSachVatTu new_vattu = new VatTu;
                cout << "Day la vat tu moi duoc them vao!!" << endl;
                cout << "Vui long cung cap them thong tin cua vat tu nay" << endl;

                char inputTenVT[51];
                char inputDonViTinh[11];
                bool done = false;
                int count = 0;
                while (!done)
                {
                    char c = getch();
                    if (c == 13 && c > 0)
                    {
                        inputTenVT[count] = '\0';
                        done = true;
                    }
                    else if (c == '\b' && c > 0)
                    {
                        cout << "\b \b";
                        inputTenVT[--count] = '\0';
                    }
                    else if (isalnum(c) && c < 50)
                    {
                        c = tolower(c);
                        cout << c;
                        inputTenVT[count++] = c;
                    }
                }
                done = false;
                count = 0;
                while (!done)
                {
                    char c = getch();
                    if (c == 13 && c > 0)
                    {
                        inputDonViTinh[count] = '\0';
                        done = true;
                    }
                    else if (c == '\b' && c > 0)
                    {
                        cout << "\b \b";
                        inputDonViTinh[--count] = '\0';
                    }
                    else if (isalnum(c) && c < 10)
                    {
                        c = tolower(c);
                        cout << c;
                        inputDonViTinh[count++] = c;
                    }
                }
                new_vattu = newDanhSachVatTu(current->maVT, inputTenVT, inputDonViTinh, current->soLuong);
                insertDanhSachVatTu(root, new_vattu);
            }
            else
            {
                DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(root, current->maVT);
                updateSoLuongTon(vattu, vattu->soLuongTon + current->soLuong);
            }
            current = current->next;
        }
    }
    else if (hd->loai == x)
    {
        if (root == nullptr)
        {
            cout << "Khong co gi trong DanhSachVatTu nen khong the xuat" << endl;
            return;
        }
        else
        {
            DanhSach_CT_HoaDon current = hd->ds_ct_hoadon;
            bool duYeuCau = true;

            while (current != nullptr)
            {
                if (isContainMaVT_DanhSachVatTu(root, current->maVT))
                {
                    DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(root, current->maVT);
                    if (vattu != nullptr)
                    {
                        int phanDu = vattu->soLuongTon - current->soLuong;
                        if (phanDu < 0)
                        {
                            duYeuCau = false;
                            cout << "Khong du so luong de xuat " << vattu->tenVT << endl;
                        }
                    }
                    else
                    {
                        duYeuCau = false;
                        cout << "MaVT " << current->maVT << " khong ton tai trong DanhSachVatTu" << endl;
                    }
                }
                current = current->next;
            }

            if (duYeuCau)
            {
                current = hd->ds_ct_hoadon;
                while (current != nullptr)
                {
                    DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(root, current->maVT);
                    int phanDu = vattu->soLuongTon - current->soLuong;
                    if (phanDu == 0)
                    {
                        removeFromDanhSachVatTu(vattu->tenVT, root);
                    }
                    else
                    {
                        updateSoLuongTon(vattu, phanDu);
                    }
                    current = current->next;
                }
            }
            else
            {
                cout << "Xuat hoa don bi huy do co vat tu khong du so luong." << endl;
                cout << "Day la chi tiet so luong cua nhung vattu trong hoa don cua ban" << endl;

                current = hd->ds_ct_hoadon;
                while (current != nullptr)
                {
                    DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(root, current->maVT);
                    if (vattu == nullptr)
                    {
                        cout << "MaVT " << current->maVT << " khong ton tai trong DanhSachVatTu!" << endl;
                    }
                    else
                    {
                        cout << "MaVT " << current->maVT << " - So luong ton: " << vattu->soLuongTon << endl;
                    }
                    current = current->next;
                }
            }
        }
    }
}

// chua test duoc
void InHoaDonTheoSoHD(DanhSachHoaDon FirstDS, DanhSachNhanVien ds_nv, DanhSachVatTu ds_vt, char soHD[21], int soLuongNV)
{
    if (soLuongNV == 0)
    {
        cout << "Khong co nhan vien nao nhap hoa don hoac hoa don khong ton tai" << endl;
        return;
    }

    for (int i = 0; i < soLuongNV; i++)
    {
        HoaDon *current_hd = ds_nv[i]->ds_hoadon;

        while (current_hd != nullptr && (strcmp(current_hd->soHD, soHD) != 0))
        {
            current_hd = current_hd->next;
        }

        if (current_hd != nullptr)
        {
            CT_HoaDon *current_ct = current_hd->ds_ct_hoadon;
            if (current_ct == nullptr)
            {
                cout << "Hoa don rong" << endl;
                return;
            }

            int tongTriGia = 0;

            cout << "-------------------- HOA DON --------------------" << endl;
            cout << "So Hoa Don: " << soHD << endl;
            cout << "Ngay: " << current_hd->date.day << "/"
                 << current_hd->date.month << "/"
                 << current_hd->date.year << endl;
            cout << "Nhan Vien: " << ds_nv[i]->ho << " " << ds_nv[i]->ten << endl;
            cout << "Loai Hoa Don: " << (current_hd->loai == n ? "Nhap" : "Xuat") << endl;
            cout << "------------------------------------------------" << endl;

            while (current_ct != nullptr)
            {
                VatTu *vattu = searchMaVT_DanhSachVatTu(ds_vt, current_ct->maVT);
                if (vattu != nullptr)
                {
                    int triGia = current_ct->soLuong * current_ct->donGia;
                    tongTriGia += triGia;
                    cout << "Ten VT: " << vattu->tenVT
                         << ", So Luong: " << current_ct->soLuong
                         << ", Don Gia: " << current_ct->donGia
                         << ", Tri Gia: " << triGia << endl;
                }
                else
                {
                    cout << "Vat tu voi ma " << current_ct->maVT << " khong ton tai" << endl;
                }
                current_ct = current_ct->next;
            }

            cout << "------------------------------------------------" << endl;
            cout << "Tong Tri Gia Hoa Don: " << tongTriGia << endl;
            cout << "------------------------------------------------" << endl;

            return;
        }
    }
    cout << "Khong tim thay hoa don voi soHD: " << soHD << endl;
}
