#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define F first
#define S second
#define MAXN 200
#define dbg_var(x) cout << #x << ": " << x << " ";

struct cart{
    /// 0 = left, 1 = up/straight, 2 = right, 3 = down
    int col, rig, dirTurn, dir;

    void to_string(){
        dbg_var(col); dbg_var(rig); dbg_var(dirTurn); dbg_var(dir); cout << "\n";
    }

    bool operator < (const cart & x) const{
        if(rig != x.rig) return rig < x.rig;
        else return col < x.col;
    }
};

list<cart> c;

int isCart(char c){
    if(c == '<') return 0;
    if(c == '^') return 1;
    if(c == '>') return 2;
    if(c == 'v') return 3;
    else return -1;
}

bool thereIsCart[MAXN][MAXN];

char path(char c){
    if(c == '<' || c == '>') return '-';
    else return '|';
}

pii cord(int dir){
    if(dir == 0) return { 0, -1};
    if(dir == 1) return { -1, 0};
    if(dir == 2) return { 0, 1};
    else return { 1, 0};
}

int curva(cart & x, char cv){
    int dir = x.dir;
    if(dir == 1) return x.dir = (cv == '/') ? 2 : 0;
    if(dir == 2) return x.dir = (cv == '/') ? 1 : 3;
    if(dir == 3) return x.dir = (cv == '/') ? 0 : 2;
    else return x.dir = (cv == '/') ? 3 : 1;
}

int turn(cart & c1){
    /// 0 = left, 1 = up/straight, 2 = right, 3 = down
    int dir = c1.dir, dirTurn = c1.dirTurn;
    assert(dir >= 0 && dir < 4 && dirTurn >=0 && dirTurn<3);
    int dirs[4][3] = {
        {3, 0, 1}, //left
        {0, 1, 2}, //up
        {1, 2, 3}, //right
        {2, 3, 0}  // down
    };
    c1.dir = dirs[dir][dirTurn]; c1.dirTurn = (dirTurn+1) % 3;
    return dirs[dir][dirTurn];
}

int N, maxX;

char dir_to_char(int dir){
    if(dir == 0) return '<';
    if(dir == 1) return '^';
    if(dir == 2) return '>';
    else return 'v';
}

void stampa(string s[]){
    string z[N];
    for(int i=0; i<N; i++) z[i] = s[i];
    for(cart & x : c){
        z[x.rig][x.col] = dir_to_char(x.dir);
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<int(s[i].size()); j++) cout << z[i][j];
        cout << "\n";
    }
    cout << "\n";
}

void eraseCard(vector<pii> v){
    //cout << "chiamo con: " << col << " " << rig << "\n\n";
    list<cart> c1;
    //cout << "cart:\n";
    //for(cart & x : c) cout << x.col << " " << x.rig <<  "\n"; cout << "\n";
    cout << "size iniziale: " << c.size() << "\n";
    cout << "da eliminare:\n";
    for(pii & x : v)cout << x.F << " " << x.S << "\n";
    cout << "\n";
    for(cart & x : c){
        //if(x.col != col || x.rig != rig) c1.push_back(x);
        int c = x.col, r = x.rig;
        bool trovato = false;
        for(pii & p : v) if(p.F == c && p.S == r){ trovato = true; break; }
        if(!trovato) c1.push_back(x);
    }
    c = c1;
    for(cart & x : c) cout << x.col << " " << x.rig <<  "\n";
    cout << "\n";
    cout << "size finale: " << c.size() << "\n";
}

bool contiene(int col, int rig, vector<pii> eliminare){
    for(pii & x : eliminare){
        if(x.F == col && x.S == rig)return true;
    }
    return false;
}

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out2.txt", "w", stdout);

    string s[MAXN];

    while(getline(cin, s[N])){
        for(int i=0; i<int(s[N].size()); i++){
            if(isCart(s[N][i]) != -1){
                c.push_back({ i, N, 0, isCart(s[N][i])});
                s[N][i] = path(s[N][i]);
                thereIsCart[N][i] = true;
            }
        }
        maxX = max(maxX, int(s[N].size()));
        N++;
    }
    c.sort();
    //for(cart & x : c) cout << x.col << " " << x.rig <<  "\n"; cout << "\n";
    while(true){
        //stampa(s);
        //cout << v++ << "\n";
        vector<pii> eliminare;
        for(cart & x : c){
            //cout << x.col << " " << x.rig <<  "\n";
            if(contiene(x.col, x.rig, eliminare))continue;
            int dirMove = (s[x.rig][x.col] == '+') ? turn(x) : (s[x.rig][x.col] == '|' || s[x.rig][x.col] == '-') ? x.dir : curva(x, s[x.rig][x.col]);
            pii p = cord(dirMove);
            thereIsCart[x.rig][x.col] = false;
            x.rig += p.F; x.col += p.S;
            if(thereIsCart[x.rig][x.col]){
                thereIsCart[x.rig][x.col] = false;
                eliminare.push_back({x.col, x.rig});
                //eraseCard(x.col, x.rig);
            }else thereIsCart[x.rig][x.col] = true;
        }
        //cout << "\n\n";
        if(!eliminare.empty()){ eraseCard(eliminare); } //cerr << c.size() << "\n"; }
        if(c.size() == 1){
            //stampa(s);
            for(cart & x : c)cout << x.col << "," << x.rig;
            return 0;
        }
        if(c.size() == 0){ cout << "size: 0"; return 0;}
        c.sort();
    }

    return 0;
}
