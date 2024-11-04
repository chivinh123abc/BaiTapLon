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

    for (int i = 0; i <= n; i++)
    {
        x[i] = i;
    }
}

void Result()
{
    cout << "/n Ket qua buoc " << ++dem << ":";
    for (int i = 1; i <= n; i++)
    {
        cout << x[i] << " ";
    }
}

void Next_P()
{
    int j = n - 1;
    while (j > 0 && x[j] > x[j + 1])
    {
        j--;
    }

    if (j > 0)
    {
        int k = n;
        while (x[j] > x[k])
        {
            k--;
        }
        int t = x[j];
        x[j] = x[k];
        x[k] = t;

        int r = j + 1, s = n;

        while (r <= s)
        {
            t = x[r];
            x[r] = x[s];
            x[s] = t;
            r++;
            s--;
        }
    }
    else
    {
        OK = FALSE;
    }
}

int main()
{
    Init();
    while (OK)
    {
        Result();
        Next_P();
    }
    system("PAUSE");
    return 0;
}