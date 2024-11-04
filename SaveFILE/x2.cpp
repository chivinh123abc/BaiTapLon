#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAX 100
#define TRUE 1
#define FALSE 0

int n, x[MAX], OK = TRUE, dem = 0;

void Init()
{
    cout << "\n Nhap n=";
    cin >> n;
}

void Result()
{
    cout << "\n Ket qua buoc " << ++dem << ":";
    for (int i = 1; i <= n; i++)
    {
        cout << x[i] << " ";
    }
}

void Try(int i)
{
    for (int j = 0; j <= 1; j++)
    {
        x[i] = j;
        if (i == n)
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