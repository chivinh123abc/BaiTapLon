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

void saveAllDataSupporter(DanhSachNhanVien ds, ofstream &outFile, int soLuongNV)
{
    if (soLuongNV > 0)
    {
        for (int i = 0; i < soLuongNV; i++)
        {
            char res[256];
            sprintf(res, "#%s|%s|%s|%s", ds[i]->maNV, ds[i]->ho, ds[i]->ten, (ds[i]->phai == nam ? "nam" : "nu"));
            outFile << res << endl;
            DanhSachHoaDon currentHD = ds[i]->ds_hoadon;
            while (currentHD != nullptr)
            {
                sprintf(res, "&%s|%d|%d|%d|%s", currentHD->soHD, currentHD->date.day, currentHD->date.month, currentHD->date.year, (currentHD->loai == n ? "nhap" : "xuat"));
                CT_HoaDon *currentCT = currentHD->ds_ct_hoadon;
                outFile << res << endl;
                while (currentCT != nullptr)
                {
                    sprintf(res, "!%s|%d|%f|%f", currentCT->maVT, currentCT->soLuong, currentCT->donGia, currentCT->vAT);
                    outFile << res << endl;
                    currentCT = currentCT->next;
                }
                currentHD = currentHD->next;
            }
        }
    }
}

void saveAllDataToFile(DanhSachNhanVien ds, const char *fileName, int soLuongNV)
{

    ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        cout << "Khong the mo file!" << endl;
        return;
    }

    saveAllDataSupporter(ds, outFile, soLuongNV);
    outFile.close();
    cout << "Thanh cong" << endl;
}

void insertAllDataSupporter(DanhSachNhanVien &ds_nv, ifstream &inFile, int &soLuongNV, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_ct_hd)
{
    char buffer[255];
    while (inFile.getline(buffer, 255))
    {
    start:
        if (buffer[0] == '#')
        {
            char inputMaNV[21];
            char inputHo[21];
            char inputTen[11];
            char inputPhai1[4];
            Phai inputPhai2;

            sscanf(buffer, "#%20[^|]|%20[^|]|%10[^|]|%5s", inputMaNV, inputHo, inputTen, inputPhai1);
            if (strcmp(inputPhai1, "nam") == 0)
            {
                inputPhai2 = nam;
            }
            else
            {
                inputPhai2 = nu;
            }

            HoaDon *new_hoadon = nullptr;
            while (inFile.getline(buffer, 255))
            {
            start2:
                if (buffer[0] == '&')
                {
                    char inputSoHD[21];
                    Date inputDate;
                    LoaiHoaDon inputLoai;
                    char inputLoai1[6];

                    sscanf(buffer, "&%20[^|]|%d|%d|%d|%5s", inputSoHD, &inputDate.day, &inputDate.month, &inputDate.year, inputLoai1);
                    if (strcmp(inputLoai1, "nhap") == 0)
                    {
                        inputLoai = n;
                    }
                    else
                    {
                        inputLoai = x;
                    }
                    //
                    CT_HoaDon *new_ct = nullptr;
                    while (inFile.getline(buffer, 255))
                    {
                        if (buffer[0] == '!')
                        {
                            char maVT[11];
                            int inputSoLuong;
                            double inputDonGia;
                            double inputVAT;

                            sscanf(buffer, "!%10[^|]|%d|%lf|%lf", maVT, &inputSoLuong, &inputDonGia, &inputVAT);
                            Them_CTHD_CanMultipleVariable(new_ct, newDanhSachCTHoaDon(maVT, inputSoLuong, inputDonGia, inputVAT));
                        }

                        if (buffer[0] == '#')
                        {
                            break;
                        }

                        if (buffer[0] == '&')
                        {
                            break;
                        }
                    }
                    InsertHoaDonVaoDSHD(new_hoadon, newHoaDon(inputSoHD, inputDate, inputLoai, new_ct));
                    CT_HoaDon *new_ct_copy = new CT_HoaDon(*new_ct);
                    InsertHoaDonVaoDSHD(ds_hd, newHoaDon(inputSoHD, inputDate, inputLoai, new_ct_copy));
                    goto start2;
                }

                if (buffer[0] == '#')
                {
                    break;
                }
            }
            insertNhanVienToDSNV(ds_nv, newNhanVien(inputMaNV, inputHo, inputTen, inputPhai2, new_hoadon), soLuongNV);
            goto start;
        }
    }
}

void insertAllDataByFile(DanhSachNhanVien &ds_nv, const char *fileName, int &soLuongNV, DanhSachHoaDon &ds_hd, DanhSach_CT_HoaDon &ds_ct_hd)
{
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "Khong the mo file" << endl;
        return;
    }

    insertAllDataSupporter(ds_nv, inFile, soLuongNV, ds_hd, ds_ct_hd);

    inFile.close();
    cout << "Da xong" << endl;
}