#include <bits/stdc++.h>
#define MOD 1000000007
#define lli long long int

using namespace std;

const int MAXN = 10005;

set<int> up;
lli pot[MAXN];
set<int> down;
int criba[MAXN];
vector<lli> res;
bool valid[MAXN];
bool estado[MAXN];
vector<lli> prime;
bitset<MAXN> used;
vector<int> lista[MAXN];

void Pre(lli n){

    for(lli i=2;i<=n;i++)
        if(!criba[i]){
            for(lli j=i*i;j<=n;j+=i)
                criba[j] = i;
            criba[i] = i;
            prime.push_back(i);
        }

    for(lli i=2;i<=n;i++){
        int j = 0;
        lli num = i;
        while(j<prime.size() && prime[j]*prime[j]<=num){
            int cont = 0;
            if(num%prime[j]==0)
                while(num%prime[j]==0)
                    num/=prime[j],cont++;
            if(cont) lista[i].push_back(prime[j]);
            j++;
        }
        if(num>1) lista[i].push_back(num);
    }
}

void Iniciar(int n){
    pot[0] = 1;
    for(int i=1;i<=n;i++)
        pot[i] = ( pot[i-1] * (n+1) ) % MOD; 
    
    up.clear();
    down.clear();
    res.clear();

    for(int i=1;i<=n;i++){
        estado[i] = false;
        down.insert(i);
        valid[i] = true;
    }   
}

int main(){
    Pre(10001);

    int t,n,k,a;
    int num,aux;
    set<int> :: iterator it;

    scanf("%d",&t);

    for(int u=1;u<=t;u++){
        scanf("%d %d",&n,&k);

        Iniciar(n); 

        for(int i=0;i<k;i++){
            scanf("%d",&a);
            estado[a] = true;
            up.insert(a);
            down.erase(a);
        }
        
        int turno = 0;
        
        while(n){
            if(!up.size() && !turno){
                it = down.end();
                it--;
                int num = *it;
                down.erase(num);
                up.insert(num);
            }
            else if(!up.size()){
                it = down.lower_bound(0);
                int num = *it;
                down.erase(num);
                up.insert(num);
            }

            used.reset();

            if(!turno){
                it = up.end();
                it--;
                num = aux = *it;
            }
            else{
                it = up.lower_bound(0);
                num = aux = *it;
            }

            valid[num] = false;
            up.erase(num);

            if(num!=1){
                for(int j=0;j<lista[num].size();j++){
                    int a = lista[num][j];
                    for(int h=0;h<lista[a].size();h++){
                        int b = lista[a][h];
                        if(!valid[b] || used[b]) continue;
                        used[b] = true;
                        if(estado[b]){
                            up.erase(b);
                            down.insert(b);
                            estado[b] = false;
                        }
                        else{
                            up.insert(b);
                            down.erase(b);
                            estado[b] = true;
                        }
                    }
                }
            }
            res.push_back(aux);

            turno = 1 - turno;
            n--;
        }

        lli fin = 0;
        for(int i=res.size()-1;i>=0;i--)
            fin =( fin + res[i] * pot[res.size()-i-1] ) % MOD;
        
        printf("Case #%d: %lld\n",u,fin);
    }
    return 0;
}
