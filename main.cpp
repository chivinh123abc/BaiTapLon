#include "drawFormatCode.cpp"
#include "vattu.cpp"
#include "stack.cpp"
#include "contactWithfile.cpp"
#include <ctime>
#include "nhanvien.cpp"
#include "hoadon.cpp"
#include <vector>
#include <cctype>
#include <cstring>
#include <iomanip>

const int firstItems = 5;
const int seccondVatTuItems = 5;
const int seccondNhanVienItems = 2;
const int seccondHoaDonItems = 4;
const int thirdHoaDonItems = 4;
const int xUI1 = 2;
const int yUI1 = 5;
const int xUI2 = 35;
const int yUI2 = 3;
const int yUINV2 = 6;
const int ENTER = 13;
const int ESC = 27;
const int TAB = 9;
const int F1 = 59;
const int F2 = 60;
const int F3 = 61;
const int F4 = 62;
const int UP_ARROW = 72;
const int DOWN_ARROW = 80;
const int LEFT_ARROW = 75;
const int RIGHT_ARROW = 77;
const char TEN_TK_ADMIN[] = "admin";
const char MK_ADMIN[] = "admin";
const char specialChars[] = "!@#$^&(),.-";
const int SCREEN_WIDTH = getConsoleWidth();
const int SCREEN_HEIGHT = getConsoleHeight();

// int idVatTuGlobalCount = 1;
// int idHoaDonGlobalCount = 1;
// int soLuongNhanVienGlobalCount = 0;

char firstUI[firstItems][50]{
    "         Vat Tu         ",
    "        Nhan Vien       ",
    "         Hoa Don        ",
    " Thong Ke Doanh Thu Nam ",
    "     Sao Luu Du Lieu    "
    //
};

char seccondVatTuUI[seccondVatTuItems][50]{
    "             Them Vat Tu             ",
    "          Hieu Chinh Vat Tu          ",
    "              Xoa Vat Tu             ",
    "     In Danh Sach Vat Tu Ton Kho     ",
    "In Ra 10 Vat Tu Co Doanh Thu Cao Nhat"
    //
};

char seccondNhanVienUI[seccondNhanVienItems][50]{
    "           Them Nhan Vien           ",
    "       In Danh Sach Nhan Vien       "
    //
};

char seccondHoaDonUI[seccondHoaDonItems][50]{
    "           Lap Hoa Don Nhap           ",
    "           Lap Hoa Don Xuat           ",
    "         In Danh Sach Hoa Don         ",
    "    In Danh Sach Hoa Don Theo Ngay    "
    //
};

char thirdHoaDonUI[thirdHoaDonItems][50]{
    "           Them Chi Tiet Hoa Don           ",
    "           Xoa Chi Tiet Hoa Don            ",
    "  Huy Hoa Don Hien Tai Va Thoat Ra Ngoai   ",
    "          Xac Nhan Va Them Hoa Don         ",

    //
};

void SetErrorColor()
{
    SetColor(0xF);
    SetBGColor(0x4);
}

void SetNormalColor()
{
    SetColor(0xF);
    SetBGColor(0x0);
}

void SetHighLight()
{
    SetColor(0x0);
    SetBGColor(0x2);
}
void SetHighLight2()
{
    SetColor(0x0);
    SetBGColor(0x7);
}

void expandArray(int *&arr, int oldSize, int newSize)
{
    int *newArr = new int[newSize];

    for (int i = 0; i < oldSize; ++i)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;

    arr = newArr;
}

void expandArray(VatTu **&arr, int oldSize, int newSize)
{
    VatTu **newArr = new VatTu *[newSize];

    for (int i = 0; i < oldSize; ++i)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;

    arr = newArr;
}

void expandArray(VatTuStack *&arr, int oldSize, int newSize)
{
    VatTuStack *newArr = new VatTuStack[newSize];

    for (int i = 0; i < oldSize; ++i)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;

    arr = newArr;
}

void expandArray(CT_HoaDon **&arr, int oldSize, int newSize)
{
    CT_HoaDon **newArr = new CT_HoaDon *[newSize];

    for (int i = 0; i < oldSize; ++i)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;

    arr = newArr;
}
void expandArray(HoaDon **&arr, int oldSize, int newSize)
{
    HoaDon **newArr = new HoaDon *[newSize];

    for (int i = 0; i < oldSize; ++i)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;

    arr = newArr;
}

void trim(char *str)
{
    int start = 0;
    while (isspace(str[start]))
    {
        ++start;
    }

    int end = strlen(str) - 1;
    while (end >= start && isspace(str[end]))
    {
        --end;
    }

    int newLength = end - start + 1;
    memmove(str, str + start, newLength);
    str[newLength] = '\0';

    // giam khoang cach giua cac tu xuong con 1 khoang trang

    int writePos = 0;
    bool inSpace = false;
    for (int readPos = 0; str[readPos] != '\0'; ++readPos)
    {
        if (isspace(str[readPos]))
        {
            if (!inSpace)
            {
                str[writePos++] = ' ';
                inSpace = true;
            }
        }
        else
        {
            str[writePos++] = str[readPos];
            inSpace = false;
        }
    }
    str[writePos] = '\0';
}

bool NamTrongKhoangTG(Date date, Date date1, Date date2)
{
    if (date.year < date1.year || date.year > date2.year)
    {
        return false;
    }

    // Kiểm tra năm, tháng
    if (date.year == date1.year && date.month < date1.month)
    {
        return false;
    }
    if (date.year == date2.year && date.month > date2.month)
    {
        return false;
    }

    if (date.year == date1.year && date.month == date1.month && date.day < date1.day)
    {
        return false;
    }
    if (date.year == date2.year && date.month == date2.month && date.day > date2.day)
    {
        return false;
    }

    return true;
}

bool isSpecialChar(char ch)
{
    // const speacialChars == {!@#$%^&*(),.} o phan khai bao
    for (char special : specialChars)
    {
        if (ch == special)
        {
            return true;
        }
    }
    return false;
}

void DrawUIInstruction()
{
    SetColor(0xB);
    drawRectangle2(0, 25, 28, 2);
    drawRectangle2(30, 25, 29, 2);
    drawRectangle2(61, 25, 20, 2);
    drawRectangle2(83, 25, 24, 2);
    SetNormalColor();
    gotoxy(2, 26);
    SetColor(0xC);
    cout << "ENTER: ";
    SetNormalColor();
    cout << "CHOOSE THIS OPTION";
    //
    gotoxy(32, 26);
    SetColor(0xC);
    cout << "ESC: ";
    SetNormalColor();
    cout << "BACK TO PREVIOUS PART";
    //
    gotoxy(63, 26);
    SetColor(0xC);
    cout << "UP_ARROW: ";
    SetNormalColor();
    cout << "MOVE UP";
    //
    gotoxy(85, 26);
    SetColor(0xC);
    cout << "DOWN_ARROW: ";
    SetNormalColor();
    cout << "MOVE DOWN";
}

void DrawAnnouncementBoard()
{
    // 91,27
    drawRectangle2(60, 26, 59, 3);
    //
    gotoxy(61, 27);
    cout << "                    ANNOUNCEMENT BOARD                    ";
    gotoxy(61, 28);
    SetBGColor(0x4);
    cout << "                                                          ";
    SetNormalColor();
}

void DrawFirstUI(int choose1)
{
    DrawUIInstruction();
    for (int iy = 0; iy < firstItems; iy++)
    {
        // drawRectangle(xUI1 - 1, yUI1 - 1, 10, 3);
        drawRectangle2(xUI1 - 1, yUI1 + iy * 3, 25, 2);
        gotoxy(xUI1, yUI1 + iy * 3 + 1);
        cout << firstUI[iy];
    }
    SetHighLight();
    drawRectangle2(xUI1 - 1, yUI1 + choose1 * 3, 25, 2);
    gotoxy(xUI1, yUI1 + choose1 * 3 + 1);
    cout << firstUI[choose1];
    SetNormalColor();
}

void DrawSeccondUIVatTu(int choose2)
{
    for (int iy = 0; iy < seccondVatTuItems; iy++)
    {
        drawRectangle2(xUI2 - 1, yUI2 + iy * 3, 38, 2);
        gotoxy(xUI2, yUI2 + iy * 3 + 1);
        cout << seccondVatTuUI[iy];
    }
    SetHighLight();
    drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
    gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
    cout << seccondVatTuUI[choose2];
    SetNormalColor();
}

void DrawSeccondUINhanVien(int choose2)
{
    for (int iy = 0; iy < seccondNhanVienItems; iy++)
    {
        drawRectangle2(xUI2 - 1, yUINV2 + iy * 3, 37, 2);
        gotoxy(xUI2, yUINV2 + iy * 3 + 1);
        cout << seccondNhanVienUI[iy];
    }
    SetHighLight();
    drawRectangle2(xUI2 - 1, yUINV2 + choose2 * 3, 37, 2);
    gotoxy(xUI2, yUINV2 + choose2 * 3 + 1);
    cout << seccondNhanVienUI[choose2];
    SetNormalColor();
};

void DrawSeccondUIHoaDon(int choose2)
{
    for (int iy = 0; iy < seccondHoaDonItems; iy++)
    {
        drawRectangle2(xUI2 - 1, yUI2 + iy * 3, 39, 2);
        gotoxy(xUI2, yUI2 + iy * 3 + 1);
        cout << seccondHoaDonUI[iy];
    }
    SetHighLight();
    drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 39, 2);
    gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
    cout << seccondHoaDonUI[choose2];
    SetNormalColor();
};

int GetFirstUIInput(char &c1, int &choose1)
{
    while (true)
    {
        c1 = getch();
        switch (c1)
        {
        case UP_ARROW:
        {

            drawRectangle2(xUI1 - 1, yUI1 + choose1 * 3, 25, 2);
            gotoxy(xUI1, yUI1 + choose1 * 3 + 1);
            cout << firstUI[choose1];
            if (choose1 == 0)
            {
                choose1 = firstItems - 1;
            }
            else
            {
                choose1--;
            }
            SetHighLight();
            drawRectangle2(xUI1 - 1, yUI1 + choose1 * 3, 25, 2);
            gotoxy(xUI1, yUI1 + choose1 * 3 + 1);
            cout << firstUI[choose1];
            SetNormalColor();

            break;
        }
        case DOWN_ARROW:
        {
            drawRectangle2(xUI1 - 1, yUI1 + choose1 * 3, 25, 2);
            gotoxy(xUI1, yUI1 + choose1 * 3 + 1);
            cout << firstUI[choose1];

            if (choose1 == firstItems - 1)
            {
                choose1 = 0;
            }
            else
            {
                choose1++;
            }
            SetHighLight();
            drawRectangle2(xUI1 - 1, yUI1 + choose1 * 3, 25, 2);
            gotoxy(xUI1, yUI1 + choose1 * 3 + 1);
            cout << firstUI[choose1];
            SetNormalColor();
            break;
        }
        case ENTER:
        {
            return choose1;
        }
        }
    }
}

int GetSeccondUIVatTuInput(char &c2, int &choose2)
{
    while (true)
    {
        c2 = getch();
        switch (c2)
        {
        case DOWN_ARROW:
        {
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondVatTuUI[choose2];
            if (choose2 == seccondVatTuItems - 1)
            {
                choose2 = 0;
            }
            else
            {
                choose2++;
            }
            SetHighLight();
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondVatTuUI[choose2];
            SetNormalColor();
            break;
        }
        case UP_ARROW:
        {
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondVatTuUI[choose2];
            if (choose2 == 0)
            {
                choose2 = seccondVatTuItems - 1;
            }
            else
            {
                choose2--;
            }
            SetHighLight();
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondVatTuUI[choose2];
            SetNormalColor();
            break;
        }
        case ESC:
        {
            choose2 = -1;
            return -1;
        }
        case ENTER:
        {
            return choose2;
        }
        }
    }
}
// HAM VE
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void DrawVatTuContactGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "BUTTON GUIDE";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "ENTER: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "ESC: Stop Program";
    drawRectangle(80, 8, 31, 4);
    gotoxy(87, 10);
    SetColor(0x2);
    cout << "INPUT RESTRICTIONS";
    SetColor(0xF);
    drawRectangle(80, 12, 31, 2);
    gotoxy(86, 13);
    cout << "Ten vat tu (20 char)";
    drawRectangle(80, 14, 31, 2);
    gotoxy(86, 15);
    cout << "Don vi tinh(10 char)";
    drawRectangle(80, 16, 31, 2);
    gotoxy(81, 17);
    cout << "So Luong Ton (Under 1 billion)";

    //
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
    gotoxy(80, 12);
    cout << char(195);
    gotoxy(111, 12);
    cout << char(180);
    gotoxy(80, 14);
    cout << char(195);
    gotoxy(111, 14);
    cout << char(180);
    gotoxy(80, 16);
    cout << char(195);
    gotoxy(111, 16);
    cout << char(180);
}

void DrawAdjustVatTuContactGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "BUTTON GUIDE";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "ENTER: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "ESC: Stop Program";
    drawRectangle(80, 8, 31, 2);
    gotoxy(86, 9);
    cout << "*: Open Vat Tu List";
    drawRectangle(80, 10, 31, 4);
    gotoxy(87, 12);
    SetColor(0x2);
    cout << "INPUT RESTRICTIONS";
    SetColor(0xF);
    drawRectangle(80, 14, 31, 2);
    gotoxy(86, 15);
    cout << "Ten vat tu (20 char)";
    drawRectangle(80, 16, 31, 2);
    gotoxy(86, 17);
    cout << "Don vi tinh(10 char)";
    drawRectangle(80, 18, 31, 2);
    gotoxy(81, 19);
    cout << "So Luong Ton (Under 1 billion)";
    drawRectangle(80, 20, 31, 4);
    gotoxy(87, 21);
    cout << "Leave fields empty";
    gotoxy(86, 22);
    cout << "when you do not want";
    gotoxy(86, 23);
    cout << "to change it's value ";

    //
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
    gotoxy(80, 10);
    cout << char(195);
    gotoxy(111, 10);
    cout << char(180);
    gotoxy(80, 14);
    cout << char(195);
    gotoxy(111, 14);
    cout << char(180);
    gotoxy(80, 16);
    cout << char(195);
    gotoxy(111, 16);
    cout << char(180);
    gotoxy(80, 18);
    cout << char(195);
    gotoxy(111, 18);
    cout << char(180);
    gotoxy(80, 20);
    cout << char(195);
    gotoxy(111, 20);
    cout << char(180);
}

void DrawRemoveVatTuContactGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "BUTTON GUIDE";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "ENTER: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "ESC: Stop Program";
    drawRectangle(80, 8, 31, 2);
    gotoxy(86, 9);
    cout << "->: Open Vat Tu List";
    drawRectangle(80, 10, 31, 2);
    gotoxy(87, 11);
    cout << "<-: Previous List";

    //
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
    gotoxy(80, 10);
    cout << char(195);
    gotoxy(111, 10);
}

void clearShowVatTuBoard()
{
    for (int i = 1; i <= 15; i++)
    {
        gotoxy(3, 6 + i);
        cout << "          ";
        gotoxy(18, 6 + i);
        cout << "                                                  ";
        gotoxy(70, 6 + i);
        cout << "          ";
        gotoxy(98, 6 + i);
        cout << "          ";
    }
};

void clearShowVatTuBoard2()
{
    for (int i = 1; i <= 15; i++)
    {
        // 15,25,15,21
        // 0,15,40,55
        gotoxy(1, 6 + i);
        cout << "              ";
        gotoxy(16, 6 + i);
        cout << "                        ";
        gotoxy(41, 6 + i);
        cout << "              ";
        gotoxy(56, 6 + i);
        cout << "                    ";
    }
};

void DrawHienThiVatTuTable(DanhSachVatTu ds_vt)
{
    if (ds_vt == nullptr)
    {
        cout << "Danh Sach Dang Trong";
        gotoxy(18, 5);
    }
    else
    {
        gotoxy(0, 27);
        SetColor(0xA);
        cout << "ENTER:";
        SetColor(0xF);
        cout << " Choose This TenVT  ";
        SetColor(0xA);
        cout << "UP_ARROW:";
        SetColor(0xF);
        cout << " Move Up  ";
        SetColor(0xA);
        cout << "DOWN_ARROW:";
        SetColor(0xF);
        cout << " Move Down";
        gotoxy(0, 28);
        SetColor(0xA);
        cout << "ESC:";
        SetColor(0xF);
        cout << " Escape From Board    ";
        SetColor(0xA);
        cout << "-->:";
        SetColor(0xF);
        cout << " Next List     ";
        SetColor(0xA);
        cout << "<--:";
        SetColor(0xF);
        cout << " Previous List   ";
        SetColor(0xF);
        //
        drawRectangle(0, 0, 118, 4);
        gotoxy(40, 2);
        SetColor(0xC);
        cout << "Bang Thong Tin Chi Tiet Vat Tu Dang Co" << endl;
        SetColor(0xF);
        drawRectangle(0, 4, 16, 2);
        gotoxy(4, 5);
        cout << "Ma Vat Tu";
        drawRectangle(16, 4, 53, 2);
        gotoxy(36, 5);
        cout << "Ten Vat Tu";
        drawRectangle(69, 4, 28, 2);
        gotoxy(78, 5);
        cout << "Don Vi Tinh";
        drawRectangle(97, 4, 21, 2);
        gotoxy(102, 5);
        cout << "So Luong Ton";
        // Phan noi dung
        drawRectangle(0, 6, 16, 16);
        drawRectangle(16, 6, 53, 16);
        drawRectangle(69, 6, 28, 16);
        drawRectangle(97, 6, 21, 16);
        //
        gotoxy(0, 4);
        cout << char(195);
        gotoxy(16, 4);
        cout << char(194);
        gotoxy(69, 4);
        cout << char(194);
        gotoxy(97, 4);
        cout << char(194);
        gotoxy(118, 4);
        cout << char(180);
        gotoxy(0, 6);
        cout << char(195);
        gotoxy(16, 6);
        cout << char(197);
        gotoxy(69, 6);
        cout << char(197);
        gotoxy(97, 6);
        cout << char(197);
        gotoxy(118, 6);
        cout << char(180);
        gotoxy(16, 22);
        cout << char(193);
        gotoxy(69, 22);
        cout << char(193);
        gotoxy(97, 22);
        cout << char(193);
        /////////////////////////
    }
}

void DrawHienThiThemVatTuTable(DanhSachVatTu ds_vt)
{
    if (ds_vt == nullptr)
    {
        cout << "Danh Sach Dang Trong";
        gotoxy(62, 28);
    }
    else
    {
        gotoxy(0, 27);
        SetColor(0xA);
        cout << "ENTER:";
        SetColor(0xF);
        cout << " Choose This TenVT  ";
        SetColor(0xA);
        cout << "UP_ARROW:";
        SetColor(0xF);
        cout << " Move Up  ";
        SetColor(0xA);
        cout << "DOWN_ARROW:";
        SetColor(0xF);
        cout << " Move Down";
        gotoxy(0, 28);
        SetColor(0xA);
        cout << "ESC:";
        SetColor(0xF);
        cout << " Escape From Board    ";
        SetColor(0xA);
        cout << "-->:";
        SetColor(0xF);
        cout << " Next List     ";
        SetColor(0xA);
        cout << "<--:";
        SetColor(0xF);
        cout << " Previous List   ";
        SetColor(0xF);
        //
        drawRectangle(0, 0, 76, 4);
        gotoxy(25, 2);
        SetColor(0xC);
        cout << "Bang Thong Tin Chi Tiet Vat Tu Dang Co" << endl;
        SetColor(0xF);
        drawRectangle(0, 4, 15, 2);
        gotoxy(3, 5);
        cout << "Ma Vat Tu";
        drawRectangle(15, 4, 25, 2);
        gotoxy(23, 5);
        cout << "Ten Vat Tu";
        drawRectangle(40, 4, 15, 2);
        gotoxy(42, 5);
        cout << "Don Vi Tinh";
        drawRectangle(55, 4, 21, 2);
        gotoxy(61, 5);
        cout << "So Luong Ton";
        // Phan noi dung
        drawRectangle(0, 6, 15, 16);
        drawRectangle(15, 6, 25, 16);
        drawRectangle(40, 6, 15, 16);
        drawRectangle(55, 6, 21, 16);
        // 15,15,25,21
        // 0,15,30,55
        gotoxy(0, 4);
        cout << char(195);
        gotoxy(15, 4);
        cout << char(194);
        gotoxy(40, 4);
        cout << char(194);
        gotoxy(55, 4);
        cout << char(194);
        gotoxy(76, 4);
        cout << char(180);
        gotoxy(0, 6);
        cout << char(195);
        gotoxy(15, 6);
        cout << char(197);
        gotoxy(40, 6);
        cout << char(197);
        gotoxy(55, 6);
        cout << char(197);
        gotoxy(76, 6);
        cout << char(180);
        gotoxy(15, 22);
        cout << char(193);
        gotoxy(40, 22);
        cout << char(193);
        gotoxy(55, 22);
        cout << char(193);
        /////////////////////////
    }
}

// THEM VAT TU
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void HienThiThemVatTu(DanhSachVatTu root, int SoLuongVatTu)
{
    DrawHienThiThemVatTuTable(root);
    unsigned char c;
    // dem trang va luu ptr vs stack tai vi tri day
    int Page = 1;
    int arr2Size = 1;
    bool backToPrv = false;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    //
    VatTu *current_vt = root;
    VatTuStack vtStack;
    // dem de gioi han so luong
    int count = 0;
    int max = 15;
    //
    clearShowVatTuBoard2();
    while (current_vt != nullptr || !vtStack.isEmpty())
    {
        while (current_vt != nullptr)
        {
            vtStack.push(current_vt);
            current_vt = current_vt->left;
        }

        current_vt = vtStack.pop();

        if (Page == arr2Size && current_vt != nullptr)
        {
            PageStack[arr2Size - 1] = vtStack;
            PageStack[arr2Size - 1].push(current_vt);
            expandArray(PageStack, arr2Size, Page + 1);

            firstPagePos[arr2Size - 1] = current_vt;
            expandArray(firstPagePos, arr2Size, Page + 1);
            arr2Size += 1;
        }
        // 15,25,15,21
        // 0,15,40,55
        gotoxy(3, 22 - (max - count));
        cout << current_vt->maVT;
        gotoxy(18, 22 - (max - count));
        cout << current_vt->tenVT;
        gotoxy(43, 22 - (max - count));
        cout << current_vt->dVT;
        gotoxy(58, 22 - (max - count));
        cout << current_vt->soLuongTon;
        count++;

        if (count >= max || count > SoLuongVatTu - 1)
        {
            backToPrv = false;
            while (true)
            {
                c = getch();
                if (c == 224)
                {
                    c = getch();
                    if (c == RIGHT_ARROW && max < SoLuongVatTu)
                    {
                        count = max;
                        max = max + 15;
                        Page++;
                        clearShowVatTuBoard2();
                        break;
                    }
                    else if (c == LEFT_ARROW && Page > 1)
                    {
                        backToPrv = true;
                        Page--;
                        current_vt = nullptr;
                        vtStack = PageStack[Page - 1];
                        max -= 15;
                        count = max - 15;
                        clearShowVatTuBoard2();
                        break;
                    }
                }
                else if (c == ESC)
                {
                    delete[] PageStack;
                    delete[] firstPagePos;
                    PageStack = nullptr;
                    firstPagePos = nullptr;
                    return;
                }
            }
            if (backToPrv)
            {
                continue;
            }
        }
        current_vt = current_vt->right;
    }
}

// VatTuStack *PageStack = new VatTuStack[1];
//  VatTu **firstPagePos
void InNoiDungTrangThemVT(DanhSachVatTu &current_vt, VatTuStack *&PageStack, VatTu **&firstPagePos, VatTuStack &vtStack, int &Page, int &arr2Size, int bodem, int max)
{
    clearShowVatTuBoard2();
    while (current_vt != nullptr || !vtStack.isEmpty())
    {
        while (current_vt != nullptr)
        {
            vtStack.push(current_vt);
            current_vt = current_vt->left;
        }

        current_vt = vtStack.pop();

        if (Page == arr2Size && current_vt != nullptr)
        {
            PageStack[arr2Size - 1] = vtStack;
            PageStack[arr2Size - 1].push(current_vt);
            expandArray(PageStack, arr2Size, Page + 1);

            firstPagePos[arr2Size - 1] = current_vt;
            expandArray(firstPagePos, arr2Size, Page + 1);
            arr2Size += 1;
        }
        // 15,25,15,21
        // 0,15,40,55
        gotoxy(3, 22 - (max - bodem));
        cout << current_vt->maVT;
        gotoxy(18, 22 - (max - bodem));
        cout << current_vt->tenVT;
        gotoxy(43, 22 - (max - bodem));
        cout << current_vt->dVT;
        gotoxy(58, 22 - (max - bodem));
        cout << current_vt->soLuongTon;
        bodem++;

        if (bodem >= max || bodem > SoLuongVatTuGlobalCount - 1)
        {
            break;
            // backToPrv = false;
            // while (true)
            // {
            //     c = getch();
            //     if (c == 224)
            //     {
            //         c = getch();
            //         if (c == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
            //         {
            //             bodem = max;
            //             max = max + 15;
            //             Page++;
            //             clearShowVatTuBoard2();
            //             break;
            //         }
            //         else if (c == LEFT_ARROW && Page > 1)
            //         {
            //             backToPrv = true;
            //             Page--;
            //             current_vt = nullptr;
            //             vtStack = PageStack[Page - 1];
            //             max -= 15;
            //             bodem = max - 15;
            //             clearShowVatTuBoard2();
            //             break;
            //         }
            //     }
            //     else if (c == ESC)
            //     {
            //         delete[] PageStack;
            //         delete[] firstPagePos;
            //         PageStack = nullptr;
            //         firstPagePos = nullptr;
            //         return;
            //     }
            // }
            // if (backToPrv)
            // {
            //     continue;
            // }
        }
        current_vt = current_vt->right;
    }
}

