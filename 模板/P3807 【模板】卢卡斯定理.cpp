#include <iostream>

using namespace std;

int p;
long long factor[1000005];

long long fastPow(long long x, long long y) {
    long long answer = 1;

    while (y) {
        if (y & 1) {
            answer = (answer * x) % p;
        }
        x = (x * x) % p;

        y >>= 1;
    }

    return answer % p;
}

long long inverse(long long x) {
    return fastPow(x, p - 2) % p;
}

void init(int n, int m) {
    factor[0] = factor[1] = 1;
    for (long long i = 2; i < std::max(n + m, p) + 5; i++) {
        factor[i] = (factor[i - 1] * i) % p;
    }
}

long long Cnm(int n, int m) {
    if (m > n) {
        return 0;
    }
    return (factor[n] * inverse(factor[m]) % p) * inverse(factor[n - m]) % p;
}

long long lucas(int n, int m) {
    if (m == 0) {
        return 1;
    } else {
        return Cnm(n % p, m % p) * lucas(n / p, m / p) % p;
    }
}

int main() {
    int testCase = 0;
    cin >> testCase;

    for (int _ = 0; _ < testCase; _++) {
        int n, m;
        cin >> n >> m >> p;
        init(n, m);
        cout << lucas(n + m, m) << endl;
    }

    return 0;
}