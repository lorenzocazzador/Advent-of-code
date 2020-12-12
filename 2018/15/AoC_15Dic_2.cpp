#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define F first
#define S second
#define MAXN 100

string s[MAXN], initial[MAXN]; ll RR, CC;

struct player{
    char tipo;
    ll r, c, vita = 200;

    void muovi(pii p){
        s[r][c] = '.';
        r = p.F;
        c = p.S;
        s[r][c] = tipo;
    }

    bool operator < (const player & a) const{
        if(r != a.r) return r < a.r;
        else return c < a.c;
    }

    bool operator == (const player & a) const{
        return tipo == a.tipo && r == a.r && c == a.c && vita == a.vita;
     }

    void to_string(){
        cout << tipo << ": " << r << " " << c << " vita: " << vita << "\n";
    }
};

vector<player> p;

void stampa(){
    int z=0;
    for(ll i=0; i<RR; i++){
        for(ll j=0; j<CC; j++) cout << s[i][j];
        if(p[z].r == i && z < p.size()) cout << "   ";
        while(p[z].r == i && z<p.size()){ cout << p[z].tipo << "(" << p[z].vita << ")"; if(++z<p.size() && p[z].r == i ) cout << ", "; }
        cout << "\n";
    }
    cout << "\n";
}

pii spost[4] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

bool inside(ll r, ll c){
    return (r >= 0 && r < RR && c >= 0 && c < CC);
}

bool isBefore(ll r1, ll c1, ll r2, ll c2){
    if(r1 == r2) return c1 < c2;
    else return r1 < r2;
}

bool isNear(char avv, ll r, ll c){
    for(ll i=0; i<4; i++){
        if(s[r+spost[i].F][c+spost[i].S] == avv) return true;
    }
    return false;
}

void muovi(player & a){
    char avv = (a.tipo == 'E') ? 'G' : 'E';
    ll distance[RR][CC], bestDistance = LLONG_MAX; pii obb {LLONG_MAX, LLONG_MAX};
    memset(distance, -1, sizeof distance);
    distance[a.r][a.c] = 0;
    queue<pii> q; q.push( {a.r, a.c} );

    while(!q.empty()){
        ll rA = q.front().F, cA = q.front().S; q.pop();

        for(ll i=0; i<4; i++){
            ll rN = rA + spost[i].F, cN = cA + spost[i].S;
            if(inside(rN, cN) && s[rN][cN] == '.' && distance[rN][cN] == -1){
                distance[rN][cN] = distance[rA][cA] + 1;
                if(isNear(avv, rN, cN) && distance[rN][cN] <= bestDistance && isBefore(rN, cN, obb.F, obb.S)){
                    bestDistance = distance[rN][cN];
                    obb = { rN, cN };
                }
                q.push( {rN, cN} );
            }
        }
    }
    /*for(ll i=0; i<RR; i++){
        for(ll j=0; j<CC; j++)if(distance[i][j] == -1) cout << '*'; else cout << distance[i][j];
        cout << "\n";
    }*/
    if(obb.F == LLONG_MAX && obb.S == LLONG_MAX) return;
    memset(distance, -1, sizeof distance);
    distance[obb.F][obb.S] = 0;
    q.push( {obb.F, obb.S} );

    while(!q.empty()){
        ll rA = q.front().F, cA = q.front().S; q.pop();

        for(ll i=0; i<4; i++){
            ll rN = rA + spost[i].F, cN = cA + spost[i].S;
            if(inside(rN, cN) && s[rN][cN] == '.' && distance[rN][cN] == -1){
                distance[rN][cN] = distance[rA][cA] + 1;
                q.push( {rN, cN} );
            }
        }
    }

    ll best = LLONG_MAX; pii res;
    for(ll i=0; i<4; i++){
        ll rN = a.r + spost[i].F, cN = a.c + spost[i].S;
        if(inside(rN, cN) && distance[rN][cN] < best && s[rN][cN] == '.' && distance[rN][cN] != -1){
            best = distance[rN][cN];
            res = { rN, cN };
        }
    }

    a.muovi(res);
}

void erase_players(){
    vector<player> tmp;
    for(player & x : p) if(x.vita > 0) tmp.push_back(x);

    p.clear();
    p = tmp;
}

ll indexPlayerAt(ll r, ll c){
    for(ll i=0; i<p.size(); i++) if(p[i].r == r && p[i].c == c) return i;
}

int E, G, attElves;

void attacca(player & att){
    char avv = (att.tipo == 'E') ? 'G' : 'E';
    ll best = LLONG_MAX; ll indVitt;

    for(ll i=0; i<4; i++){
        ll rN = att.r + spost[i].F, cN = att.c + spost[i].S;
        if(s[rN][cN] == avv){
            ll ind = indexPlayerAt(rN, cN);
            if(p[ind].vita < best && p[ind].vita > 0){
                best = p[ind].vita;
                indVitt = ind;
            }
        }
    }

    p[indVitt].vita -= (att.tipo == 'E') ? attElves : 3;

    if(p[indVitt].vita <= 0){
        s[p[indVitt].r][p[indVitt].c] = '.';
        (p[indVitt].tipo == 'E') ? E-- : G--;
    }
}

ll res;

bool simula(){

    for(int i=0; i<RR; i++) s[i] = initial[i];

    p.clear(); E = 0; G = 0;
    for(ll i=0; i<RR; i++){
        for(ll j=0; j<CC; j++){
            if(s[i][j] != '.' && s[i][j] != '#'){
                p.push_back({ s[i][j], i, j });
                (s[i][j] == 'E') ? E++ : G++;
            }
        }
    }

    ll nRounds = 0; bool noTarget = false;
    int startE = E;
    //int V = 25;
    //while(V--){
    while(E != 0 && G != 0){
        //cout << nRounds << " " << p.size() << " nElfi: " << E << " nGoblin: " << G << "\n"; stampa(); cout << "\n";
        for(player & x : p){
            if(x.vita <= 0) continue;

            char avv = (x.tipo == 'E') ? 'G' : 'E';

            if(isNear(avv, x.r, x.c))
                attacca(x);
            else{
                muovi(x);
                if(isNear(avv, x.r, x.c)) attacca(x);
            }
            if((G == 0 || E == 0) && !(x == p[p.size()-1])){ noTarget = true; break; }
        }
        erase_players();
        sort(p.begin(), p.end());
        if(!noTarget)nRounds++;
    }

    //cout << nRounds << " " << p.size() << " nElfi: " << E << " nGoblin: " << G << "\n"; stampa(); cout << "\n";

    ll vitaRestante = 0;
    for(player & x : p) vitaRestante += x.vita;
    res = vitaRestante * nRounds;

    return (E == startE && G==0);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while(cin >> initial[RR]) RR++;
    CC = ll(initial[0].size());

    attElves = 4;
    while(!simula()) attElves++;
    cout << "attElves: " << attElves << "\n";
    cout << res << "\n";

    return 0;
}

