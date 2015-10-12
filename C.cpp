#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Arista;

const int INF = 1e8;
const int MAXN = 40020;

int n,m;
int num[25][MAXN];
char mat[25][MAXN];
int mov[5] = { 1 , 0 };
int mov2[5] = { 0 , 1 };

int pareja[MAXN];
bool visitado[MAXN];
vector<int> grafo[MAXN];

int CaminoIncremental(int u) {
    visitado[u] = true;
    for (int i = 0; i < grafo[u].size(); ++i)
        if (pareja[grafo[u][i]] == -1) 
            return pareja[grafo[u][i]] = u;
    for (int i = 0; i < grafo[u].size(); ++i) {
        int v = grafo[u][i];
        if (visitado[pareja[v]]) continue;
        if (CaminoIncremental(pareja[v]) != -1)
            return pareja[v] = u;
    }
    return -1;
}

vector<Arista> MaxEmparejamientoBipartito(
    const vector<int>& l, const vector<int>& r) {
    int n = l.size() + r.size();
    fill(pareja, pareja + n, -1);
    for (int i = 0; i < l.size(); ++i) {
        fill(visitado, visitado + n, false);
        CaminoIncremental(l[i]);
    }
    vector<Arista> parejas;
    for (int i = 0; i < r.size(); ++i)
        if (pareja[r[i]] != -1) parejas.push_back(
            Arista(pareja[r[i]], r[i]));
    return parejas;
}

bool valid(int i,int j){
	if(i<0 || j<0 || i==n || j==m) return false;
	if(mat[i][j]=='#') return false;
	return true;
}

void AgregaArista(int a,int b){
	grafo[a].push_back(b);
	grafo[a].push_back(b);
}

int main(){

	int c = 1;

	while(scanf("%d %d",&n,&m) && n && m){
		for(int i=0;i<n;i++)
			scanf("\n%s",mat[i]);

		int u = 0,cont = 0;
		vector<int> l,r;

		for(int i=0;i<2 * n * m + 4;i++)
			grafo[i].clear();

		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				num[i][j] = u++;
				l.push_back(num[i][j]);
				r.push_back(num[i][j] + n * m);
			}

		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(mat[i][j]=='#')
					continue;
				cont++;
				for(int h=0;h<2;h++)
					if( valid( i + mov[h] , j + mov2[h] ) ){
						AgregaArista( num[i][j] , num[i + mov[h]][j + mov2[h]] + n * m );
						AgregaArista( num[i + mov[h]][j + mov2[h]] , num[i][j]  + n * m );
					}
			}
		int res = ( cont - MaxEmparejamientoBipartito(l,r).size() );

		if(res&1) res = res / 2 + 1;
		else res = res / 2;

		printf("Case #%d: %d\n",c++,res);
	}
	return 0;
}
