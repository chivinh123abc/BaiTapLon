#include "foundationStruct.cpp"

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
            rp = nullptr;
        }
        else
        {
            DanhSachVatTu t = rp->right;
            rp = t;
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
    if (root == nullptr)
    {
        return nullptr;
    }

    DanhSachVatTu current = root;

    while (current != nullptr && (strcmp(current->tenVT, tenVT) != 0))
    {
        if (strcmp(current->tenVT, tenVT) > 0)
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

DanhSachVatTu searchMaVT_DanhSachVatTu(DanhSachVatTu root, char maVT[])
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (strcmp(root->maVT, maVT) == 0)
    {
        return root;
    }

    DanhSachVatTu leftSearch = searchMaVT_DanhSachVatTu(root->left, maVT);
    if (leftSearch != nullptr)
    {
        return leftSearch;
    }

    return searchMaVT_DanhSachVatTu(root->right, maVT);
}

bool isContainMaVT_DanhSachVatTu(DanhSachVatTu root, char maVT[])
{
    if (root == nullptr)
    {
        return false;
    }

    if (strcmp(root->maVT, maVT) == 0)
    {
        return true;
    }

    return isContainMaVT_DanhSachVatTu(root->left, maVT) || isContainMaVT_DanhSachVatTu(root->right, maVT);
}

bool isContainTenVT_DanhSachVatTu(DanhSachVatTu root, char tenVT[])
{
    if (root == nullptr)
    {
        return false;
    }

    if (strcmp(root->tenVT, tenVT) == 0)
    {
        return true;
    }

    return isContainTenVT_DanhSachVatTu(root->left, tenVT) || isContainTenVT_DanhSachVatTu(root->right, tenVT);
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
    "2. Hien thi vat tu",
    "3. Hieu chinh vat tu",
    "4. Xoa vat tu",
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

    bool running = true;

    while (running)
    {

        for (int i = 0; i < MENU_ITEMS; i++)
        {
            cout << menuName[i] << endl;
        }
        cout << "What you want to do" << endl;

        choose = getch();

        switch (choose)
        {
        case '1':
        {
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
                    inputMaVT[count] = '\0';
                    done = true;
                }
                else if (ch == '\b' && count > 0)
                {
                    // lui ve 1 nut de in ky tu trang sau do lai lui tiep de tiep tuc
                    cout << "\b \b";
                    inputMaVT[--count] = '\0';
                }
                else if (isalnum(ch) && count < 10)
                {
                    ch = tolower(ch);
                    cout << ch;
                    inputMaVT[count++] = ch;
                }
            }
            cout << endl;

            if (isContainMaVT_DanhSachVatTu(root, inputMaVT))
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
                    else if (isalnum(ch) && count < 50)
                    {
                        ch = tolower(ch);
                        cout << ch;
                        inputTenVT[count++] = ch;
                    }
                }
                cout << endl;

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
                    else if (isalnum(ch) && count < 10)
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

                cout << "Ma vat tu nhap: " << inputMaVT << endl;
                cout << "Ten vat tu nhap: " << inputTenVT << endl;
                cout << "DVT nhap: " << inputDVT << endl;
                cout << "Soluongton nhap: " << inputC_SoLuongTon << endl;
                cout << "Soluongton nhap main: " << inputSoLuongTon << endl;

                DanhSachVatTu dsvt_moi = newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon);
                insertDanhSachVatTu(root, dsvt_moi);
            }

            break;
        }
        case '2':
        {
            inDanhSachVatTuTheoTenVT(root);
            break;
        }
        case '3':
        {
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
                else if (isalnum(ch) && count < 10)
                {
                    ch = tolower(ch);
                    cout << ch;
                    inputMaVT[count++] = ch;
                }
            }
            cout << endl;

            DanhSachVatTu foundVT = searchMaVT_DanhSachVatTu(root, inputMaVT);
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
                    else if (isalnum(ch) && count < 50)
                    {
                        ch = tolower(ch);
                        cout << ch;
                        inputTenVT[count++] = ch;
                    }
                }
                cout << endl;

                if (isContainTenVT_DanhSachVatTu(root, inputTenVT))
                {
                    cout << "Ten vat tu da ton tai khong the tiep tuc chinh sua" << endl;
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
                        else if (isalnum(ch) && count < 10)
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

                    removeFromDanhSachVatTu(foundVT->tenVT, root);
                    insertDanhSachVatTu(root, newDanhSachVatTu(inputMaVT, inputTenVT, inputDVT, inputSoLuongTon));
                }
            }
            break;
        }
        case '4':
        {
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
                    done = true;
                }
                else if (ch == '\b' && count > 0)
                {
                    cout << "\b \b";
                    inputTenVT[--count] = '\0';
                }
                else if (isalnum(ch) && count < 50)
                {
                    ch = tolower(ch);
                    cout << ch;
                    inputTenVT[count++] = ch;
                }
            }
            inputTenVT[count] = '\0';
            cout << endl;
            removeFromDanhSachVatTu(inputTenVT, root);
            break;
        }
        case '0':
        {
            cout << "Thoat chuong trinh" << endl;
            running = false;
            break;
        }
        case 13:
        {
            cout << "Thoat chuong trinh" << endl;
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
}

int main()
{
    DanhSachVatTu root = nullptr;

    insertDanhSachVatTu(root, newDanhSachVatTu("05", "05", "cai", 25));
    insertDanhSachVatTu(root, newDanhSachVatTu("04", "04", "cai", 20));
    insertDanhSachVatTu(root, newDanhSachVatTu("01", "01", "cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("02", "02", "cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("10", "10", "cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("03", "03", "chiec", 15));
    insertDanhSachVatTu(root, newDanhSachVatTu("06", "06", "bo", 5));
    insertDanhSachVatTu(root, newDanhSachVatTu("07", "07", "hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("07", "07", "hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("08", "08", "bo", 12));
    insertDanhSachVatTu(root, newDanhSachVatTu("14", "14", "cai", 18));

    updateMenu(root);

    return 0;
}