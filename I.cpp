#include <bits/stdc++.h>

using namespace std;

int n,m;
int total;
int num[5][5];
int res[5][5] = {{ 1 , 4 , 11 },{ 4 , 64 , 1392 },{ 11 , 1392 , 389497 }};

bool valid(int i,int j,vector<bool> vis){
	if(vis[j]) return false;

	if(i==1){
		if( j==3 && !vis[2] ) return false;
		if( j==9 && !vis[5] ) return false;
		if( j==7 && !vis[4] ) return false;
		return true;
	}

	if(i==2){
		if( j==8 && !vis[5] ) return false;
		return true;
	}

	if(i==3){
		if( j==1 && !vis[2] ) return false;
		if( j==7 && !vis[5] ) return false;
		if( j==9 && !vis[6] ) return false;
		return true;
	}

	if(i==4){
		if( j==6 && !vis[5] ) return false;
		return true;
	}

	if(i==6){
		if( j==4 && !vis[5] ) return false;
		return true;
	}

	if(i==7){
		if( j==1 && !vis[4] ) return false;
		if( j==3 && !vis[5] ) return false;
		if( j==9 && !vis[8] ) return false;
		return true;
	}

	if(i==8){
		if( j==2 && !vis[5] ) return false;
		return true;
	}

	if(i==9){
		if( j==1 && !vis[5] ) return false;
		if( j==3 && !vis[6] ) return false;
		if( j==7 && !vis[8] ) return false;
		return true;
	}

	return true;
}

int busca(int act,vector<bool> vis,int len){
	if(len==total) return 1;

	vis[ act ] = true;

	int res = 0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if( valid( act , num[i][j] , vis ) )
				res += busca( num[i][j] , vis , len + 1 );
	return res;
}

int main(){
	int u=1;

	/*for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			num[i][j] = u++;

	vector<bool> vis;

	for(int i=0;i<10;i++)
		vis.push_back(false);
	

	for(int y=1;y<=3;y++){
		printf("{ ");
		for(int k=1;k<=3;k++){
			int res = 0;
			n = y;
			m = k;
			for(int h=1;h<=n*m;h++){
				total = h;
				for(int i=0;i<n;i++)
					for(int j=0;j<m;j++)
						res += busca( num[i][j] , vis , 1 );
			}
			printf("%d , ",res);
		}
		printf("},\n");
	}*/

	while(scanf("%d %d",&n,&m) && n && m){
		printf("Case #%d: %d\n",u++,res[n-1][m-1]);
	}
	return 0;
}
