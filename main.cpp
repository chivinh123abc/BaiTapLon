#include "drawFormatCode.cpp"
#include "vattu.cpp"
#include "nhanvien.cpp"
#include "hoadon.cpp"
#include "main.h"

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

void NoiDungVatTu(DanhSachVatTu ds_vt, int viTri, char noidung[51])
{
    int count = 1;
    int max = 15;
    int choose = 1;
    char vtCode[11];
    unsigned char c;
    VatTu *current_vt = nullptr;
    //
initial:
    clearShowVatTuBoard();
    dinhDangMaVatTu(vtCode, "vt", count);
    current_vt = searchMaVT_DanhSachVatTu(ds_vt, vtCode);
    do
    {
        if (current_vt != nullptr)
        {
            gotoxy(3, 21 - (max - count));
            cout << current_vt->maVT;
            gotoxy(18, 21 - (max - count));
            cout << current_vt->tenVT;
            gotoxy(70, 21 - (max - count));
            cout << current_vt->dVT;
            gotoxy(98, 21 - (max - count));
            cout << current_vt->soLuongTon;
        }
        else
        {
            cout << "Ma vat tu " << vtCode << " khong ton tai." << endl;
        }
        count++;
        dinhDangMaVatTu(vtCode, "vt", count);
        current_vt = searchMaVT_DanhSachVatTu(ds_vt, vtCode);
    } while (current_vt != nullptr && count <= max);

    //
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
                if (count == max)
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose = 1;
                    count = max + 1;
                    max = count + 14;
                    goto initial;
                }
                break;
            }
            case LEFT_ARROW:
            {
                if (count > 15)
                {
                    gotoxy(16, 6 + choose);
                    cout << char(179) << " ";
                    choose = 1;
                    max = count - (15 - (max - count));
                    count = max - 14;
                    goto initial;
                }
                break;
            }
            }
        }
        else if (c == ENTER)
        {
            char inputRel[11];
            int pos = count - (15 - (max - count)) + choose;
            dinhDangMaVatTu(inputRel, "vt", pos);
            VatTu *rel = searchMaVT_DanhSachVatTu(ds_vt, inputRel);
            strcpy(noidung, rel->tenVT);
            return;
        }
        else if (c == ESC)
        {
            return;
        }
    }
}

void HienThiVatTuDangCoTrongHieuChinh(DanhSachVatTu ds_vt, int viTri, char noidung[51])
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
        cout << " choose this tenVT  ";
        SetColor(0xA);
        cout << "UP_ARROW:";
        SetColor(0xF);
        cout << " Move up  ";
        SetColor(0xA);
        cout << "DOWN_ARROW:";
        SetColor(0xF);
        cout << " Move down";
        gotoxy(0, 28);
        SetColor(0xA);
        cout << "ESC:";
        SetColor(0xF);
        cout << " Escape from board    ";
        SetColor(0xA);
        cout << "-->:";
        SetColor(0xF);
        cout << " Move right    ";
        SetColor(0xA);
        cout << "<--:";
        SetColor(0xF);
        cout << " Move left       ";
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
        NoiDungVatTu(ds_vt, viTri, noidung);
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
                HienThiVatTuDangCoTrongHieuChinh(ds_vt, soThuTu, inputTenVT);
                clrscr();
                HieuChinhVatTuDrawSupport();
                DrawAdjustVatTuContactGuide();
                gotoxy(18, 5);
                count = strlen(inputTenVT);
                if (count != 0)
                {
                    cout << inputTenVT;
                }
                continue;
            }
        }
        else if (count >= 0 && ch == 13)
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
                gotoxy(0, 0);
                cout << "Xoa Vat Tu Theo Ten Vat Tu" << endl;
                char inputTenVT[51];
                int count = 0;
                bool done = false;
                cout << "Nhap Ten Vat Tu (bo trong de giu nguyen): ";
                while (!done)
                {
                    char ch = getch();
                    if (count > 0 && ch == 13)
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
                }
                cout << endl;
                removeFromDanhSachVatTu(inputTenVT, ds_vt);
                Sleep(2000);
                clrscr();
                break;
            }
            case 3:
            {
                gotoxy(0, 0);
                if (ds_vt == nullptr)
                {
                    cout << "Danh Sach Trong" << endl;
                }
                clrscr();
                inDanhSachVatTuTheoTenVT(ds_vt);
                Sleep(5000);
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

    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000001", "banh xe", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000002", "banh bo", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000003", "banh bao", "cai", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000004", "xe dap", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000005", "xe bo", "chiec", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000006", "con ga", "con", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000007", "con cho", "con", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000008", "but muc xanh", "cay", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000009", "9", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000010", "10", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000011", "11", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000012", "12", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000013", "13", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000014", "14", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000015", "15", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000016", "16", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000017", "17", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000018", "18", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000019", "19", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000020", "20", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000021", "21", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000022", "22", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000023", "23", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000024", "24", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000025", "25", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000026", "26", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000027", "27", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000028", "28", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000029", "29", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000030", "30", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000031", "31", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000032", "32", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000033", "33", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000034", "34", "1", 1));
    insertDanhSachVatTu(ds_vt, newDanhSachVatTu("vt-0000035", "35", "1", 1));

    menu(ds_vt, ds_hd, ds_cthd, ds_nv, idVatTuGlobalCount, idHoaDonGlobalCount, soLuongNhanVienGlobalCount);
}
