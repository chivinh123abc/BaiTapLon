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
    cout << "Insert Guide";
    drawRectangle(80, 4, 31, 2);
    gotoxy(85, 5);
    cout << "Enter: Confirm Your Input";
    drawRectangle(80, 6, 31, 2);
    gotoxy(88, 7);
    cout << "Esc: Stop Program";
    drawRectangle(80, 8, 31, 4);
    gotoxy(87, 10);
    cout << "Input Restrictions";
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
    cout << "Them thong tin vat tu" << endl;
    int choice = -1;
    char inputMaVT[11];
    int count = 0;
    bool done = false;

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
        char ch = getch();
        if (count > 0 && ch == 13)
        {
            inputTenVT[count] = '\0';
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
            inputTenVT[count++] = ch;
        }
        else if (ch == ESC)
        {
            gotoxy(2, 11);
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
            char ch = getch();
            if (ch == 13 && count > 0)
            {
                inputDVT[count] = '\0';
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
                inputDVT[count++] = ch;
            }
            else if (ch == ESC)
            {
                gotoxy(2, 11);
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
            char ch = getch();
            if (ch == 13 && count > 0)
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
                gotoxy(2, 11);
                cout << "Quit";
                return;
            }
        }
        cout << endl;

        int inputSoLuongTon = stoi(inputC_SoLuongTon);

        DanhSachVatTu dsvt_moi = newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon);
        insertDanhSachVatTu(ds_vt, dsvt_moi);
        gotoxy(2, 11);
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
                gotoxy(0, 0);
                int count = 0;
                bool done = false;
                char inputTenVT[51];

                cout << "Nhap ten vat tu cua vat tu can hieu chinh: ";
                while (!done)
                {
                    char ch = getch();
                    if (count >= 0 && ch == 13)
                    {
                        inputTenVT[count] = '\0';
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
                        inputTenVT[count++] = ch;
                    }
                }
                cout << endl;

                if (!isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
                {
                    cout << "Ten vat tu khong tim thay" << endl;
                }
                else
                {
                    VatTu *foundVT = searchTenVT_DanhSachVatTu(ds_vt, inputTenVT);
                    char inputDVT[11];
                    count = 0;
                    done = false;

                    cout << "Nhap don vi tinh: ";
                    while (!done)
                    {
                        char ch = getch();
                        if (ch == 13 && count >= 0)
                        {
                            inputDVT[count] = '\0';
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
                            inputDVT[count++] = ch;
                        }
                    }
                    cout << endl;

                    char inputC_SoLuongTon[10];
                    count = 0;
                    done = false;

                    cout << "Nhap so luong ton: ";

                    while (!done)
                    {
                        char ch = getch();
                        if (ch == 13 && count >= 0)
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
                    ds_vt = balanceTree(ds_vt);
                }

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

    menu(ds_vt, ds_hd, ds_cthd, ds_nv, idVatTuGlobalCount, idHoaDonGlobalCount, soLuongNhanVienGlobalCount);

    int z;
    cin >> z;
}
