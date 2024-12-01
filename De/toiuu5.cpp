#include <iostream>
#include <cstring>
using namespace std;

struct Lenh
{
    char loai[4]; // ATO hoặc LO
    int soLuong;
    int giaDat;
    int thoiGian;
};

bool soSanhLenhMua(const Lenh &a, const Lenh &b)
{
    if (a.giaDat != b.giaDat)
        return a.giaDat > b.giaDat;
    return a.thoiGian < b.thoiGian;
}

// (uu tien gia thap -> thoigian)
bool soSanhLenhBan(const Lenh &a, const Lenh &b)
{
    if (a.giaDat != b.giaDat)
        return a.giaDat < b.giaDat;
    return a.thoiGian < b.thoiGian;
}

int timGiaKhopTotNhat(Lenh lenhMua[], int nMua, Lenh lenhBan[], int nBan)
{
    for (int i = 0; i < nMua - 1; i++)
    {
        for (int j = i + 1; j < nMua; j++)
        {
            if (!soSanhLenhMua(lenhMua[i], lenhMua[j]))
            {
                swap(lenhMua[i], lenhMua[j]);
            }
        }
    }
    for (int i = 0; i < nBan - 1; i++)
    {
        for (int j = i + 1; j < nBan; j++)
        {
            if (!soSanhLenhBan(lenhBan[i], lenhBan[j]))
            {
                swap(lenhBan[i], lenhBan[j]);
            }
        }
    }

    // Xu ly khop lenh
    int giaKhopTotNhat = 0, soLuongKhopMax = 0;

    for (int gia = 8000; gia <= 10000; gia++)
    {
        int soLuongMua = 0, soLuongBan = 0;

        // Tinh tong so luong co the khop
        for (int i = 0; i < nMua; i++)
        {
            if (lenhMua[i].giaDat >= gia)
            {
                soLuongMua += lenhMua[i].soLuong;
            }
        }
        for (int i = 0; i < nBan; i++)
        {
            if (lenhBan[i].giaDat <= gia)
            {
                soLuongBan += lenhBan[i].soLuong;
            }
        }

        // So luong khop thuc the là min(soLuongMua, soLuongBan)
        int soLuongKhop = min(soLuongMua, soLuongBan);

        // Cap nhat gia khop tot  nhat
        if (soLuongKhop > soLuongKhopMax)
        {
            soLuongKhopMax = soLuongKhop;
            giaKhopTotNhat = gia;
        }
    }

    return giaKhopTotNhat;
}

int main()
{
    // Mang lenh mua va ban
    Lenh lenhMua[100], lenhBan[100];
    int nMua, nBan;

    // Nhap so luong lenh mua
    cout << "Nhap so luong lenh mua: ";
    cin >> nMua;
    cout << "Nhap thong tin lenh mua:\n";
    for (int i = 0; i < nMua; i++)
    {
        cout << "Lenh " << i + 1 << " (loai, soLuong, giaDat, thoiGian): ";
        cin >> lenhMua[i].loai >> lenhMua[i].soLuong >> lenhMua[i].giaDat >> lenhMua[i].thoiGian;
    }

    cout << "Nhap so luong lenh ban: ";
    cin >> nBan;
    cout << "Nhap thong tin lenh ban:\n";
    for (int i = 0; i < nBan; i++)
    {
        cout << "Lenh " << i + 1 << " (loai, soLuong, giaDat, thoiGian): ";
        cin >> lenhBan[i].loai >> lenhBan[i].soLuong >> lenhBan[i].giaDat >> lenhBan[i].thoiGian;
    }

    // Xu ly
    int giaKhop = timGiaKhopTotNhat(lenhMua, nMua, lenhBan, nBan);
    cout << "Gia khop lenh tot nhat: " << giaKhop << endl;

    return 0;
}
