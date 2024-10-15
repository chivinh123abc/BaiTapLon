#include "vattu.cpp"
#include "nhanvien.cpp"
#include "hoadon.cpp"
// Part1 : VATTU------------------------
void saveVatTuSupporter(DanhSachVatTu root, ofstream &outFile)
{
    if (root != nullptr)
    {
        saveVatTuSupporter(root->left, outFile);
        char res[101];
        sprintf(res, "%s|%s|%s|%d", root->maVT, root->tenVT, root->dVT, root->soLuongTon);
        outFile << res << endl;
        saveVatTuSupporter(root->right, outFile);
    }
}

void saveVatTuToFile(DanhSachVatTu root, const char *fileName)
{

    ofstream outFile(fileName);

    if (!outFile.is_open())
    {
        cout << "Khong the mo file!" << endl;
        return;
    }

    saveVatTuSupporter(root, outFile);
    outFile.close();
    cout << "Thanh cong" << endl;
}

// hien tai chi tach theo tung dong
void insertVatTuByFileSupporter(DanhSachVatTu &root, ifstream &inFile)
{
    char buffer[256];
    while (inFile.getline(buffer, 256))
    {
        char inputMaVatTu[11];
        char inputTenVT[51];
        char inputDVT[11];
        int inputSoLuongTon;

        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%d", inputMaVatTu, inputTenVT, inputDVT, &inputSoLuongTon);

        insertDanhSachVatTu(root, newDanhSachVatTu(inputMaVatTu, inputTenVT, inputDVT, inputSoLuongTon));
    }
}

void insertVatTuByFile(DanhSachVatTu &root, const char *fileName)
{
    ifstream inFile(fileName);

    if (!inFile.is_open())
    {
        cout << "Khong the mo file" << endl;
        return;
    }

    insertVatTuByFileSupporter(root, inFile);

    inFile.close();
    cout << "Da xong" << endl;
}

// Part1 : NHANVIEN------------------------

void saveNhanVienSupporter(DanhSachNhanVien ds, ofstream &outFile, int soLuongNV)
{
    if (soLuongNV > 0)
    {
        for (int i = 0; i < soLuongNV; i++)
        {
            char res[101];
            sprintf(res, "%s|%s|%s|%s", ds[i]->maNV, ds[i]->ho, ds[i]->ten, (ds[i]->phai == nam ? "nam" : "nu"));
            outFile << res << endl;
        }
    }
}

void saveNhanVienToFile(DanhSachNhanVien ds, const char *fileName, int soLuongNV)
{

    ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        cout << "Khong the mo file!" << endl;
        return;
    }

    saveNhanVienSupporter(ds, outFile, soLuongNV);
    outFile.close();
    cout << "Thanh cong" << endl;
}

void insertNhanVienByFileSupporter(DanhSachNhanVien &ds, ifstream &inFile, int &soLuongNV)
{
    char buffer[256];
    while (inFile.getline(buffer, 256))
    {
        char inputMaNV[21];
        char inputHo[11];
        char inputTen[21];
        char inputPhai1[4];
        Phai inputPhai2;

        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%3s", inputMaNV, inputHo, inputTen, inputPhai1);
        if (strcmp(inputPhai1, "nam") == 0)
        {
            inputPhai2 = nam;
        }
        else
        {
            inputPhai2 = nu;
        }

        cout << "Doc nhan vien: " << inputMaNV << ", " << inputHo << ", " << inputTen << ", " << (inputPhai2 == nam ? "nam" : "nu") << endl;

        insertNhanVienToDSNV(ds, newNhanVien(inputMaNV, inputHo, inputTen, inputPhai2, nullptr), soLuongNV);
    }
}

void insertNhanVienByFile(DanhSachNhanVien &ds, const char *fileName, int &soLuongNV)
{
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "Khong the mo file" << endl;
        return;
    }

    insertNhanVienByFileSupporter(ds, inFile, soLuongNV);

    inFile.close();
    cout << "Da xong" << endl;
}
