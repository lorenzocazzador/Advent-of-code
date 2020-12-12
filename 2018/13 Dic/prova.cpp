#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define F first
#define S second
#define MAXN 200
#define dbg_var(x) cout << #x << ": " << x << " ";
string s[MAXN];

struct cart{
    /// 0 = left, 1 = up/straight, 2 = right, 3 = down
    int col, rig, dirTurn, dir;

    void to_string(){
        dbg_var(col); dbg_var(rig); dbg_var(dirTurn); dbg_var(dir); cout << "\n";
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
    if(dir == 3) return { 0, 1};
    else return { 1, 0};
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

int main(){
    freopen("input1.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int N = 0, maxX = 0;

    while(getline(cin, s[N])){ N++; }
    for(int i=0; i<N; i++)cout << s[i] << "\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<int(s[i].size()); j++){
            if(isCart(s[i][j]) != -1){
                c.push_back({ j, i, 0, isCart(s[i][j])});
                //s[N][i] = path(s[N][i]);
                //thereIsCart[N][i] = true;
            }
        }
    }
    //for(int i=0; i<N; i++)cout << s[i] << "\n";
    //for(cart & x : c) x.to_string();

    int C = 10;
    while(C--){
        for(int i=0; i<N; i++){
            for(int j=0; j<maxX; j++) cout << thereIsCart[i][j] << " "; cout << "\n";
        }
        cout << "\n";
        for(cart & x : c){
            int dirMove = (s[x.rig][x.col] == '+') ? turn(x) : x.dir;
            pii p = cord(dirMove);
            thereIsCart[x.rig][x.col] = false;
            x.rig += p.F; x.col += p.S;
            if(thereIsCart[x.rig][x.col]){ cout << x.rig << "," << x.col; break; }
            else thereIsCart[x.rig][x.col] = true;
        }

    }
    return 0;
}
