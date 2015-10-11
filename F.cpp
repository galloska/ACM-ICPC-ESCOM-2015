#include <bits/stdc++.h>
#define pii pair<int,int>

using namespace std;

const int INF = 1e8;
const int LOGV = 20;
const int MAXN = 10005;

int region;
int dist[MAXN];
bool vis[MAXN];
int num[MAXN];
int low[MAXN];
int numeracion;
int table[MAXN];
int nuevo[MAXN];
int level[MAXN];
int parent[MAXN];
int P[MAXN][LOGV];
map<pii,int> check;
vector<pii> puentes;
vector<int> grafo[MAXN];

int loga(int v){
	table[0] = table[1] = 0;
	for(int i=2;i<=v;i++)
		table[i] = table[i>>1] + 1;
}

void Pre(int v){
	int log = table[v];

	for(int i=0;i<v;i++)
		P[i][0] = parent[i];
	
	for(int j=1;j<=log;j++)
		for(int i=0;i<v;i++)
			P[i][j] = P[ P[i][j-1] ][j-1];
}

int LCA(int v,int a,int b){
	int log = table[v];

	if(level[a]<level[b]) swap(a,b);

	for(int i=log;i>=0;i--)
		if(level[a] - ( 1 << i ) >= level[b] )
			a = P[a][i];

	if(a==b) return a;

	for(int i=log;i>=0;i--)
		if(P[a][i] != P[b][i] )
			a = P[a][i] , b = P[b][i];

	return P[a][0];
}

void dfs(int u){
	vis[u] = true;
	nuevo[u] = region;

	for(int i=0;i<grafo[u].size();i++){
		int v = grafo[u][i];
		if(!vis[v])
			dfs(v);
	}
}

void Puentes(int u,int p){
	int hijos = 0;
	low[u]= num[u] = ++numeracion;

	for(int i=0;i<grafo[u].size();i++){
		int v = grafo[u][i];
		if(v==p) continue;
		if(!num[v]){
			++hijos;
			Puentes( v , u );

			if(low[v] > num[u]){
				check[ pii( min( u , v ) , max( u , v ) ) ] = 1;
				puentes.push_back( pii( u , v ) );
			}
			
			low[u] = min( low[u] , low[v] );
		}
		else
			low[u] = min( low[u] , num[v] );
	}
}

void Encuentra(int n){
	numeracion = 0;
	fill( num , num + n , 0 );
	fill( low , low + n , 0 );
	puentes.clear();

	for(int i=0;i<n;i++)
		if(!num[i])
			Puentes( i , -1 );
}

void bfs(int u,int n){
	queue<int> q;
	fill( dist , dist + n , INF );
	dist[u] = 0;
	parent[u] = u;
	q.push(u);

	while(!q.empty()){
		int u = q.front();
		q.pop();

		for(int i=0;i<grafo[u].size();i++){
			int v = grafo[u][i];
			if( dist[v] == INF ){
				parent[v] = u;
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
}

void Construye(int n){

	for(int i=0;i<n;i++)
		grafo[i].clear();

	for(int i=0;i<puentes.size();i++){
		int u = puentes[i].first;
		int v = puentes[i].second;
		grafo[nuevo[u]].push_back( nuevo[v] );
		grafo[nuevo[v]].push_back( nuevo[u] );
	}

	fill( vis , vis + region , false );
	bfs( 0 , region );

	for(int i=0;i<region;i++)
		level[i] = dist[i];
}

int main(){
	int n,m,a,b,q,u=1;
	loga( MAXN - 1 );
	while(1){
		scanf("%d %d",&n,&m);
		if(!n && !m) return 0;

		vector<pii> aristas;
		for(int i=0;i<n;i++)
			grafo[i].clear();
		check.clear();

		while(m--){
			scanf("%d %d",&a,&b);
			a--,b--;
			aristas.push_back( pii( a , b ) );
			grafo[a].push_back(b);
			grafo[b].push_back(a);
		}

		Encuentra(n);

		for(int i=0;i<n;i++)
			grafo[i].clear();

		for(int i=0;i<aristas.size();i++){
			a = aristas[i].first;
			b = aristas[i].second;
			if(a>b)
				swap( a , b );
			if( check.find( pii( a , b ) ) == check.end() ){
				grafo[a].push_back(b);
				grafo[b].push_back(a);
			}
		}

		fill( vis , vis + n , false );
		region = 0;

		for(int i=0;i<n;i++)
			if(!vis[i]){
				dfs(i);
				region++;
			}

		/*for(int i=0;i<n;i++)
			printf("%d ",nuevo[i]);
		printf("\n");*/

		Construye(n);

		n = region;
		Pre( n );
		//printf("%d puentes\n",n);

		/*for(int i=0;i<n;i++)
			printf("%d ",dist[nuevo[i]]);
		printf("\n");*/

		if(u>1) printf("\n");
		printf("Case #%d:\n",u++);
		scanf("%d",&q);
		while(q--){
			scanf("%d %d",&a,&b);
			a--,b--;
			int comun = LCA( n , nuevo[a] , nuevo[b] );
			//printf("%d %d %d\n",comun , nuevo[a],nuevo[b]);
			printf("%d\n", ( dist[nuevo[a]] + dist[nuevo[b]] - 2 * dist[comun] ) * 50 );
		}
	}
	return 0;
}
