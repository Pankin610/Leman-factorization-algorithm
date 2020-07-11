/*

Code by: Pavel Sankin
github.com/Pankin610

Leman's algroithm. Factorizes a given integer <= 10^18
Time Complexity: O( n^(1/3) ), pretty big constant.

Possible use: Competetive Programming.

*/


#include <bits/stdc++.h>

using namespace std;

long long mul(long long a, long long b, long long m) {
    // multiplies two numbers <= 10^18 modulo m <= 10^18

    a %= m, b %= m;
    long long q = (long long)((long double)a * (long double)b / (long double)m);
    long long res = a * b - q * m;
    while(res < 0)
        res += m;
    return res % m;
}

long long bin_pow(long long num, long long st, long long mod) {
    if (st == 0)
        return 1;
    if (st % 2 == 1)
        return mul(bin_pow(num, st - 1, mod), num, mod);
    else {
        long long qz = bin_pow(num, st / 2, mod);
        return mul(qz, qz, mod);
    }
}

vector<long long> factorize(long long n) {
    vector<long long> ans;

    int sqrt3 = 0;
    for (long long i = 2; i * i * i <= n && n > 1; i++) {
        while(n % i == 0) {
            ans.push_back(i);
            n /= i;
        }
        sqrt3 = i;
    }
    if (n == 1)
        return ans;

    int sqrt6 = sqrt(sqrt3) + 5;

    for (int k = 1; k <= sqrt3 + 5; k++) {
        int d_max = sqrt6 / (4 * sqrt(k)) + 20;
        for (int d = 0; d < d_max; d++) {
            long long A = (long long)(sqrt((long double)4 * (long double)k * (long double)n)) + d;
            long long B = (long long)(sqrt((long double)A * (long double)A - (long double)4 * (long double)k * (long double)n));

            if (mul(A, A, n) != mul(B, B, n))
                continue;

            long long g;

            g = __gcd(n, A + B);
            if (g > 1 && g < n) {
                ans.push_back(g);
                ans.push_back(n / g);
                return ans;
            }

            g = __gcd(n, A - B);
            if (g > 1 && g < n) {
                ans.push_back(g);
                ans.push_back(n / g);
                return ans;
            }
        }
    }

    ans.push_back(n);
    return ans;
}
