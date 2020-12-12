#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define F first
#define S second
#define MAXR 1900
#define MAXC 550

ll maxC, minC, maxR;
char grid[MAXR][MAXC];

void dbg_pii(pii x) { cerr << "r: " << x.F << " c: " << x.S << "\n"; }

void stampa(){
    cout << "     ";
    for(ll i=minC; i<maxC; i++) cout << i/100; cout << "\n     ";
    for(ll i=minC; i<maxC; i++) cout << ((i%100)/10); cout << "\n     ";
    for(ll i=minC; i<maxC; i++) cout << (i%10); cout << "\n";
    for(ll i=0; i<maxR; i++){
        /// ABCD
        if(i<10) cout << "   "; else if(i<100) cout << "  "; else if(i<1000) cout << " ";
        cout << i << " ";
        for(ll j=minC; j<maxC; j++) cout << grid[i][j];
        cout << "\n";
    }
}

bool isInsideBox(int r, int c){
    if(grid[r][c] == '#') return false;

    bool sx = false, dx = false;
    int colIniz, colFin;
    for(int i=c-1; i>=minC; i--) if(grid[r][i] == '#'){ colIniz = i; sx=true; break; }
    for(int i=c+1; i<maxC; i++) if(grid[r][i] == '#'){ colFin = i; dx=true; break; }

    if(!(sx&&dx)) return false;

    while(grid[r][colIniz] == '#') r++;
    r--;
    while(grid[r][colIniz] == '#') colIniz++;
    colIniz--;

    return colIniz == colFin;
}

void fillBox(int r, int c){
    assert(isInsideBox(r, c));

    int colIniz, colFin;
    for(int i=c-1; i>=minC; i--) if(grid[r][i] == '#'){ colIniz = i+1; break; }
    for(int i=c+1; i<maxC; i++) if(grid[r][i] == '#'){ colFin = i-1; break; }

    while(grid[r][colIniz] != '#'){
        for(int i=colIniz; i<= colFin; i++) if(grid[r][i] == '.') grid[r][i] = '~';
        r++;
    }

}

int nChiamate;
void solve(ll rig, ll col, int nChiam){
    if(rig == maxR-1) return;

    while( !isInsideBox(++rig, col) ) grid[rig][col] = '|';

    fillBox(rig, col);

    rig--;

    /// Vai a sx
    for(ll i=col-1; i>=minC; i--){
        if(grid[rig][i] == '#') break;
        else if(grid[rig][i] == '.'){
            grid[rig][i] = '|';
            if(grid[rig+1][i] == '.'){ solve(rig, i, ++nChiamate); break; }
        }
    }

    /// Vai a dx
    for(ll i=col+1; i<maxC; i++){
        //cout << rig << " " << i << "\n";
        if(grid[rig][i] == '#'){ break; }
        else if(grid[rig][i] == '.'){
            grid[rig][i] = '|';
            if(grid[rig+1][i] == '.'){ solve(rig, i, ++nChiamate); break; }
        }
    }

}

ll calcolaRes(){
    ll res = 0;
    for(ll i=0; i<maxR; i++){
        for(ll j=minC; j<maxC; j++) if(grid[i][j] == '|' || grid[i][j] == '~') res++;
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char c, d;
    ll v1, v2, v3; minC = INT_MAX;

    memset(grid, '.', sizeof grid);
    grid[0][500] = '+';

    while(cin >> d >> c >> v1 >> c >> c >> c >> v2 >> c >> c >> v3){
        /// x -> colonna, y -> riga
        if(d == 'x'){
            maxC = max(maxC, v1); minC = min(minC, v1);
            maxR = max(maxR, v3);
            for(ll r = v2; r <= v3; r++) grid[r][v1] = '#';
        }else{
            maxR = max(maxR, v1);
            maxC = max(maxC, v3); minC = min(minC, v2);
            for(ll c = v2; c <= v3; c++) grid[v1][c] = '#';
        }
    }

    maxC++; maxR++;

    //cout << isBetweenClay( {19, 500} );


    solve(0, 500, ++nChiamate);

    stampa();

    //cerr << isInsideBox(2, 496);

    //cout << "\n"; cout << "res: " << calcolaRes();

    return 0;
}
