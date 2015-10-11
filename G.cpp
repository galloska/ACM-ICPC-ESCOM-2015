#include <bits/stdc++.h>
#define pii pair<double,double>

using namespace std;

const int MAXN = 100005;

pii num[MAXN];

int main(){
	int n,k,u=1;

	while(1){
		scanf("%d %d",&n,&k);
		if(!n && !k) return 0;

		double sum = 0.0;

		for(int i=0;i<n;i++)
			scanf("%lf %lf",&num[i].first,&num[i].second);

		sort( num , num + n );

		for(int i=0;i<n;i++){
			if(i < k - 1)
				sum += num[i].first;
		}
		double res = double(1LL<<60);

		for(int i=0;i<n;i++){
			if( i < k - 1 ) continue;
			res = min( res , (sum + num[i].first) * (num[i].second / num[i].first) );
		}

		printf("Case #%d: %.6lf\n",u++,res);
	}
	return 0;
}