void ThemVatTu(DanhSachVatTu &ds_vt)
{
    // dem trang va luu ptr vs stack tai vi tri day
    int Page = 1;
    int arr2Size = 1;
    bool backToPrv = false;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    VatTu *current_vt = ds_vt;
    VatTuStack vtStack;
    int bodem = 0;
    int max = 15;
    //
    while (true)
    {
        drawRectangle(79, 0, 40, 2);
        drawRectangle(79, 2, 15, 2);
        drawRectangle(94, 2, 25, 2);
        DrawHienThiThemVatTuTable(ds_vt);
        InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
        DrawAnnouncementBoard();
        gotoxy(79, 2);
        cout << char(195);
        gotoxy(94, 2);
        cout << char(194);
        gotoxy(94, 4);
        cout << char(193);
        gotoxy(119, 2);
        cout << char(180);
        gotoxy(89, 1);
        SetColor(0xC);
        cout << "Them thong tin vat tu" << endl;
        SetColor(0xF);
        char inputMaVT[11];
        int count;
        unsigned char ch;
        gotoxy(82, 3);
        cout << "Ma Vat Tu";
        //
        drawRectangle(79, 4, 15, 2);
        drawRectangle(94, 4, 25, 2);
        gotoxy(79, 4);
        cout << char(195);
        gotoxy(119, 4);
        cout << char(180);
        gotoxy(94, 4);
        cout << char(197);
        gotoxy(94, 6);
        cout << char(193);
        gotoxy(82, 5);
        cout << "Ten Vat Tu";
        //
        drawRectangle(79, 6, 15, 2);
        drawRectangle(94, 6, 25, 2);
        gotoxy(79, 6);
        cout << char(195);
        gotoxy(94, 6);
        cout << char(197);
        gotoxy(94, 8);
        cout << char(193);
        gotoxy(119, 6);
        cout << char(180);
        gotoxy(81, 7);
        cout << "Don Vi Tinh";
        //
        drawRectangle(79, 8, 15, 2);
        drawRectangle(94, 8, 25, 2);
        gotoxy(79, 8);
        cout << char(195);
        gotoxy(94, 8);
        cout << char(197);
        gotoxy(94, 10);
        cout << char(193);
        gotoxy(119, 8);
        cout << char(180);
        gotoxy(81, 9);
        cout << "So luong ton";
        //
        gotoxy(96, 3);
        // dinhDangMaVatTu(inputMaVT, "vt", idVatTuGlobalCount);
        // cout << "maVT cua ban la " << inputMaVT << endl;
        count = 0;
        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
                {
                    bodem = max;
                    max = max + 15;
                    Page++;
                    current_vt = current_vt->right;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                else if (ch == LEFT_ARROW && Page > 1)
                {
                    backToPrv = true;
                    Page--;
                    current_vt = nullptr;
                    vtStack = PageStack[Page - 1];
                    max -= 15;
                    bodem = max - 15;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                gotoxy(96 + count, 3);
                continue;
            }
            else if (count > 0 && ch == 13)
            {
                inputMaVT[count] = '\0';
                trim(inputMaVT);
                if (isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
                {
                    gotoxy(62, 28);
                    SetBGColor(0x4);
                    cout << "Cay da ton tai vat tu [" << inputMaVT << "]" << endl;
                    gotoxy(96 + count, 3);
                    SetNormalColor();
                    continue;
                }
                else
                {
                    gotoxy(61, 28);
                    SetBGColor(0x4);
                    cout << "                                                          ";
                    SetNormalColor();
                    break;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputMaVT[--count] = '\0';
            }
            else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
            {
                cout << ch;
                ch = tolower(ch);
                inputMaVT[count++] = ch;
            }
            else if (ch == ESC)
            {
                gotoxy(62, 28);
                cout << "Quit";
                return;
            }
        }

        char inputTenVT[21];
        count = 0;
        gotoxy(96, 5);

        while (true)
        {

            ch = getch();

            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
                {
                    bodem = max;
                    max = max + 15;
                    Page++;
                    current_vt = current_vt->right;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                else if (ch == LEFT_ARROW && Page > 1)
                {
                    backToPrv = true;
                    Page--;
                    current_vt = nullptr;
                    vtStack = PageStack[Page - 1];
                    max -= 15;
                    bodem = max - 15;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                gotoxy(96 + count, 5);
                continue;
            }
            else if (count > 0 && ch == 13)
            {
                inputTenVT[count] = '\0';
                trim(inputTenVT);
                if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
                {
                    gotoxy(62, 28);
                    SetBGColor(0x4);
                    cout << "Cay da ton tai vat tu [" << inputTenVT << "]" << endl;
                    SetNormalColor();
                    gotoxy(96 + count, 5);
                    continue;
                }
                else
                {
                    gotoxy(61, 28);
                    SetBGColor(0x4);
                    cout << "                                                          ";
                    SetNormalColor();
                    break;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputTenVT[--count] = '\0';
            }
            else if ((isalnum(ch) || ch == ' ') && count < 20)
            {
                cout << ch;
                ch = tolower(ch);
                inputTenVT[count++] = ch;
            }
            else if (ch == ESC)
            {
                return;
            }
        }
        char inputDVT[11];
        count = 0;
        gotoxy(96, 7);

        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
                {
                    bodem = max;
                    max = max + 15;
                    Page++;
                    current_vt = current_vt->right;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                else if (ch == LEFT_ARROW && Page > 1)
                {
                    backToPrv = true;
                    Page--;
                    current_vt = nullptr;
                    vtStack = PageStack[Page - 1];
                    max -= 15;
                    bodem = max - 15;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                gotoxy(96 + count, 7);
                continue;
            }
            else if (ch == 13 && count > 0)
            {
                inputDVT[count] = '\0';
                trim(inputDVT);
                break;
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputDVT[--count] = '\0';
            }
            else if ((isalnum(ch) || ch == ' ') && count < 10)
            {
                cout << ch;
                ch = tolower(ch);
                inputDVT[count++] = ch;
            }
            else if (ch == ESC)
            {
                return;
            }
        }

        char inputC_SoLuongTon[10];
        count = 0;
        gotoxy(96, 9);

        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
                {
                    bodem = max;
                    max = max + 15;
                    Page++;
                    current_vt = current_vt->right;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                else if (ch == LEFT_ARROW && Page > 1)
                {
                    backToPrv = true;
                    Page--;
                    current_vt = nullptr;
                    vtStack = PageStack[Page - 1];
                    max -= 15;
                    bodem = max - 15;
                    InNoiDungTrangThemVT(current_vt, PageStack, firstPagePos, vtStack, Page, arr2Size, bodem, max);
                }
                gotoxy(96 + count, 9);
                continue;
            }
            else if (ch == 13 && count > 0)
            {
                inputC_SoLuongTon[count] = '\0';
                break;
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputC_SoLuongTon[--count] = '\0';
            }
            else if (isdigit(ch) && count < 9)
            {
                cout << ch;
                inputC_SoLuongTon[count++] = ch;
            }
            else if (ch == ESC)
            {
                return;
            }
        }
        cout << endl;

        int inputSoLuongTon = stoi(inputC_SoLuongTon);

        DanhSachVatTu dsvt_moi = newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon);
        insertDanhSachVatTu(ds_vt, dsvt_moi);
        //
        gotoxy(62, 28);
        SetBGColor(0x4);
        cout << "SUCCESSFUL";
        SetNormalColor();
        // Kiem tra muon nhap tiep hay thoat
        gotoxy(1, 23);
        cout << "DO YOU WANT TO CONTINUE ADD MORE VATTU (y: Continue, n: Exit)";
        while (true)
        {
            ch = getch();
            if (ch == 'y' || ch == 'Y')
            {
                Page = 1;
                arr2Size = 1;
                backToPrv = false;
                VatTuStack *PageStack = new VatTuStack[1];
                VatTu **firstPagePos = new VatTu *[1];
                vtStack.sp = -1;
                current_vt = ds_vt;
                bodem = 0;
                max = 15;
                //
                clrscr();
                break;
            }
            else if (ch == 'n' || ch == 'N')
            {
                return;
            }
        }
    }
}

// HIEU CHINH VAT TU
//+++++++++++++++++++++++++++++++++++++++++++

// Dung de ho tro ve lai vung nhap input
void HieuChinhVatTuDrawSupport()
{
    // drawRectangle(79, 0, 40, 2);
    // drawRectangle(79, 2, 15, 2);
    // drawRectangle(94, 2, 25, 2);
    //
    drawRectangle(79, 0, 40, 2);
    drawRectangle(79, 2, 40, 2);
    gotoxy(79, 2);
    cout << char(195);
    gotoxy(119, 2);
    cout << char(180);
    gotoxy(86, 1);
    SetColor(0xC);
    cout << "Hieu Chinh Thong Tin Vat Tu";
    SetColor(0xF);
    gotoxy(85, 3);
    cout << "Nhap ma vat tu can hieu chinh";
    drawRectangle(79, 4, 15, 2);
    drawRectangle(94, 4, 25, 2);
    gotoxy(79, 4);
    cout << char(195);
    gotoxy(119, 4);
    cout << char(180);
    gotoxy(94, 4);
    cout << char(194);
    gotoxy(94, 6);
    cout << char(193);
    gotoxy(82, 5);
    cout << "Ma Vat Tu";
    gotoxy(96, 5);
}

// NOTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
void NoiDungVatTu(DanhSachVatTu ds_vt, char noidung[11], int &dem, int SoLuongVatTu, int &Page, int &arr2Size, VatTuStack *&PageStack, VatTu **&firstPagePos, char pageMaVTData[15][11], VatTu *&current_vt, VatTuStack &vtStack, int &bodem, int &max, int &ptrY)
{
    // unsigned char ch;
    // int Page = 1;
    // int arr2Size = 1;
    // VatTuStack *PageStack = new VatTuStack[1];
    // VatTu **firstPagePos = new VatTu *[1];
    // char pageMaVTData[15][11];
    // // bool backToPrev = false;
    // VatTu *current_vt = ds_vt;
    // VatTuStack vtStack;
    // int bodem = 0;
    // int max = 15;
    // int ptrY = 0;
    //
    // clearShowVatTuBoard2();
    while (current_vt != nullptr || !vtStack.isEmpty())
    {
        while (current_vt != nullptr)
        {
            vtStack.push(current_vt);
            current_vt = current_vt->left;
        }

        current_vt = vtStack.pop();
        //
        if (Page == arr2Size && current_vt != nullptr)
        {
            PageStack[arr2Size - 1] = vtStack;
            PageStack[arr2Size - 1].push(current_vt);
            expandArray(PageStack, arr2Size, Page + 1);

            firstPagePos[arr2Size - 1] = current_vt;
            expandArray(firstPagePos, arr2Size, Page + 1);
            arr2Size += 1;
        }

        // 15,25,15,21
        // 0,15,40,55
        gotoxy(2, 22 - (max - bodem));
        cout << current_vt->maVT;
        gotoxy(17, 22 - (max - bodem));
        cout << current_vt->tenVT;
        gotoxy(42, 22 - (max - bodem));
        cout << current_vt->dVT;
        gotoxy(57, 22 - (max - bodem));
        cout << current_vt->soLuongTon;
        strcpy(pageMaVTData[15 - (max - bodem)], current_vt->maVT);
        bodem++;

        if (bodem >= max || bodem > SoLuongVatTu - 1)
        {
            if (14 - (max - bodem) < ptrY)
            {
                gotoxy(0, 7 + ptrY);
                cout << char(179) << " ";
                ptrY = 14 - (max - bodem);
            }
            gotoxy(0, 7 + ptrY);
            SetColor(0x4);
            cout << "->";
            SetColor(0xF);
            break;
            // while (true)
            // {
            //     ch = getch();
            //     if (ch == 224)
            //     {
            //         ch = getch();
            // if (ch == RIGHT_ARROW && max < SoLuongVatTu)
            // {

            //     bodem = max;
            //     max = max + 15;
            //     Page++;
            //     clearShowVatTuBoard();
            //     break;
            // }
            // else if (ch == LEFT_ARROW && Page > 1)
            // {
            //     Page--;
            //     current_vt = nullptr;
            //     vtStack = PageStack[Page - 1];
            //     max -= 15;
            //     bodem = max - 15;
            //     backToPrev = true;
            //     clearShowVatTuBoard();
            //     break;
            // }
            // else if (ch == DOWN_ARROW && ptrY < 14 - (max - bodem))
            // {
            //     gotoxy(0, 7 + ptrY);
            //     cout << char(179) << " ";
            //     ptrY += 1;
            //     gotoxy(0, 7 + ptrY);
            //     SetColor(0x4);
            //     cout << "->";
            //     SetColor(0xF);
            //     continue;
            // }
            // else if (ch == UP_ARROW && ptrY > 0)
            // {
            //     gotoxy(0, 7 + ptrY);
            //     cout << char(179) << " ";
            //     ptrY -= 1;
            //     gotoxy(0, 7 + ptrY);
            //     SetColor(0x4);
            //     cout << "->";
            //     SetColor(0xF);
            //     continue;
            // }
            //     }
            //     else if (ch == ESC)
            //     {
            //         return;
            //     }
            //     else if (ch == ENTER && ptrY < 15 - (max - bodem))
            //     {
            //         gotoxy(0, 0);
            //         strcpy(noidung, pageMaVTData[ptrY]);
            //         dem = strlen(noidung);
            //         return;
            //     }
            // }
            // if (backToPrev)
            // {
            //     backToPrev = false;
            //     continue;
            // }
        }

        current_vt = current_vt->right;
    }
}

void HienThiVatTuDangCoTrongHieuChinh(DanhSachVatTu ds_vt, char noidung[11], int &dem, int SoLuongVatTu, int &Page, int &arr2Size, VatTuStack *&PageStack, VatTu **&firstPagePos, char pageMaVTData[15][11], VatTu *&current_vt, VatTuStack &vtStack, int &bodem, int &max, int &ptrY)
{
    if (ds_vt == nullptr)
    {
        cout << "Danh Sach Dang Trong";
        gotoxy(18, 5);
    }
    else
    {
        //
        // gotoxy(0, 27);
        // SetColor(0xA);
        // cout << "ENTER:";
        // SetColor(0xF);
        // cout << " Choose This MaVT  ";
        // SetColor(0xA);
        // cout << "UP_ARROW:";
        // SetColor(0xF);
        // cout << " Move Up  ";
        // SetColor(0xA);
        // cout << "DOWN_ARROW:";
        // SetColor(0xF);
        // cout << " Move Down";
        // gotoxy(0, 28);
        // SetColor(0xA);
        // cout << "ESC:";
        // SetColor(0xF);
        // cout << " Escape From Board    ";
        // SetColor(0xA);
        // cout << "-->:";
        // SetColor(0xF);
        // cout << " Next List     ";
        // SetColor(0xA);
        // cout << "<--:";
        // SetColor(0xF);
        // cout << " Previous List   ";
        // SetColor(0xF);
        //
        drawRectangle(0, 0, 76, 4);
        gotoxy(14, 2);
        SetColor(0xC);
        cout << "Bang Thong Tin Chi Tiet Vat Tu Dang Co";
        SetColor(0xF);
        drawRectangle(0, 4, 15, 2);
        gotoxy(4, 5);
        cout << "Ma Vat Tu";
        drawRectangle(15, 4, 25, 2);
        gotoxy(16, 5);
        cout << "Ten Vat Tu";
        drawRectangle(40, 4, 15, 2);
        gotoxy(41, 5);
        cout << "Don Vi Tinh";
        drawRectangle(55, 4, 21, 2);
        gotoxy(56, 5);
        cout << "So Luong Ton";
        // Phan noi dung
        drawRectangle(0, 6, 15, 16);
        drawRectangle(15, 6, 25, 16);
        drawRectangle(40, 6, 15, 16);
        drawRectangle(55, 6, 21, 16);
        //
        gotoxy(0, 4);
        cout << char(195);
        gotoxy(15, 4);
        cout << char(194);
        gotoxy(40, 4);
        cout << char(194);
        gotoxy(55, 4);
        cout << char(194);
        gotoxy(76, 4);
        cout << char(180);
        gotoxy(0, 6);
        cout << char(195);
        gotoxy(15, 6);
        cout << char(197);
        gotoxy(40, 6);
        cout << char(197);
        gotoxy(55, 6);
        cout << char(197);
        gotoxy(76, 6);
        cout << char(180);
        gotoxy(15, 22);
        cout << char(193);
        gotoxy(40, 22);
        cout << char(193);
        gotoxy(55, 22);
        cout << char(193);
        /////////////////////////
        NoiDungVatTu(ds_vt, noidung, dem, SoLuongVatTu, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
    }
}

void HieuChinhVatTu(DanhSachVatTu &ds_vt)
{

    int Page = 1;
    int arr2Size = 1;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    char pageMaVTData[15][11];
    VatTu *current_vt = ds_vt;
    VatTuStack vtStack;
    int bodem = 0;
    int max = 15;
    int ptrY = 0;

    // drawRectangle(79, 0, 40, 2);
    // drawRectangle(79, 2, 15, 2);
    // drawRectangle(94, 2, 25, 2);

    while (true)
    {
        int count = 0;
        char inputMaVT[11];
        unsigned char ch;
        VatTu *foundVT;

        HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
        DrawAnnouncementBoard();
        HieuChinhVatTuDrawSupport();
        //
        drawRectangle(79, 6, 15, 2);
        drawRectangle(94, 6, 25, 2);
        gotoxy(79, 6);
        cout << char(195);
        gotoxy(94, 6);
        cout << char(197);
        gotoxy(94, 8);
        cout << char(193);
        gotoxy(119, 6);
        cout << char(180);
        gotoxy(81, 7);
        cout << "Ten VT(old)";
        //
        drawRectangle(79, 8, 15, 2);
        drawRectangle(94, 8, 25, 2);
        gotoxy(79, 8);
        cout << char(195);
        gotoxy(94, 8);
        cout << char(197);
        gotoxy(94, 10);
        cout << char(193);
        gotoxy(119, 8);
        cout << char(180);
        gotoxy(81, 9);
        cout << "DV Tinh(old)";
        //
        gotoxy(96, 5);

        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
                {

                    bodem = max;
                    max = max + 15;
                    Page++;
                    current_vt = current_vt->right;
                    clearShowVatTuBoard2();
                    HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
                    gotoxy(96 + count, 5);
                }
                else if (ch == LEFT_ARROW && Page > 1)
                {
                    Page--;
                    current_vt = nullptr;
                    vtStack = PageStack[Page - 1];
                    max -= 15;
                    bodem = max - 15;
                    clearShowVatTuBoard2();
                    HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
                    gotoxy(96 + count, 5);
                }
                else if (ch == DOWN_ARROW && ptrY < 14 - (max - bodem))
                {
                    gotoxy(0, 7 + ptrY);
                    cout << char(179) << " ";
                    ptrY += 1;
                    gotoxy(0, 7 + ptrY);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                    gotoxy(96 + count, 5);
                    continue;
                }
                else if (ch == UP_ARROW && ptrY > 0)
                {
                    gotoxy(0, 7 + ptrY);
                    cout << char(179) << " ";
                    ptrY -= 1;
                    gotoxy(0, 7 + ptrY);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                    gotoxy(96 + count, 5);
                    continue;
                }
            }
            else if (ch == '*')
            {
                gotoxy(96, 5);
                cout << pageMaVTData[ptrY];
                strcpy(inputMaVT, pageMaVTData[ptrY]);
                count = strlen(pageMaVTData[ptrY]);
                // clrscr();
                // HieuChinhVatTuDrawSupport();
                // DrawAdjustVatTuContactGuide();
                // gotoxy(18, 5);
                // if (count != 0)
                // {
                //     cout << inputMaVT;
                // }
                continue;
            }
            else if (count > 0 && ch == ENTER)
            {
                inputMaVT[count] = '\0';
                trim(inputMaVT);
                //
                if (!isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
                {
                    gotoxy(62, 28);
                    SetErrorColor();
                    cout << "Ma vat tu [" << inputMaVT << "] khong duoc tim thay" << endl;
                    SetNormalColor();
                    gotoxy(96 + count, 5);
                    continue;
                }
                else
                {
                    gotoxy(62, 28);
                    SetErrorColor();
                    cout << "                                                  ";
                    SetNormalColor();
                    foundVT = searchMaVT_DanhSachVatTu(ds_vt, inputMaVT);
                    gotoxy(96, 7);
                    cout << foundVT->tenVT;
                    gotoxy(96, 9);
                    cout << foundVT->dVT;
                    break;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputMaVT[--count] = '\0';
            }
            else if (ch == ESC)
            {
                gotoxy(62, 28);
                SetErrorColor();
                cout << "Quit";
                SetNormalColor();
                return;
            }
            else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
            {
                cout << ch;
                ch = tolower(ch);
                inputMaVT[count++] = ch;
            }
        }

        // foundVT = searchMaVT_DanhSachVatTu(ds_vt, inputMaVT);
        char inputTenVT[21];
        char inputDVT[11];
        count = 0;
        //
        drawRectangle(79, 12, 15, 2);
        drawRectangle(94, 12, 25, 2);
        gotoxy(94, 12);
        cout << char(194);
        gotoxy(81, 13);
        cout << "Ten VT(new)";
        //
        drawRectangle(79, 14, 15, 2);
        drawRectangle(94, 14, 25, 2);
        gotoxy(79, 14);
        cout << char(195);
        gotoxy(94, 14);
        cout << char(197);
        gotoxy(94, 16);
        cout << char(193);
        gotoxy(119, 14);
        cout << char(180);
        gotoxy(81, 15);
        cout << "DV Tinh(new)";
        //
        gotoxy(96, 13);
        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW)
                {
                    continue;
                }
                else if (ch == LEFT_ARROW)
                {
                    continue;
                }
            }
            else if (ch == 13 && count >= 0)
            {
                inputTenVT[count] = '\0';
                trim(inputTenVT);
                if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
                {
                    gotoxy(62, 28);
                    SetErrorColor();
                    cout << "Ten vat tu [" << inputTenVT << "] da ton tai" << endl;
                    SetNormalColor();
                    gotoxy(96 + count, 13);
                    continue;
                }
                else
                {
                    if (count == 0)
                    {
                        gotoxy(96, 13);
                        cout << foundVT->tenVT;
                        count = strlen(foundVT->tenVT);
                    }
                    SetErrorColor();
                    gotoxy(62, 28);
                    cout << "                                                  ";
                    SetNormalColor();
                    break;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputTenVT[--count] = '\0';
            }
            else if ((isalnum(ch) || ch == ' ') && count < 20)
            {
                cout << ch;
                ch = tolower(ch);
                inputTenVT[count++] = ch;
            }
            else if (ch == ESC)
            {
                gotoxy(62, 28);
                SetErrorColor();
                cout << "Quit";
                SetNormalColor();
                return;
            }
        }
        //
        count = 0;
        //
        gotoxy(96, 15);
        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW)
                {
                    continue;
                }
                else if (ch == LEFT_ARROW)
                {
                    continue;
                }
            }
            else if (ch == 13 && count >= 0)
            {
                inputDVT[count] = '\0';
                trim(inputDVT);
                if (count == 0)
                {
                    gotoxy(96, 15);
                    cout << foundVT->dVT;
                    count = strlen(foundVT->dVT);
                }
                break;
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputDVT[--count] = '\0';
            }
            else if ((isalnum(ch) || ch == ' ') && count < 10)
            {
                cout << ch;
                ch = tolower(ch);
                inputDVT[count++] = ch;
            }
            else if (ch == ESC)
            {
                gotoxy(62, 28);
                cout << "Quit";
                return;
            }
        }
        cout << endl;

        if (strlen(inputTenVT) == 0)
        {
            strcpy(inputTenVT, foundVT->tenVT);
        }

        if (strlen(inputDVT) == 0)
        {
            strcpy(inputDVT, foundVT->dVT);
        }

        int inputSoLuongTon = foundVT->soLuongTon;
        removeFromDanhSachVatTu(foundVT->tenVT, ds_vt);
        SoLuongVatTuGlobalCount--;
        insertDanhSachVatTu(ds_vt, newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon));
        gotoxy(62, 28);
        SetErrorColor();
        cout << "Successful";
        SetNormalColor();

        // Kiem tra muon nhap tiep hay thoat
        gotoxy(1, 23);
        cout << "DO YOU WANT TO CONTINUE MODIFY VATTU (y: Continue, n: Exit)";
        while (true)
        {
            ch = getch();
            if (ch == 'y' || ch == 'Y')
            {
                Page = 1;
                arr2Size = 1;
                VatTuStack *PageStack = new VatTuStack[1];
                VatTu **firstPagePos = new VatTu *[1];
                char pageMaVTData[15][11];
                current_vt = ds_vt;
                vtStack.sp = -1;
                bodem = 0;
                max = 15;
                ptrY = 0;
                clrscr();
                break;
            }
            else if (ch == 'n' || ch == 'N')
            {
                return;
            }
        }
    };
}

