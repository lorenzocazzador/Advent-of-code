#include <bits/stdc++.h>
using namespace std;

#define MAXN 1500
int sq[MAXN][MAXN], res;
bool siSovrappone[MAXN];

void inserisci(int id, int c, int r, int W, int T){
    for(int i=0; i<T; i++){
        for(int j=0; j<W; j++){
            if(sq[r+i][c+j] != 0){
                siSovrappone[sq[r+i][c+j]] = true;
                siSovrappone[id] = true;
            }
            sq[r+i][c+j] = id;
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    string s; char c;
    int id, inchLeft, inchTop, W, T, nIds = 0;
    while(cin >> c >> id >> c >> inchLeft >> c >> inchTop >> c >> W >> c >> T){
        //cout << inchLeft << " " << inchTop << " " << W << " " << T << "\n";
        inserisci(id, inchLeft, inchTop, W, T);
        nIds++;
    }
    for(int i=1; i<=nIds; i++) if(!siSovrappone[i]) cout << i << "\n";
    return 0;
}
