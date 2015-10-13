#include <bits/stdc++.h>
#define lli long long int

using namespace std;

const int INF = 1e8;
const int MAXN = 105;
const int MAXV = 4099;

int n;
int num[MAXN];
int otra[MAXN];
int primo[MAXN];
int criba[MAXN];
int memo[MAXN][MAXV];

void Pre(int u){
    int cont = 0;

    for(int i=2;i<=u;i++)
        if(!criba[i]){
            for(lli j=i*i;j<=u;j+=i)
                criba[j] = i;
            criba[i] = i;
            primo[i] = cont++;
        }

    //printf("%d\n",cont);

    for(int i=2;i<=u;i++){
        int nueva = 0 , aux = i;
        while(aux!=1){
            nueva |= (1<<primo[criba[aux]]);
            aux /= criba[aux];
        }
        otra[i] = nueva;
    }
}

int DP(int id,int mask){
    if(id==n) return memo[id][mask] = 0;
    if(memo[id][mask]!=-1) return memo[id][mask];

    int res = INF;

    for(int i=1;i<=39;i++){
        if(mask&otra[i]) continue;
        res = min( res , DP( id + 1 , mask | otra[i] ) + abs(num[id] - i) );
    }

    return memo[id][mask] = res;
}

void DP2(int id,int mask){
    if(id==n){
        printf("\n");
        return;
    }

    for(int i=1;i<=39;i++){
        if(mask&otra[i]) continue;

        if(memo[id][mask] - abs(num[id] - i)==memo[id+1][mask|otra[i]]){
            printf(" %d",i);
            DP2(id+1 , mask|otra[i]);
            return;
        }
    }
}

int main(){

    int u = 1;
    Pre(39);
    //printf("%d\n",(1<<13));

    while(scanf("%d",&n) && n){
        for(int i=0;i<n;i++)
            scanf("%d",&num[i]);

        for(int i=0;i<n;i++)
            fill( memo[i] , memo[i] + MAXV , -1 );

        DP(0,0);
        printf("Case #%d:",u++);
        DP2(0,0);
    }

    return 0;
}