void XoaVatTuDrawSupport()
{
    drawRectangle(79, 0, 40, 2);
    drawRectangle(79, 2, 40, 2);
    gotoxy(79, 2);
    cout << char(195);
    gotoxy(119, 2);
    cout << char(180);
    gotoxy(89, 1);
    SetColor(0xC);
    cout << "Xoa Thong Tin Vat Tu" << endl;
    SetColor(0xF);
    gotoxy(83, 3);
    cout << "Nhap ma vat tu cua vat tu can xoa";
    drawRectangle(79, 4, 15, 2);
    drawRectangle(94, 4, 25, 2);
    gotoxy(79, 4);
    cout << char(195);
    gotoxy(119, 4);
    cout << char(180);
    gotoxy(94, 4);
    cout << char(194);
    gotoxy(94, 6);
    cout << char(193);
    gotoxy(81, 5);
    cout << "Ma Vat Tu";
}

void XoaVatTu(DanhSachVatTu &ds_vt, int &soLuongVatTu)
{
    int Page = 1;
    int arr2Size = 1;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    char pageMaVTData[15][11];
    bool backToPrev = false;
    VatTu *current_vt = ds_vt;
    VatTuStack vtStack;
    int bodem = 0;
    int max = 15;
    int ptrY = 0;
    char inputMaVT[11];
    int count = 0;
    unsigned char ch;
    //
    while (true)
    {
        count = 0;
        DrawAnnouncementBoard();
        XoaVatTuDrawSupport();
        HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
        gotoxy(96, 5);
        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongVatTuGlobalCount)
                {

                    bodem = max;
                    max = max + 15;
                    Page++;
                    current_vt = current_vt->right;
                    clearShowVatTuBoard2();
                    HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
                    gotoxy(96 + count, 5);
                }
                else if (ch == LEFT_ARROW && Page > 1)
                {
                    Page--;
                    current_vt = nullptr;
                    vtStack = PageStack[Page - 1];
                    max -= 15;
                    bodem = max - 15;
                    clearShowVatTuBoard2();
                    HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount, Page, arr2Size, PageStack, firstPagePos, pageMaVTData, current_vt, vtStack, bodem, max, ptrY);
                    gotoxy(96 + count, 5);
                }
                else if (ch == DOWN_ARROW && ptrY < 14 - (max - bodem))
                {
                    gotoxy(0, 7 + ptrY);
                    cout << char(179) << " ";
                    ptrY += 1;
                    gotoxy(0, 7 + ptrY);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                    gotoxy(96 + count, 5);
                    continue;
                }
                else if (ch == UP_ARROW && ptrY > 0)
                {
                    gotoxy(0, 7 + ptrY);
                    cout << char(179) << " ";
                    ptrY -= 1;
                    gotoxy(0, 7 + ptrY);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                    gotoxy(96 + count, 5);
                    continue;
                }
            }
            else if (ch == '*')
            {
                gotoxy(96, 5);
                cout << pageMaVTData[ptrY];
                strcpy(inputMaVT, pageMaVTData[ptrY]);
                count = strlen(pageMaVTData[ptrY]);
                continue;
            }
            else if (count > 0 && ch == 13)
            {
                inputMaVT[count] = '\0';
                trim(inputMaVT);
                if (isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
                {
                    // last check
                    bool isDelete;
                    gotoxy(1, 23);
                    cout << "ARE YOU SURE YOU WANT TO DELETE " << inputMaVT << " (y: Delete, n: No)";
                    while (true)
                    {
                        ch = getch();
                        if (ch == 'y' || ch == 'Y')
                        {
                            isDelete = true;
                            break;
                        }
                        else if (ch == 'n' || ch == 'N')
                        {
                            isDelete = false;
                            break;
                        }
                    }
                    //
                    if (!isDelete)
                    {
                        gotoxy(1, 23);
                        cout << "                                                                                ";
                        gotoxy(62, 28);
                        SetErrorColor();
                        cout << "CANCELED" << endl;
                        SetNormalColor();
                        gotoxy(96 + count, 5);
                        continue;
                    }
                    //
                    VatTu *deletedVT = searchMaVT_DanhSachVatTu(ds_vt, inputMaVT);
                    removeFromDanhSachVatTu(deletedVT->tenVT, ds_vt);
                    soLuongVatTu--;
                    gotoxy(62, 28);
                    SetErrorColor();
                    cout << "                                                         ";
                    gotoxy(62, 28);
                    cout << "Removed " << inputMaVT << " from DanhSach";
                    SetNormalColor();
                    gotoxy(1, 23);
                    cout << "                                                                                ";
                    break;
                }
                else
                {
                    gotoxy(62, 28);
                    SetErrorColor();
                    cout << "Cay khong ton tai vat tu [" << inputMaVT << "]" << endl;
                    SetNormalColor();
                    gotoxy(96 + count, 5);
                    continue;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputMaVT[--count] = '\0';
            }
            else if (ch == ESC)
            {
                gotoxy(62, 28);
                cout << "Quit";
                return;
            }
            else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
            {
                cout << ch;
                ch = tolower(ch);
                inputMaVT[count++] = ch;
            }
        }

        // Kiem tra muon nhap tiep hay thoat
        gotoxy(1, 23);
        cout << "DO YOU WANT TO CONTINUE MODIFY VATTU (y: Continue, n: Exit)";
        while (true)
        {
            ch = getch();
            if (ch == 'y' || ch == 'Y')
            {
                Page = 1;
                arr2Size = 1;
                VatTuStack *PageStack = new VatTuStack[1];
                VatTu **firstPagePos = new VatTu *[1];
                char pageMaVTData[15][11];
                current_vt = ds_vt;
                vtStack.sp = -1;
                bodem = 0;
                max = 15;
                ptrY = 0;
                clrscr();
                break;
            }
            else if (ch == 'n' || ch == 'N')
            {
                return;
            }
        }
    };
};

// HIEN THI VAT TU
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void HienThiVatTu(DanhSachVatTu root, int SoLuongVatTu)
{
    DrawHienThiVatTuTable(root);
    unsigned char c;
    // dem trang va luu ptr vs stack tai vi tri day
    int Page = 1;
    int arr2Size = 1;
    bool backToPrv = false;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    //
    VatTu *current_vt = root;
    VatTuStack vtStack;
    // dem de gioi han so luong
    int count = 0;
    int max = 15;
    //
    clearShowVatTuBoard();
    while (current_vt != nullptr || !vtStack.isEmpty())
    {
        while (current_vt != nullptr)
        {
            vtStack.push(current_vt);
            current_vt = current_vt->left;
        }

        current_vt = vtStack.pop();

        if (Page == arr2Size && current_vt != nullptr)
        {
            PageStack[arr2Size - 1] = vtStack;
            PageStack[arr2Size - 1].push(current_vt);
            expandArray(PageStack, arr2Size, Page + 1);

            firstPagePos[arr2Size - 1] = current_vt;
            expandArray(firstPagePos, arr2Size, Page + 1);
            arr2Size += 1;
        }

        gotoxy(3, 22 - (max - count));
        cout << current_vt->maVT;
        gotoxy(18, 22 - (max - count));
        cout << current_vt->tenVT;
        gotoxy(71, 22 - (max - count));
        cout << current_vt->dVT;
        gotoxy(99, 22 - (max - count));
        cout << current_vt->soLuongTon;
        count++;

        if (count >= max || count > SoLuongVatTu - 1)
        {
            backToPrv = false;
            while (true)
            {
                c = getch();
                if (c == 224)
                {
                    c = getch();
                    if (c == RIGHT_ARROW && max < SoLuongVatTu)
                    {
                        count = max;
                        max = max + 15;
                        Page++;
                        clearShowVatTuBoard();
                        break;
                    }
                    else if (c == LEFT_ARROW && Page > 1)
                    {
                        backToPrv = true;
                        Page--;
                        current_vt = nullptr;
                        vtStack = PageStack[Page - 1];
                        max -= 15;
                        count = max - 15;
                        clearShowVatTuBoard();
                        break;
                    }
                }
                else if (c == ESC)
                {
                    delete[] PageStack;
                    delete[] firstPagePos;
                    PageStack = nullptr;
                    firstPagePos = nullptr;
                    return;
                }
            }
            if (backToPrv)
            {
                continue;
            }
        }

        current_vt = current_vt->right;
    }
}

// Cac ham xu ly trong NV

int GetSeccondUINhanVienInput(char &c2, int &choose2)
{
    while (true)
    {
        c2 = getch();
        switch (c2)
        {
        case DOWN_ARROW:
        {
            drawRectangle2(xUI2 - 1, yUINV2 + choose2 * 3, 37, 2);
            gotoxy(xUI2, yUINV2 + choose2 * 3 + 1);
            cout << seccondNhanVienUI[choose2];
            if (choose2 == seccondNhanVienItems - 1)
            {
                choose2 = 0;
            }
            else
            {
                choose2++;
            }
            SetHighLight();
            drawRectangle2(xUI2 - 1, yUINV2 + choose2 * 3, 37, 2);
            gotoxy(xUI2, yUINV2 + choose2 * 3 + 1);
            cout << seccondNhanVienUI[choose2];
            SetNormalColor();
            break;
        }
        case UP_ARROW:
        {
            drawRectangle2(xUI2 - 1, yUINV2 + choose2 * 3, 37, 2);
            gotoxy(xUI2, yUINV2 + choose2 * 3 + 1);
            cout << seccondNhanVienUI[choose2];
            if (choose2 == 0)
            {
                choose2 = seccondNhanVienItems - 1;
            }
            else
            {
                choose2--;
            }
            SetHighLight();
            drawRectangle2(xUI2 - 1, yUINV2 + choose2 * 3, 37, 2);
            gotoxy(xUI2, yUINV2 + choose2 * 3 + 1);
            cout << seccondNhanVienUI[choose2];
            SetNormalColor();
            break;
        }
        case ESC:
        {
            choose2 = -1;
            return -1;
        }
        case ENTER:
        {
            return choose2;
        }
        }
    }
};

void DrawIsAdministrative()
{
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 70, 2);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(70, 2);
    cout << char(180);
    gotoxy(24, 1);
    SetColor(0xC);
    cout << "Dang Nhap Vao Tai Khoan";
    SetColor(0xF);
    gotoxy(5, 3);
    cout << "Dien Thong Tin Tai Khoan Cua Ban De Co The Tiep Tuc Thao Tac";
    drawRectangle(0, 4, 15, 2);
    drawRectangle(15, 4, 55, 2);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(70, 4);
    cout << char(180);
    gotoxy(15, 4);
    cout << char(194);
    gotoxy(15, 6);
    cout << char(193);
    gotoxy(1, 5);
    cout << "Ten Tai Khoan";
}

void DrawIsAdministrativeGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "Button Guide";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(83, 5);
    cout << "Enter: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(82, 7);
    cout << "UP_ARROW: Show/Hide Password";
    drawRectangle(80, 8, 31, 2);
    gotoxy(87, 9);
    cout << "ESC: Exit Program";
    drawRectangle(80, 10, 31, 4);
    gotoxy(87, 12);
    SetColor(0x2);
    cout << "Login restriction";
    SetColor(0xF);
    ///
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
    gotoxy(80, 10);
    cout << char(195);
    gotoxy(111, 10);
    cout << char(180);
}

bool isAdminSupporter(char tk[], char mk[])
{
    if (strcmp(tk, TEN_TK_ADMIN) == 0 && strcmp(mk, MK_ADMIN) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isAdministrative()
{
    clrscr();
    DrawIsAdministrativeGuide();
    DrawIsAdministrative();
    //
    char tk[51];
    char mk[51];
    unsigned char ch;
    int count = 0;
    bool showPassword = false;
    gotoxy(18, 5);
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == ENTER && count > 0)
        {
            tk[count] = '\0';
            trim(tk);
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            tk[--count] = '\0';
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 50)
        {
            cout << ch;
            tk[count++] = ch;
        }
        else if (ch == ESC)
        {
            return false;
        }
    }
    cout << endl;
    //
    count = 0;
    drawRectangle(0, 6, 15, 2);
    drawRectangle(15, 6, 55, 2);
    gotoxy(0, 6);
    cout << char(195);
    gotoxy(15, 6);
    cout << char(197);
    gotoxy(70, 6);
    cout << char(180);
    gotoxy(15, 8);
    cout << char(193);
    //
    gotoxy(1, 7);
    cout << "Nhap mat khau";
    gotoxy(18, 7);
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            if (ch == UP_ARROW)
            {
                showPassword = !showPassword;
                if (showPassword)
                {
                    mk[count] = '\0';
                    gotoxy(18, 7);
                    cout << mk;
                }
                else
                {
                    mk[count] = '\0';
                    gotoxy(18, 7);
                    for (int i = 0; i < count; i++)
                    {
                        cout << '*';
                    }
                }
                continue;
            }
            continue;
        }
        else if (ch == ENTER && count > 0)
        {
            mk[count] = '\0';
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            mk[--count] = '\0';
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 50)
        {
            mk[count++] = ch;
            if (!showPassword)
            {
                cout << '*';
            }
            else
            {
                cout << ch;
            }
        }
        else if (ch == ESC)
        {
            return false;
        }
    }
    gotoxy(18, 0);
    // Xu li
    if (isAdminSupporter(tk, mk))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void VeGioiTinh(int choose)
{
    if (choose == 0)
    {
        SetHighLight();
        gotoxy(16, 9);
        cout << "|           Nam           |";
        SetNormalColor();
        gotoxy(44, 9);
        cout << "|           Nu           |";
    }
    else if (choose == 1)
    {
        gotoxy(16, 9);
        cout << "|           Nam           |";
        SetHighLight();
        gotoxy(44, 9);
        cout << "|           Nu           |";
        SetNormalColor();
    }
}

void DrawThemNhanVienContactGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "Button Guide";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "Enter: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "Esc: Stop Program";
    drawRectangle(80, 8, 31, 2);
    gotoxy(87, 9);
    cout << "-->: Move_Right";
    drawRectangle(80, 10, 31, 2);
    gotoxy(87, 11);
    cout << "<--: Move_Left";
    drawRectangle(80, 12, 31, 4);
    gotoxy(81, 13);
    SetColor(0x4);
    cout << "Please Enter Name As Instruct";
    SetColor(0xF);
    gotoxy(85, 14);
    cout << "Example: Nguyen Van A";
    gotoxy(83, 15);
    cout << "HoNV: Nguyen Van, TenNV: A";
    // drawRectangle(80, 16, 31, 2);
    // gotoxy(83, 17);

    // drawRectangle(80, 16, 31, 2);
    // gotoxy(81, 17);
    // cout << "So Luong Ton (Under 1 billion)";

    //
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
    gotoxy(80, 10);
    cout << char(195);
    gotoxy(111, 10);
    cout << char(180);
    gotoxy(80, 12);
    cout << char(195);
    gotoxy(111, 12);
    cout << char(180);
    // gotoxy(80, 16);
    // cout << char(195);
    // gotoxy(111, 16);
    // cout << char(180);
    // gotoxy(80, 16);
    // cout << char(195);
    // gotoxy(111, 16);
    // cout << char(180);
}

void ThemNhanVien(DanhSachNhanVien &ds_nv, int &soLuongNhanVienCount)
{
    unsigned char ch;
    char inputMaNV[11];
    char inputHoNV[21];
    int count = 0;
    //
    DrawThemNhanVienContactGuide();
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 15, 2);
    drawRectangle(15, 2, 55, 2);
    //
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(70, 2);
    cout << char(180);
    gotoxy(15, 2);
    cout << char(194);
    gotoxy(15, 4);
    cout << char(193);
    //
    gotoxy(26, 1);
    SetColor(0xC);
    cout << "Them Nhan Vien Moi" << endl;
    SetColor(0xF);
    gotoxy(2, 3);
    cout << "Ma Nhan Vien";
    gotoxy(17, 3);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == ESC)
        {
            gotoxy(0, 5);
            cout << "Quit";
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputMaNV[count] = '\0';
            trim(inputMaNV);
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputMaNV[--count] == '\0';
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            inputMaNV[count++] = ch;
        }
    }
    //
    drawRectangle(0, 4, 15, 2);
    drawRectangle(15, 4, 55, 2);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(70, 4);
    cout << char(180);
    gotoxy(15, 4);
    cout << char(197);
    gotoxy(15, 6);
    cout << char(193);
    gotoxy(2, 5);
    cout << "Ho Nhan Vien";
    count = 0;
    gotoxy(18, 5);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == ESC)
        {
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputHoNV[count] = '\0';
            trim(inputHoNV);
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputHoNV[--count] == '\0';
        }
        else if ((isalnum(ch) || ch == ' ') && count < 20)
        {
            inputHoNV[count++] = ch;
            cout << ch;
        }
    }

    //
    char inputTenNV[11];
    count = 0;
    drawRectangle(0, 6, 15, 2);
    drawRectangle(15, 6, 55, 2);
    gotoxy(0, 6);
    cout << char(195);
    gotoxy(70, 6);
    cout << char(180);
    gotoxy(15, 6);
    cout << char(197);
    gotoxy(15, 8);
    cout << char(193);
    //
    gotoxy(1, 7);
    cout << "Ten Nhan Vien";
    gotoxy(18, 7);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == ESC)
        {
            gotoxy(0, 9);
            cout << "Quit";
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputTenNV[count] = '\0';
            trim(inputTenNV);
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputTenNV[--count] == '\0';
        }
        else if (isalnum(ch) && count < 10)
        {
            inputTenNV[count++] = ch;
            cout << ch;
        }
    }
    //
    drawRectangle(0, 8, 15, 2);
    drawRectangle(15, 8, 55, 2);
    gotoxy(0, 8);
    cout << char(195);
    gotoxy(70, 8);
    cout << char(180);
    gotoxy(15, 8);
    cout << char(197);
    gotoxy(15, 10);
    cout << char(193);
    //
    gotoxy(3, 9);
    cout << "Gioi Tinh";
    Phai inputPhai;
    count = 0;
    //
    VeGioiTinh(count);
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            switch (ch)
            {
            case RIGHT_ARROW:
            {
                if (count == 0)
                {
                    count = 1;
                    VeGioiTinh(count);
                    continue;
                }
                break;
            }
            case LEFT_ARROW:
            {
                if (count == 1)
                {
                    count = 0;
                    VeGioiTinh(count);
                    continue;
                }
                break;
            }
            }
        }
        else if (ch == ESC)
        {
            gotoxy(0, 11);
            cout << "Quit";
            return;
        }
        else if (ch == ENTER)
        {
            if (count == 0)
            {
                inputPhai = nam;
            }
            else if (count == 1)
            {
                inputPhai = nu;
            }
            break;
        }
    }

    NhanVien *new_nv = newNhanVien(inputMaNV, inputHoNV, inputTenNV, inputPhai);
    insertNhanVienToDSNV(ds_nv, new_nv, soLuongNhanVienCount);
};

// hienthinhanvien
void clearNhanVienTable()
{
    for (int i = 0; i < 15; i++)
    {
        gotoxy(2, 7 + i);
        cout << "            ";
        gotoxy(16, 7 + i);
        cout << "                     ";
        gotoxy(41, 7 + i);
        cout << "              ";
        gotoxy(57, 7 + i);
        cout << "      ";
    }
}

void DrawHienThiNhanVienTable(DanhSachNhanVien ds_nv, int soLuongNhanVien)
{
    if (soLuongNhanVien == 0)
    {
        cout << "Danh Sach Dang Trong";
        gotoxy(18, 5);
    }
    else
    {
        //
        drawRectangle(0, 0, 63, 4);
        gotoxy(4, 2);
        SetColor(0xC);
        cout << "Bang Chi Tiet Danh Sach Nhan Vien" << endl;
        SetColor(0xF);
        drawRectangle(0, 4, 15, 2);
        gotoxy(2, 5);
        cout << "Ma Nhan Vien";
        drawRectangle(15, 4, 25, 2);
        gotoxy(27, 5);
        cout << "Ho";
        drawRectangle(40, 4, 16, 2);
        gotoxy(47, 5);
        cout << "Ten";
        drawRectangle(56, 4, 7, 2);
        gotoxy(58, 5);
        cout << "Phai";
        // Phan noi dung
        drawRectangle(0, 6, 15, 16);
        drawRectangle(15, 6, 25, 16);
        drawRectangle(40, 6, 16, 16);
        drawRectangle(56, 6, 7, 16);
        //
        gotoxy(0, 4);
        cout << char(195);
        gotoxy(15, 4);
        cout << char(194);
        gotoxy(40, 4);
        cout << char(194);
        gotoxy(56, 4);
        cout << char(194);
        gotoxy(63, 4);
        cout << char(180);
        gotoxy(0, 6);
        cout << char(195);
        gotoxy(15, 6);
        cout << char(197);
        gotoxy(40, 6);
        cout << char(197);
        gotoxy(56, 6);
        cout << char(197);
        gotoxy(63, 6);
        cout << char(180);
        gotoxy(15, 22);
        cout << char(193);
        gotoxy(40, 22);
        cout << char(193);
        gotoxy(56, 22);
        cout << char(193);
        /////////////////////////
    }
}

void DrawHienThiNhanVienTableGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "Button Guide";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(87, 5);
    cout << "Esc: Stop Program";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "-->: Next Page";
    drawRectangle(80, 8, 31, 2);
    gotoxy(88, 9);
    cout << "<--: Prev Page";

    //
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
}

void HienThiNhanVien(DanhSachNhanVien ds_nv, int SoLuongNhanVien)
{
    unsigned char ch;
    int pos = 0;
    int max = pos + 15;
    // gotoxy(2, 5);Ma NV
    // gotoxy(16, 5);Ho
    // gotoxy(41, 5);Ten
    // gotoxy(57, 5);Phai
    DrawHienThiNhanVienTable(ds_nv, SoLuongNhanVien);
    DrawHienThiNhanVienTableGuide();
    while (true)
    {
        for (int i = pos; i < SoLuongNhanVien && i < max; ++i)
        {
            gotoxy(2, 7 + (i - pos));
            cout << ds_nv[i]->maNV;
            gotoxy(16, 7 + (i - pos));
            cout << ds_nv[i]->ho;
            gotoxy(41, 7 + (i - pos));
            cout << ds_nv[i]->ten;
            gotoxy(57, 7 + (i - pos));
            cout << (ds_nv[i]->phai == nam ? "Nam" : "Nu");
        }

        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
                if (ch == RIGHT_ARROW && max < SoLuongNhanVien - 1)
                {
                    pos += 15;
                    max = pos + 15;
                    clearNhanVienTable();
                    break;
                }
                else if (ch == LEFT_ARROW && max > 15)
                {
                    max -= 15;
                    pos = max - 15;
                    clearNhanVienTable();
                    break;
                };
            }
            else if (ch == ESC)
            {
                return;
            }
        }
    }
}

// Phan Hoa Don

int GetSeccondUIHoaDonInput(char &c2, int &choose2)
{
    while (true)
    {
        c2 = getch();
        switch (c2)
        {
        case DOWN_ARROW:
        {
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 39, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondHoaDonUI[choose2];
            if (choose2 == seccondHoaDonItems - 1)
            {
                choose2 = 0;
            }
            else
            {
                choose2++;
            }
            SetHighLight();
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 39, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondHoaDonUI[choose2];
            SetNormalColor();
            break;
        }
        case UP_ARROW:
        {
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 39, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondHoaDonUI[choose2];
            if (choose2 == 0)
            {
                choose2 = seccondHoaDonItems - 1;
            }
            else
            {
                choose2--;
            }
            // duyendotroiphantaita

            SetHighLight();
            drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 39, 2);
            gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
            cout << seccondHoaDonUI[choose2];
            SetNormalColor();
            break;
        }
        case ESC:
        {
            choose2 = -1;
            return -1;
        }
        case ENTER:
        {
            return choose2;
        }
        }
    }
};

