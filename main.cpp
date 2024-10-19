#include "drawFormatCode.cpp"
#include "vattu.cpp"
#include "stack.cpp"
#include "nhanvien.cpp"
#include "hoadon.cpp"
#include "main.h"
#include <vector>

const int firstItems = 4;
const int seccondVatTuItems = 5;
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

// Dung de ho tro ve lai vung nhap in put
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
    cout << "Nhap ten vat tu cua vat tu can hieu chinh";
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
    cout << "Ten Vat Tu";
    gotoxy(18, 5);
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

void NoiDungVatTu(DanhSachVatTu ds_vt, int viTri, char noidung[51], int &dem, int VatTuCount)
{
    // count = bien chay theo vong de lay so ma vat tu dang ton tai
    int count = 1;
    // lay min va max o trang dau tien de thuan tien hon trong viec tinh toan va xu li loi
    int firstMin = 1;
    int firstMax = -1;
    // max cua moi page co the co (dung de gioi han trang va xu li viec qua trang moi)
    int max = 15;
    // vi tri cua ptr
    int choose = 1;
    // maVT nhung viet bang chu khac de tranh bi trung
    char vtCode[11];
    // tao vector de chua tung header cua page de viec quay nguoc de dang hon
    int arrSize = 1;
    int *everyFirst = new int[arrSize];
    //  fPos dung de lay gia tri dau tien trong lan dau tien duyet
    int fPos = 1;
    // the hien trang hien tai dang o va dung de goi first cua ds moi page khi di nguoc
    int Page = 1;
    // vector chua maVt chi tiet moi page (capnhatlientuc) // KHONG DC DUNG VECTOR
    int everyPageValue[15];
    int valuePos = 0;
    //  Khoi tao co ban de khai bao
    unsigned char c;
    VatTu *current_vt = nullptr;
    //
initial:
    clearShowVatTuBoard();

    while (count <= max && count < VatTuCount)
    {
        dinhDangMaVatTu(vtCode, "vt", count);
        current_vt = searchMaVT_DanhSachVatTu(ds_vt, vtCode);

        if (current_vt != nullptr)
        {
            gotoxy(3, 21 - (max - count));
            cout << current_vt->maVT;
            gotoxy(18, 21 - (max - count));
            cout << current_vt->tenVT;
            gotoxy(71, 21 - (max - count));
            cout << current_vt->dVT;
            gotoxy(99, 21 - (max - count));
            cout << current_vt->soLuongTon;
            everyPageValue[valuePos] = count;
            valuePos++;
        }
        else
        {
            if (count == firstMin)
            {
                firstMin++;
            }
            if (count == fPos)
            {
                fPos++;
            }
            max++;
        }
        // lay gia tri dau tien moi trang lam moc (khong so bi loi tai vi moi lan dung xong se chay lai tu dau)
        if (fPos == count && Page == arrSize)
        {
            // cho vi tri hien tai chua gia tri dau tien cua moi trang
            everyFirst[arrSize - 1] = fPos;
            // mo rong sau khi cap phat vung nho de danh (chi du ra 1 phan nen chac khong anh huong nhieu)
            expandArray(everyFirst, arrSize, Page + 1);
            arrSize++;
        }
        //
        count++;
    }
    //
    if (firstMax == -1)
    {
        firstMax = max;
    }

    count--;
    //
    gotoxy(16, 6 + choose);
    SetColor(0x4);
    cout << "->";
    SetColor(0xF);
    //
    while (true)
    {
        c = getch();
        if (c == 224)
        {
            c = getch();
            switch (c)
            {
            case UP_ARROW:
            {
                if (choose == 1)
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose = 15 - (max - count);
                    gotoxy(16, 6 + choose);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                }
                else
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose--;
                    gotoxy(16, 6 + choose);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                }
                break;
            }
            case DOWN_ARROW:
            {
                if (choose == 15 - (max - count))
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose = 1;
                    gotoxy(16, 6 + choose);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                }
                else
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose++;
                    gotoxy(16, 6 + choose);
                    SetColor(0x4);
                    cout << "->";
                    SetColor(0xF);
                }
                break;
            }
            case RIGHT_ARROW:
            {
                if (count == max && max < VatTuCount - 1)
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose = 1;
                    Page++;
                    count = max + 1;
                    fPos = count;
                    max = count + 14;
                    valuePos = 0;
                    goto initial;
                }
                break;
            }
            case LEFT_ARROW:
            {
                if (count > firstMax)
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose = 1;
                    Page--;
                    count = everyFirst[Page - 1];
                    max = count + 14;
                    valuePos = 0;
                    goto initial;
                }
                break;
            }
            }
        }
        else if (c == ENTER)
        {
            char inputRel[11];
            int pos = everyPageValue[choose - 1];
            dinhDangMaVatTu(inputRel, "vt", pos);
            VatTu *rel = searchMaVT_DanhSachVatTu(ds_vt, inputRel);
            dem = strlen(rel->tenVT);
            strcpy(noidung, rel->tenVT);
            return;
        }
        else if (c == ESC)
        {
            return;
        }
    }
}

