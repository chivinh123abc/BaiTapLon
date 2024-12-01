#include <iostream>
using namespace std;

// dynamic programming - DP
int main()
{
    cout << "nhap so luong bo test: ";
    int T;

    cin >> T;

    int *results = new int[T];

    for (int t = 0; t < T; ++t)
    {
        int N, K;
        cout << "nhap N va K: "; //->N la so luong phan tu cua day, K la kich thuoc day con
        cin >> N >> K;

        int *A = new int[N];
        for (int i = 0; i < N; ++i)
        {
            cout << "Nhap phan tu thu: " << i + 1 << ": ";
            cin >> A[i];
        }

        int **dp = new int *[N];
        for (int i = 0; i < N; ++i)
        {
            dp[i] = new int[K + 1](); // khoi tao mang tat ca bang 0
        }

        for (int i = 0; i < N; ++i)
        {
            dp[i][1] = 1;
        }

        for (int k = 2; k <= K; ++k)
        {
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < i; ++j)
                {
                    if (A[j] < A[i])
                    {
                        dp[i][k] += dp[j][k - 1];
                    }
                }
            }
        }

        int result = 0;
        for (int i = 0; i < N; ++i)
        {
            result += dp[i][K];
        }

        results[t] = result;

        for (int i = 0; i < N; ++i)
        {
            delete[] dp[i];
        }
        delete[] dp;
        delete[] A;
    }

    cout << "Ket qua: ";
    for (int t = 0; t < T; ++t)
    {
        cout << results[t] << " ";
    }

    delete[] results;

    return 0;
}
