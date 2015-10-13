#include <bits/stdc++.h>
#define MOD 1000000007
#define lli long long int

using namespace std;

const int MAXN = 10005;

lli pot[MAXN];
int criba[MAXN];
bool valid[MAXN];
bool estado[MAXN];
vector<lli> prime;
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

int main(){
    Pre(10001);

	int t,n,k,a;

	scanf("%d",&t);

	for(int u=1;u<=t;u++){
		scanf("%d %d",&n,&k);

        pot[0] = 1;
        for(int i=1;i<=n;i++)
            pot[i] = ( pot[i-1] * (n+1) ) % MOD; 
		
		set<int> up,down;

        for(int i=1;i<=n;i++){
            estado[i] = false;
            down.insert(i);
            valid[i] = true;
        }		

		for(int i=0;i<k;i++){
			scanf("%d",&a);
			estado[a] = true;
			up.insert(a);
            down.erase(a);
		}
		
		int turno = 0;
		vector<lli> res;
		
		while(n){
			if(!up.size() && !turno){
                set<int> :: iterator it = down.end();
				it--;
				int num = *it;
				down.erase(num);
                up.insert(num);
			}
            else if(!up.size()){
                set<int> :: iterator it = down.lower_bound(0);
				int num = *it;
				down.erase(num);
                up.insert(num);
			}

            bitset<10001> used;

			if(!turno){
				set<int> :: iterator it = up.end();
				it--;
				int num = *it;
                valid[num] = false;
                up.erase(num);
                int aux = num;

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
			}
			else{
				set<int> :: iterator it = up.lower_bound(0);
				int num = *it;
                valid[num] = false;
                up.erase(num);
                int aux = num;

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
			}
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
