#include "vattu.cpp"

void saveVatTuToFile(DanhSachVatTu root, ofstream &outFile)
{
    if (root == nullptr)
    {
        return;
    }

    saveVatTuToFile(root->left, outFile);
    char res[101];
    sprintf(res, "#%s|%s|%s|%d", root->tenVT, root->maVT, root->dVT, root->soLuongTon);
    outFile << res << endl;
    saveVatTuToFile(root->right, outFile);
}

int main()
{
    DanhSachVatTu root = nullptr;

    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000001", "05", "cai", 25));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000002", "04", "cai", 20));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000003", "01", "cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000004", "02", "cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000005", "10", "cai", 10));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000006", "03", "chiec", 15));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000007", "06", "bo", 5));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000008", "12", "hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000009", "07", "hop", 30));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000010", "08", "bo", 12));
    insertDanhSachVatTu(root, newDanhSachVatTu("xd-0000011", "14", "cai", 18));

    ofstream outFile("output.txt");
    if (outFile.is_open())
    {
        saveVatTuToFile(root, outFile);
        outFile.close();
        cout << "Ghi thanh cong" << endl;
    }
    else
    {
        cout << "Khong The Mo Tep" << endl;
    }

    return 0;
}