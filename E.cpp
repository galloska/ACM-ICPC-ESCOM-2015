#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
using namespace std;

typedef long long int lld;

lld h[100100];
lld b[100100];
char s[100100];

#define BASE 33
#define MOD 1000000007LL
#define MODH

typedef pair< lld, lld > pii;

pii EE(int a, int b) {
	if (b == 0) return pii(1, 0);
	pii aux = EE(b, a % b);
	return pii(aux.second, aux.first - aux.second * (a/b));
}

int modinv(lld a, lld mod) {
	return (EE(a, mod).first + mod) % mod;
}

int main() {
	int n, k, i, l, t;
	lld r;
	map< lld, lld > m;
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	b[0] = 1;
	for (i = 1; i <= 100000; i++) {
		b[i] = b[i - 1] * BASE;
	}
	cin >> n;
	for (t = 1; t <= n; t++) {
		r = 0;
		m.clear();
		cin >> s >> k;
		for (i = 1; s[i - 1]; i++) {
			h[i] = (h[i - 1] * BASE) + (s[i - 1] - 'a' + 1);
		}
		l = i;
		for (i = k; s[i - 1]; i++) {
			lld p =  h[i] - (h[i - k] * b[k]);
			m[p] = m[p] + l - i;
		}
		for (auto v : m) {
			lld x = v.second % MOD;
			lld y = x - 1;
			if (y < 0)
				y = MOD - 1;
			r = (r + ((((x * y) % MOD) * modinv(2, MOD)) % MOD)) % MOD;
		}
		cout << "Case #" << t << ": " << r << endl;
	}
	return 0;
}
