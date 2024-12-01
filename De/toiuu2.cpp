#include <iostream>
#include <vector>

using namespace std;

// Binary search
// Ham tim kiem ham bao quanh
void tim2DuongBaoQuanh(const vector<double> &a, const vector<double> &b, double x_p, double y_p, int &line1, int &line2)
{
    int left = 0, right = a.size() - 1;

    // Tim kiem nhi phan gia tri can tim
    while (left < right - 1)
    {
        int mid = (left + right) / 2;
        // Tinh gia tri y của duong thang tại x_p
        double y_mid = a[mid] * x_p + b[mid];

        if (y_mid < y_p)
        {
            left = mid; // P nam ben phai
        }
        else
        {
            right = mid; // P nam ben trai
        }
    }

    // Luu ket qua vào line1 và line2
    line1 = left;  // Duong ben duoi
    line2 = right; // Duong ben tren
}

int main()
{
    int n;
    cout << "Nhap so luong duong thang N: ";
    cin >> n;

    vector<double> a(n), b(n);
    cout << "Nhap he so a va b cho moi duong (y = ax + b):\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i] >> b[i];
    }

    double x_p, y_p;
    cout << "Nhap toa do diem P(x, y): ";
    cin >> x_p >> y_p;

    // Chi so cua 2 duong bao quanh (dia chi cua no)
    int line1 = -1, line2 = -1;

    // Tim
    tim2DuongBaoQuanh(a, b, x_p, y_p, line1, line2);

    // Ket
    cout << "Hai duong bao quanh P la:\n";
    cout << "Duong 1: y = " << a[line1] << "x + " << b[line1] << "\n";
    cout << "Duong 2: y = " << a[line2] << "x + " << b[line2] << "\n";

    return 0;
}