void DrawNhapHoaDon(LoaiHoaDon loai, const char maHoaDon[])
{
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 70, 2);
    drawRectangle(0, 4, 15, 2);
    drawRectangle(15, 4, 55, 2);
    //
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(70, 2);
    cout << char(180);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(15, 4);
    cout << char(194);
    gotoxy(15, 6);
    cout << char(193);
    gotoxy(70, 4);
    cout << char(180);
    //

    gotoxy(10, 1);
    SetColor(0xC);
    cout << "Vui Long Nhap Nhung Thong Tin Can Thiet Cho Hoa Don";
    SetColor(0xF);
    gotoxy(25, 3);
    cout << "Loai Hoa Don: ";
    if (loai == n)
    {
        cout << "Nhap";
    }
    else
    {
        cout << "Xuat";
    }
}

bool isNamNhuan(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

void SetDateHighLightColor()
{
    SetBGColor(0xA);
    SetColor(0x0);
}

void cout2ChuSo(int x)
{
    if (x < 10)
    {
        cout << "0" << x;
    }
    else if (x <= 31)
    {
        cout << x;
    }
}

void dateChooseTable(Date &date)
{
    unsigned char ch;
    int posX = 73; // max 92
    int posY = 5;  // max 10
    date.day = 1;
    date.month = 1;
    date.year = 2024;
    drawRectangle(72, 0, 21, 2);
    gotoxy(73, 1);
    cout << "<       2024       >";
    drawRectangle(72, 2, 21, 2);
    gotoxy(73, 3);
    cout << "<     Thang 01     >";
    drawRectangle(72, 4, 21, 6);
    gotoxy(72, 2);
    cout << char(195);
    gotoxy(93, 2);
    cout << char(180);
    gotoxy(72, 4);
    cout << char(195);
    gotoxy(93, 4);
    cout << char(180);
    for (int ix = 75; ix < 93; ix += 3)
    {
        gotoxy(ix, 4);
        cout << char(194);
        gotoxy(ix, 5);
        cout << char(179);
        gotoxy(ix, 6);
        cout << char(179);
        gotoxy(ix, 7);
        cout << char(179);
        gotoxy(ix, 8);
        cout << char(179);
        gotoxy(ix, 9);
        cout << char(179);
        gotoxy(ix, 10);
        cout << char(193);
    }

    for (int iy = 5; iy < 11; iy++)
    {
        for (int ix = 73; ix < 93; ix += 3)
        {
            gotoxy(ix, iy);
            if (date.day < 10)
            {
                cout << "0" << date.day;
                date.day++;
            }
            else if (date.day <= 31)
            {
                cout << date.day;
                date.day++;
            }
            else
            {
                continue;
            }
        }
    }

    //
    date.day = 1;
    SetDateHighLightColor();
    gotoxy(posX, posY);
    // in so 2 chu so
    cout2ChuSo(date.day);
    SetNormalColor();

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            if (ch == RIGHT_ARROW && posX < 91 && date.day + 1 <= 31)
            {
                SetNormalColor();
                gotoxy(posX, posY);
                cout2ChuSo(date.day++);
                SetDateHighLightColor();
                posX += 3;
                gotoxy(posX, posY);
                cout2ChuSo(date.day);
                SetNormalColor();
            }
            else if (ch == LEFT_ARROW && posX > 75)
            {
                SetNormalColor();
                gotoxy(posX, posY);
                cout2ChuSo(date.day--);
                SetDateHighLightColor();
                posX -= 3;
                gotoxy(posX, posY);
                cout2ChuSo(date.day);
                SetNormalColor();
            }
            else if (ch == DOWN_ARROW && posY < 9 && date.day + 7 <= 31)
            {
                SetNormalColor();
                gotoxy(posX, posY);
                cout2ChuSo(date.day);
                date.day += 7;
                SetDateHighLightColor();
                posY += 1;
                gotoxy(posX, posY);
                cout2ChuSo(date.day);
                SetNormalColor();
            }
            else if (ch == UP_ARROW && posY > 5)
            {
                SetNormalColor();
                gotoxy(posX, posY);
                cout2ChuSo(date.day);
                date.day -= 7;
                SetDateHighLightColor();
                posY -= 1;
                gotoxy(posX, posY);
                cout2ChuSo(date.day);
                SetNormalColor();
            }
        }
        else if (ch == ENTER)
        {
            gotoxy(20, 20);
            cout2ChuSo(date.day);
        }
    }
    return;
}

bool isValidDoule(const char input[])
{
    int dot_count = 0;
    int len = strlen(input);

    for (int i = 0; i < len; ++i)
    {
        if (input[i] == '.')
        {
            dot_count++;
            if (dot_count > 1)
            {
                return false;
            }
        }
    }
    return dot_count == 1 || dot_count == 0;
}

void drawCT_HoaDonUI(int choose)
{
    //  for (int iy = 0; iy < seccondVatTuItems; iy++)
    // {
    //     drawRectangle2(xUI2 - 1, yUI2 + iy * 3, 38, 2);
    //     gotoxy(xUI2, yUI2 + iy * 3 + 1);
    //     cout << seccondVatTuUI[iy];
    // }
    // SetHighLight();
    // drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
    // gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
    // cout << seccondVatTuUI[choose2];
    // SetNormalColor();

    for (int i = 0; i < thirdHoaDonItems; i++)
    {
        drawRectangle2(0, 10 + i * 3, 44, 2);
        gotoxy(1, 10 + i * 3 + 1);
        cout << thirdHoaDonUI[i];
    }

    // SetHighLight();
    // drawRectangle2(xUI2 - 1, yUI2 + choose2 * 3, 38, 2);
    // gotoxy(xUI2, yUI2 + choose2 * 3 + 1);
    // cout << seccondVatTuUI[choose2];
    // SetNormalColor();
    SetHighLight();
    drawRectangle2(0, 10 + choose * 3, 44, 2);
    gotoxy(1, 10 + choose * 3 + 1);
    cout << thirdHoaDonUI[choose];
    SetNormalColor();
}

void clearBottomScreen()
{
    for (int y = 10; y < 30; y++)
    {
        gotoxy(0, y);
        cout << "                                                                       ";
    }
}

// CHI TIET HOA DON

void DrawHoaDonContactGuide()
{
    drawRectangle(80, 0, 31, 4);
    gotoxy(90, 2);
    SetColor(0x2);
    cout << "Button Guide";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "Enter: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "Esc: Stop Program";
    drawRectangle(80, 8, 31, 2);
    gotoxy(83, 9);
    SetColor(0x2);
    cout << "TAB: Back To Previous Part";
    SetColor(0xF);
    drawRectangle(80, 10, 31, 2);
    gotoxy(86, 11);
    cout << "UP_Arrow: Move Up";
    drawRectangle(80, 12, 31, 2);
    gotoxy(86, 13);
    cout << "DOWN_Arrow: Move Down";
    drawRectangle(80, 14, 31, 2);
    gotoxy(81, 15);
    cout << "NONE";

    //
    gotoxy(80, 4);
    cout << char(195);
    gotoxy(111, 4);
    cout << char(180);
    gotoxy(80, 6);
    cout << char(195);
    gotoxy(111, 6);
    cout << char(180);
    gotoxy(80, 8);
    cout << char(195);
    gotoxy(111, 8);
    cout << char(180);
    gotoxy(80, 10);
    cout << char(195);
    gotoxy(111, 10);
    cout << char(180);
    gotoxy(80, 12);
    cout << char(195);
    gotoxy(111, 12);
    cout << char(180);
    gotoxy(80, 14);
    cout << char(195);
    gotoxy(111, 14);
    cout << char(180);
}

void themChiTietHoaDonNhap(HoaDon *&hoadon, DanhSachVatTu &ds_vt)
{
    DanhSach_CT_HoaDon new_ct_hd = new CT_HoaDon;
    unsigned char ch;
    int count = 0;
    //
    drawRectangle(0, 10, 70, 2);
    gotoxy(25, 11);
    SetColor(0x4);
    cout << "Them Chi Tiet Hoa Don";
    SetColor(0xF);
    drawRectangle(0, 12, 15, 2);
    drawRectangle(15, 12, 55, 2);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(15, 12);
    cout << char(194);
    gotoxy(15, 14);
    cout << char(193);
    gotoxy(70, 12);
    cout << char(180);
    //
    gotoxy(3, 13);
    cout << "Ma Vat Tu";
    gotoxy(18, 13);

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            gotoxy(0, 15);
            cout << "Quit";
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            new_ct_hd->maVT[count] = '\0';
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            new_ct_hd->maVT[--count] = '\0';
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            new_ct_hd->maVT[count++] = ch;
        }
    }
    //
    drawRectangle(0, 14, 15, 2);
    drawRectangle(15, 14, 55, 2);
    gotoxy(0, 14);
    cout << char(195);
    gotoxy(15, 14);
    //
    cout << char(197);
    gotoxy(15, 16);
    cout << char(193);
    gotoxy(70, 14);
    cout << char(180);
    //
    char inputSoLuong[10];
    gotoxy(4, 15);
    cout << "So Luong";
    count = 0;
    gotoxy(18, 15);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            gotoxy(0, 17);
            cout << "Quit";
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputSoLuong[count] = '\0';
            new_ct_hd->soLuong = stoi(inputSoLuong);
            VatTu *vatTu = searchMaVT_DanhSachVatTu(ds_vt, new_ct_hd->maVT);

            if (vatTu == nullptr)
            {
                break;
            }

            if (vatTu->soLuongTon + new_ct_hd->soLuong <= 999999999)
            {
                gotoxy(0, 17);
                cout << "                                                 ";
                break;
            }
            else
            {
                gotoxy(0, 17);
                cout << "So Luong Vuot Qua Suc Chua Cua Kho (<999,999,999)";
                gotoxy(18 + count, 15);
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputSoLuong[--count] = '\0';
        }
        else if (isdigit(ch) && count < 9)
        {
            inputSoLuong[count++] = ch;
            cout << ch;
        }
    }

    //
    drawRectangle(0, 16, 15, 2);
    drawRectangle(15, 16, 55, 2);
    gotoxy(0, 16);
    cout << char(195);
    gotoxy(15, 16);
    //
    cout << char(197);
    gotoxy(15, 18);
    cout << char(193);
    gotoxy(70, 16);
    cout << char(180);
    //
    char inputdonGia[16];
    count = 0;
    //
    gotoxy(4, 17);
    cout << "Don Gia";
    gotoxy(18, 17);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ENTER && count > 0)
        {
            inputdonGia[count] = '\0';

            if (isValidDoule(inputdonGia))
            {
                gotoxy(0, 19);
                cout << "                                                      ";
                new_ct_hd->donGia = stod(inputdonGia);
                break;
            }
            else
            {
                gotoxy(0, 19);
                cout << "Don Gia Khong Hop Le (Chi dung 1 dau '.' de phan cach)";
                gotoxy(18 + count, 17);
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputdonGia[--count] = '\0';
            continue;
        }
        else if ((isdigit(ch) || ch == '.') && count < 15)
        {
            cout << ch;
            inputdonGia[count++] = ch;
            continue;
        }
    }
    //

    drawRectangle(0, 18, 15, 2);
    drawRectangle(15, 18, 55, 2);
    gotoxy(0, 18);
    cout << char(195);
    gotoxy(15, 18);
    //
    cout << char(197);
    gotoxy(15, 20);
    cout << char(193);
    gotoxy(70, 18);
    cout << char(180);
    //
    char inputVAT[16];
    count = 0;
    //
    gotoxy(4, 19);
    cout << "VAT (%)";
    gotoxy(18, 19);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ENTER && count > 0)
        {
            inputVAT[count] = '\0';
            if (isValidDoule(inputVAT))
            {
                gotoxy(0, 21);
                cout << "                                                      ";
                new_ct_hd->vAT = stod(inputVAT);
                break;
            }
            else
            {
                gotoxy(0, 21);
                cout << "VAT Khong Hop Le (Chi dung 1 dau '.' de phan cach)";
                gotoxy(18 + count, 19);
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputVAT[--count] = '\0';
            continue;
        }
        else if ((isdigit(ch) || ch == '.') && count < 15)
        {
            cout << ch;
            inputVAT[count++] = ch;
            continue;
        }
    }

    CT_HoaDon *current = hoadon->ds_ct_hoadon;
    if (current == nullptr)
    {
        Them_CTHD_CanMultipleVariable(hoadon->ds_ct_hoadon, new_ct_hd);
        return;
    }

    while (current != nullptr)
    {
        if ((strcmp(current->maVT, new_ct_hd->maVT) == 0) && new_ct_hd->donGia == current->donGia && new_ct_hd->vAT == current->vAT)
        {
            current->soLuong += new_ct_hd->soLuong;
            return;
        }
        current = current->next;
    }

    Them_CTHD_CanMultipleVariable(hoadon->ds_ct_hoadon, new_ct_hd);
    return;
}

void themChiTietHoaDonXuat(HoaDon *&hoadon, DanhSachVatTu &ds_vt)
{
    DanhSach_CT_HoaDon new_ct_hd = new CT_HoaDon;
    unsigned char ch;
    int count = 0;
    //
    drawRectangle(0, 10, 70, 2);
    gotoxy(25, 11);
    SetColor(0x4);
    cout << "Them Chi Tiet Hoa Don";
    SetColor(0xF);
    drawRectangle(0, 12, 15, 2);
    drawRectangle(15, 12, 55, 2);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(15, 12);
    cout << char(194);
    gotoxy(15, 14);
    cout << char(193);
    gotoxy(70, 12);
    cout << char(180);
    //
    gotoxy(3, 13);
    cout << "Ma Vat Tu";
    gotoxy(18, 13);

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            gotoxy(0, 15);
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            new_ct_hd->maVT[count] = '\0';
            if (!isContainMaVT_DanhSachVatTu(ds_vt, new_ct_hd->maVT))
            {
                gotoxy(2, 15);
                cout << "Khong Ton Tai MaVT Nay Nen Khong The Xuat HD";
                gotoxy(18 + count, 13);
                continue;
            }
            else
            {
                gotoxy(2, 15);
                cout << "                                             ";
                break;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            new_ct_hd->maVT[--count] = '\0';
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            new_ct_hd->maVT[count++] = ch;
        }
    }
    //
    drawRectangle(0, 14, 15, 2);
    drawRectangle(15, 14, 55, 2);
    gotoxy(0, 14);
    cout << char(195);
    gotoxy(15, 14);
    //
    cout << char(197);
    gotoxy(15, 16);
    cout << char(193);
    gotoxy(70, 14);
    cout << char(180);
    //
    VatTu *foundVT = searchMaVT_DanhSachVatTu(ds_vt, new_ct_hd->maVT);
    bool isTonTai = false;
    if (KiemTraMaVT_CTHD(hoadon->ds_ct_hoadon, new_ct_hd->maVT))
    {
        isTonTai = true;
    }
    char inputSoLuong[10];
    //
    gotoxy(4, 15);
    cout << "So Luong";
    count = 0;
    gotoxy(18, 15);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            gotoxy(0, 17);
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputSoLuong[count] = '\0';
            new_ct_hd->soLuong = stoi(inputSoLuong);

            if (new_ct_hd->soLuong == 0)
            {
                gotoxy(0, 17);
                cout << "So luong khong the la 0";
                gotoxy(18 + count, 15);
                continue;
            }

            if (isTonTai == true)
            {
                CT_HoaDon *current = hoadon->ds_ct_hoadon;

                if (current == nullptr)
                {
                    break;
                }
                int soLuongDaCo = 0;
                while (current != nullptr)
                {
                    if (strcmp(current->maVT, new_ct_hd->maVT) == 0)
                    {
                        soLuongDaCo += current->soLuong;
                    }
                    current = current->next;
                }

                if (soLuongDaCo + new_ct_hd->soLuong <= foundVT->soLuongTon)
                {
                    gotoxy(0, 17);
                    cout << "                                      ";
                    gotoxy(0, 18);
                    cout << "                                                                      ";
                    break;
                }
                else
                {
                    gotoxy(0, 17);
                    cout << "                                      ";
                    gotoxy(0, 17);
                    cout << "Khong du so luong de xuat";
                    gotoxy(0, 18);
                    cout << "So Luong con lai co the xuat cua " << new_ct_hd->maVT << " la: " << foundVT->soLuongTon - soLuongDaCo;
                    gotoxy(18 + count, 15);
                    continue;
                }
            }
            else if (foundVT->soLuongTon < new_ct_hd->soLuong && isTonTai == false)
            {
                gotoxy(0, 17);
                cout << "Khong du so luong de xuat";
                gotoxy(0, 18);
                cout << "So Luong hien tai trong kho cua " << new_ct_hd->maVT << " la: " << foundVT->soLuongTon;
                gotoxy(18 + count, 15);
                continue;
            }
            else
            {
                gotoxy(0, 17);
                cout << "                              ";
                gotoxy(0, 18);
                cout << "                                                                      ";
                break;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputSoLuong[--count] = '\0';
        }
        else if (isdigit(ch) && count < 9)
        {
            inputSoLuong[count++] = ch;
            cout << ch;
        }
    }

    //
    drawRectangle(0, 16, 15, 2);
    drawRectangle(15, 16, 55, 2);
    gotoxy(0, 16);
    cout << char(195);
    gotoxy(15, 16);
    //
    cout << char(197);
    gotoxy(15, 18);
    cout << char(193);
    gotoxy(70, 16);
    cout << char(180);
    //
    char inputdonGia[16];
    count = 0;
    //
    gotoxy(4, 17);
    cout << "Don Gia";
    gotoxy(18, 17);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ENTER && count > 0)
        {
            inputdonGia[count] = '\0';

            if (isValidDoule(inputdonGia))
            {
                gotoxy(0, 19);
                cout << "                                                      ";
                new_ct_hd->donGia = stod(inputdonGia);
                break;
            }
            else
            {
                gotoxy(0, 19);
                cout << "Don Gia Khong Hop Le (Chi dung 1 dau '.' de phan cach)";
                gotoxy(18 + count, 17);
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputdonGia[--count] = '\0';
            continue;
        }
        else if ((isdigit(ch) || ch == '.') && count < 15)
        {
            cout << ch;
            inputdonGia[count++] = ch;
            continue;
        }
    }
    //

    drawRectangle(0, 18, 15, 2);
    drawRectangle(15, 18, 55, 2);
    gotoxy(0, 18);
    cout << char(195);
    gotoxy(15, 18);
    //
    cout << char(197);
    gotoxy(15, 20);
    cout << char(193);
    gotoxy(70, 18);
    cout << char(180);
    //
    char inputVAT[16];
    count = 0;
    //
    gotoxy(4, 19);
    cout << "VAT (%)";
    gotoxy(18, 19);
    //
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ENTER && count > 0)
        {
            inputVAT[count] = '\0';
            if (isValidDoule(inputVAT))
            {
                gotoxy(0, 21);
                cout << "                                                      ";
                new_ct_hd->vAT = stod(inputVAT);
                break;
            }
            else
            {
                gotoxy(0, 21);
                cout << "VAT Khong Hop Le (Chi dung 1 dau '.' de phan cach)";
                gotoxy(18 + count, 19);
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputVAT[--count] = '\0';
            continue;
        }
        else if ((isdigit(ch) || ch == '.') && count < 15)
        {
            cout << ch;
            inputVAT[count++] = ch;
            continue;
        }
    }
    //
    // Kiem rta trung lap de don 2 thanh 1
    CT_HoaDon *current = hoadon->ds_ct_hoadon;
    if (current == nullptr)
    {
        Them_CTHD_CanMultipleVariable(hoadon->ds_ct_hoadon, new_ct_hd);
        return;
    }

    while (current != nullptr)
    {
        if ((strcmp(current->maVT, new_ct_hd->maVT) == 0) && new_ct_hd->donGia == current->donGia && new_ct_hd->vAT == current->vAT)
        {
            current->soLuong += new_ct_hd->soLuong;
            return;
        }
        current = current->next;
    }

    Them_CTHD_CanMultipleVariable(hoadon->ds_ct_hoadon, new_ct_hd);
    return;
}

bool isNhanVien(DanhSachNhanVien ds_nv, char inputMaNV[11], int soLuongNhanVien)
{
    clrscr();
    drawRectangle(0, 0, 70, 2);
    gotoxy(3, 1);
    cout << "Nhap Ma Nhan Vien Cua Ban De Co The Thuc Hien Chuc Nang Nay";
    drawRectangle(0, 2, 15, 2);
    gotoxy(2, 3);
    cout << "Ma Nhan Vien";
    drawRectangle(15, 2, 55, 2);
    //
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(15, 2);
    cout << char(194);
    gotoxy(70, 2);
    cout << char(180);
    gotoxy(15, 4);
    cout << char(193);
    //
    int counter = 0;
    gotoxy(18, 3);
    unsigned char ch;
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            gotoxy(0, 5);
            cout << "Quit";
            Sleep(2000);
            return false;
        }
        else if (ch == ENTER && counter > 0)
        {
            inputMaNV[counter] = '\0';
            if (isNhanVienInDSNV(ds_nv, inputMaNV, soLuongNhanVien))
            {
                clrscr();
                return true;
            }
            else
            {
                gotoxy(1, 5);
                cout << "Ma Nhan Vien Khong Ton Tai Ban Muon Nhap Lai Hay Dung Tai Day(y/n): ";
                while (true)
                {
                    ch = getch();
                    if (ch == 'y' || ch == 'Y')
                    {
                        gotoxy(1, 5);
                        cout << "                                                                       ";
                        counter = 0;
                        gotoxy(18, 3);
                        cout << "          ";
                        gotoxy(18, 3);
                        break;
                    }
                    else if (ch == 'n' || ch == 'N')
                    {
                        return false;
                    }
                }
                continue;
            }
        }
        else if (ch == '\b' && counter > 0)
        {
            inputMaNV[--counter] = '\0';
            cout << "\b \b";
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && counter < 10)
        {
            cout << ch;
            ch = tolower(ch);
            inputMaNV[counter++] = ch;
        }
    }
    return false;
};

void ClearCTHDTable()
{
    for (int i = 0; i < 10; i++)
    {
        gotoxy(1, 15 + i);
        cout << "              ";
        gotoxy(16, 15 + i);
        cout << "              ";
        gotoxy(31, 15 + i);
        cout << "              ";
        gotoxy(46, 15 + i);
        cout << "              ";
    }
}

bool QuickChooseXoaCTHD(DanhSachHoaDon ds_hd, char inputMaVT[11], int &soKyTu)
{
    // Khai bao bien can
    unsigned char ch;
    int count = 0;
    int max = count + 10;
    int ptrY = 0;
    // VatTu **firstPagePos = new VatTu *[1];
    CT_HoaDon **firstPageEl = new CT_HoaDon *[1];
    CT_HoaDon **PageEl = new CT_HoaDon *[10];
    int page = 1;
    int size = 1;
    CT_HoaDon *current = ds_hd->ds_ct_hoadon;
    //
    drawRectangle(0, 10, 30, 2);
    drawRectangle(0, 12, 15, 2);
    drawRectangle(15, 12, 15, 2);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(30, 12);
    cout << char(180);
    gotoxy(15, 12);
    cout << char(194);
    gotoxy(15, 14);
    cout << char(193);
    //
    gotoxy(7, 11);
    cout << "Chon MaVT can xoa";
    gotoxy(2, 13);
    cout << "Ma Vat Tu";
    gotoxy(18, 13);
    cout << "So Luong";
    //
    drawRectangle(0, 14, 15, 11);
    drawRectangle(15, 14, 15, 11);
    gotoxy(0, 14);
    cout << char(195);
    gotoxy(30, 14);
    cout << char(180);
    gotoxy(15, 14);
    cout << char(197);
    gotoxy(15, 25);
    cout << char(193);
    //
    if (current == nullptr)
    {
        return false;
    }

    while ((count < max) && current != nullptr)
    {
        gotoxy(2, 25 - (max - count));
        cout << current->maVT;
        gotoxy(18, 25 - (max - count));
        cout << current->soLuong;

        if ((max - count) == 10 && size == page)
        {
            firstPageEl[size - 1] = current;
            expandArray(firstPageEl, size, size + 1);
            size++;
        }

        PageEl[10 - (max - count)] = current;
        //
        current = current->next;
        count += 1;

        if (count == max || current == nullptr)
        {
            gotoxy(0, 15 + ptrY);
            SetColor(0x4);
            cout << "->";
            SetColor(0xF);
            while (true)
            {
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();
                    if (ch == UP_ARROW && ptrY > 0)
                    {
                        gotoxy(0, 15 + ptrY);
                        cout << char(179) << " ";
                        ptrY -= 1;
                        SetColor(0x4);
                        gotoxy(0, 15 + ptrY);
                        cout << "->";
                        SetColor(0xF);
                        continue;
                    }
                    else if (ch == DOWN_ARROW && ptrY < (9 - (max - count)))
                    {
                        gotoxy(0, 15 + ptrY);
                        cout << char(179) << " ";
                        ptrY += 1;
                        SetColor(0x4);
                        gotoxy(0, 15 + ptrY);
                        cout << "->";
                        SetColor(0xF);
                        continue;
                    }
                    else if (ch == RIGHT_ARROW && current != nullptr)
                    {
                        count = max;
                        max = count + 10;
                        page++;
                        ClearCTHDTable();
                        break;
                    }
                    else if (ch == LEFT_ARROW && count > 10)
                    {
                        max = max - 10;
                        count = max - 10;
                        page--;
                        current = firstPageEl[page - 1];
                        ClearCTHDTable();
                        break;
                    }
                }
                else if (ch == ESC)
                {
                    return false;
                }
                else if (ch == ENTER && ptrY < (10 - (max - count)))
                {
                    strcpy(inputMaVT, PageEl[ptrY]->maVT);
                    soKyTu = strlen(inputMaVT);
                    return true;
                }
            }
        }
    }
    return false;
}

