#include "foundationStruct.cpp"
#pragma once

DanhSachVatTu newDanhSachVatTu(const char maVT[], const char tenVT[], const char dVT[], int soLuongTon)
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

void updateSoLuongTon(DanhSachVatTu &vt, int soLuong)
{
    if (vt == nullptr)
    {
        return;
    }
    vt->soLuongTon = soLuong;
}

void dinhDangMaVatTu(char rel[11], const char dinhDang[3], int &soThuTuMaVT)
{
    // dung sprintf dinh dang dai ma VT
    sprintf(rel, "%s-%07d", dinhDang, soThuTuMaVT);
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
        SoLuongVatTuGlobalCount++;
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
            // nếu có lỗi thì quay lại xóa
            delete rp;
        }
        else if (rp->left == nullptr)
        {
            root = rp->right;
            // nếu có lỗi thì quay lại xóa
            delete rp;
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

// int main()
// {
//     DanhSachVatTu root = nullptr;

//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000001", "05", "cai", 25));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000002", "04", "cai", 20));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000003", "01", "cai", 10));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000004", "02", "cai", 10));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000005", "10", "cai", 10));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000006", "03", "chiec", 15));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000007", "06", "bo", 5));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000008", "12", "hop", 30));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000009", "07", "hop", 30));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000010", "08", "bo", 12));
//     insertDanhSachVatTu(root, newDanhSachVatTu("vt-0000011", "14", "cai", 18));

//     updateMenu(root);

//     return 0;
// }