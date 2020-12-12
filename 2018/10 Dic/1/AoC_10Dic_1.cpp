#include <bits/stdc++.h>
using namespace std;

#define dbg_var(x) cout << #x << ": " << x << " ";

struct punto{
    int x, y, xV, yV;

    void aggiorna(){
        x += xV;
        y += yV;
    }

    bool operator < (const punto & p) const{
        if(y != p.y) return y < p.y;
        else return x < p.x;
    }
};

int minX, maxX, minY, maxY;
vector<punto> p;

void stampa(){
    int nC = abs(minX)+abs(maxX)+1, nR = abs(minY)+abs(maxY)+1;

    //dbg_var(minX);  dbg_var(maxX);  dbg_var(minY);  dbg_var(maxY); cout << "\n";
    //dbg_var(nR); dbg_var(nC); cout << "\n";

    int i = minY, j = minX, precX = INT_MAX, precY = INT_MAX;
    for(punto pto : p){
        if(pto.x == precX && pto.y == precY)continue;
        while(i != pto.y ){
            for(int z = j; z < maxX+1; z++) cout << ".";
            i++;
            cout << "\n";
            j = minX;
        }
        while(j != pto.x ){ cout << "."; j++; }
        cout << "#"; j++;
        precX = pto.x; precY = pto.y;
    }
    cout << "\n";
}

void aggiorna(){
    minX = INT_MAX; minY = INT_MAX, maxX = INT_MIN; maxY = INT_MIN;
    for(punto & z : p){
        z.aggiorna();
        minX = min(minX, z.x);
        minY = min(minY, z.y);
        maxX = max(maxX, z.x);
        maxY = max(maxY, z.y);
    }
    sort(p.begin(), p.end());
}
///position=< 9,  1> velocity=< 0,  2>

int main(){
    freopen("input1.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string s; char c;
    int x, y, xV, yV; minX = INT_MAX; minY = INT_MAX; maxX = INT_MIN; maxY = INT_MIN;

    while(cin >> s >> x >> c >> y >> c >> s >> xV >> c >> yV >> c){
        //cout << x << " " << y << " " << xV << " " << yV << "\n";
        punto pto = {x, y, xV, yV};
        minX = min(minX, x); maxX = max(maxX, x);
        minY = min(minY, y); maxY = max(maxY, y);
        p.push_back(pto);
    }

    sort(p.begin(), p.end());
    //for(punto pto : p) cout << pto.x << " " << pto.y << "\n";

    //stampa();
    int minDiffX = INT_MAX, minDiffY = INT_MAX;
    for(int i=0; i<100000; i++){
        aggiorna();
        //cout << i+1 << ": "; dbg_var(minX);  dbg_var(maxX);  dbg_var(minY);  dbg_var(maxY); cout << "\n";
        minDiffX = min(minDiffX, (maxX-minX));
        minDiffY = min(minDiffY, (maxY-minY));
        if(minDiffX == 61 && minDiffY == 9){ cout << "seconds: " << i+1 << "\n"; stampa(); break; }
        //stampa();
    }

    //dbg_var(minDiffX); cout << "\n";
    //dbg_var(minDiffY);
    return 0;
}
