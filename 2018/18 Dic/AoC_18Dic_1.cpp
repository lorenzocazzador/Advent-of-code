#include <bits/stdc++.h>
using namespace std;

#define MAXN 100
typedef long long ll;
typedef pair<ll, ll> pii;

char s1[MAXN][MAXN], s2[MAXN][MAXN];
bool actualS1, processed[MAXN][MAXN];
ll N;

pair<ll, ll> p[] = { {-1, -1}, {-1,0}, {-1,1}, {0,-1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

#define F first
#define S second

ll nO, nL, nW;
bool inside(ll r, ll c){
    return r>=0 && r<N && c>=0 && c<N;
}

void contaAdj(ll r, ll c){
	nW = nO = nL = 0;
    for(pair<ll, ll> & x : p){
        ll rN = r + x.F, cN = c + x.S;
        if(inside(rN, cN)){
            char c = ((actualS1) ? s1[rN][cN] : s2[rN][cN]);
            if( c == '.' ) nO++;
            else if( c == '|' ) nW++;
            else if( c == '#' ) nL++;
        }
    }
}

void stampa(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cout << ( actualS1 ? s1[i][j] : s2[i][j]);
        cout << "\n";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    while(cin >> s1[N]){ N++; }

    actualS1 = true;

    ll V = 10;

    queue<pii> q;
    V--;
    for(ll i=0; i<N; i++){
        for(ll j=0; j<N; j++){
            contaAdj(i, j);
            if(actualS1){
                if(s1[i][j] == '.' && nW>=3){ s2[i][j] = '|'; q.push({i,j}); }
                else if(s1[i][j] == '|' && nL>=3){ s2[i][j] = '#'; q.push({i,j}); }
                else if(s1[i][j] == '#' && (nW == 0 || nL == 0)){ s2[i][j] = '.'; q.push({i,j}); }
                else s2[i][j] = s1[i][j];
            }else{
                if(s2[i][j] == '.' && nW>=3){ s1[i][j] = '|'; q.push({i,j}); }
                else if(s2[i][j] == '|' && nL>=3){ s1[i][j] = '#'; q.push({i,j}); }
                else if(s2[i][j] == '#' && (nW == 0 || nL == 0)){ s1[i][j] = '.'; q.push({i,j}); }
                else s1[i][j] = s2[i][j];
            }
        }
    }

    while(V--){
        bool changed = false;
        for(ll i=0; i<N; i++){
            for(ll j=0; j<N; j++){
                contaAdj(i, j);
                if(actualS1){
                    if(s1[i][j] == '.' && nW>=3){ s2[i][j] = '|'; changed = true; }
                    else if(s1[i][j] == '|' && nL>=3){ s2[i][j] = '#'; changed = true; }
                    else if(s1[i][j] == '#' && (nW == 0 || nL == 0)){ s2[i][j] = '.'; changed = true; }
                    else s2[i][j] = s1[i][j];
                }else{
                    if(s2[i][j] == '.' && nW>=3){ s1[i][j] = '|'; changed = true; }
                    else if(s2[i][j] == '|' && nL>=3){ s1[i][j] = '#'; changed = true; }
                    else if(s2[i][j] == '#' && (nW == 0 || nL == 0)){ s1[i][j] = '.'; changed = true; }
                    else s1[i][j] = s2[i][j];
                }
            }
        }
        if(!changed) break;
        actualS1 = !actualS1;
    }

    nL = nW = 0;
    for(ll i=0; i<N; i++){
        for(ll j=0; j<N; j++){
            char c = ((actualS1) ? s1[i][j] : s2[i][j]);
            if( c == '|' ) nW++;
            else if( c == '#' ) nL++;
        }
    }

    cout << nW * nL;
    return 0;
}
