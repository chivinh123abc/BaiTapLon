#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// DO phuc tap nlogn;

using namespace std;

// Kiem tra co phai so nguyen to khong
bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i <= sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

vector<int> XuLyNoiDung(vector<int> &arr)
{
    vector<int> primes, nonPrimes;

    for (int num : arr)
    {
        if (isPrime(num))
        {
            primes.push_back(num);
        }
        else
        {
            nonPrimes.push_back(num);
        }
    }

    sort(primes.begin(), primes.end());
    sort(nonPrimes.begin(), nonPrimes.end());

    primes.insert(primes.end(), nonPrimes.begin(), nonPrimes.end());
    return primes;
}

int main()
{
    int n;
    cout << "Nhap so luong phan tu cua day: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Nhap day so: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    // Xu ly
    vector<int> res = XuLyNoiDung(arr);
    //
    cout << "Ket Qua: ";
    for (int num : res)
    {
        cout << num << " ";
    }

    return 0;
}
