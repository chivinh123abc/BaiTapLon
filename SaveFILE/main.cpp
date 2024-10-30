#include "drawFormatCode.cpp"
#include "vattu.cpp"
#include "stack.cpp"
#include <ctime>
#include "nhanvien.cpp"
#include "hoadon.cpp"
#include <vector>

const int firstItems = 4;
const int seccondVatTuItems = 5;
const int seccondNhanVienItems = 2;
const int seccondHoaDonItems = 3;
const int thirdHoaDonItems = 4;
const int xUI1 = 0;
const int yUI1 = 10;
const int xUI2 = 30;
const int yUI2 = 10;
const int ENTER = 13;
const int ESC = 27;
const int UP_ARROW = 72;
const int DOWN_ARROW = 80;
const int LEFT_ARROW = 75;
const int RIGHT_ARROW = 77;
const char TEN_TK_ADMIN[] = "admin";
const char MK_ADMIN[] = "admin";
const char specialChars[] = "!@#$%^&*(),.-";
const int SCREEN_WIDTH = getConsoleWidth();
const int SCREEN_HEIGHT = getConsoleHeight();

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
    "         In Danh Sach Hoa Don         "
    //
};

char thirdHoaDonUI[thirdHoaDonItems][50]{
    "           Them Chi Tiet Hoa Don           ",
    "           Xoa Chi Tiet Hoa Don            ",
    "           Huy Hoa Don Hien Tai            ",
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
    SetColor(0x1);
    SetBGColor(0x3);
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

void DrawFirstUI(int choose1)
{
    for (int iy = 0; iy < firstItems; iy++)
    {
        gotoxy(xUI1, yUI1 + iy);
        cout << firstUI[iy];
    }
    SetHighLight();
    gotoxy(xUI1, yUI1 + choose1);
    cout << firstUI[choose1];
    SetNormalColor();
}

void DrawSeccondUIVatTu(int choose2)
{
    for (int iy = 0; iy < seccondVatTuItems; iy++)
    {
        gotoxy(xUI2, yUI2 + iy);
        cout << seccondVatTuUI[iy];
    }
    SetHighLight();
    gotoxy(xUI2, yUI2 + choose2);
    cout << seccondVatTuUI[choose2];
    SetNormalColor();
}

void DrawSeccondUINhanVien(int choose2)
{
    for (int iy = 0; iy <= seccondNhanVienItems; iy++)
    {
        gotoxy(xUI2, yUI2 + iy);
        cout << seccondNhanVienUI[iy];
    }
    SetHighLight();
    gotoxy(xUI2, yUI2 + choose2);
    cout << seccondNhanVienUI[choose2];
    SetNormalColor();
};

void DrawSeccondUIHoaDon(int choose2)
{
    for (int iy = 0; iy <= seccondHoaDonItems; iy++)
    {
        gotoxy(xUI2, yUI2 + iy);
        cout << seccondHoaDonUI[iy];
    }
    SetHighLight();
    gotoxy(xUI2, yUI2 + choose2);
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

int GetSeccondUIVatTuInput(char &c2, int &choose2)
{
    while (true)
    {
        c2 = getch();
        switch (c2)
        {
        case DOWN_ARROW:
        {
            if (choose2 == seccondVatTuItems - 1)
            {
                choose2 = 0;
            }
            else
            {
                choose2++;
            }
            DrawSeccondUIVatTu(choose2);
            break;
        }
        case UP_ARROW:
        {
            if (choose2 == 0)
            {
                choose2 = seccondVatTuItems - 1;
            }
            else
            {
                choose2--;
            }
            DrawSeccondUIVatTu(choose2);
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
    cout << "Button Guide";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "Enter: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "Esc: Stop Program";
    drawRectangle(80, 8, 31, 4);
    gotoxy(87, 10);
    SetColor(0x2);
    cout << "Input Restrictions";
    SetColor(0xF);
    drawRectangle(80, 12, 31, 2);
    gotoxy(86, 13);
    cout << "Ten vat tu (50 char)";
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
    cout << "Button Guide";
    SetColor(0xF);
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "Enter: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "Esc: Stop Program";
    drawRectangle(80, 8, 31, 2);
    gotoxy(86, 9);
    cout << "->: Open Vat Tu List";
    drawRectangle(80, 10, 31, 2);
    gotoxy(87, 11);
    cout << "<-: Previous List";
    drawRectangle(80, 12, 31, 4);
    gotoxy(87, 14);
    SetColor(0x2);
    cout << "Input Restrictions";
    SetColor(0xF);
    drawRectangle(80, 16, 31, 2);
    gotoxy(86, 17);
    cout << "Ten vat tu (50 char)";
    drawRectangle(80, 18, 31, 2);
    gotoxy(86, 19);
    cout << "Don vi tinh(10 char)";
    drawRectangle(80, 20, 31, 2);
    gotoxy(81, 21);
    cout << "So Luong Ton (Under 1 billion)";
    drawRectangle(80, 22, 31, 4);
    gotoxy(87, 23);
    cout << "Leave fields empty";
    gotoxy(86, 24);
    cout << "when you do not want";
    gotoxy(86, 25);
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
    gotoxy(80, 12);
    cout << char(195);
    gotoxy(111, 12);
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
    gotoxy(80, 22);
    cout << char(195);
    gotoxy(111, 22);
    cout << char(180);
}

void DrawRemoveVatTuContactGuide()
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

// THEM VAT TU
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void ThemVatTu(DanhSachVatTu &ds_vt)
{
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 15, 2);
    drawRectangle(15, 2, 55, 2);
    //
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(15, 2);
    cout << char(194);
    gotoxy(15, 4);
    cout << char(193);
    gotoxy(70, 2);
    cout << char(180);
    //
    gotoxy(24, 1);
    SetColor(0xC);
    cout << "Them thong tin vat tu" << endl;
    SetColor(0xF);
    // int choice = -1;
    char inputMaVT[11];
    int count = 0;
    unsigned char ch;
    //
    gotoxy(3, 3);
    cout << "Ma Vat Tu";
    gotoxy(17, 3);
    // dinhDangMaVatTu(inputMaVT, "vt", idVatTuGlobalCount);
    // cout << "maVT cua ban la " << inputMaVT << endl;
    while (true)
    {

        ch = getch();

        if (ch == 224)
        {
            ch = getch();
            continue;
        }
        else if (count > 0 && ch == 13)
        {
            inputMaVT[count] = '\0';
            trim(inputMaVT);
            if (isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
            {
                gotoxy(2, 7);
                SetErrorColor();
                cout << "Cay da ton tai vat tu [" << inputMaVT << "]" << endl;
                count = 0;
                strcpy(inputMaVT, "");
                SetNormalColor();
                gotoxy(18, 5);
                cout << "                                                  ";
                gotoxy(18, 5);
                continue;
            }
            else
            {
                gotoxy(2, 7);
                cout << "                                                                  ";
                break;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputMaVT[--count] = '\0';
        }
        else if ((isalnum(ch) || ch == ' ') && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            inputMaVT[count++] = ch;
        }
        else if (ch == ESC)
        {
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
    }
    cout << endl;

    char inputTenVT[51];
    count = 0;
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
    //
    gotoxy(3, 5);
    cout << "Ten Vat Tu";
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
        else if (count > 0 && ch == 13)
        {
            inputTenVT[count] = '\0';
            trim(inputTenVT);
            if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
            {
                gotoxy(2, 7);
                SetErrorColor();
                cout << "Cay da ton tai vat tu [" << inputTenVT << "]" << endl;
                count = 0;
                strcpy(inputTenVT, "");
                SetNormalColor();
                gotoxy(18, 5);
                cout << "                                                  ";
                gotoxy(18, 5);
                continue;
            }
            else
            {
                gotoxy(2, 7);
                cout << "                                                                  ";
                break;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputTenVT[--count] = '\0';
        }
        else if ((isalnum(ch) || ch == ' ') && count < 50)
        {
            cout << ch;
            ch = tolower(ch);
            inputTenVT[count++] = ch;
        }
        else if (ch == ESC)
        {
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
    }
    cout << endl;
    //

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
    gotoxy(2, 7);
    char inputDVT[11];
    count = 0;
    cout << "Don Vi Tinh";
    gotoxy(18, 7);

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
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
            gotoxy(0, 9);
            cout << "Quit";
            return;
        }
    }
    cout << endl;

    char inputC_SoLuongTon[10];
    count = 0;
    //
    drawRectangle(0, 8, 15, 2);
    drawRectangle(15, 8, 55, 2);
    gotoxy(0, 8);
    cout << char(195);
    gotoxy(15, 8);
    cout << char(197);
    gotoxy(15, 10);
    cout << char(193);
    gotoxy(70, 8);
    cout << char(180);
    //
    gotoxy(2, 9);
    cout << "So luong ton";
    gotoxy(18, 9);

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
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
            gotoxy(0, 11);
            cout << "Quit";
            return;
        }
    }
    cout << endl;

    int inputSoLuongTon = stoi(inputC_SoLuongTon);

    DanhSachVatTu dsvt_moi = newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon);
    insertDanhSachVatTu(ds_vt, dsvt_moi);
    gotoxy(0, 11);
    cout << "Successful";
}

// HIEU CHINH VAT TU
//+++++++++++++++++++++++++++++++++++++++++++

// Dung de ho tro ve lai vung nhap input
void HieuChinhVatTuDrawSupport()
{
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 70, 2);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(70, 2);
    cout << char(180);
    gotoxy(22, 1);
    SetColor(0xC);
    cout << "Hieu Chinh Thong Tin Vat Tu" << endl;
    SetColor(0xF);
    gotoxy(15, 3);
    cout << "Nhap ma vat tu cua vat tu can hieu chinh";
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
    gotoxy(4, 5);
    cout << "Ma Vat Tu";
    gotoxy(18, 5);
}

// NOTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
void NoiDungVatTu(DanhSachVatTu ds_vt, char noidung[11], int &dem, int SoLuongVatTu)
{
    unsigned char c;
    // dem trang va luu ptr vs stack tai vi tri day
    int Page = 1;
    int arr2Size = 1;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    char pageMaVTData[15][11];
    //
    VatTu *current_vt = ds_vt;
    VatTuStack vtStack;
    // dem de gioi han so luong
    int count = 1;
    int max = 15;
    //
    int ptrY = 0;
    //
    clearShowVatTuBoard();
    while (current_vt != nullptr || !vtStack.isEmpty())
    {
        while (current_vt != nullptr)
        {
            vtStack.push(current_vt);
            current_vt = current_vt->left;
        }

        if (Page == arr2Size)
        {
            PageStack[arr2Size - 1] = vtStack;
            expandArray(PageStack, arr2Size, Page + 1);
        }

        current_vt = vtStack.pop();
        //
        if (Page == arr2Size && current_vt != nullptr)
        {
            firstPagePos[arr2Size - 1] = current_vt;
            expandArray(firstPagePos, arr2Size, Page + 1);
            arr2Size += 1;
        }

        gotoxy(3, 21 - (max - count));
        cout << current_vt->maVT;
        gotoxy(18, 21 - (max - count));
        cout << current_vt->tenVT;
        gotoxy(71, 21 - (max - count));
        cout << current_vt->dVT;
        gotoxy(99, 21 - (max - count));
        cout << current_vt->soLuongTon;
        strcpy(pageMaVTData[14 - (max - count)], current_vt->maVT);
        count++;

        if (count > max || count > SoLuongVatTu)
        {
            gotoxy(0, 7 + ptrY);
            SetColor(0x4);
            cout << "->";
            SetColor(0xF);
            while (true)
            {
                c = getch();
                if (c == 224)
                {
                    c = getch();
                    if (c == RIGHT_ARROW && max < SoLuongVatTu)
                    {
                        count = max + 1;
                        max = count + 14;
                        Page++;
                        clearShowVatTuBoard();
                        break;
                    }
                    else if (c == LEFT_ARROW && Page > 1)
                    {
                        Page--;
                        current_vt = firstPagePos[Page - 1];
                        vtStack = PageStack[Page - 1];
                        max -= 15;
                        count = max - 14;
                        clearShowVatTuBoard();
                        break;
                    }
                    else if (c == DOWN_ARROW && ptrY < 13 - (max - count))
                    {
                        gotoxy(0, 7 + ptrY);
                        cout << char(179) << " ";
                        ptrY += 1;
                        gotoxy(0, 7 + ptrY);
                        SetColor(0x4);
                        cout << "->";
                        SetColor(0xF);
                        continue;
                    }
                    else if (c == UP_ARROW && ptrY > 0)
                    {
                        gotoxy(0, 7 + ptrY);
                        cout << char(179) << " ";
                        ptrY -= 1;
                        gotoxy(0, 7 + ptrY);
                        SetColor(0x4);
                        cout << "->";
                        SetColor(0xF);
                        continue;
                    }
                }
                else if (c == ESC)
                {
                    return;
                }
                else if (c == ENTER && ptrY < 14 - (max - count))
                {
                    gotoxy(0, 0);
                    strcpy(noidung, pageMaVTData[ptrY]);
                    dem = strlen(noidung);
                    return;
                }
            }
        }

        current_vt = current_vt->right;
    }
}

void HienThiVatTuDangCoTrongHieuChinh(DanhSachVatTu ds_vt, char noidung[11], int &dem, int SoLuongVatTu)
{
    if (ds_vt == nullptr)
    {
        cout << "Danh Sach Dang Trong";
        gotoxy(18, 5);
    }
    else
    {
        //
        gotoxy(0, 27);
        SetColor(0xA);
        cout << "ENTER:";
        SetColor(0xF);
        cout << " Choose This MaVT  ";
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
        NoiDungVatTu(ds_vt, noidung, dem, SoLuongVatTu);
    }
}

void HieuChinhVatTu(DanhSachVatTu &ds_vt)
{
    int count = 0;
    char inputMaVT[11];
    unsigned char ch;

    HieuChinhVatTuDrawSupport();

    while (true)
    {
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
            if (ch == RIGHT_ARROW)
            {
                clrscr();
                HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount);
                clrscr();
                HieuChinhVatTuDrawSupport();
                DrawAdjustVatTuContactGuide();
                gotoxy(18, 5);
                if (count != 0)
                {
                    cout << inputMaVT;
                }
                continue;
            }
        }
        else if (count > 0 && ch == 13)
        {
            inputMaVT[count] = '\0';
            trim(inputMaVT);
            //
            if (!isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
            {
                gotoxy(2, 7);
                SetErrorColor();
                cout << "Ma vat tu [" << inputMaVT << "] khong duoc tim thay" << endl;
                SetNormalColor();
                gotoxy(18 + count, 5);
                continue;
            }
            else
            {
                gotoxy(2, 7);
                cout << "                                                  ";
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
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
        else if ((isalnum(ch) || ch == ' ' || isSpecialChar(ch)) && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            inputMaVT[count++] = ch;
        }
    }
    cout << endl;

    VatTu *foundVT = searchMaVT_DanhSachVatTu(ds_vt, inputMaVT);
    char inputTenVT[51];
    count = 0;
    //
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
    gotoxy(3, 7);
    cout << "Ten Vat Tu";
    gotoxy(18, 7);
    while (true)
    {
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
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
                gotoxy(2, 9);
                SetErrorColor();
                cout << "Ma vat tu [" << inputTenVT << "] da ton tai" << endl;
                SetNormalColor();
                gotoxy(18 + count, 7);
                continue;
            }
            else
            {
                gotoxy(2, 9);
                cout << "                                                  ";
                break;
            }
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputTenVT[--count] = '\0';
        }
        else if ((isalnum(ch) || ch == ' ') && count < 50)
        {
            cout << ch;
            ch = tolower(ch);
            inputTenVT[count++] = ch;
        }
        else if (ch == ESC)
        {
            gotoxy(0, 9);
            cout << "Quit";
            return;
        }
    }
    cout << endl;
    //

    char inputDVT[11];
    count = 0;
    //
    drawRectangle(0, 8, 15, 2);
    drawRectangle(15, 8, 55, 2);
    gotoxy(0, 8);
    cout << char(195);
    gotoxy(15, 8);
    cout << char(197);
    gotoxy(15, 10);
    cout << char(193);
    gotoxy(70, 8);
    cout << char(180);
    //
    gotoxy(2, 9);
    cout << "Don Vi Tinh";
    gotoxy(18, 9);
    while (true)
    {
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
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
            gotoxy(0, 11);
            cout << "Quit";
            return;
        }
    }
    cout << endl;
    //

    char inputC_SoLuongTon[10];
    count = 0;
    //
    drawRectangle(0, 10, 15, 2);
    drawRectangle(15, 10, 55, 2);
    gotoxy(0, 10);
    cout << char(195);
    gotoxy(15, 10);
    cout << char(197);
    gotoxy(15, 12);
    cout << char(193);
    gotoxy(70, 10);
    cout << char(180);
    //
    gotoxy(2, 11);
    cout << "So luong ton";
    gotoxy(18, 11);

    while (true)
    {
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
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
            gotoxy(0, 13);
            cout << "Quit";
            return;
        }
    }
    cout << endl;
    int inputSoLuongTon;

    if (strlen(inputTenVT) == 0)
    {
        strcpy(inputTenVT, foundVT->tenVT);
    }

    if (strlen(inputDVT) == 0)
    {
        strcpy(inputDVT, foundVT->dVT);
    }

    if (strlen(inputC_SoLuongTon) == 0)
    {
        inputSoLuongTon = foundVT->soLuongTon;
    }
    else
    {
        inputSoLuongTon = stoi(inputC_SoLuongTon);
    }
    //
    removeFromDanhSachVatTu(foundVT->tenVT, ds_vt);
    SoLuongVatTuGlobalCount--;
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon));
    //
    gotoxy(0, 13);
    cout << "Successful";
}

