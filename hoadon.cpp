#include "foundationStruct.cpp"

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
        InChiTietCTHoaDon(ds_cthoadon); // Gọi hàm in chi tiết
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
        // Ví dụ cách sài: ds_cthoadon = SapXepDanhSachCTHoaDon(ds_cthoadon, tieuchi);
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