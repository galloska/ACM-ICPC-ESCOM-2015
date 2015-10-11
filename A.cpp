#include <bits/stdc++.h>
using namespace std;

long long int a, b, x, y;

int main (){

	int t = 0;
	scanf ("%lld %lld %lld %lld", &a, &b, &x, &y);
	while (a != 0 || b != 0 || x != 0 || y != 0){
		t++;
		if (b * x < a * y)
			printf ("Case #%d: You owe me a beer!\n", t);
		else printf ("Case #%d: No beer for the captain.\n", t);
		long long int numerador = b * x + a * y;
		long long int denominador = a * x * 2;
		long long int div = __gcd (numerador, denominador);
		numerador /= div;
		denominador /= div;
		if (numerador % denominador == 0)
			printf ("Avg. arrival time: %lld\n", numerador / denominador);
		else printf ("Avg. arrival time: %lld/%lld\n", numerador, denominador);
		scanf ("%lld %lld %lld %lld", &a, &b, &x, &y);		
	}
	return 0;
}