void XoaVatTuDrawSupport()
{
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 70, 2);
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(70, 2);
    cout << char(180);
    gotoxy(20, 1);
    SetColor(0xC);
    cout << "Xoa Thong Tin Vat Tu" << endl;
    SetColor(0xF);
    gotoxy(17, 3);
    cout << "Nhap ma vat tu cua vat tu can xoa";
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
    gotoxy(3, 5);
    cout << "Ma Vat Tu";
    gotoxy(18, 5);
}

void XoaVatTu(DanhSachVatTu &ds_vt, int &soLuongVatTu)
{
    XoaVatTuDrawSupport();
    char inputMaVT[11];
    int count = 0;
    unsigned char ch;

    while (true)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            if (ch == RIGHT_ARROW)
            {
                int soThuTu = 0;
                clrscr();
                HienThiVatTuDangCoTrongHieuChinh(ds_vt, inputMaVT, count, SoLuongVatTuGlobalCount);
                clrscr();
                XoaVatTuDrawSupport();
                DrawRemoveVatTuContactGuide();
                gotoxy(18, 5);
                if (count != 0)
                {
                    cout << inputMaVT;
                }
                continue;
            }
        }
        else if (count > 0 && ch == 13)
        {
            inputMaVT[count] = '\0';
            trim(inputMaVT);
            //
            if (isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
            {
                VatTu *deletedVT = searchMaVT_DanhSachVatTu(ds_vt, inputMaVT);
                removeFromDanhSachVatTu(deletedVT->tenVT, ds_vt);
                soLuongVatTu--;
                gotoxy(2, 7);
                cout << "                                                         ";
                gotoxy(2, 7);
                cout << "Removed " << inputMaVT << " from DanhSach";
                break;
            }
            else
            {
                gotoxy(2, 7);
                SetErrorColor();
                cout << "Cay khong ton tai vat tu [" << inputMaVT << "]" << endl;
                SetNormalColor();
                gotoxy(18 + count, 5);
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
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
        else if ((isalnum(ch) || ch == ' ' || isSpecialChar(ch)) && count < 10)
        {
            cout << ch;
            ch = tolower(ch);
            inputMaVT[count++] = ch;
        }
    }
}

// HIEN THI VAT TU
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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

void HienThiVatTu(DanhSachVatTu root, int SoLuongVatTu)
{
    DrawHienThiVatTuTable(root);
    unsigned char c;
    // dem trang va luu ptr vs stack tai vi tri day
    int Page = 1;
    int arr2Size = 1;
    VatTuStack *PageStack = new VatTuStack[1];
    VatTu **firstPagePos = new VatTu *[1];
    //
    VatTu *current_vt = root;
    VatTuStack vtStack;
    // dem de gioi han so luong
    int count = 1;
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

        if (Page == arr2Size)
        {
            PageStack[arr2Size - 1] = vtStack;
            expandArray(PageStack, arr2Size, Page + 1);
        }

        current_vt = vtStack.pop();
        //
        if (Page == arr2Size && current_vt != nullptr)
        {
            firstPagePos[arr2Size - 1] = current_vt;
            expandArray(firstPagePos, arr2Size, Page + 1);
            arr2Size += 1;
        }

        gotoxy(3, 21 - (max - count));
        cout << current_vt->maVT;
        gotoxy(18, 21 - (max - count));
        cout << current_vt->tenVT;
        gotoxy(71, 21 - (max - count));
        cout << current_vt->dVT;
        gotoxy(99, 21 - (max - count));
        cout << current_vt->soLuongTon;
        count++;

        if (count > max || count > SoLuongVatTu)
        {
            while (true)
            {
                c = getch();
                if (c == 224)
                {
                    c = getch();
                    if (c == RIGHT_ARROW && max < SoLuongVatTu)
                    {
                        count = max + 1;
                        max = count + 14;
                        Page++;
                        clearShowVatTuBoard();
                        break;
                    }
                    else if (c == LEFT_ARROW && Page > 1)
                    {
                        Page--;
                        current_vt = firstPagePos[Page - 1];
                        vtStack = PageStack[Page - 1];
                        max -= 15;
                        count = max - 14;
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
            if (choose2 == seccondNhanVienItems - 1)
            {
                choose2 = 0;
            }
            else
            {
                choose2++;
            }
            DrawSeccondUINhanVien(choose2);
            break;
        }
        case UP_ARROW:
        {
            if (choose2 == 0)
            {
                choose2 = seccondNhanVienItems - 1;
            }
            else
            {
                choose2--;
            }
            DrawSeccondUINhanVien(choose2);
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
        else if ((isalnum(ch) || ch == ' ' || isSpecialChar(ch)) && count < 10)
        {
            inputMaNV[count++] = ch;
            cout << ch;
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
    cout << char(194);
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
            if (choose2 == seccondHoaDonItems - 1)
            {
                choose2 = 0;
            }
            else
            {
                choose2++;
            }
            DrawSeccondUIHoaDon(choose2);
            break;
        }
        case UP_ARROW:
        {
            if (choose2 == 0)
            {
                choose2 = seccondHoaDonItems - 1;
            }
            else
            {
                choose2--;
            }
            DrawSeccondUIHoaDon(choose2);
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
    for (int i = 0; i < thirdHoaDonItems; i++)
    {
        gotoxy(0, 10 + i);
        cout << thirdHoaDonUI[i];
    }

    SetHighLight();
    gotoxy(0, 10 + choose);
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

void themChiTietHoaDonNhap(HoaDon *&hoadon, DanhSachVatTu &ds_vt)
{
    DanhSach_CT_HoaDon new_ct_hd = new CT_HoaDon;
    new_ct_hd->vAT = -1;
    new_ct_hd->donGia = -1;
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
        else if (ch == ENTER && count > 0)
        {
            inputSoLuong[count] = '\0';
            new_ct_hd->soLuong = stoi(inputSoLuong);
            break;
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
    // CapNhatLaiSoLuong
    if (!isContainMaVT_DanhSachVatTu(ds_vt, new_ct_hd->maVT))
    {
        DanhSachVatTu new_vattu = new VatTu;
        drawRectangle(0, 18, 70, 3);
        gotoxy(1, 19);
        cout << "Day la vat tu moi duoc them vao!!";
        gotoxy(1, 20);
        cout << "Vui long cung cap them thong tin cua vat tu nay";
        char inputTenVT[51];
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
                break;
            }
            else if (ch == '\b' && count > 0)
            {
                cout << "\b \b";
                inputTenVT[--count] = '\0';
            }
            else if (isalnum(ch) && count < 50)
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
            else if (isalnum(ch) && count < 50)
            {
                cout << ch;
                ch = tolower(ch);
                inputDonViTinh[count++] = ch;
            }
        }
        new_vattu = newDanhSachVatTu(new_ct_hd->maVT, inputTenVT, inputDonViTinh, new_ct_hd->soLuong);
        // NOTE NHE DE DEBUG SAU
        Them_CTHD(hoadon->ds_ct_hoadon, new_ct_hd);
        insertDanhSachVatTu(ds_vt, new_vattu);
        getch();
    }
    else
    {
        if (KiemTraMaVT_CTHD(hoadon->ds_ct_hoadon, new_ct_hd->maVT))
        {
            DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(ds_vt, new_ct_hd->maVT);
            updateSoLuongTon(vattu, vattu->soLuongTon + new_ct_hd->soLuong);
            CT_HoaDon *foundCt_hoadon = timKiemCTHoaDon(hoadon->ds_ct_hoadon, new_ct_hd->maVT);
            foundCt_hoadon->soLuong += new_ct_hd->soLuong;
            gotoxy(18, 26);
        }
        else
        {
            Them_CTHD(hoadon->ds_ct_hoadon, new_ct_hd);
            DanhSachVatTu vattu = searchMaVT_DanhSachVatTu(ds_vt, new_ct_hd->maVT);
            updateSoLuongTon(vattu, vattu->soLuongTon + new_ct_hd->soLuong);
            gotoxy(18, 26);
        }
    }

    clearBottomScreen();
    return;
}

void LapHoaDonNhap(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSachNhanVien ds_nv, int &idHoaDonCount, int soLuongNhanVienCount)
{
    unsigned char ch;
    int count = 0;
    char inputSoHoaDon[21];
    LoaiHoaDon inputLoai = n;
    Date inputDate;
    char charInputDate[6];
    time_t now = time(nullptr);      // lay thoi gian hien tai
    tm *localTime = localtime(&now); // chuyen sang struct tm de truy xuat du lieu
    //
    DrawNhapHoaDon(inputLoai, inputSoHoaDon);
    gotoxy(3, 5);
    cout << "So Hoa Don";
    gotoxy(18, 5);
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
            // return;
            continue;
        }
        else if (ch == ENTER && count > 0)
        {
            inputSoHoaDon[count] = '\0';

            //

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
                    ch = getch();
                    if (ch == 224)
                    {
                        ch = getch();
                        continue;
                    }
                    else if (ch == ESC)
                    {
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
                                ch = getch();
                                if (ch == 224)
                                {
                                    ch = getch();
                                    continue;
                                }
                                else if (ch == ESC)
                                {
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
            }
            else if (ch == UP_ARROW && choose3 > 0)
            {
                choose3 -= 1;
            }
        }
        else if (ch == ENTER)
        {
            if (choose3 == 0)
            {
                clearBottomScreen();
                themChiTietHoaDonNhap(new_hd, ds_vt);
            }
            else if (choose3 == 1)
            {
                clearBottomScreen();
                gotoxy(0, 20);
                InDanhSachCTHoaDon(new_hd->ds_ct_hoadon);
                continue;
            }
            else if (choose3 == 2)
            {
                while (true)
                {
                    clearBottomScreen();
                    gotoxy(0, 20);
                    cout << "Do you want to exit(y:Yes, n: No): ";
                    ch = getch();
                    if (ch == 'n' || ch == 'N')
                    {
                        clearBottomScreen();
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
                InsertHoaDonVaoDSHD(ds_hd, new_hd);
                continue;
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

void menu(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_cthd, DanhSachNhanVien &ds_nv, int &idHoaDonCount, int &soLuongNhanVienCount)
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
                DrawVatTuContactGuide();
                ThemVatTu(ds_vt);
                Sleep(2000);
                clrscr();
                break;
            }
            case 1:
            {
                clrscr();
                DrawAdjustVatTuContactGuide();
                HieuChinhVatTu(ds_vt);
                Sleep(2000);
                clrscr();
                break;
            }
            case 2:
            {
                clrscr();
                DrawRemoveVatTuContactGuide();
                XoaVatTu(ds_vt, SoLuongVatTuGlobalCount);
                Sleep(2000);
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
                gotoxy(0, 0);
                clrscr();
                cout << "In ra 10 vat tu co doanh thu cao nhat";
                Sleep(5000);
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
            choose2 = 0;
            DrawSeccondUIHoaDon(choose2);
            GetSeccondUIHoaDonInput(c2, choose2);
            clrscr();
            gotoxy(30, 10);
            if (choose2 == 0)
            {
                LapHoaDonNhap(ds_vt, ds_hd, ds_nv, idHoaDonGlobalCount, soLuongNhanVienCount);
                //
            }
            else if (choose2 == 1)
            {
                cout << "HD Xuat";
            }
            else if (choose2 == 2)
            {
                cout << "In HoaDon";
            }

            //
            clrscr();
            DrawFirstUI(choose1);
            break;
        }
        case 3:
        {
            gotoxy(30, 10);
            clrscr();
            cout << "ThongKeDoanhThuNam!";
            DrawFirstUI(choose1);
            break;
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
    // hideCursor();
    // ThemNhanVien(ds_nv, soLuongNhanVienGlobalCount);
    // clrscr();
    // ThemNhanVien(ds_nv, soLuongNhanVienGlobalCount);

    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-001", "Luong Chi", "Vinh", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-002", "Nguyen Minh", "Tuan", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-003", "Tran Quoc", "Duc", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-004", "Pham Thi", "Linh", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-005", "Le Van", "Khanh", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-006", "Do Thi", "Nhung", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-007", "Luong Chi", "Tuan", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-008", "Nguyen Minh", "Anh", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-009", "Tran Quoc", "Vinh", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-010", "Pham Thi", "Hoa", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-011", "Le Van", "Khanh", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-012", "Do Thi", "Linh", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-013", "Luong Chi", "Duc", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-014", "Nguyen Minh", "Tuan", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-015", "Tran Quoc", "Vinh", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-016", "Pham Thi", "Anh", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-017", "Le Van", "Duc", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-018", "Do Thi", "Hoa", nu, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-019", "Luong Chi", "Khanh", nam, nullptr), soLuongNhanVienGlobalCount);
    insertNhanVienToDSNV(ds_nv, newNhanVien("NV-020", "Nguyen Minh", "Linh", nu, nullptr), soLuongNhanVienGlobalCount);
    //
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000001", "xe dap", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000002", "may tinh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000003", "dien thoai", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000004", "sach", "cuon", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000005", "tu quang", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000006", "ban ghe", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000007", "tivi", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000008", "tu lanh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000009", "may giat", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000010", "de giuong", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000011", "bon rua", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000012", "ghe sofa", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000013", "tu xe", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000014", "ke sach", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000015", "dong ho", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000016", "bong den", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000017", "tu lam", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000018", "bi ve", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000019", "may hut bui", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000020", "quat dien", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000021", "dieu hoa", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000022", "bep ga", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000023", "may xay sinh to", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000024", "bep dien", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000025", "ket sat", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000026", "binh nuoc", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000027", "ghe xep", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000028", "ban an", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000029", "ban tra", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000030", "may pha ca phe", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000031", "khung tranh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000032", "ke chua do", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000033", "chai nuoc", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000034", "cai thi", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000035", "cai nia", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000036", "bat an", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000037", "coc uong", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000038", "ro trai cay", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000039", "khay dung thuc an", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000040", "binh sua", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000041", "mon trang mieng", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000042", "mon an nhanh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000043", "my an lien", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000044", "tuong ot", "chai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000045", "dau an", "chai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000046", "gia vi", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000047", "muoi", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000048", "duong", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000049", "tieu", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000050", "hat nem", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000051", "thia nhua", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000052", "chen nhua", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000053", "khan an", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000054", "khung banh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000055", "hop dung thuc an", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000056", "hop giu nhiet", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000057", "binh dung nuoc", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000058", "chau cay", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000059", "thung rac", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000060", "choi quet", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000061", "khay lam banh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000062", "ke bep", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000063", "goi cafe", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000064", "bo noi", "bo", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000065", "bo dao", "bo", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000066", "bo ly", "bo", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000067", "bat an com", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000068", "bat canh", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000069", "gang tay", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000070", "khan giay", "goi", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000071", "bao tay", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000072", "banh xe", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000073", "banh bao", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000074", "banh beo", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000075", "banh xeo", "chiec", 1));

    menu(ds_vt, ds_hd, ds_cthd, ds_nv, idHoaDonGlobalCount, soLuongNhanVienGlobalCount);
}