void HienThiVatTuDangCoTrongHieuChinh(DanhSachVatTu ds_vt, int viTri, char noidung[51], int &dem, int VatTuCount)
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
        NoiDungVatTu(ds_vt, viTri, noidung, dem, VatTuCount);
    }
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

void NhapVatTu(DanhSachVatTu &ds_vt, int &idVatTuCount)
{
    drawRectangle(0, 0, 70, 2);
    drawRectangle(0, 2, 70, 2);
    //
    gotoxy(0, 2);
    cout << char(195);
    gotoxy(70, 2);
    cout << char(180);
    //
    gotoxy(24, 1);
    SetColor(0xC);
    cout << "Them thong tin vat tu" << endl;
    SetColor(0xF);
    int choice = -1;
    char inputMaVT[11];
    int count = 0;
    bool done = false;
    unsigned char ch;

    gotoxy(21, 3);
    dinhDangMaVatTu(inputMaVT, "vt", idVatTuCount);
    cout << "maVT cua ban la " << inputMaVT << endl;

    char inputTenVT[51];
    count = 0;
    done = false;
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
    //
    gotoxy(3, 5);
    cout << "Ten Vat Tu";
    gotoxy(18, 5);
    while (!done)
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
            done = true;
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
    if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
    {
        gotoxy(2, 7);
        SetErrorColor();
        cout << "Cay da ton tai vat tu vs tenVT la " << inputTenVT << " nen khong the them gia tri " << endl;
        SetNormalColor();
    }
    else
    {
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
        done = false;
        cout << "Don Vi Tinh";
        gotoxy(18, 7);

        while (!done)
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
                done = true;
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
        done = false;
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

        while (!done)
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
                done = true;
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
}

void HieuChinhVatTu(DanhSachVatTu &ds_vt)
{
    int count = 0;
    bool done = false;
    char inputTenVT[51];
    unsigned char ch;

    HieuChinhVatTuDrawSupport();

    while (!done)
    {
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
            if (ch == RIGHT_ARROW)
            {
                int soThuTu = 0;
                clrscr();
                HienThiVatTuDangCoTrongHieuChinh(ds_vt, soThuTu, inputTenVT, count, idVatTuGlobalCount);
                clrscr();
                HieuChinhVatTuDrawSupport();
                DrawAdjustVatTuContactGuide();
                gotoxy(18, 5);
                if (count != 0)
                {
                    cout << inputTenVT;
                }
                continue;
            }
        }
        else if (count > 0 && ch == 13)
        {
            inputTenVT[count] = '\0';
            trim(inputTenVT);
            done = true;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputTenVT[--count] = '\0';
        }
        else if (ch == ESC)
        {
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
        else if ((isalnum(ch) || ch == ' ') && count < 50)
        {
            cout << ch;
            ch = tolower(ch);
            inputTenVT[count++] = ch;
        }
    }
    cout << endl;

    if (!isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
    {
        gotoxy(2, 7);
        SetErrorColor();
        cout << "Ten vat tu " << inputTenVT << " khong duoc tim thay" << endl;
        SetNormalColor();
    }
    else
    {
        VatTu *foundVT = searchTenVT_DanhSachVatTu(ds_vt, inputTenVT);
        char inputDVT[11];
        count = 0;
        done = false;
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
        cout << "Don vi tinh";
        gotoxy(18, 7);
        while (!done)
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
                done = true;
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
        done = false;
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

        while (!done)
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
                done = true;
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
        int inputSoLuongTon;

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
        strcpy(foundVT->dVT, inputDVT);
        foundVT->soLuongTon = inputSoLuongTon;
        //
        ds_vt = balanceTree(ds_vt);
        //
        gotoxy(0, 11);
        cout << "Successful";
    }
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
    cout << "Nhap ten vat tu cua vat tu can xoa";
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
    cout << "Ten Vat Tu";
    gotoxy(18, 5);
}

void XoaVatTu(DanhSachVatTu &ds_vt, int &soLuongVatTu)
{
    XoaVatTuDrawSupport();
    char inputTenVT[51];
    int count = 0;
    bool done = false;
    unsigned char ch;
    while (!done)
    {
        ch = getch();
        if (ch == 224)
        {
            ch = getch();
            if (ch == RIGHT_ARROW)
            {
                int soThuTu = 0;
                clrscr();
                HienThiVatTuDangCoTrongHieuChinh(ds_vt, soThuTu, inputTenVT, count, idVatTuGlobalCount);
                clrscr();
                XoaVatTuDrawSupport();
                DrawRemoveVatTuContactGuide();
                gotoxy(18, 5);
                if (count != 0)
                {
                    cout << inputTenVT;
                }
                continue;
            }
        }
        else if (count > 0 && ch == 13)
        {
            inputTenVT[count] = '\0';
            trim(inputTenVT);
            done = true;
        }
        else if (ch == '\b' && count > 0)
        {
            cout << "\b \b";
            inputTenVT[--count] = '\0';
        }
        else if (ch == ESC)
        {
            gotoxy(0, 7);
            cout << "Quit";
            return;
        }
        else if ((isalnum(ch) || ch == ' ') && count < 50)
        {
            cout << ch;
            ch = tolower(ch);
            inputTenVT[count++] = ch;
        }
    }
    cout << endl;
    if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
    {
        removeFromDanhSachVatTu(inputTenVT, ds_vt);
        soLuongVatTu--;
        gotoxy(2, 7);
        cout << "Removed " << inputTenVT << " from DanhSach";
    }
    else
    {
        gotoxy(2, 7);
        SetErrorColor();
        cout << "Cay khong ton tai vat tu vs tenVT la " << inputTenVT << " nen khong the xoa gia tri " << endl;
        SetNormalColor();
    }
}

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

        if (count > max || count >= SoLuongVatTu)
        {
            while (true)
            {
                c = getch();
                if (c == 224)
                {
                    c = getch();
                    if (c == RIGHT_ARROW && count > max - 1)
                    {
                        count = max + 1;
                        max = count + 14;
                        Page++;
                        clearShowVatTuBoard();
                        break;
                    }
                    else if (c == LEFT_ARROW && count > 16)
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

void menu(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_cthd, DanhSachNhanVien &ds_nv, int &idVatTuCount, int &idHoaDonCount, int &soLuongNhanVienCount)
{
    int choose1 = 0;
    int choose2 = 0;
    int CurrentScreenWidth = getConsoleWidth();
    int CurrentScreenHeight = getConsoleHeight();
    char c1;
    char c2;
init:
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
                NhapVatTu(ds_vt, idVatTuCount);
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
                break;
            }
            case -1:
            {
                clrscr();
                break;
            }
            default:
            {
                break;
            }
            }
            DrawFirstUI(choose1);
            break;
        }
        case 1:
        {
            gotoxy(30, 10);
            clrscr();
            cout << "Here1!";
            DrawFirstUI(choose1);
            break;
        }
        case 2:
        {
            gotoxy(30, 10);
            clrscr();
            cout << "Here2!";
            DrawFirstUI(choose1);
            break;
        }
        case 3:
        {
            gotoxy(30, 10);
            clrscr();
            cout << "Here3!";
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
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000053", "khăn an", "cai", 1));
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

    menu(ds_vt, ds_hd, ds_cthd, ds_nv, idVatTuGlobalCount, idHoaDonGlobalCount, soLuongNhanVienGlobalCount);
}
