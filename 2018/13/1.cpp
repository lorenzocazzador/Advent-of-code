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

vector<cart> c;

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

int main() {
    freopen("input/in.txt", "r", stdin);
    freopen("output/out1.txt", "w", stdout);

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
    sort(c.begin(),c.end());
    //for(int i=0; i<N; i++)cout << s[i] << "\n";
    //for(cart & x : c) x.to_string();
    //cout << "arrivo\n\n";
    while(true) {
        //stampa(s);
        for(cart & x : c) {
            int dirMove = (s[x.rig][x.col] == '+') ? turn(x) : (s[x.rig][x.col] == '|' || s[x.rig][x.col] == '-') ? x.dir : curva(x, s[x.rig][x.col]);
            //dbg_var(dirMove);
            pii p = cord(dirMove);
            //cout << p.F << " " << p.S <<"\n";
            thereIsCart[x.rig][x.col] = false;
            x.rig += p.F; x.col += p.S;
            if(thereIsCart[x.rig][x.col]) { cout << x.col << "," << x.rig; return 0; }
            else thereIsCart[x.rig][x.col] = true;
        }
        sort(c.begin(),c.end());
    }

    //stampa(s);
    return 0;
}