bool QuickChooseXoaCTHD_2(DanhSachHoaDon ds_hd, int &soKyTu, CT_HoaDon *&ct_canxoa)
{
    // Khai bao bien can
    unsigned char ch;
    int count = 0;
    int max = count + 10;
    int ptrY = 0;
    // VatTu **firstPagePos = new VatTu *[1];
    CT_HoaDon **firstPageEl = new CT_HoaDon *[1];
    CT_HoaDon **PageEl = new CT_HoaDon *[10];
    int page = 1;
    int size = 1;
    CT_HoaDon *current = ds_hd->ds_ct_hoadon;
    //
    drawRectangle(0, 10, 60, 2);
    drawRectangle(0, 12, 15, 2);
    drawRectangle(15, 12, 15, 2);
    drawRectangle(30, 12, 15, 2);
    drawRectangle(45, 12, 15, 2);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(15, 12);
    cout << char(194);
    gotoxy(15, 14);
    cout << char(193);
    gotoxy(30, 12);
    cout << char(194);
    gotoxy(30, 14);
    cout << char(193);
    gotoxy(45, 12);
    cout << char(194);
    gotoxy(45, 14);
    cout << char(193);
    gotoxy(60, 12);
    cout << char(180);
    //
    gotoxy(7, 11);
    cout << "Chon MaVT can xoa";
    gotoxy(2, 13);
    cout << "Ma Vat Tu";
    gotoxy(18, 13);
    cout << "So Luong";
    gotoxy(32, 13);
    cout << "Don Gia";
    gotoxy(47, 13);
    cout << "Vat";
    //
    drawRectangle(0, 14, 15, 11);
    drawRectangle(15, 14, 15, 11);
    drawRectangle(30, 14, 15, 11);
    drawRectangle(45, 14, 15, 11);
    gotoxy(0, 14);
    cout << char(195);
    gotoxy(15, 14);
    cout << char(197);
    gotoxy(15, 25);
    cout << char(193);
    gotoxy(30, 14);
    cout << char(197);
    gotoxy(30, 25);
    cout << char(193);
    gotoxy(45, 14);
    cout << char(197);
    gotoxy(45, 25);
    cout << char(193);
    gotoxy(60, 14);
    cout << char(180);
    //
    if (current == nullptr)
    {
        return false;
    }

    while ((count < max) && current != nullptr)
    {
        gotoxy(2, 25 - (max - count));
        cout << current->maVT;
        gotoxy(18, 25 - (max - count));
        cout << current->soLuong;
        gotoxy(32, 25 - (max - count));
        cout << fixed << setprecision(2) << current->donGia;
        gotoxy(47, 25 - (max - count));
        cout << fixed << setprecision(2) << current->vAT;

        if ((max - count) == 10 && page == size)
        {
            firstPageEl[size - 1] = current;
            expandArray(firstPageEl, size, size + 1);
            size++;
        }

        PageEl[10 - (max - count)] = current;
        //
        current = current->next;
        count += 1;

        if (count == max || current == nullptr)
        {
            gotoxy(0, 15 + ptrY);
            SetColor(0x4);
            cout << "->";
            SetColor(0xF);
            while (true)
            {
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();
                    if (ch == UP_ARROW && ptrY > 0)
                    {
                        gotoxy(0, 15 + ptrY);
                        cout << char(179) << " ";
                        ptrY -= 1;
                        SetColor(0x4);
                        gotoxy(0, 15 + ptrY);
                        cout << "->";
                        SetColor(0xF);
                        continue;
                    }
                    else if (ch == DOWN_ARROW && ptrY < (9 - (max - count)))
                    {
                        gotoxy(0, 15 + ptrY);
                        cout << char(179) << " ";
                        ptrY += 1;
                        SetColor(0x4);
                        gotoxy(0, 15 + ptrY);
                        cout << "->";
                        SetColor(0xF);
                        continue;
                    }
                    else if (ch == RIGHT_ARROW && current != nullptr)
                    {
                        count = max;
                        max = count + 10;
                        page++;
                        ClearCTHDTable();
                        break;
                    }
                    else if (ch == LEFT_ARROW && count > 10)
                    {
                        max = max - 10;
                        count = max - 10;
                        page--;
                        current = firstPageEl[page - 1];
                        ClearCTHDTable();
                        break;
                    }
                }
                else if (ch == ESC || ch == '*')
                {
                    return false;
                }
                else if (ch == ENTER && ptrY < (10 - (max - count)))
                {
                    ct_canxoa = PageEl[ptrY];
                    soKyTu = strlen(ct_canxoa->maVT);
                    return true;
                }
            }
        }
    }
    return false;
}

void XemThongTinCTVT(DanhSachHoaDon ds_hd)
{
    // Khai bao bien can
    unsigned char ch;
    int count = 0;
    int max = count + 10;
    // VatTu **firstPagePos = new VatTu *[1];
    CT_HoaDon **firstPageEl = new CT_HoaDon *[1];
    int page = 1;
    int size = 1;
    CT_HoaDon *current = ds_hd->ds_ct_hoadon;
    //
    drawRectangle(0, 10, 30, 2);
    drawRectangle(0, 12, 15, 2);
    drawRectangle(15, 12, 15, 2);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(30, 12);
    cout << char(180);
    gotoxy(15, 12);
    cout << char(194);
    gotoxy(15, 14);
    cout << char(193);
    //
    gotoxy(7, 11);
    cout << "Xem Thong Tin";
    gotoxy(2, 13);
    cout << "Ma Vat Tu";
    gotoxy(18, 13);
    cout << "So Luong";
    //
    drawRectangle(0, 14, 15, 11);
    drawRectangle(15, 14, 15, 11);
    gotoxy(0, 14);
    cout << char(195);
    gotoxy(30, 14);
    cout << char(180);
    gotoxy(15, 14);
    cout << char(197);
    gotoxy(15, 25);
    cout << char(193);
    //
    if (current == nullptr)
    {
        return;
    }

    while ((count < max) && current != nullptr)
    {
        gotoxy(2, 25 - (max - count));
        cout << current->maVT;
        gotoxy(18, 25 - (max - count));
        cout << current->soLuong;

        if ((max - count) == 10 && size == page)
        {
            firstPageEl[size - 1] = current;
            expandArray(firstPageEl, size, size + 1);
            size++;
        }

        //
        current = current->next;
        count += 1;

        if (count == max || current == nullptr)
        {
            while (true)
            {
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();

                    if (ch == RIGHT_ARROW && current != nullptr)
                    {
                        count = max;
                        max = count + 10;
                        page++;
                        ClearCTHDTable();
                        break;
                    }
                    else if (ch == LEFT_ARROW && count > 10)
                    {
                        max = max - 10;
                        count = max - 10;
                        page--;
                        current = firstPageEl[page - 1];
                        ClearCTHDTable();
                        break;
                    }
                }
                else if (ch == ESC)
                {
                    ClearCTHDTable();
                    return;
                }
                else if (ch == '*')
                {
                    ClearCTHDTable();
                    return;
                }
            }
        }
    }
}

void DrawXoaCTHD()
{
    clearBottomScreen();
    drawRectangle(0, 10, 70, 2);
    drawRectangle(0, 12, 15, 2);
    drawRectangle(15, 12, 55, 2);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(70, 12);
    cout << char(180);
    gotoxy(15, 12);
    cout << char(194);
    gotoxy(15, 14);
    cout << char(193);
    //
    gotoxy(11, 11);
    cout << "Nhap MaVT Ban Can Xoa Trong Chi Tiet Hoa Don Nay";
    gotoxy(2, 13);
    cout << "Ma Vat Tu";
    gotoxy(18, 13);
}

void XoaChiTietHoaDon(DanhSachHoaDon &new_ds_hd, DanhSachVatTu &ds_vt)
{
    CT_HoaDon *ct_canxoa = new CT_HoaDon;
    int count;
    bool quickChoose = false;
    unsigned char ch;
    char inputSoLuongMuonXoa[10];
    //
letDelete:
    DrawXoaCTHD();
    count = 0;
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == '*' && new_ds_hd->ds_ct_hoadon != nullptr)
        {
            clearBottomScreen();
            if (QuickChooseXoaCTHD_2(new_ds_hd, count, ct_canxoa))
            {
                DrawXoaCTHD();
                gotoxy(18, 13);
                cout << "               ";
                gotoxy(18, 13);
                cout << ct_canxoa->maVT;
                // in VAT va Don Gia
                drawRectangle(0, 14, 15, 2);
                drawRectangle(15, 14, 55, 2);
                gotoxy(0, 14);
                cout << char(195);
                gotoxy(70, 14);
                cout << char(180);
                gotoxy(15, 16);
                cout << char(193);
                gotoxy(15, 14);
                cout << char(197);
                gotoxy(1, 15);
                cout << "Don Gia";
                gotoxy(18, 15);
                cout << fixed << setprecision(2) << ct_canxoa->donGia;
                drawRectangle(0, 16, 15, 2);
                drawRectangle(15, 16, 55, 2);
                gotoxy(0, 16);
                cout << char(195);
                gotoxy(70, 16);
                cout << char(180);
                gotoxy(15, 18);
                cout << char(193);
                gotoxy(15, 16);
                cout << char(197);
                gotoxy(1, 17);
                cout << "VAT";
                gotoxy(18, 17);
                cout << fixed << setprecision(2) << ct_canxoa->vAT;
                gotoxy(1, 19);
                cout << "Enter De Xac Nhan, TAB: Quay lai phan nhap maVT";
                // xu li
                while (true)
                {
                    ch = getch();
                    if (ch == 224)
                    {
                        ch = getch();
                    }
                    else if (ch == ENTER)
                    {
                        gotoxy(1, 19);
                        cout << "                                                ";
                        quickChoose = true;
                        break;
                    }
                    else if (ch == TAB)
                    {
                        gotoxy(1, 19);
                        cout << "                                                ";
                        goto letDelete;
                    }
                }
                break;
            }
            else
            {
                clearBottomScreen();
                DrawXoaCTHD();
                gotoxy(18, 13);
                ct_canxoa->maVT[count] = '\0';
                cout << ct_canxoa->maVT;
                gotoxy(18 + count, 13);
                continue;
            }
            // HamQUickChose
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            ct_canxoa->maVT[count] = '\0';
            if (timKiemCTHoaDon(new_ds_hd->ds_ct_hoadon, ct_canxoa->maVT) == nullptr)
            {
                gotoxy(1, 15);
                cout << "Hoa don nay khong co chi tiet hoa don voi maVT nay vui long nhap lai";
                gotoxy(18 + count, 13);
                continue;
            }
            else
            {
                gotoxy(1, 15);
                cout << "                                                                     ";
                break;
            };
        }
        else if (ch == '\b' && count > 0)
        {
            ct_canxoa->maVT[--count] = '\0';
            cout << "\b \b";
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            ct_canxoa->maVT[count++] = ch;
        }
    }
    //

    if (quickChoose == false)
    {
        char inputdonGia[16];
        char inputVAT[16];
        DrawXoaCTHD();
        gotoxy(18, 13);
        cout << "               ";
        gotoxy(18, 13);
        cout << ct_canxoa->maVT;
        // in VAT va Don Gia
        count = 0;
        drawRectangle(0, 14, 15, 2);
        drawRectangle(15, 14, 55, 2);
        gotoxy(0, 14);
        cout << char(195);
        gotoxy(70, 14);
        cout << char(180);
        gotoxy(15, 16);
        cout << char(193);
        gotoxy(15, 14);
        cout << char(197);
        gotoxy(1, 15);
        cout << "Don Gia";
        gotoxy(18, 15);

        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
            }
            else if (ch == ENTER && count > 0)
            {
                inputdonGia[count] = '\0';
                if (isValidDoule(inputdonGia))
                {
                    ct_canxoa->donGia = stod(inputdonGia);
                    // tim kiem de xac dinh ton tai;
                    CT_HoaDon *runVar = new_ds_hd->ds_ct_hoadon;

                    if (runVar == nullptr)
                    {
                        gotoxy(0, 17);
                        cout << "Khong Tim Thay Ma Vat Tu Da Nhap Voi Don Gia Nay";
                        gotoxy(18 + count, 15);
                        continue;
                    }

                    while (runVar != nullptr)
                    {
                        if ((strcmp(runVar->maVT, ct_canxoa->maVT) == 0) && runVar->donGia == ct_canxoa->donGia)
                        {
                            break;
                        }
                        runVar = runVar->next;
                    }

                    if (runVar == nullptr)
                    {
                        gotoxy(0, 17);
                        cout << "Khong Tim Thay Ma Vat Tu Da Nhap Voi Don Gia Nay";
                        gotoxy(18 + count, 15);
                        continue;
                    }
                    else
                    {
                        gotoxy(0, 17);
                        cout << "                                                      ";
                        break;
                    }
                }
                else
                {
                    gotoxy(0, 17);
                    cout << "Don Gia Khong Hop Le (Chi dung 1 dau '.' de phan cach)";
                    gotoxy(18 + count, 15);
                    continue;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputdonGia[--count] = '\0';
                continue;
            }
            else if ((isdigit(ch) || ch == '.') && count < 15)
            {
                cout << ch;
                inputdonGia[count++] = ch;
                continue;
            }
        }
        //
        drawRectangle(0, 16, 15, 2);
        drawRectangle(15, 16, 55, 2);
        count = 0;
        gotoxy(0, 16);
        cout << char(195);
        gotoxy(70, 16);
        cout << char(180);
        gotoxy(15, 18);
        cout << char(193);
        gotoxy(15, 16);
        cout << char(197);
        gotoxy(1, 17);
        cout << "VAT";
        gotoxy(18, 17);

        //
        while (true)
        {
            ch = getch();
            if (ch == 224)
            {
                ch = getch();
            }
            else if (ch == ENTER && count > 0)
            {
                inputVAT[count] = '\0';
                if (isValidDoule(inputVAT))
                {
                    ct_canxoa->vAT = stod(inputVAT);
                    // tim kiem de xac dinh ton tai;
                    CT_HoaDon *runVar = new_ds_hd->ds_ct_hoadon;

                    if (runVar == nullptr)
                    {
                        gotoxy(0, 19);
                        cout << "Khong Tim Thay Ma Vat Tu Da Nhap Voi VAT Nay";
                        gotoxy(18 + count, 17);
                        continue;
                    }

                    while (runVar != nullptr)
                    {
                        if ((strcmp(runVar->maVT, ct_canxoa->maVT) == 0) && runVar->donGia == ct_canxoa->donGia && runVar->vAT == ct_canxoa->vAT)
                        {
                            break;
                        }
                        runVar = runVar->next;
                    }

                    if (runVar == nullptr)
                    {
                        gotoxy(0, 19);
                        cout << "Khong Tim Thay Ma Vat Tu Da Nhap Voi VAT Nay";
                        gotoxy(18 + count, 17);
                        continue;
                    }
                    else
                    {
                        gotoxy(0, 19);
                        cout << "                                                      ";
                        break;
                    }
                    break;
                }
                else
                {
                    gotoxy(0, 19);
                    cout << "VAT Khong Hop Le (Chi dung 1 dau '.' de phan cach)";
                    gotoxy(18 + count, 17);
                    continue;
                }
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputVAT[--count] = '\0';
                continue;
            }
            else if ((isdigit(ch) || ch == '.') && count < 15)
            {
                cout << ch;
                inputVAT[count++] = ch;
                continue;
            }
        }
    }
    // Xu li sau
    count = 0;
    drawRectangle(0, 18, 70, 2);
    drawRectangle(0, 20, 15, 2);
    drawRectangle(15, 20, 55, 2);
    gotoxy(0, 18);
    cout << char(195);
    gotoxy(0, 20);
    cout << char(195);
    gotoxy(70, 18);
    cout << char(180);
    gotoxy(70, 20);
    cout << char(180);
    gotoxy(15, 20);
    cout << char(194);
    gotoxy(15, 18);
    cout << char(193);
    gotoxy(15, 22);
    cout << char(193);
    gotoxy(7, 19);
    cout << "Nhap So Luong Ban Muon Bo Di (Bo trong neu muon xoa tat ca)";
    gotoxy(3, 21);
    cout << "So Luong";
    gotoxy(18, 21);
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        if (ch == TAB)
        {
            clearBottomScreen();
            goto letDelete;
        }
        else if (ch == '*')
        {
            clearBottomScreen();
            XemThongTinCTVT(new_ds_hd);
            // Ve lai, co the viet thanh ham rieng
            DrawXoaCTHD();
            cout << ct_canxoa->maVT;
            drawRectangle(0, 14, 70, 2);
            drawRectangle(0, 16, 15, 2);
            drawRectangle(15, 16, 55, 2);
            gotoxy(0, 14);
            cout << char(195);
            gotoxy(0, 16);
            cout << char(195);
            gotoxy(70, 14);
            cout << char(180);
            gotoxy(70, 16);
            cout << char(180);
            gotoxy(15, 16);
            cout << char(194);
            gotoxy(15, 14);
            cout << char(193);
            gotoxy(15, 18);
            cout << char(193);
            gotoxy(7, 15);
            cout << "Nhap So Luong Ban Muon Bo Di (Bo trong neu muon xoa tat ca)";
            gotoxy(3, 17);
            cout << "So Luong";
            gotoxy(18, 17);
            inputSoLuongMuonXoa[count] = '\0';
            cout << inputSoLuongMuonXoa;
            //
            continue;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count >= 0)
        {
            inputSoLuongMuonXoa[count] = '\0';
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            inputSoLuongMuonXoa[--count] = '\0';
            cout << "\b \b";
        }
        else if (isdigit(ch) && count < 9)
        {
            cout << ch;
            inputSoLuongMuonXoa[count++] = ch;
        }
    }

    // code hoat dong tot den day
    // gotoxy(0, 28);
    // cout << " I CAME TO HERE";
    // getch();

    // tim kiem noi de xoa
    CT_HoaDon *thisCT_HD = new_ds_hd->ds_ct_hoadon;
    while (thisCT_HD != nullptr)
    {
        if ((strcmp(thisCT_HD->maVT, ct_canxoa->maVT) == 0) && thisCT_HD->donGia == ct_canxoa->donGia && thisCT_HD->vAT == ct_canxoa->vAT)
        {
            break;
        }
        thisCT_HD = thisCT_HD->next;
    }

    if (strlen(inputSoLuongMuonXoa) == 0 || thisCT_HD->soLuong <= stoi(inputSoLuongMuonXoa))
    {
        CT_HoaDon *prev = nullptr;
        CT_HoaDon *current = new_ds_hd->ds_ct_hoadon;

        while (current != nullptr)
        {
            if (strcmp(ct_canxoa->maVT, current->maVT) == 0)
            {
                break;
            }
            prev = current;
            current = current->next;
        }
        if (prev == nullptr)
        {
            new_ds_hd->ds_ct_hoadon = current->next;
        }
        else
        {
            prev->next = current->next;
            delete current;
            current = nullptr;
        }
    }
    else
    {
        thisCT_HD->soLuong -= stoi(inputSoLuongMuonXoa);
    }

    gotoxy(1, 25);
    cout << "Thanh cong";
    Sleep(2000);
    clearBottomScreen();
    return;
};

