#include "vattu.cpp"

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

// int main()
// {
//     DanhSachVatTu root = nullptr;

//     insertVatTuByFile(root, "vattu.txt");
//     inDanhSachVatTuTheoTenVT(root);
//     saveVatTuToFile(root, "vattu.txt");

//     return 0;
// }