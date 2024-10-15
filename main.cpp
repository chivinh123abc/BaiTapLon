#include "drawFormatCode.cpp"
#include "vattu.cpp"
#include "nhanvien.cpp"
#include "hoadon.cpp"
#include "main.h"

const int firstItems = 4;
const int xUI1 = 0;
const int yUI1 = 10;
const int ENTER = 13;
const int UP_ARROW = 72;
const int DOWN_ARROW = 80;

// int idVatTuGlobalCount = 1;
// int idHoaDonGlobalCount = 1;
// int soLuongNhanVienGlobalCount = 0;

char firstUI[firstItems][50]{
    "         Vat Tu         ",
    "        Nhan Vien       ",
    "         Hoa Don        ",
    " Thong Ke Doanh Thu Nam "
    //
};

void SetNormalColor()
{
    SetColor(0xF);
    SetBGColor(0x0);
}

void SetHighLight()
{
    SetColor(0x1);
    SetBGColor(0x3);
}

void DrawFirstUI(int choose)
{
    for (int iy = 0; iy < firstItems; iy++)
    {
        gotoxy(xUI1, yUI1 + iy);
        cout << firstUI[iy] << endl;
    }
    SetHighLight();
    gotoxy(xUI1, yUI1 + choose);
    cout << firstUI[choose];
    SetNormalColor();
}

void menu(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_cthd, DanhSachNhanVien &ds_nv, int &idVatTuCount, int &idHoaDonCount, int &soLuongNhanVienCount)
{
    int choose1 = 0;
    char c1;
    DrawFirstUI(choose1);
init:
    while (true)
    {
        GetFirstUIInput(c1, choose1);

        switch (choose1)
        {
        case 0:
        {
            gotoxy(30, 10);
            cout << "Here0!";
            break;
        }
        case 1:
        {
            gotoxy(30, 10);
            cout << "Here1!";
            break;
        }
        case 2:
        {
            gotoxy(30, 10);
            cout << "Here2!";
            break;
        }
        case 3:
        {
            gotoxy(30, 10);
            cout << "Here3!";
            break;
        }
        }
    }
}

int GetFirstUIInput(char &c1, int &choose1)
{
    while (true)
    {
        c1 = getch();
        switch (c1)
        {
        case UP_ARROW:
        {
            if (choose1 == 0)
            {
                choose1 = firstItems - 1;
            }
            else
            {
                choose1--;
            }
            DrawFirstUI(choose1);
            break;
        }
        case DOWN_ARROW:
        {
            if (choose1 == firstItems - 1)
            {
                choose1 = 0;
            }
            else
            {
                choose1++;
            }
            DrawFirstUI(choose1);
            break;
        }
        case ENTER:
        {
            return choose1;
        }
        }
    }
}

int main()
{
    DanhSachHoaDon ds_hd;
    DanhSach_CT_HoaDon ds_cthd;
    DanhSachNhanVien ds_nv;
    DanhSachVatTu ds_vt;

    menu(ds_vt, ds_hd, ds_cthd, ds_nv, idVatTuGlobalCount, idHoaDonGlobalCount, soLuongNhanVienGlobalCount);

    int z;
    cin >> z;
}