void LapHoaDonNhap(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSachNhanVien &ds_nv, int soLuongNhanVienCount, const char maNV[])
{
    unsigned char ch;
    int count = 0;
    char inputSoHoaDon[21];
    LoaiHoaDon inputLoai = n;
    Date inputDate;
    char charInputDate[6];
    time_t now = time(nullptr);      // lay thoi gian hien tai
    tm *localTime = localtime(&now); // chuyen sang struct tm de truy xuat du lieu
    // Cho phep quay nguoc lai voi dieu kien la ham chua co du lieu
    bool backAllow = true;
//
startLapHoaDon:
    DrawNhapHoaDon(inputLoai, inputSoHoaDon);
    DrawHoaDonContactGuide();
    //
    gotoxy(3, 5);
    cout << "So Hoa Don";
    gotoxy(18, 5);
    while (true)
    {
    soHDon:
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputSoHoaDon[count] = '\0';
            //
            if (isContainSoHoaDon(ds_hd, inputSoHoaDon))
            {
                gotoxy(0, 9);
                cout << "So HD Nay Da Ton Tai Nen Khong The Them";
                gotoxy(18 + count, 5);
                continue;
            }
            else
            {
                gotoxy(0, 9);
                cout << "                                        ";
            }
            // ve input Ngay
            drawRectangle(0, 6, 15, 2);
            drawRectangle(15, 6, 55, 2);
            gotoxy(0, 6);
            cout << char(195);
            gotoxy(15, 6);
            cout << char(197);
            gotoxy(15, 8);
            cout << char(193);
            gotoxy(70, 6);
            cout << char(180);
            //
            count = 0;
            gotoxy(3, 7);
            cout << "Ngay Lap:";
            gotoxy(17, 7);
            cout << "Nam:           |Thang:         |Ngay:         ";
            gotoxy(22, 7);
            while (true)
            {
            namLap:
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();
                    // TAM DUNG SU DUNG NO DE DANH NEU DU TG
                    //  if (ch == UP_ARROW)
                    //  {
                    //      dateChooseTable(inputDate);
                    //  }
                    continue;
                }
                else if (ch == TAB)
                {
                    gotoxy(22, 7);
                    cout << "    ";
                    count = 0;
                    gotoxy(18, 5);
                    cout << "                     ";
                    gotoxy(18, 5);
                    goto soHDon;
                }
                else if (ch == ESC)
                {
                    clearBottomScreen();
                    return;
                }
                else if (ch == ENTER && count > 0)
                {
                    charInputDate[count] = '\0';
                    inputDate.year = stoi(charInputDate);
                    if (inputDate.year <= localTime->tm_year + 1900) // nam bat dau tu 1900 nen +1900 vao
                    {
                        gotoxy(40, 7);
                        count = 0;
                        while (true)
                        {
                        thangLap:
                            ch = getch();
                            if (ch == 224)
                            {
                                ch = getch();
                                continue;
                            }
                            else if (ch == TAB)
                            {
                                gotoxy(40, 7);
                                cout << "  ";
                                gotoxy(22, 7);
                                count = 0;
                                cout << "    ";
                                gotoxy(22, 7);
                                goto namLap;
                            }
                            else if (ch == ESC)
                            {
                                clearBottomScreen();
                                return;
                            }
                            else if (ch == ENTER && count > 0)
                            {
                                charInputDate[count] = '\0';
                                inputDate.month = stoi(charInputDate);
                                if ((inputDate.year == localTime->tm_year + 1900) && inputDate.month > localTime->tm_mon + 1)
                                {
                                    gotoxy(40, 7);
                                    cout << "  ";
                                    gotoxy(40, 7);
                                    count = 0;
                                    continue;
                                }
                                else if (inputDate.month > 12)
                                {
                                    gotoxy(40, 7);
                                    cout << "  ";
                                    gotoxy(40, 7);
                                    count = 0;
                                    continue;
                                }
                                else
                                {
                                    gotoxy(55, 7);
                                    count = 0;
                                    //
                                    while (true)
                                    {
                                    ngayLap:
                                        ch = getch();
                                        if (ch == 224)
                                        {
                                            ch = getch();
                                            continue;
                                        }
                                        else if (ch == TAB)
                                        {

                                            gotoxy(55, 7);
                                            cout << "  ";
                                            gotoxy(40, 7);
                                            count = 0;
                                            cout << "  ";
                                            gotoxy(40, 7);
                                            goto thangLap;
                                        }
                                        else if (ch == ESC)
                                        {
                                            clearBottomScreen();
                                            return;
                                        }
                                        else if (ch == ENTER && count > 0)
                                        {
                                            charInputDate[count] = '\0';
                                            inputDate.day = stoi(charInputDate);
                                            if (inputDate.month == 2)
                                            {
                                                if (isNamNhuan(inputDate.year) && inputDate.day <= 29)
                                                {
                                                    break;
                                                }
                                                else if (!isNamNhuan(inputDate.year) && inputDate.day <= 28)
                                                {
                                                    break;
                                                }
                                                else
                                                {
                                                    gotoxy(55, 7);
                                                    cout << "  ";
                                                    gotoxy(55, 7);
                                                    count = 0;
                                                    continue;
                                                }
                                            }
                                            else if (inputDate.day <= 30 && (inputDate.month == 4 || inputDate.month == 6 || inputDate.month == 9 || inputDate.month == 11))
                                            {
                                                break;
                                            }
                                            else if (inputDate.day <= 31)
                                            {
                                                break;
                                            }
                                            else
                                            {
                                                gotoxy(55, 7);
                                                cout << "  ";
                                                gotoxy(55, 7);
                                                count = 0;
                                                continue;
                                            }
                                        }
                                        else if (ch == '\b' && count > 0)
                                        {
                                            charInputDate[--count] = '\0';
                                            cout << "\b \b";
                                        }
                                        else if (isdigit(ch) && count < 2)
                                        {
                                            charInputDate[count++] = ch;
                                            cout << ch;
                                        }
                                    };
                                };
                                break;
                            }
                            else if (ch == '\b' && count > 0)
                            {
                                charInputDate[--count] = '\0';
                                cout << "\b \b";
                            }
                            else if (isdigit(ch) && count < 2)
                            {
                                charInputDate[count++] = ch;
                                cout << ch;
                            }
                        }
                        break;
                    }
                    else
                    {
                        gotoxy(22, 7);
                        cout << "    ";
                        gotoxy(22, 7);
                        count = 0;
                        continue;
                    }
                }
                else if (ch == '\b' && count > 0)
                {
                    charInputDate[--count] = '\0';
                    cout << "\b \b";
                }
                else if (isdigit(ch) && count < 4)
                {
                    charInputDate[count++] = ch;
                    cout << ch;
                }
            }
            //
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            inputSoHoaDon[--count] = '\0';
            cout << "\b \b";
            continue;
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 20)
        {
            cout << ch;
            inputSoHoaDon[count++] = ch;
            continue;
        }
    }

    // da tao hoa don
    HoaDon *new_hd = newHoaDon(inputSoHoaDon, inputDate, inputLoai, nullptr);
    //  phan nhap chi tiet hoa don;
    int choose3 = 0;
    while (true)
    {
        drawCT_HoaDonUI(choose3);
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            if (ch == DOWN_ARROW && choose3 < thirdHoaDonItems - 1)
            {
                choose3 += 1;
                drawCT_HoaDonUI(choose3);
            }
            else if (ch == UP_ARROW && choose3 > 0)
            {
                choose3 -= 1;
                drawCT_HoaDonUI(choose3);
            }
            else if (ch == DOWN_ARROW && choose3 == thirdHoaDonItems - 1)
            {
                choose3 = 0;
                drawCT_HoaDonUI(choose3);
            }
            else if (ch == UP_ARROW && choose3 == 0)
            {
                choose3 = thirdHoaDonItems - 1;
                drawCT_HoaDonUI(choose3);
            }
        }
        else if (ch == ESC)
        {
            gotoxy(0, 20);
            cout << "Khong Duoc Phep Nhan ESC De Thoat";
            gotoxy(0, 21);
            system("Pause");
            gotoxy(0, 20);
            cout << "                                                ";
            gotoxy(0, 21);
            cout << "                                                     ";
            continue;
        }
        else if (ch == TAB && backAllow == true)
        {
            gotoxy(55, 7);
            cout << "  ";
            count = 0;
            clearBottomScreen();
            gotoxy(55, 7);
            goto ngayLap;
        }
        else if (ch == ENTER)
        {
            if (choose3 == 0)
            {
                clearBottomScreen();
                themChiTietHoaDonNhap(new_hd, ds_vt);
                clearBottomScreen();
                backAllow = false;
                drawCT_HoaDonUI(choose3);
            }
            else if (choose3 == 1)
            {
                clearBottomScreen();
                XoaChiTietHoaDon(new_hd, ds_vt);
                clearBottomScreen();
                drawCT_HoaDonUI(choose3);
                continue;
            }
            else if (choose3 == 2)
            {
                while (true)
                {
                    clearBottomScreen();
                    gotoxy(0, 20);
                    cout << "Do you want to cancel this recipe(y:Yes, n: No): ";
                    ch = getch();
                    if (ch == 'n' || ch == 'N')
                    {
                        clearBottomScreen();
                        drawCT_HoaDonUI(choose3);
                        break;
                    }
                    else if (ch == 'y' || ch == 'Y')
                    {
                        return;
                    }
                }
            }
            else if (choose3 == 3)
            {

                while (true)
                {
                    clearBottomScreen();
                    gotoxy(0, 20);
                    cout << "Do you want to insert this recipe(y:Yes, n: No): ";
                    ch = getch();
                    if (ch == 'n' || ch == 'N')
                    {
                        clearBottomScreen();
                        drawCT_HoaDonUI(choose3);
                        break;
                    }
                    else if (ch == 'y' || ch == 'Y')
                    {
                        if (new_hd->ds_ct_hoadon == nullptr)
                        {
                            return;
                        }
                        CT_HoaDon *current = new_hd->ds_ct_hoadon;
                        while (current != nullptr)
                        {
                            if (!isContainMaVT_DanhSachVatTu(ds_vt, current->maVT))
                            {
                                DanhSachVatTu new_vattu = new VatTu;
                                drawRectangle(0, 18, 70, 3);
                                gotoxy(1, 19);
                                cout << current->maVT << " la vat tu moi duoc them vao!!";
                                gotoxy(1, 20);
                                cout << "Vui long cung cap them thong tin cua vat tu nay";
                                char inputTenVT[21];
                                //
                                drawRectangle(0, 21, 15, 2);
                                drawRectangle(15, 21, 55, 2);
                                gotoxy(0, 21);
                                cout << char(195);
                                gotoxy(15, 21);
                                cout << char(194);
                                gotoxy(15, 23);
                                cout << char(193);
                                gotoxy(70, 21);
                                cout << char(180);
                                //
                                gotoxy(1, 22);
                                cout << "Ten Vat Tu";
                                count = 0;
                                gotoxy(18, 22);
                                while (true)
                                {
                                    ch = getch();

                                    if (ch == 224)
                                    {
                                        ch = getch();
                                    }
                                    else if (ch == ESC)
                                    {
                                        return;
                                    }
                                    else if (ch == ENTER && count > 0)
                                    {
                                        inputTenVT[count] = '\0';
                                        if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
                                        {
                                            gotoxy(1, 24);
                                            cout << "TenVT " << inputTenVT << "Da Ton Tai";
                                            gotoxy(18 + count, 22);
                                            continue;
                                        }
                                        else
                                        {
                                            gotoxy(1, 24);
                                            cout << "                                                                     ";
                                            break;
                                        }
                                        break;
                                    }
                                    else if (ch == '\b' && count > 0)
                                    {
                                        cout << "\b \b";
                                        inputTenVT[--count] = '\0';
                                    }
                                    else if ((isalnum(ch) || ch == ' ') && count < 20)
                                    {
                                        cout << ch;
                                        ch = tolower(ch);
                                        inputTenVT[count++] = ch;
                                    }
                                }

                                //
                                char inputDonViTinh[11];
                                count = 0;
                                //
                                drawRectangle(0, 23, 15, 2);
                                drawRectangle(15, 23, 55, 2);
                                gotoxy(0, 23);
                                cout << char(195);
                                gotoxy(15, 23);
                                cout << char(197);
                                gotoxy(15, 25);
                                cout << char(193);
                                gotoxy(70, 23);
                                cout << char(180);
                                //
                                gotoxy(1, 24);
                                cout << "Don Vi Tinh";
                                gotoxy(18, 24);
                                while (true)
                                {
                                    ch = getch();

                                    if (ch == 224)
                                    {
                                        ch = getch();
                                    }
                                    else if (ch == ESC)
                                    {
                                        return;
                                    }
                                    else if (ch == ENTER && count > 0)
                                    {
                                        inputDonViTinh[count] = '\0';
                                        break;
                                    }
                                    else if (ch == '\b' && count > 0)
                                    {
                                        cout << "\b \b";
                                        inputDonViTinh[--count] = '\0';
                                    }
                                    else if ((isalnum(ch) || ch == ' ') && count < 10)
                                    {
                                        cout << ch;
                                        ch = tolower(ch);
                                        inputDonViTinh[count++] = ch;
                                    }
                                }
                                new_vattu = newDanhSachVatTu(current->maVT, inputTenVT, inputDonViTinh, current->soLuong);
                                insertDanhSachVatTu(ds_vt, new_vattu);
                                clearBottomScreen();
                            }
                            else
                            {
                                DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(ds_vt, current->maVT);
                                updateSoLuongTon(vattu, vattu->soLuongTon + current->soLuong);
                            }
                            current = current->next;
                        }
                        int vitriNV = searchNhanVienFromDSNV(ds_nv, maNV, soLuongNhanVienCount);
                        HoaDon *new_hd_copy = new HoaDon(*new_hd);
                        InsertHoaDonVaoDSHD(ds_nv[vitriNV]->ds_hoadon, new_hd);
                        InsertHoaDonVaoDSHD(ds_hd, new_hd_copy);
                        return;
                    }
                }
            }
        }
    }

    // drawRectangle(0, 8, 15, 2);
    // drawRectangle(15, 8, 55, 2);
    // gotoxy(0, 8);
    // cout << char(195);
    // gotoxy(15, 8);
    // cout << char(197);
    // gotoxy(15, 10);
    // cout << char(193);
    // gotoxy(70, 8);
    // cout << char(180);
};

void LapHoaDonXuat(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSachNhanVien &ds_nv, int soLuongNhanVienCount, const char maNV[])
{
    unsigned char ch;
    int count = 0;
    char inputSoHoaDon[21];
    LoaiHoaDon inputLoai = x;
    Date inputDate;
    char charInputDate[6];
    time_t now = time(nullptr);      // lay thoi gian hien tai
    tm *localTime = localtime(&now); // chuyen sang struct tm de truy xuat du lieu
    // Cho phep quay nguoc lai voi dieu kien la ham chua co du lieu
    bool backAllow = true;
//
startLapHoaDon:
    DrawNhapHoaDon(inputLoai, inputSoHoaDon);
    DrawHoaDonContactGuide();
    //
    gotoxy(3, 5);
    cout << "So Hoa Don";
    gotoxy(18, 5);
    while (true)
    {
    soHDon:
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputSoHoaDon[count] = '\0';
            // loc maHD
            if (isContainSoHoaDon(ds_hd, inputSoHoaDon))
            {
                gotoxy(0, 9);
                cout << "Ma HD Nay Da Ton Tai Nen Khong The Them";
                gotoxy(18 + count, 5);
                continue;
            }
            else
            {
                gotoxy(0, 9);
                cout << "                                        ";
            }
            //  ve input Ngay
            drawRectangle(0, 6, 15, 2);
            drawRectangle(15, 6, 55, 2);
            gotoxy(0, 6);
            cout << char(195);
            gotoxy(15, 6);
            cout << char(197);
            gotoxy(15, 8);
            cout << char(193);
            gotoxy(70, 6);
            cout << char(180);
            //
            count = 0;
            gotoxy(3, 7);
            cout << "Ngay Lap:";
            gotoxy(17, 7);
            cout << "Nam:           |Thang:         |Ngay:         ";
            gotoxy(22, 7);
            while (true)
            {
            namLap:
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();
                    // TAM DUNG SU DUNG NO DE DANH NEU DU TG
                    //  if (ch == UP_ARROW)
                    //  {
                    //      dateChooseTable(inputDate);
                    //  }
                    continue;
                }
                else if (ch == TAB)
                {
                    gotoxy(22, 7);
                    cout << "    ";
                    count = 0;
                    gotoxy(18, 5);
                    cout << "                     ";
                    gotoxy(18, 5);
                    goto soHDon;
                }
                else if (ch == ESC)
                {
                    clearBottomScreen();
                    return;
                }
                else if (ch == ENTER && count > 0)
                {
                    charInputDate[count] = '\0';
                    inputDate.year = stoi(charInputDate);
                    if (inputDate.year <= localTime->tm_year + 1900) // nam bat dau tu 1900 nen +1900 vao
                    {
                        gotoxy(40, 7);
                        count = 0;
                        while (true)
                        {
                        thangLap:
                            ch = getch();
                            if (ch == 224)
                            {
                                ch = getch();
                                continue;
                            }
                            else if (ch == TAB)
                            {
                                gotoxy(40, 7);
                                cout << "  ";
                                gotoxy(22, 7);
                                count = 0;
                                cout << "    ";
                                gotoxy(22, 7);
                                goto namLap;
                            }
                            else if (ch == ESC)
                            {
                                clearBottomScreen();
                                return;
                            }
                            else if (ch == ENTER && count > 0)
                            {
                                charInputDate[count] = '\0';
                                inputDate.month = stoi(charInputDate);
                                if ((inputDate.year == localTime->tm_year + 1900) && inputDate.month > localTime->tm_mon + 1)
                                {
                                    gotoxy(40, 7);
                                    cout << "  ";
                                    gotoxy(40, 7);
                                    count = 0;
                                    continue;
                                }
                                else if (inputDate.month > 12)
                                {
                                    gotoxy(40, 7);
                                    cout << "  ";
                                    gotoxy(40, 7);
                                    count = 0;
                                    continue;
                                }
                                else
                                {
                                    gotoxy(55, 7);
                                    count = 0;
                                    //
                                    while (true)
                                    {
                                    ngayLap:
                                        ch = getch();
                                        if (ch == 224)
                                        {
                                            ch = getch();
                                            continue;
                                        }
                                        else if (ch == TAB)
                                        {

                                            gotoxy(55, 7);
                                            cout << "  ";
                                            gotoxy(40, 7);
                                            count = 0;
                                            cout << "  ";
                                            gotoxy(40, 7);
                                            goto thangLap;
                                        }
                                        else if (ch == ESC)
                                        {
                                            clearBottomScreen();
                                            return;
                                        }
                                        else if (ch == ENTER && count > 0)
                                        {
                                            charInputDate[count] = '\0';
                                            inputDate.day = stoi(charInputDate);
                                            if (inputDate.month == 2)
                                            {
                                                if (isNamNhuan(inputDate.year) && inputDate.day <= 29)
                                                {
                                                    break;
                                                }
                                                else if (!isNamNhuan(inputDate.year) && inputDate.day <= 28)
                                                {
                                                    break;
                                                }
                                                else
                                                {
                                                    gotoxy(55, 7);
                                                    cout << "  ";
                                                    gotoxy(55, 7);
                                                    count = 0;
                                                    continue;
                                                }
                                            }
                                            else if (inputDate.day <= 30 && (inputDate.month == 4 || inputDate.month == 6 || inputDate.month == 9 || inputDate.month == 11))
                                            {
                                                break;
                                            }
                                            else if (inputDate.day <= 31)
                                            {
                                                break;
                                            }
                                            else
                                            {
                                                gotoxy(55, 7);
                                                cout << "  ";
                                                gotoxy(55, 7);
                                                count = 0;
                                                continue;
                                            }
                                        }
                                        else if (ch == '\b' && count > 0)
                                        {
                                            charInputDate[--count] = '\0';
                                            cout << "\b \b";
                                        }
                                        else if (isdigit(ch) && count < 2)
                                        {
                                            charInputDate[count++] = ch;
                                            cout << ch;
                                        }
                                    };
                                };
                                break;
                            }
                            else if (ch == '\b' && count > 0)
                            {
                                charInputDate[--count] = '\0';
                                cout << "\b \b";
                            }
                            else if (isdigit(ch) && count < 2)
                            {
                                charInputDate[count++] = ch;
                                cout << ch;
                            }
                        }
                        break;
                    }
                    else
                    {
                        gotoxy(22, 7);
                        cout << "    ";
                        gotoxy(22, 7);
                        count = 0;
                        continue;
                    }
                }
                else if (ch == '\b' && count > 0)
                {
                    charInputDate[--count] = '\0';
                    cout << "\b \b";
                }
                else if (isdigit(ch) && count < 4)
                {
                    charInputDate[count++] = ch;
                    cout << ch;
                }
            }
            //
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            inputSoHoaDon[--count] = '\0';
            cout << "\b \b";
            continue;
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 20)
        {
            cout << ch;
            inputSoHoaDon[count++] = ch;
            continue;
        }
    }

    //
    HoaDon *new_hd = newHoaDon(inputSoHoaDon, inputDate, inputLoai, nullptr);
    //  phan nhap chi tiet hoa don xuat;
    int choose3 = 0;
    drawCT_HoaDonUI(choose3);
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            if (ch == DOWN_ARROW && choose3 < thirdHoaDonItems - 1)
            {
                choose3 += 1;
                drawCT_HoaDonUI(choose3);
            }
            else if (ch == UP_ARROW && choose3 > 0)
            {
                choose3 -= 1;
                drawCT_HoaDonUI(choose3);
            }
            else if (ch == DOWN_ARROW && choose3 == thirdHoaDonItems - 1)
            {
                choose3 = 0;
                drawCT_HoaDonUI(choose3);
            }
            else if (ch == UP_ARROW && choose3 == 0)
            {
                choose3 = thirdHoaDonItems - 1;
                drawCT_HoaDonUI(choose3);
            }
        }
        else if (ch == ESC)
        {
            gotoxy(0, 11);
            return;
        }
        else if (ch == TAB && backAllow == true)
        {
            gotoxy(55, 7);
            cout << "  ";
            count = 0;
            clearBottomScreen();
            gotoxy(55, 7);
            goto ngayLap;
        }
        else if (ch == ENTER)
        {
            if (choose3 == 0)
            {
                clearBottomScreen();
                //"Them chitiethoadon"
                themChiTietHoaDonXuat(new_hd, ds_vt);
                clearBottomScreen();
                backAllow = false;
                drawCT_HoaDonUI(choose3);
            }
            else if (choose3 == 1)
            {
                clearBottomScreen();
                gotoxy(0, 20);
                XoaChiTietHoaDon(new_hd, ds_vt);
                clearBottomScreen();
                drawCT_HoaDonUI(choose3);
                continue;
            }
            else if (choose3 == 2)
            {
                // Huy Hoa Don
                while (true)
                {
                    clearBottomScreen();
                    gotoxy(0, 20);
                    cout << "Do you want to cancel this recipe(y:Yes, n: No): ";
                    ch = getch();
                    if (ch == 'n' || ch == 'N')
                    {
                        clearBottomScreen();
                        drawCT_HoaDonUI(choose3);
                        break;
                    }
                    else if (ch == 'y' || ch == 'Y')
                    {
                        return;
                    }
                }
                continue;
            }
            else if (choose3 == 3)
            {
                while (true)
                {
                    clearBottomScreen();
                    gotoxy(0, 20);
                    cout << "Do you want to insert this recipe(y:Yes, n: No): ";
                    ch = getch();
                    if (ch == 'n' || ch == 'N')
                    {
                        clearBottomScreen();
                        drawCT_HoaDonUI(choose3);
                        break;
                    }
                    else if (ch == 'y' || ch == 'Y')
                    {
                        if (new_hd->ds_ct_hoadon == nullptr)
                        {
                            return;
                        }
                        CT_HoaDon *current = new_hd->ds_ct_hoadon;
                        while (current != nullptr)
                        {
                            // Khong can kiem tra cong kenh vi da loc dk luc tao;
                            DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(ds_vt, current->maVT);
                            updateSoLuongTon(vattu, vattu->soLuongTon - current->soLuong);

                            current = current->next;
                        }
                        int vitriNV = searchNhanVienFromDSNV(ds_nv, maNV, soLuongNhanVienCount);
                        //
                        // ds_nv[vitriNV]->ds_hoadon = new_hd;
                        // Co the dan den loi neu gan ca 2 cung luc tai vi dia chi next se chi co 1 va bi thay doi
                        // CO THE THEM VAO 1 NEXT NX CHO HOA DON NHUNG BI PHIEN VA PHA CAU TRUC
                        HoaDon *new_hd_copy = new HoaDon(*new_hd);
                        InsertHoaDonVaoDSHD(ds_nv[vitriNV]->ds_hoadon, new_hd);
                        InsertHoaDonVaoDSHD(ds_hd, new_hd_copy);
                        return;
                        // xu ly du lieu (chua gan)
                    }
                }
            }
        }
    }
}

int TimNhanVienTheoSoHD(DanhSachNhanVien ds_nv, int soLuongNV, const char soHD[])
{
    for (int i = 0; i < soLuongNV; i++)
    {
        NhanVien *nv = ds_nv[i];
        DanhSachHoaDon current_hoadon = ds_nv[i]->ds_hoadon;
        while (current_hoadon != nullptr)
        {
            if (strcmp(current_hoadon->soHD, soHD) == 0)
            {
                return i;
            }
            current_hoadon = current_hoadon->next;
        }
    }
    return -1;
}

void clearHoaDonTable()
{
    for (int i = 0; i < 15; i++)
    {
        gotoxy(1, 7 + i);
        cout << "          ";
        gotoxy(12, 7 + i);
        cout << "                               ";
        gotoxy(44, 7 + i);
        cout << "    ";
        gotoxy(49, 7 + i);
        cout << "                    ";
        gotoxy(71, 7 + i);
        cout << "         ";
        gotoxy(81, 7 + i);
        cout << "                ";
        gotoxy(98, 7 + i);
        cout << "                     ";
    }
}

