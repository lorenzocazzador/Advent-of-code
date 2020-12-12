#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define F first
#define S second
#define MAXR 1900
#define MAXC 550

ll maxC, minC, maxR, minR;
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

bool isBetweenClay(pii p){
    ll r = p.F, c = p.S;
    //cout << r << " " << c << "\n";
    if(grid[r][c] == '#') return false;
    bool sx = false, dx = false;
    /// SX
    for(ll i=c-1; i>=minC; i--){
        if(grid[r][i] == '#' && grid[r+1][i] == '#'){ sx = true; break; }
        else if(grid[r+1][i] == '.') break;
    }
    /// DX
    for(ll i=c+1; i<maxC; i++){
        //cout << r << " " << i << "\n";
        if(grid[r][i] == '#' && grid[r+1][i] == '#'){ dx = true; break; }
        else if(grid[r+1][i] == '.'){ break; }
    }

    //cout << sx << " " << dx << "\n";
    return (sx && dx);
}

void fillWater(pii p){
    ll r = p.F, c = p.S;
    assert(grid[r][c] == '|');

    /// SX
    for(ll i=c-1; i>=minC; i--) if(grid[r][i] == '#') break; else grid[r][i] = '~';
    /// DX
    for(ll i=c; i<maxC; i++) if(grid[r][i] == '#') break; else grid[r][i] = '~';
}

int nChiamate;
void solve(ll rig, ll col, int nChiam){
    //cerr << "nChiamata: " << nChiam << " rig: " << rig << " col: " << col << "\n";

    if(rig == maxR-1) return;

    stack<pii> pila;

    int vol = 0;

    while(grid[++rig][col] == '.'){
            pila.push( {rig, col} );
            grid[rig][col] = '|';
    }
    if(grid[rig][col] == '|') return;
    while(!pila.empty() && isBetweenClay(pila.top())){
        pii att = pila.top(); pila.pop();
        fillWater(att);
    }

    if(pila.empty()) return;

    rig = pila.top().F; col = pila.top().S;

    /// Vai a sx
    for(ll i=col-1; i>=minC; i--){
        if(grid[rig][i] == '#') break;
        else if(grid[rig][i] == '.'){
            grid[rig][i] = '|';
            if(grid[rig+1][i] == '.'){ solve(rig, i, ++nChiamate); if(grid[rig+1][i-1] == '.')break; }
            else if(grid[rig+1][i] == '|') break;
        }
    }
    /// Vai a dx
    for(ll i=col+1; i<maxC; i++){
        //cout << rig << " " << i << "\n";
        if(grid[rig][i] == '#'){ break; }
        else if(grid[rig][i] == '.'){
            grid[rig][i] = '|';
            if(grid[rig+1][i] == '.'){ solve(rig, i, ++nChiamate); if(grid[rig+1][i+1] == '.')break; }
            else if(grid[rig+1][i] == '|') break;
        }
    }



    while(!pila.empty() && isBetweenClay(pila.top())){
        pii att = pila.top(); pila.pop();
        fillWater(att);
    }

    //if(nChiam == 2) cerr << "rig: " << rig << " col: " << col << "\n";
    if(pila.empty()) return;
    rig = pila.top().F; col = pila.top().S;

    if(grid[rig][col-1] == '.'){
        /// Vai a sx
        for(ll i=col-1; i>=minC; i--){
            if(grid[rig][i] == '#') break;
            else if(grid[rig][i] == '.'){
                grid[rig][i] = '|';
                if(grid[rig+1][i] == '.'){ solve(rig, i, ++nChiamate); break; }
                else if(grid[rig+1][i] == '|') break;
            }
        }
    }

    if(grid[rig][col+1] == '.'){
        /// Vai a dx
        for(ll i=col+1; i<maxC; i++){
            //cout << rig << " " << i << "\n";
            if(grid[rig][i] == '#'){ break; }
            else if(grid[rig][i] == '.'){
                grid[rig][i] = '|';
                if(grid[rig+1][i] == '.'){ solve(rig, i, ++nChiamate); break; }
                else if(grid[rig+1][i] == '|') break;
            }
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char c, d;
    ll v1, v2, v3; minC = INT_MAX, minR = INT_MAX;

    memset(grid, '.', sizeof grid);
    grid[0][500] = '+';

    while(cin >> d >> c >> v1 >> c >> c >> c >> v2 >> c >> c >> v3){
        /// x -> colonna, y -> riga
        if(d == 'x'){
            maxC = max(maxC, v1); minC = min(minC, v1);
            maxR = max(maxR, v3); minR = min(minR, v2);
            for(ll r = v2; r <= v3; r++) grid[r][v1] = '#';
        }else{
            maxR = max(maxR, v1); minR = min(minR, v1);
            maxC = max(maxC, v3); minC = min(minC, v2);
            for(ll c = v2; c <= v3; c++) grid[v1][c] = '#';
        }
    }

    maxC+=2; maxR++;

    //cout << isBetweenClay( {19, 500} );


    solve(0, 500, ++nChiamate);

    stampa();

    ll dry = 0, rest = 0;
    for(ll i=minR; i<maxR; i++){
        for(ll j=minC; j<maxC; j++) if(grid[i][j] == '|') dry++; else if(grid[i][j] == '~') rest++;
    }

    cout << "\n"; cout << "res part1: " << dry+rest << "\nres part2: " << rest;

    return 0;
}
