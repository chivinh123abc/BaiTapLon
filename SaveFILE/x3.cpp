#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAX 100
#define TRUE 1
#define FALSE 0

int n, k, x[MAX], OK = TRUE, dem = 0;

void Init()
{
    cout << "\n Nhap n=";
    cin >> n;
    cout << "\n Nhap k=";
    cin >> k;
    x[0] = 0;
}

void Result()
{
    cout << "\n Ket qua buoc " << ++dem << ":";
    for (int i = 1; i <= k; i++)
    {
        cout << x[i] << " ";
    }
}

void Try(int i)
{
    for (int j = x[i - 1] + 1; j <= n - k + i; j++)
    {
        x[i] = j;
        if (i == k)
        {
            Result();
        }
        else
        {
            Try(i + 1);
        }
    }
}

int main()
{
    Init();
    Try(1);
    system("PAUSE");
    return 0;
}