void InHoaDonTheoSoHoaDon(DanhSachHoaDon ds_hd, DanhSachVatTu ds_vt, DanhSachNhanVien ds_nv, int soLuongNV)
{
    int max = 15;
    unsigned char ch;
    char inputSoHD[21];
    int count;

startIn:
    //
    clrscr();
    count = 0;
    max = 15;
    //
    gotoxy(0, 27);
    SetColor(0xA);
    cout << "ENTER:";
    SetColor(0xF);
    cout << " Accept  ";
    SetColor(0xA);
    cout << "TAB:";
    SetColor(0xF);
    cout << " Change SoHD  ";
    SetColor(0xA);
    cout << "DOWN_ARROW:";
    SetColor(0xF);
    cout << " Move Down";
    gotoxy(0, 28);
    SetColor(0xA);
    cout << "ESC:";
    SetColor(0xF);
    cout << " Escape From Board    ";
    SetColor(0xA);
    cout << "-->:";
    SetColor(0xF);
    cout << " Next List     ";
    SetColor(0xA);
    cout << "<--:";
    SetColor(0xF);
    cout << " Previous List   ";
    SetColor(0xF);
    //
    drawRectangle(0, 0, 119, 2);
    gotoxy(45, 1);
    SetColor(0x4);
    cout << "In Thong Tin Hoa Don Theo So Hoa Don";
    SetColor(0xF);
    drawRectangle(0, 2, 30, 2);
    drawRectangle(30, 2, 89, 2);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(30, 2);
    cout << char(194);
    gotoxy(30, 4);
    cout << char(193);
    gotoxy(119, 2);
    cout << char(180);

    gotoxy(2, 3);
    cout << "Nhap So Hoa Don Ban Muon In";
    gotoxy(32, 3);

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            inputSoHD[count] = '\0';
            if (!isContainSoHoaDon(ds_hd, inputSoHD))
            {
                gotoxy(0, 5);
                cout << "Khong Ton Tai So Hoa Don Nay Nen Khong The Truy Xuat";
                gotoxy(32 + count, 3);
                continue;
            }
            gotoxy(0, 5);
            cout << "                                                     ";
            break;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputSoHD[--count] = '\0';
        }
        else if ((isalnum(ch) || isSpecialChar(ch)) && count < 20)
        {
            cout << ch;
            ch = tolower(ch);
            inputSoHD[count++] = ch;
        }
    }
    //

    //
    drawRectangle(0, 4, 11, 2);
    drawRectangle(11, 4, 32, 2);
    drawRectangle(43, 4, 5, 2);
    drawRectangle(48, 4, 21, 2);
    drawRectangle(69, 4, 11, 2);
    drawRectangle(80, 4, 17, 2);
    drawRectangle(97, 4, 22, 2);
    SetColor(0xB);
    gotoxy(4, 5);
    cout << "Ngay";
    gotoxy(23, 5);
    cout << "Ho Va Ten";
    gotoxy(44, 5);
    cout << "Loai";
    gotoxy(54, 5);
    cout << "Ten Vat Tu";
    gotoxy(71, 5);
    cout << "So Luong";
    gotoxy(85, 5);
    cout << "Don Gia";
    gotoxy(105, 5);
    cout << "Tri Gia";
    SetColor(0xF);
    // Phan chua noi dung
    drawRectangle(0, 6, 11, 16);
    drawRectangle(11, 6, 32, 16);
    drawRectangle(43, 6, 5, 16);
    drawRectangle(48, 6, 21, 16);
    drawRectangle(69, 6, 11, 16);
    drawRectangle(80, 6, 17, 16);
    drawRectangle(97, 6, 22, 16);
    drawRectangle(0, 22, 15, 2);
    drawRectangle(15, 22, 104, 2);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(11, 4);
    cout << char(194);
    gotoxy(30, 4);
    cout << char(193);
    gotoxy(43, 4);
    cout << char(194);
    gotoxy(48, 4);
    cout << char(194);
    gotoxy(69, 4);
    cout << char(194);
    gotoxy(80, 4);
    cout << char(194);
    gotoxy(97, 4);
    cout << char(194);
    gotoxy(119, 4);
    cout << char(180);
    gotoxy(0, 6);
    cout << char(195);
    gotoxy(11, 6);
    cout << char(197);
    gotoxy(43, 6);
    cout << char(197);
    gotoxy(48, 6);
    cout << char(197);
    gotoxy(69, 6);
    cout << char(197);
    gotoxy(80, 6);
    cout << char(197);
    gotoxy(97, 6);
    cout << char(197);
    gotoxy(119, 6);
    cout << char(180);
    gotoxy(0, 22);
    cout << char(195);
    gotoxy(11, 22);
    cout << char(193);
    gotoxy(43, 22);
    cout << char(193);
    gotoxy(48, 22);
    cout << char(193);
    gotoxy(69, 22);
    cout << char(193);
    gotoxy(80, 22);
    cout << char(193);
    gotoxy(97, 22);
    cout << char(193);
    gotoxy(119, 22);
    cout << char(180);
    gotoxy(15, 22);
    cout << char(194);
    gotoxy(15, 24);
    cout << char(193);
    // Noi Dung
    HoaDon *HoaDon = searchSoHoaDon(ds_hd, inputSoHD);
    CT_HoaDon *current = HoaDon->ds_ct_hoadon;
    CT_HoaDon **firstPageEl = new CT_HoaDon *[1];
    VatTu *current_vt = new VatTu;
    int vitriNV = TimNhanVienTheoSoHD(ds_nv, soLuongNV, inputSoHD);
    int size = 1;
    int Page = 1;
    double sumOfHD = 0;
    count = 0;
    // tim tong
    while (current != nullptr)
    {
        sumOfHD += current->donGia * current->soLuong * (1 + (current->vAT / 100.0));
        current = current->next;
    }

    gotoxy(4, 23);
    cout << "Tong HD";
    gotoxy(18, 23);
    cout << fixed << setprecision(2) << sumOfHD;
    // Dat lai
    current = HoaDon->ds_ct_hoadon;
    //
    if (current == nullptr)
    {
        gotoxy(1, 7);
        cout << "NONE";
        gotoxy(12, 7);
        cout << "Hoa Don Nay Khong Co Du Lieu";
        gotoxy(44, 7);
        cout << "NONE";
        gotoxy(49, 7);
        cout << "NONE";
        gotoxy(71, 7);
        cout << "NONE";
        gotoxy(82, 7);
        cout << "NONE";
        gotoxy(99, 7);
        cout << "NONE";
        getch();
        return;
    }
    while (count < max && current != nullptr)
    {
        current_vt = searchMaVT_DanhSachVatTu(ds_vt, current->maVT);

        if ((max - count) == 15 && Page == size)
        {
            firstPageEl[size - 1] = current;
            expandArray(firstPageEl, size, size + 1);
            size++;
        }

        gotoxy(1, 22 - (max - count));
        if (HoaDon->date.day < 10)
        {
            cout << "0" << HoaDon->date.day << '/';
        }
        if (HoaDon->date.month < 10)
        {
            cout << "0" << HoaDon->date.month << '/';
        }
        cout << HoaDon->date.year;
        //
        gotoxy(12, 22 - (max - count));
        cout << ds_nv[vitriNV]->ho << " " << ds_nv[vitriNV]->ten;
        gotoxy(44, 22 - (max - count));
        if (HoaDon->loai == n)
        {
            cout << "Nhap";
        }
        else
        {
            cout << "Xuat";
        }
        gotoxy(49, 22 - (max - count));
        cout << current_vt->tenVT;
        gotoxy(71, 22 - (max - count));
        cout << current->soLuong;
        gotoxy(82, 22 - (max - count));
        cout << fixed << setprecision(2) << current->donGia;
        gotoxy(99, 22 - (max - count));
        cout << fixed << setprecision(2) << current->donGia * current->soLuong * (1 + (current->vAT / 100.0));
        //
        current = current->next;
        count++;

        if (count >= max || current == nullptr)
        {
            while (true)
            {
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();
                    if (ch == RIGHT_ARROW && current != nullptr)
                    {
                        count = count + 15;
                        max = count + 15;
                        Page++;
                        clearHoaDonTable();
                        break;
                    }
                    else if (ch == LEFT_ARROW && Page > 1)
                    {
                        max = max - 15;
                        count = max - 15;
                        Page--;
                        current = firstPageEl[Page - 1];
                        clearHoaDonTable();
                        break;
                    }
                }
                else if (ch == ESC)
                {
                    return;
                }
                else if (ch == TAB)
                {
                    goto startIn;
                }
            }
        }
    }

    // TEST
    // gotoxy(1, 7);
    // cout << "20/10/2024";
    // gotoxy(12, 7);
    // cout << "Luong Chi Vinh Junior Ryan Ngok";
    // gotoxy(44, 7);
    // cout << "Xuat";
    // gotoxy(49, 7);
    // cout << "Banh xe vo dich kkkk";
    // gotoxy(71, 7);
    // cout << "999999999";
    // gotoxy(82, 7);
    // cout << "123456789123456";
    // gotoxy(99, 7);
    // cout << "1234567891234567";

    getch();
    return;
}

bool isContainMaVTInDoanhThu(DoanhThuVT *dtvt, int soLuongDangCo, const char maVT[11])
{
    for (int i = 0; i < soLuongDangCo; i++)
    {
        if (strcmp(dtvt[i].maVT, maVT) == 0)
        {
            return true;
        };
    }
    return false;
}

int searchMaVTInDoanhThu(DoanhThuVT *dtvt, int soLuongDangCo, const char maVT[11])
{
    for (int i = 0; i < soLuongDangCo; i++)
    {
        if (strcmp(dtvt[i].maVT, maVT) == 0)
        {
            return i;
        };
    }
    return -1;
}

