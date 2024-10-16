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
            return -1;
        }
        case ENTER:
        {
            return choose2;
        }
        }
    }
}

void menu(DanhSachVatTu &ds_vt, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_cthd, DanhSachNhanVien &ds_nv, int &idVatTuCount, int &idHoaDonCount, int &soLuongNhanVienCount)
{
    int choose1 = 0;
    int choose2 = 0;
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
                gotoxy(0, 0);
                cout << "Them thong tin vat tu: " << endl;
                int choice = -1;
                char inputMaVT[11];
                int count = 0;
                bool done = false;

                dinhDangMaVatTu(inputMaVT, "vt", idVatTuCount);
                cout << "maVT cua ban la " << inputMaVT << endl;

                if (isContainMaVT_DanhSachVatTu(ds_vt, inputMaVT))
                {
                    cout << "Cay da ton tai vat tu voi maVT la " << inputMaVT << " nen khong the them gia tri " << endl;
                }
                else
                {
                    char inputTenVT[51];
                    count = 0;
                    done = false;

                    cout << "Nhap Ten Vat Tu: ";
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
                            ch = tolower(ch);
                            cout << ch;
                            inputTenVT[count++] = ch;
                        }
                    }
                    cout << endl;

                    if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
                    {
                        cout << "Cay da ton tai vat tu vs tenVT la " << inputTenVT << " nen khong the them gia tri " << endl;
                    }
                    else
                    {
                        char inputDVT[11];
                        count = 0;
                        done = false;

                        cout << "Nhap don vi tinh: ";
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
                                ch = tolower(ch);
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
                        }
                        cout << endl;

                        int inputSoLuongTon = stoi(inputC_SoLuongTon);

                        DanhSachVatTu dsvt_moi = newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon);
                        insertDanhSachVatTu(ds_vt, dsvt_moi);
                    }
                }
                Sleep(2000);
                clrscr();
                break;
            }
            case 1:
            {
                // can xem xet lai viec nhap tenvt thay vi mavt
                gotoxy(0, 0);
                char inputMaVT[11];
                int count = 0;
                bool done = false;

                cout << "Nhap ma vat tu cua vat tu can hieu chinh: ";
                while (!done)
                {
                    char ch = getch();

                    if (ch == 13 && count > 0)
                    {
                        inputMaVT[count] = '\0';
                        done = true;
                    }
                    else if (ch == '\b' && count > 0)
                    {
                        cout << "\b \b";
                        inputMaVT[--count] = '\0';
                    }
                    else if ((isalnum(ch) || ch == ' ' || ch == '-') && count < 10)
                    {
                        ch = tolower(ch);
                        cout << ch;
                        inputMaVT[count++] = ch;
                    }
                }
                cout << endl;

                DanhSachVatTu foundVT = searchMaVT_DanhSachVatTu(ds_vt, inputMaVT);
                if (foundVT == nullptr)
                {
                    cout << "Ma Vat Tu Khong Ton Tai" << endl;
                }
                else
                {
                    char inputTenVT[51];
                    count = 0;
                    done = false;

                    cout << "Nhap Ten Vat Tu: ";
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
                            ch = tolower(ch);
                            cout << ch;
                            inputTenVT[count++] = ch;
                        }
                    }
                    cout << endl;

                    if (isContainTenVT_DanhSachVatTu(ds_vt, inputTenVT))
                    {
                        cout << "Ten vat tu khong tim thay" << endl;
                    }
                    else
                    {
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
                                ch = tolower(ch);
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

                        removeFromDanhSachVatTu(foundVT->tenVT, ds_vt);
                        insertDanhSachVatTu(ds_vt, newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon));
                    }
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
                        ch = tolower(ch);
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
                clrscr();
                break;
            }
            case 4:
            {
                gotoxy(0, 0);
                clrscr();
                cout << "44444";
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

//////
// char menuName[MENU_ITEMS][51]{
//     "1. Them vat tu",
//     "2. Hien thi vat tu",
//     "3. Hieu chinh vat tu",
//     "4. Xoa vat tu",
//     "Esc. Exit"
//     //
// };
// char vattuName[VATTU_ITEMS][51]{
//     "1. Vat Tu Xay Dung (gach, xi mang,...)",
//     "2. Vat Tu San Xuat (may moc, linh kien,...)",
//     "3. Vat Tu Tieu Dung (thuc pham, hang hoa,...)"
//     //
// };

// // them/xoa/hieu chinh thong tin vat tu,
// // rieng so luong ton chi cho phep nhap khi do la vat tu moi them
// void updateMenu(DanhSachVatTu &root)
// {
//     int choose = -1;
//     cout << "---------------------------------------------------" << endl;

//     // Hiển thị menu

//     bool running = true;

//     while (running)
//     {
//     start:
//         for (int i = 0; i < MENU_ITEMS; i++)
//         {
//             cout << menuName[i] << endl;
//         }
//         cout << "What you want to do" << endl;

//         choose = getch();

//         switch (choose)
//         {
//         case '1':
//         {
//             //         case '1':
//         {
//             cout << "Them thong tin vat tu: " << endl;

//             int choice = -1;
//             char inputMaVT[11];
//             int count = 0;
//             bool done = false;

//             dinhDangMaVatTu(inputMaVT, "vt", idVatTuGlobalCount);
//             cout << "maVT cua ban la " << inputMaVT << endl;

//             if (isContainMaVT_DanhSachVatTu(root, inputMaVT))
//             {
//                 cout << "Cay da ton tai vat tu voi maVT la " << inputMaVT << " nen khong the them gia tri " << endl;
//             }
//             else
//             {
//                 char inputTenVT[51];
//                 count = 0;
//                 done = false;

//                 cout << "Nhap Ten Vat Tu: ";
//                 while (!done)
//                 {
//                     char ch = getch();
//                     if (count > 0 && ch == 13)
//                     {
//                         inputTenVT[count] = '\0';
//                         done = true;
//                     }
//                     else if (ch == '\b' && count > 0)
//                     {
//                         cout << "\b \b";
//                         inputTenVT[--count] = '\0';
//                     }
//                     else if ((isalnum(ch) || ch == ' ') && count < 50)
//                     {
//                         ch = tolower(ch);
//                         cout << ch;
//                         inputTenVT[count++] = ch;
//                     }
//                 }
//                 cout << endl;

//                 char inputDVT[11];
//                 count = 0;
//                 done = false;

//                 cout << "Nhap don vi tinh: ";
//                 while (!done)
//                 {
//                     char ch = getch();
//                     if (ch == 13 && count > 0)
//                     {
//                         inputDVT[count] = '\0';
//                         done = true;
//                     }
//                     else if (ch == '\b' && count > 0)
//                     {
//                         cout << "\b \b";
//                         inputDVT[--count] = '\0';
//                     }
//                     else if ((isalnum(ch) || ch == ' ') && count < 10)
//                     {
//                         ch = tolower(ch);
//                         cout << ch;
//                         inputDVT[count++] = ch;
//                     }
//                 }
//                 cout << endl;

//                 char inputC_SoLuongTon[10];
//                 count = 0;
//                 done = false;

//                 cout << "Nhap so luong ton: ";

//                 while (!done)
//                 {
//                     char ch = getch();
//                     if (ch == 13 && count > 0)
//                     {
//                         inputC_SoLuongTon[count] = '\0';
//                         done = true;
//                     }
//                     else if (ch == '\b' && count > 0)
//                     {
//                         cout << "\b \b";
//                         inputC_SoLuongTon[--count] = '\0';
//                     }
//                     else if (isdigit(ch) && count < 9)
//                     {
//                         cout << ch;
//                         inputC_SoLuongTon[count++] = ch;
//                     }
//                 }
//                 cout << endl;

//                 int inputSoLuongTon = stoi(inputC_SoLuongTon);

//                 cout << "Ma vat tu nhap: " << inputMaVT << endl;
//                 cout << "Ten vat tu nhap: " << inputTenVT << endl;
//                 cout << "DVT nhap: " << inputDVT << endl;
//                 cout << "Soluongton nhap: " << inputC_SoLuongTon << endl;
//                 cout << "Soluongton nhap main: " << inputSoLuongTon << endl;

//                 DanhSachVatTu dsvt_moi = newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon);
//                 insertDanhSachVatTu(root, dsvt_moi);
//             }
//             break;
//         }
//         case '2':
//         {
//             if (root == nullptr)
//             {
//                 cout << "Danh Sach Trong" << endl;
//             }
//             inDanhSachVatTuTheoTenVT(root);
//             break;
//         }
//         case '3':
//         {
//             char inputMaVT[11];
//             int count = 0;
//             bool done = false;

//             cout << "Nhap ma vat tu cua vat tu can hieu chinh: ";
//             while (!done)
//             {
//                 char ch = getch();

//                 if (ch == 13 && count > 0)
//                 {
//                     inputMaVT[count] = '\0';
//                     done = true;
//                 }
//                 else if (ch == '\b' && count > 0)
//                 {
//                     cout << "\b \b";
//                     inputMaVT[--count] = '\0';
//                 }
//                 else if (isalnum(ch) && count < 10)
//                 {
//                     ch = tolower(ch);
//                     cout << ch;
//                     inputMaVT[count++] = ch;
//                 }
//             }
//             cout << endl;

//             DanhSachVatTu foundVT = searchMaVT_DanhSachVatTu(root, inputMaVT);
//             if (foundVT == nullptr)
//             {
//                 cout << "Ma Vat Tu Khong Ton Tai" << endl;
//             }
//             else
//             {
//                 char inputTenVT[51];
//                 count = 0;
//                 done = false;

//                 cout << "Nhap Ten Vat Tu: ";
//                 while (!done)
//                 {
//                     char ch = getch();
//                     if (count >= 0 && ch == 13)
//                     {
//                         inputTenVT[count] = '\0';
//                         done = true;
//                     }
//                     else if (ch == '\b' && count > 0)
//                     {
//                         cout << "\b \b";
//                         inputTenVT[--count] = '\0';
//                     }
//                     else if (isalnum(ch) && count < 50)
//                     {
//                         ch = tolower(ch);
//                         cout << ch;
//                         inputTenVT[count++] = ch;
//                     }
//                 }
//                 cout << endl;

//                 if (isContainTenVT_DanhSachVatTu(root, inputTenVT))
//                 {
//                     cout << "Ten vat tu da ton tai khong the tiep tuc chinh sua" << endl;
//                 }
//                 else
//                 {
//                     char inputDVT[11];
//                     count = 0;
//                     done = false;

//                     cout << "Nhap don vi tinh: ";
//                     while (!done)
//                     {
//                         char ch = getch();
//                         if (ch == 13 && count >= 0)
//                         {
//                             inputDVT[count] = '\0';
//                             done = true;
//                         }
//                         else if (ch == '\b' && count > 0)
//                         {
//                             cout << "\b \b";
//                             inputDVT[--count] = '\0';
//                         }
//                         else if (isalnum(ch) && count < 10)
//                         {
//                             ch = tolower(ch);
//                             cout << ch;
//                             inputDVT[count++] = ch;
//                         }
//                     }
//                     cout << endl;

//                     char inputC_SoLuongTon[10];
//                     count = 0;
//                     done = false;

//                     cout << "Nhap so luong ton: ";

//                     while (!done)
//                     {
//                         char ch = getch();
//                         if (ch == 13 && count >= 0)
//                         {
//                             inputC_SoLuongTon[count] = '\0';
//                             done = true;
//                         }
//                         else if (ch == '\b' && count > 0)
//                         {
//                             cout << "\b \b";
//                             inputC_SoLuongTon[--count] = '\0';
//                         }
//                         else if (isdigit(ch) && count < 9)
//                         {
//                             cout << ch;
//                             inputC_SoLuongTon[count++] = ch;
//                         }
//                     }
//                     cout << endl;
//                     int inputSoLuongTon;
//                     if (strlen(inputTenVT) == 0)
//                     {
//                         strcpy(inputTenVT, foundVT->tenVT);
//                     }

//                     if (strlen(inputDVT) == 0)
//                     {
//                         strcpy(inputDVT, foundVT->dVT);
//                     }

//                     if (strlen(inputC_SoLuongTon) == 0)
//                     {
//                         inputSoLuongTon = foundVT->soLuongTon;
//                     }
//                     else
//                     {
//                         inputSoLuongTon = stoi(inputC_SoLuongTon);
//                     }

//                     removeFromDanhSachVatTu(foundVT->tenVT, root);
//                     insertDanhSachVatTu(root, newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon));
//                 }
//             }
//             break;
//         }
//         case '4':
//         {
//             cout << "Xoa Vat Tu Theo Ten Vat Tu" << endl;
//             char inputTenVT[51];
//             int count = 0;
//             bool done = false;
//             cout << "Nhap Ten Vat Tu (bo trong de giu nguyen): ";
//             while (!done)
//             {
//                 char ch = getch();
//                 if (count > 0 && ch == 13)
//                 {
//                     inputTenVT[count] = '\0';
//                     done = true;
//                 }
//                 else if (ch == '\b' && count > 0)
//                 {
//                     cout << "\b \b";
//                     inputTenVT[--count] = '\0';
//                 }
//                 else if (isalnum(ch) && count < 50)
//                 {
//                     ch = tolower(ch);
//                     cout << ch;
//                     inputTenVT[count++] = ch;
//                 }
//             }

//             cout << endl;
//             removeFromDanhSachVatTu(inputTenVT, root);
//             break;
//         }
//         case 27:
//         {
//             cout << "Thoat chuong trinh" << endl;
//             running = false;
//             break;
//         }
//         default:
//         {
//             cout << "Invalid choice. Please try again." << endl;
//             break;
//         }
//         }
//     }
// }