void In10VatTuDoanhThuCaoNhat(DanhSachVatTu ds_vt, DanhSachNhanVien ds_nv, DanhSachHoaDon ds_hd, int soLuongVatTu, int soLuongNV)
{
    // Kiem tra kha thi
    if (ds_vt == nullptr || ds_nv == nullptr || ds_hd == nullptr)
    {
        return;
    }
    //
    unsigned char ch;
    int count;
    Date ngayDau;
    Date ngayCuoi;
    char charInputDate[6];
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    bool backAllow = true;
    //

    //
//
start:
    clrscr();
    //
    gotoxy(0, 27);
    SetColor(0xA);
    cout << "ENTER:";
    SetColor(0xF);
    cout << " Accept  ";
    SetColor(0xA);
    cout << "TAB:";
    SetColor(0xF);
    cout << " Change SoHD  ";
    SetColor(0xA);
    cout << "DOWN_ARROW:";
    SetColor(0xF);
    cout << " Move Down";
    gotoxy(0, 28);
    SetColor(0xA);
    cout << "ESC:";
    SetColor(0xF);
    cout << " Escape From Board    ";
    SetColor(0xA);
    cout << "-->:";
    SetColor(0xF);
    cout << " Next List     ";
    SetColor(0xA);
    cout << "<--:";
    SetColor(0xF);
    cout << " Previous List   ";
    SetColor(0xF);
    //
    count = 0;
    drawRectangle(0, 0, 119, 2);
    gotoxy(45, 1);
    SetColor(0x4);
    cout << "BANG LIET KE 10 VAT TU CO DOANH THU CAO NHAT";
    SetColor(0xF);
    drawRectangle(0, 2, 30, 2);
    drawRectangle(30, 2, 89, 2);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(30, 2);
    cout << char(194);
    gotoxy(30, 4);
    cout << char(193);
    gotoxy(119, 2);
    cout << char(180);
    gotoxy(2, 3);
    cout << "Nhap Ngay Thu Nhat";
    gotoxy(32, 3);
    cout << "Nam:           |Thang:         |Ngay:         ";
    gotoxy(37, 3);
    while (true)
    {
    namLap:
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            // TAM DUNG SU DUNG NO DE DANH NEU DU TG
            //  if (ch == UP_ARROW)
            //  {
            //      dateChooseTable(inputDate);
            //  }
            continue;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            charInputDate[count] = '\0';
            ngayDau.year = stoi(charInputDate);
            if (ngayDau.year <= localTime->tm_year + 1900) // nam bat dau tu 1900 nen +1900 vao
            {
                gotoxy(55, 3);
                count = 0;
                while (true)
                {
                thangLap:
                    ch = getch();
                    if (ch == 224)
                    {
                        ch = getch();
                        continue;
                    }
                    else if (ch == TAB)
                    {
                        gotoxy(55, 3);
                        cout << "  ";
                        gotoxy(37, 3);
                        count = 0;
                        cout << "    ";
                        gotoxy(37, 3);
                        goto namLap;
                    }
                    else if (ch == ESC)
                    {
                        clearBottomScreen();
                        return;
                    }
                    else if (ch == ENTER && count > 0)
                    {
                        charInputDate[count] = '\0';
                        ngayDau.month = stoi(charInputDate);
                        if ((ngayDau.year == localTime->tm_year + 1900) && ngayDau.month > localTime->tm_mon + 1)
                        {
                            gotoxy(55, 3);
                            cout << "  ";
                            gotoxy(55, 3);
                            count = 0;
                            continue;
                        }
                        else if (ngayDau.month > 12)
                        {
                            gotoxy(55, 3);
                            cout << "  ";
                            gotoxy(55, 3);
                            count = 0;
                            continue;
                        }
                        else
                        {
                            gotoxy(70, 3);
                            count = 0;
                            //
                            while (true)
                            {
                            ngayLap:
                                ch = getch();
                                if (ch == 224)
                                {
                                    ch = getch();
                                    continue;
                                }
                                else if (ch == TAB)
                                {

                                    gotoxy(70, 3);
                                    cout << "  ";
                                    gotoxy(55, 3);
                                    count = 0;
                                    cout << "  ";
                                    gotoxy(55, 3);
                                    goto thangLap;
                                }
                                else if (ch == ESC)
                                {
                                    clearBottomScreen();
                                    return;
                                }
                                else if (ch == ENTER && count > 0)
                                {
                                    charInputDate[count] = '\0';
                                    ngayDau.day = stoi(charInputDate);
                                    if (ngayDau.month == 2)
                                    {
                                        if (isNamNhuan(ngayDau.year) && ngayDau.day <= 29)
                                        {
                                            break;
                                        }
                                        else if (!isNamNhuan(ngayDau.year) && ngayDau.day <= 28)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            gotoxy(70, 3);
                                            cout << "  ";
                                            gotoxy(70, 3);
                                            count = 0;
                                            continue;
                                        }
                                    }
                                    else if (ngayDau.day <= 30 && (ngayDau.month == 4 || ngayDau.month == 6 || ngayDau.month == 9 || ngayDau.month == 11))
                                    {
                                        break;
                                    }
                                    else if (ngayDau.day <= 31)
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        gotoxy(70, 3);
                                        cout << "  ";
                                        gotoxy(70, 3);
                                        count = 0;
                                        continue;
                                    }
                                }
                                else if (ch == '\b' && count > 0)
                                {
                                    charInputDate[--count] = '\0';
                                    cout << "\b \b";
                                }
                                else if (isdigit(ch) && count < 2)
                                {
                                    charInputDate[count++] = ch;
                                    cout << ch;
                                }
                            };
                        };
                        break;
                    }
                    else if (ch == '\b' && count > 0)
                    {
                        charInputDate[--count] = '\0';
                        cout << "\b \b";
                    }
                    else if (isdigit(ch) && count < 2)
                    {
                        charInputDate[count++] = ch;
                        cout << ch;
                    }
                }
                break;
            }
            else
            {
                gotoxy(37, 3);
                cout << "    ";
                gotoxy(37, 3);
                count = 0;
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            charInputDate[--count] = '\0';
            cout << "\b \b";
        }
        else if (isdigit(ch) && count < 4)
        {
            charInputDate[count++] = ch;
            cout << ch;
        }
    }

    // Input 2
    drawRectangle(0, 4, 30, 2);
    drawRectangle(30, 4, 89, 2);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(30, 4);
    cout << char(197);
    gotoxy(30, 6);
    cout << char(193);
    gotoxy(119, 4);
    cout << char(180);
    count = 0;
    gotoxy(2, 5);
    cout << "Nhap Ngay Thu Hai";
    gotoxy(32, 5);
    cout << "Nam:           |Thang:         |Ngay:         ";
    gotoxy(37, 5);
    while (true)
    {
    namLap2:
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            // TAM DUNG SU DUNG NO DE DANH NEU DU TG
            //  if (ch == UP_ARROW)
            //  {
            //      dateChooseTable(inputDate);
            //  }
            continue;
        }
        else if (ch == TAB)
        {
            count = 0;
            gotoxy(37, 5);
            cout << "  ";
            gotoxy(70, 3);
            cout << "    ";
            gotoxy(70, 3);
            goto ngayLap;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            charInputDate[count] = '\0';
            ngayCuoi.year = stoi(charInputDate);
            if (ngayCuoi.year <= localTime->tm_year + 1900 && ngayCuoi.year >= ngayDau.year) // nam bat dau tu 1900 nen +1900 vao
            {
                gotoxy(55, 5);
                count = 0;
                while (true)
                {
                thangLap2:
                    ch = getch();
                    if (ch == 224)
                    {
                        ch = getch();
                        continue;
                    }
                    else if (ch == TAB)
                    {
                        gotoxy(55, 5);
                        cout << "  ";
                        gotoxy(37, 5);
                        count = 0;
                        cout << "    ";
                        gotoxy(37, 5);
                        goto namLap2;
                    }
                    else if (ch == ESC)
                    {
                        clearBottomScreen();
                        return;
                    }
                    else if (ch == ENTER && count > 0)
                    {
                        charInputDate[count] = '\0';
                        ngayCuoi.month = stoi(charInputDate);
                        if (((ngayCuoi.year == localTime->tm_year + 1900) &&
                             (ngayCuoi.month > localTime->tm_mon + 1)) ||
                            (ngayCuoi.month < ngayDau.month && ngayCuoi.year == ngayDau.year))
                        {
                            gotoxy(55, 5);
                            cout << "  ";
                            gotoxy(55, 5);
                            count = 0;
                            continue;
                        }
                        else if (ngayCuoi.month > 12)
                        {
                            gotoxy(55, 5);
                            cout << "  ";
                            gotoxy(55, 5);
                            count = 0;
                            continue;
                        }
                        else
                        {
                            gotoxy(70, 5);
                            count = 0;
                            //
                            while (true)
                            {
                            ngayLap2:
                                ch = getch();
                                if (ch == 224)
                                {
                                    ch = getch();
                                    continue;
                                }
                                else if (ch == TAB)
                                {

                                    gotoxy(70, 5);
                                    cout << "  ";
                                    gotoxy(55, 5);
                                    count = 0;
                                    cout << "  ";
                                    gotoxy(55, 5);
                                    goto thangLap2;
                                }
                                else if (ch == ESC)
                                {
                                    clearBottomScreen();
                                    return;
                                }
                                else if (ch == ENTER && count > 0)
                                {
                                    charInputDate[count] = '\0';
                                    ngayCuoi.day = stoi(charInputDate);
                                    if (ngayCuoi.month == 2)
                                    {
                                        if ((isNamNhuan(ngayCuoi.year) && ngayCuoi.day <= 29) &&
                                            (ngayCuoi.year > ngayDau.year ||
                                             (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                             (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                        {
                                            break;
                                        }
                                        else if ((!isNamNhuan(ngayCuoi.year) && ngayCuoi.day <= 28) &&
                                                 (ngayCuoi.year > ngayDau.year ||
                                                  (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                                  (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            gotoxy(70, 5);
                                            cout << "  ";
                                            gotoxy(70, 5);
                                            count = 0;
                                            continue;
                                        }
                                    }
                                    else if ((ngayCuoi.day <= 30 && (ngayCuoi.month == 4 || ngayCuoi.month == 6 || ngayCuoi.month == 9 || ngayCuoi.month == 11)) &&
                                             (ngayCuoi.year > ngayDau.year ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                    {
                                        break;
                                    }
                                    else if (ngayCuoi.day <= 31 &&
                                             (ngayCuoi.year > ngayDau.year ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        gotoxy(70, 5);
                                        cout << "  ";
                                        gotoxy(70, 5);
                                        count = 0;
                                        continue;
                                    }
                                }
                                else if (ch == '\b' && count > 0)
                                {
                                    charInputDate[--count] = '\0';
                                    cout << "\b \b";
                                }
                                else if (isdigit(ch) && count < 2)
                                {
                                    charInputDate[count++] = ch;
                                    cout << ch;
                                }
                            };
                        };
                        break;
                    }
                    else if (ch == '\b' && count > 0)
                    {
                        charInputDate[--count] = '\0';
                        cout << "\b \b";
                    }
                    else if (isdigit(ch) && count < 2)
                    {
                        charInputDate[count++] = ch;
                        cout << ch;
                    }
                }
                break;
            }
            else
            {
                gotoxy(37, 5);
                cout << "    ";
                gotoxy(37, 5);
                count = 0;
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            charInputDate[--count] = '\0';
            cout << "\b \b";
        }
        else if (isdigit(ch) && count < 4)
        {
            charInputDate[count++] = ch;
            cout << ch;
        }
    }
    //
    drawRectangle(0, 7, 30, 2);
    drawRectangle(30, 7, 40, 2);
    drawRectangle(70, 7, 49, 2);
    drawRectangle(0, 9, 30, 11);
    drawRectangle(30, 9, 40, 11);
    drawRectangle(70, 9, 49, 11);

    gotoxy(0, 9);
    cout << char(195);
    gotoxy(30, 7);
    cout << char(194);
    gotoxy(70, 7);
    cout << char(194);
    gotoxy(119, 9);
    cout << char(180);
    gotoxy(30, 9);
    cout << char(197);
    gotoxy(70, 9);
    cout << char(197);
    gotoxy(30, 20);
    cout << char(193);
    gotoxy(70, 20);
    cout << char(193);

    gotoxy(1, 8);
    cout << "Ma Vat Tu";
    gotoxy(31, 8);
    cout << "Ten VT";
    gotoxy(71, 8);
    cout << "Doanh Thu";
    // Xu Ly LOGIC
    DoanhThuVT doanhThu[soLuongVatTu];
    int soLuongVTCoDoanhThu = 0;
    // Duyet qua tat ca hoa don va lay gia tri
    HoaDon *currentHoaDon = ds_hd;

    while (currentHoaDon != nullptr)
    {
        if (currentHoaDon->loai == x && NamTrongKhoangTG(currentHoaDon->date, ngayDau, ngayCuoi))
        {
            CT_HoaDon *currentCTHoaDon = currentHoaDon->ds_ct_hoadon;

            while (currentCTHoaDon != nullptr)
            {
                if (isContainMaVTInDoanhThu(doanhThu, soLuongVTCoDoanhThu, currentCTHoaDon->maVT))
                {
                    int viTriMaVT = searchMaVTInDoanhThu(doanhThu, soLuongVTCoDoanhThu, currentCTHoaDon->maVT);
                    doanhThu[viTriMaVT].doanhthu += currentCTHoaDon->soLuong * currentCTHoaDon->donGia * (1 + currentCTHoaDon->vAT / 100);
                }
                else
                {
                    doanhThu[soLuongVTCoDoanhThu].doanhthu += currentCTHoaDon->soLuong * currentCTHoaDon->donGia * (1 + currentCTHoaDon->vAT / 100);
                    strcpy(doanhThu[soLuongVTCoDoanhThu].maVT, currentCTHoaDon->maVT);
                    soLuongVTCoDoanhThu += 1;
                };
                currentCTHoaDon = currentCTHoaDon->next;
            }
        }
        currentHoaDon = currentHoaDon->next;
    }

    if (soLuongVTCoDoanhThu == 0)
    {
        gotoxy(1, 10);
        cout << "None";
        gotoxy(31, 10);
        cout << "None";
        gotoxy(71, 10);
        cout << "None";
    }
    else
    {
        quickSortDoanhThu(doanhThu, 0, soLuongVTCoDoanhThu - 1);

        for (int i = soLuongVTCoDoanhThu - 1; i >= 0; i--)
        {
            gotoxy(2, 10 + (soLuongVTCoDoanhThu - 1 - i));
            cout << doanhThu[i].maVT;
            VatTu *foundVT = searchMaVT_DanhSachVatTu(ds_vt, doanhThu[i].maVT);
            gotoxy(32, 10 + (soLuongVTCoDoanhThu - 1 - i));
            cout << foundVT->tenVT;
            gotoxy(72, 10 + (soLuongVTCoDoanhThu - 1 - i));
            cout << fixed << setprecision(2) << doanhThu[i].doanhthu;
            if (i < soLuongVTCoDoanhThu - 9)
            {
                break;
            }
        }
    }

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == TAB)
        {
            goto start;
        }
        else if (ch == ESC)
        {
            return;
        }
    }
};

void clearThongKeTable()
{
    for (int i = 0; i < 13; i++)
    {
        gotoxy(2, 13 + i);
        cout << "                    ";
        gotoxy(25, 13 + i);
        cout << "           ";
        gotoxy(39, 13 + i);
        cout << "     ";
        gotoxy(47, 13 + i);
        cout << "                                ";
        gotoxy(83, 13 + i);
        cout << "                               ";
    }
}

void ThongKeHoaDonTrong1KhoangTG(DanhSachVatTu ds_vt, DanhSachNhanVien ds_nv, DanhSachHoaDon ds_hd, int soLuongVatTu, int soLuongNV)
{
    if (ds_vt == nullptr || ds_nv == nullptr || ds_hd == nullptr)
    {
        return;
    }
    //
    unsigned char ch;
    int count;
    Date ngayDau;
    Date ngayCuoi;
    char charInputDate[6];
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    bool backAllow = true;
//
//
start:
    clrscr();
    //
    gotoxy(0, 27);
    SetColor(0xA);
    cout << "ENTER:";
    SetColor(0xF);
    cout << " Accept  ";
    SetColor(0xA);
    cout << "TAB:";
    SetColor(0xF);
    cout << " Change DATE  ";
    SetColor(0xA);
    cout << "DOWN_ARROW:";
    SetColor(0xF);
    cout << " Move Down";
    gotoxy(0, 28);
    SetColor(0xA);
    cout << "ESC:";
    SetColor(0xF);
    cout << " Escape From Board    ";
    SetColor(0xA);
    cout << "-->:";
    SetColor(0xF);
    cout << " Next List     ";
    SetColor(0xA);
    cout << "<--:";
    SetColor(0xF);
    cout << " Previous List   ";
    SetColor(0xF);
    //
    count = 0;
    drawRectangle(0, 0, 119, 2);
    gotoxy(35, 1);
    SetColor(0x4);
    cout << "VUI LONG NHAP KHOANG THOI GIAN DE LIET KE HOA DON";
    SetColor(0xF);
    drawRectangle(0, 2, 30, 2);
    drawRectangle(30, 2, 89, 2);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(30, 2);
    cout << char(194);
    gotoxy(30, 4);
    cout << char(193);
    gotoxy(119, 2);
    cout << char(180);
    gotoxy(2, 3);
    cout << "Nhap Ngay Thu Nhat";
    gotoxy(32, 3);
    cout << "Nam:           |Thang:         |Ngay:         ";
    gotoxy(37, 3);
    while (true)
    {
    namLap:
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            // TAM DUNG SU DUNG NO DE DANH NEU DU TG
            //  if (ch == UP_ARROW)
            //  {
            //      dateChooseTable(inputDate);
            //  }
            continue;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            charInputDate[count] = '\0';
            ngayDau.year = stoi(charInputDate);
            if (ngayDau.year <= localTime->tm_year + 1900) // nam bat dau tu 1900 nen +1900 vao
            {
                gotoxy(55, 3);
                count = 0;
                while (true)
                {
                thangLap:
                    ch = getch();
                    if (ch == 224)
                    {
                        ch = getch();
                        continue;
                    }
                    else if (ch == TAB)
                    {
                        gotoxy(55, 3);
                        cout << "  ";
                        gotoxy(37, 3);
                        count = 0;
                        cout << "    ";
                        gotoxy(37, 3);
                        goto namLap;
                    }
                    else if (ch == ESC)
                    {
                        clearBottomScreen();
                        return;
                    }
                    else if (ch == ENTER && count > 0)
                    {
                        charInputDate[count] = '\0';
                        ngayDau.month = stoi(charInputDate);
                        if ((ngayDau.year == localTime->tm_year + 1900) && ngayDau.month > localTime->tm_mon + 1)
                        {
                            gotoxy(55, 3);
                            cout << "  ";
                            gotoxy(55, 3);
                            count = 0;
                            continue;
                        }
                        else if (ngayDau.month > 12)
                        {
                            gotoxy(55, 3);
                            cout << "  ";
                            gotoxy(55, 3);
                            count = 0;
                            continue;
                        }
                        else
                        {
                            gotoxy(70, 3);
                            count = 0;
                            //
                            while (true)
                            {
                            ngayLap:
                                ch = getch();
                                if (ch == 224)
                                {
                                    ch = getch();
                                    continue;
                                }
                                else if (ch == TAB)
                                {

                                    gotoxy(70, 3);
                                    cout << "  ";
                                    gotoxy(55, 3);
                                    count = 0;
                                    cout << "  ";
                                    gotoxy(55, 3);
                                    goto thangLap;
                                }
                                else if (ch == ESC)
                                {
                                    clearBottomScreen();
                                    return;
                                }
                                else if (ch == ENTER && count > 0)
                                {
                                    charInputDate[count] = '\0';
                                    ngayDau.day = stoi(charInputDate);
                                    if (ngayDau.month == 2)
                                    {
                                        if (isNamNhuan(ngayDau.year) && ngayDau.day <= 29)
                                        {
                                            break;
                                        }
                                        else if (!isNamNhuan(ngayDau.year) && ngayDau.day <= 28)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            gotoxy(70, 3);
                                            cout << "  ";
                                            gotoxy(70, 3);
                                            count = 0;
                                            continue;
                                        }
                                    }
                                    else if (ngayDau.day <= 30 && (ngayDau.month == 4 || ngayDau.month == 6 || ngayDau.month == 9 || ngayDau.month == 11))
                                    {
                                        break;
                                    }
                                    else if (ngayDau.day <= 31)
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        gotoxy(70, 3);
                                        cout << "  ";
                                        gotoxy(70, 3);
                                        count = 0;
                                        continue;
                                    }
                                }
                                else if (ch == '\b' && count > 0)
                                {
                                    charInputDate[--count] = '\0';
                                    cout << "\b \b";
                                }
                                else if (isdigit(ch) && count < 2)
                                {
                                    charInputDate[count++] = ch;
                                    cout << ch;
                                }
                            };
                        };
                        break;
                    }
                    else if (ch == '\b' && count > 0)
                    {
                        charInputDate[--count] = '\0';
                        cout << "\b \b";
                    }
                    else if (isdigit(ch) && count < 2)
                    {
                        charInputDate[count++] = ch;
                        cout << ch;
                    }
                }
                break;
            }
            else
            {
                gotoxy(37, 3);
                cout << "    ";
                gotoxy(37, 3);
                count = 0;
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            charInputDate[--count] = '\0';
            cout << "\b \b";
        }
        else if (isdigit(ch) && count < 4)
        {
            charInputDate[count++] = ch;
            cout << ch;
        }
    }

    // Input 2
    drawRectangle(0, 4, 30, 2);
    drawRectangle(30, 4, 89, 2);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(30, 4);
    cout << char(197);
    gotoxy(30, 6);
    cout << char(193);
    gotoxy(119, 4);
    cout << char(180);
    count = 0;
    gotoxy(2, 5);
    cout << "Nhap Ngay Thu Hai";
    gotoxy(32, 5);
    cout << "Nam:           |Thang:         |Ngay:         ";
    gotoxy(37, 5);
    while (true)
    {
    namLap2:
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            // TAM DUNG SU DUNG NO DE DANH NEU DU TG
            //  if (ch == UP_ARROW)
            //  {
            //      dateChooseTable(inputDate);
            //  }
            continue;
        }
        else if (ch == TAB)
        {
            count = 0;
            gotoxy(37, 5);
            cout << "  ";
            gotoxy(70, 3);
            cout << "    ";
            gotoxy(70, 3);
            goto ngayLap;
        }
        else if (ch == ESC)
        {
            clearBottomScreen();
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            charInputDate[count] = '\0';
            ngayCuoi.year = stoi(charInputDate);
            if (ngayCuoi.year <= localTime->tm_year + 1900 && ngayCuoi.year >= ngayDau.year) // nam bat dau tu 1900 nen +1900 vao
            {
                gotoxy(55, 5);
                count = 0;
                while (true)
                {
                thangLap2:
                    ch = getch();
                    if (ch == 224)
                    {
                        ch = getch();
                        continue;
                    }
                    else if (ch == TAB)
                    {
                        gotoxy(55, 5);
                        cout << "  ";
                        gotoxy(37, 5);
                        count = 0;
                        cout << "    ";
                        gotoxy(37, 5);
                        goto namLap2;
                    }
                    else if (ch == ESC)
                    {
                        clearBottomScreen();
                        return;
                    }
                    else if (ch == ENTER && count > 0)
                    {
                        charInputDate[count] = '\0';
                        ngayCuoi.month = stoi(charInputDate);
                        if (((ngayCuoi.year == localTime->tm_year + 1900) &&
                             (ngayCuoi.month > localTime->tm_mon + 1)) ||
                            (ngayCuoi.month < ngayDau.month && ngayCuoi.year == ngayDau.year))
                        {
                            gotoxy(55, 5);
                            cout << "  ";
                            gotoxy(55, 5);
                            count = 0;
                            continue;
                        }
                        else if (ngayCuoi.month > 12)
                        {
                            gotoxy(55, 5);
                            cout << "  ";
                            gotoxy(55, 5);
                            count = 0;
                            continue;
                        }
                        else
                        {
                            gotoxy(70, 5);
                            count = 0;
                            //
                            while (true)
                            {
                            ngayLap2:
                                ch = getch();
                                if (ch == 224)
                                {
                                    ch = getch();
                                    continue;
                                }
                                else if (ch == TAB)
                                {

                                    gotoxy(70, 5);
                                    cout << "  ";
                                    gotoxy(55, 5);
                                    count = 0;
                                    cout << "  ";
                                    gotoxy(55, 5);
                                    goto thangLap2;
                                }
                                else if (ch == ESC)
                                {
                                    clearBottomScreen();
                                    return;
                                }
                                else if (ch == ENTER && count > 0)
                                {
                                    charInputDate[count] = '\0';
                                    ngayCuoi.day = stoi(charInputDate);
                                    if (ngayCuoi.month == 2)
                                    {
                                        if ((isNamNhuan(ngayCuoi.year) && ngayCuoi.day <= 29) &&
                                            (ngayCuoi.year > ngayDau.year ||
                                             (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                             (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                        {
                                            break;
                                        }
                                        else if ((!isNamNhuan(ngayCuoi.year) && ngayCuoi.day <= 28) &&
                                                 (ngayCuoi.year > ngayDau.year ||
                                                  (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                                  (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            gotoxy(70, 5);
                                            cout << "  ";
                                            gotoxy(70, 5);
                                            count = 0;
                                            continue;
                                        }
                                    }
                                    else if ((ngayCuoi.day <= 30 && (ngayCuoi.month == 4 || ngayCuoi.month == 6 || ngayCuoi.month == 9 || ngayCuoi.month == 11)) &&
                                             (ngayCuoi.year > ngayDau.year ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                    {
                                        break;
                                    }
                                    else if (ngayCuoi.day <= 31 &&
                                             (ngayCuoi.year > ngayDau.year ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month > ngayDau.month) ||
                                              (ngayCuoi.year == ngayDau.year && ngayCuoi.month == ngayDau.month && ngayCuoi.day >= ngayDau.day)))
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        gotoxy(70, 5);
                                        cout << "  ";
                                        gotoxy(70, 5);
                                        count = 0;
                                        continue;
                                    }
                                }
                                else if (ch == '\b' && count > 0)
                                {
                                    charInputDate[--count] = '\0';
                                    cout << "\b \b";
                                }
                                else if (isdigit(ch) && count < 2)
                                {
                                    charInputDate[count++] = ch;
                                    cout << ch;
                                }
                            };
                        };
                        break;
                    }
                    else if (ch == '\b' && count > 0)
                    {
                        charInputDate[--count] = '\0';
                        cout << "\b \b";
                    }
                    else if (isdigit(ch) && count < 2)
                    {
                        charInputDate[count++] = ch;
                        cout << ch;
                    }
                }
                break;
            }
            else
            {
                gotoxy(37, 5);
                cout << "    ";
                gotoxy(37, 5);
                count = 0;
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            charInputDate[--count] = '\0';
            cout << "\b \b";
        }
        else if (isdigit(ch) && count < 4)
        {
            charInputDate[count++] = ch;
            cout << ch;
        }
    }
    // XU Li
    drawRectangle(0, 6, 119, 2);
    drawRectangle(0, 8, 59, 2);
    drawRectangle(59, 8, 60, 2);
    drawRectangle(0, 10, 24, 2);
    drawRectangle(24, 10, 14, 2);
    drawRectangle(38, 10, 8, 2);
    drawRectangle(46, 10, 36, 2);
    drawRectangle(82, 10, 37, 2);
    drawRectangle(0, 12, 24, 14);
    drawRectangle(24, 12, 14, 14);
    drawRectangle(38, 12, 8, 14);
    drawRectangle(46, 12, 36, 14);
    drawRectangle(82, 12, 37, 14);
    gotoxy(0, 6);
    cout << char(195);
    gotoxy(0, 8);
    cout << char(195);
    gotoxy(0, 10);
    cout << char(195);
    gotoxy(0, 12);
    cout << char(195);
    gotoxy(119, 6);
    cout << char(180);
    gotoxy(119, 8);
    cout << char(180);
    gotoxy(119, 10);
    cout << char(180);
    gotoxy(119, 12);
    cout << char(180);
    gotoxy(30, 6);
    cout << char(193);
    gotoxy(59, 8);
    cout << char(194);
    gotoxy(59, 10);
    cout << char(193);
    gotoxy(24, 10);
    cout << char(194);
    gotoxy(38, 10);
    cout << char(194);
    gotoxy(46, 10);
    cout << char(194);
    gotoxy(82, 10);
    cout << char(194);
    gotoxy(24, 12);
    cout << char(197);
    gotoxy(38, 12);
    cout << char(197);
    gotoxy(46, 12);
    cout << char(197);
    gotoxy(82, 12);
    cout << char(197);
    gotoxy(24, 26);
    cout << char(193);
    gotoxy(38, 26);
    cout << char(193);
    gotoxy(46, 26);
    cout << char(193);
    gotoxy(82, 26);
    cout << char(193);

    // Số HĐ 20		Ngày lập xx/xx/xxxx 10     Loại HĐ 4		Họ tên NV lập 31		Trị giá hóa đơn 30
    //
    gotoxy(34, 7);
    SetColor(0x4);
    cout << "BANG LIET KE HOA DON TRONG KHOANG THOI GIAN (dd/mm/yyyy)";
    SetColor(0xF);

    gotoxy(7, 11);
    cout << "So Hoa Don";
    gotoxy(27, 11);
    cout << "Ngay Lap";
    gotoxy(39, 11);
    cout << "Loai HD";
    gotoxy(52, 11);
    cout << "Ho Va Ten Nhan Vien Lap";
    gotoxy(93, 11);
    cout << "Tri Gia Hoa Don";

    gotoxy(20, 9);
    cout << "TU NGAY: ";
    if (ngayDau.day < 10)
    {
        cout << '0';
    }
    cout << ngayDau.day << '/';
    if (ngayDau.month < 10)
    {
        cout << '0';
    }
    cout << ngayDau.month << '/';
    cout << ngayDau.year;

    gotoxy(80, 9);
    cout << "DEN NGAY: ";
    if (ngayCuoi.day < 10)
    {
        cout << '0';
    }
    cout << ngayCuoi.day << '/';
    if (ngayCuoi.month < 10)
    {
        cout << '0';
    }
    cout << ngayCuoi.month << '/';
    cout << ngayCuoi.year;

    //
    count = 0;
    int max = 13;
    HoaDon *currentHoaDon = ds_hd;
    int sizeARR = 1;
    int Page = 1;
    int this_nhanvien;
    HoaDon **firstPagePosHoaDon = new HoaDon *[1];
    while (currentHoaDon != nullptr && count < max)
    {
        if (NamTrongKhoangTG(currentHoaDon->date, ngayDau, ngayCuoi))
        {
            this_nhanvien = TimNhanVienTheoSoHD(ds_nv, soLuongNV, currentHoaDon->soHD);
            CT_HoaDon *current_CT = currentHoaDon->ds_ct_hoadon;
            double tongTriGia = 0;

            if (Page == sizeARR && currentHoaDon != nullptr)
            {
                firstPagePosHoaDon[sizeARR - 1] = currentHoaDon;
                expandArray(firstPagePosHoaDon, sizeARR, sizeARR + 1);
                sizeARR++;
            }

            while (current_CT != nullptr)
            {
                tongTriGia += current_CT->soLuong * current_CT->donGia * (1 + (current_CT->vAT / 100.0));
                current_CT = current_CT->next;
            }

            gotoxy(2, 26 - (max - count));
            cout << currentHoaDon->soHD;
            gotoxy(26, 26 - (max - count));
            if (currentHoaDon->date.day < 10)
            {
                cout << '0';
            }
            cout << ngayDau.day << '/';
            if (currentHoaDon->date.month < 10)
            {
                cout << '0';
            }
            cout << currentHoaDon->date.month << "/";
            cout << setw(4) << setfill('0') << currentHoaDon->date.year;
            gotoxy(40, 26 - (max - count));
            if (currentHoaDon->loai == n)
            {
                cout << "Nhap";
            }
            else
            {
                cout << "Xuat";
            }
            gotoxy(48, 26 - (max - count));
            cout << ds_nv[this_nhanvien]->ho << " " << ds_nv[this_nhanvien]->ten;
            gotoxy(84, 26 - (max - count));
            cout << fixed << setprecision(2) << tongTriGia;

            count++;
        }
        currentHoaDon = currentHoaDon->next;

        if (count >= max || currentHoaDon == nullptr)
        {
            while (true)
            {
                ch = getch();
                if (ch == 224)
                {
                    ch = getch();
                    if (ch == RIGHT_ARROW && currentHoaDon != nullptr)
                    {
                        count += 13;
                        max = count + 13;
                        Page += 1;
                        clearThongKeTable();
                        break;
                    }
                    else if (ch == LEFT_ARROW && Page > 1)
                    {
                        max = max - 13;
                        count = max - 13;
                        Page -= 1;
                        currentHoaDon = firstPagePosHoaDon[Page - 1];
                        clearThongKeTable();
                        break;
                    }
                }
                else if (ch == TAB)
                {
                    goto start;
                }
                else if (ch == ESC)
                {
                    return;
                }
            }
            continue;
        }
    }
}

void ThongKeDoanhThuTrong1Nam(DanhSachVatTu ds_vt, DanhSachNhanVien ds_nv, DanhSachHoaDon ds_hd, int soLuongVatTu, int SoLuongNV)
{
    unsigned char ch;
    int count;
    int years;
    char charInputDate[6];
start:
    clrscr();
    count = 0;

    //
    //
    gotoxy(0, 27);
    SetColor(0xA);
    cout << "ENTER:";
    SetColor(0xF);
    cout << " Accept  ";
    SetColor(0xA);
    cout << "TAB:";
    SetColor(0xF);
    cout << " Change DATE  ";
    SetColor(0xA);
    cout << "DOWN_ARROW:";
    SetColor(0xF);
    cout << " Move Down";
    gotoxy(0, 28);
    SetColor(0xA);
    cout << "ESC:";
    SetColor(0xF);
    cout << " Escape From Board    ";
    SetColor(0xA);
    cout << "-->:";
    SetColor(0xF);
    cout << " Next List     ";
    SetColor(0xA);
    cout << "<--:";
    SetColor(0xF);
    cout << " Previous List   ";
    SetColor(0xF);
    //
    drawRectangle(0, 0, 119, 2);
    gotoxy(40, 1);
    SetColor(0x4);
    cout << "BANG THONG KE DOANH THU NAM: ";
    SetColor(0xF);
    gotoxy(69, 1);
    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
        }
        else if (ch == ESC)
        {
            return;
        }
        else if (ch == ENTER && count > 0)
        {
            charInputDate[count] = '\0';
            years = stoi(charInputDate);
            if (years > 0 && years <= 2024)
            {
                gotoxy(1, 3);
                cout << "                   ";
                break;
            }
            else
            {
                gotoxy(1, 3);
                cout << "So Nam Khong Hop Le";
                gotoxy(69 + count, 1);
                continue;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            charInputDate[--count] = '\0';
        }
        else if (isdigit(ch) && count < 4)
        {
            charInputDate[count++] = ch;
            cout << ch;
        }
    }
    //
    drawRectangle(0, 2, 59, 2);
    drawRectangle(59, 2, 60, 2);
    drawRectangle(0, 4, 59, 13);
    drawRectangle(59, 4, 60, 13);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(119, 2);
    cout << char(180);
    gotoxy(0, 4);
    cout << char(195);
    gotoxy(119, 4);
    cout << char(180);
    gotoxy(59, 2);
    cout << char(194);
    gotoxy(59, 4);
    cout << char(197);
    gotoxy(59, 17);
    cout << char(193);
    gotoxy(27, 3);
    cout << "THANG";
    gotoxy(84, 3);
    cout << "DOANH THU";
    // Khai Bao Tien Xu Ly
    double doanhThuThang[12] = {0};
    // Xu Ly
    HoaDon *currentHoaDon = ds_hd;
    while (currentHoaDon != nullptr)
    {
        if (currentHoaDon->date.year == years)
        {
            CT_HoaDon *currentCT = currentHoaDon->ds_ct_hoadon;
            while (currentCT != nullptr)
            {
                if (currentHoaDon->loai == n)
                {
                    doanhThuThang[currentHoaDon->date.month - 1] -= currentCT->soLuong * currentCT->donGia * (1 + (currentCT->vAT / 100.0));
                }
                else
                {
                    doanhThuThang[currentHoaDon->date.month - 1] += currentCT->soLuong * currentCT->donGia * (1 + (currentCT->vAT / 100.0));
                }
                currentCT = currentCT->next;
            }
        }
        currentHoaDon = currentHoaDon->next;
    }

    for (int i = 0; i < 12; i++)
    {
        gotoxy(2, 5 + i);
        cout << "Thang " << i + 1;
        gotoxy(61, 5 + i);
        cout << fixed << setprecision(2) << doanhThuThang[i];
    }

    while (true)
    {
        ch = getch();
        if (ch == TAB)
        {
            goto start;
        }
        else if (ch == ESC)
        {
            return;
        }
    }
}

void menu(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_cthd, DanhSachNhanVien &ds_nv, int &soLuongNhanVienCount)
{
    int choose1 = 0;
    int choose2 = 0;
    int CurrentScreenWidth = getConsoleWidth();
    int CurrentScreenHeight = getConsoleHeight();
    char c1;
    char c2;
    clrscr();
    DrawFirstUI(choose1);
    while (true)
    {
        GetFirstUIInput(c1, choose1);
        switch (choose1)
        {
        case 0:
        {
            choose2 = 0;
            DrawSeccondUIVatTu(choose2);
            GetSeccondUIVatTuInput(c2, choose2);
            switch (choose2)
            {
            case 0:
            {
                clrscr();
                ThemVatTu(ds_vt);
                // Sleep(2000);
                clrscr();
                break;
            }
            case 1:
            {
                clrscr();
                // DrawAdjustVatTuContactGuide();
                HieuChinhVatTu(ds_vt);
                Sleep(2000);
                clrscr();
                break;
            }
            case 2:
            {
                clrscr();
                // DrawRemoveVatTuContactGuide();
                XoaVatTu(ds_vt, SoLuongVatTuGlobalCount);
                // Sleep(2000);
                clrscr();
                break;
            }
            case 3:
            {
                clrscr();
                gotoxy(0, 0);
                HienThiVatTu(ds_vt, SoLuongVatTuGlobalCount);
                clrscr();
                break;
            }
            case 4:
            {
                clrscr();
                gotoxy(0, 0);
                In10VatTuDoanhThuCaoNhat(ds_vt, ds_nv, ds_hd, SoLuongVatTuGlobalCount, soLuongNhanVienCount);
                clrscr();
                break;
            }
            case -1:
            {
                clrscr();
                break;
            }
            }
            DrawFirstUI(choose1);
            break;
        }
        case 1:
        {
            choose2 = 0;
            DrawSeccondUINhanVien(choose2);
            GetSeccondUINhanVienInput(c2, choose2);
            switch (choose2)
            {
            case 0:
            {
                gotoxy(0, 0);
                clrscr();
                ThemNhanVien(ds_nv, soLuongNhanVienGlobalCount);
                // if (isAdministrative())
                // {
                //     clrscr();
                //     ThemNhanVien(ds_nv, soLuongNhanVienGlobalCount);
                // }
                // else
                // {
                //     gotoxy(20, 20);
                //     cout << "NONONONONO";
                //     Sleep(3000);
                // }
                clrscr();
                break;
            }
            case 1:
            {
                gotoxy(0, 0);
                clrscr();
                HienThiNhanVien(ds_nv, soLuongNhanVienCount);
                clrscr();
                break;
            }
            case -1:
            {
                clrscr();
                break;
            }
            }
            //
            DrawFirstUI(choose1);
            break;
        }
        case 2:
        {
            char inputMaNV[11];
            //
            if (!isNhanVien(ds_nv, inputMaNV, soLuongNhanVienGlobalCount))
            {
                clrscr();
                DrawFirstUI(choose1);
                break;
            }
            ////////////////////////
            choose2 = 0;
            while (true)
            {
                DrawFirstUI(choose1);
                DrawSeccondUIHoaDon(choose2);
                GetSeccondUIHoaDonInput(c2, choose2);
                clrscr();
                gotoxy(30, 10);
                if (choose2 == 0)
                {
                    LapHoaDonNhap(ds_vt, ds_hd, ds_nv, soLuongNhanVienCount, inputMaNV);
                    clrscr();
                    continue;
                }
                else if (choose2 == 1)
                {
                    LapHoaDonXuat(ds_vt, ds_hd, ds_nv, soLuongNhanVienCount, inputMaNV);
                    clrscr();
                    continue;
                }
                else if (choose2 == 2)
                {
                    InHoaDonTheoSoHoaDon(ds_hd, ds_vt, ds_nv, soLuongNhanVienCount);
                    clrscr();
                    continue;
                }
                else if (choose2 == 3)
                {
                    ThongKeHoaDonTrong1KhoangTG(ds_vt, ds_nv, ds_hd, SoLuongVatTuGlobalCount, soLuongNhanVienCount);
                    clrscr();
                    continue;
                }
                else if (choose2 == -1)
                {
                    break;
                }
            }
            //
            clrscr();
            DrawFirstUI(choose1);
            break;
        }
        case 3:
        {
            clrscr();
            ThongKeDoanhThuTrong1Nam(ds_vt, ds_nv, ds_hd, SoLuongVatTuGlobalCount, soLuongNhanVienCount);
            clrscr();
            DrawFirstUI(choose1);
            break;
        }
        case 4:
        {
            clrscr();
            gotoxy(0, 0);
            cout << "Sao Luu Du Lieu";
            saveVatTuToFile(ds_vt, "vattu.txt");
            saveAllDataToFile(ds_nv, "data.txt", soLuongNhanVienGlobalCount);
            // int a = searchNhanVienFromDSNV(ds_nv, "1", soLuongNhanVienCount);
            // DanhSachHoaDon hoadon = ds_nv[a]->ds_hoadon;
            // while (hoadon != nullptr)
            // {
            //     cout << hoadon->soHD << endl;
            //     hoadon = hoadon->next;
            // }
            getch();
            clrscr();
            DrawFirstUI(choose1);
            break;
        }
        }
    }
}

int main()
{
    DanhSachHoaDon ds_hd = nullptr;
    DanhSach_CT_HoaDon ds_cthd = nullptr;
    DanhSachNhanVien ds_nv;
    DanhSachVatTu ds_vt = nullptr;

    insertAllDataByFile(ds_nv, "data.txt", soLuongNhanVienGlobalCount, ds_hd, ds_cthd);
    insertVatTuByFile(ds_vt, "vattu.txt");

    menu(ds_vt, ds_hd, ds_cthd, ds_nv, soLuongNhanVienGlobalCount);
}