#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define F first
#define S second
#define MAXN 100

string s[MAXN]; ll RR, CC;

void stampa(){
    for(ll i=0; i<RR; i++){
        for(ll j=0; j<CC; j++) cout << s[i][j];
        cout << "\n";
    }
    cout << "\n";
}

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

    void to_string(){
        cout << tipo << ": " << r << " " << c << " vita: " << vita << "\n";
    }
};

vector<player> p;

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

    p = tmp;
}

ll indexPlayerAt(ll r, ll c){
    for(ll i=0; i<p.size(); i++) if(p[i].r == r && p[i].c == c) return i;
}

int E, G;

/*bool eliminato(player z){
    for(player & x : daEliminare) if(x.r == z.r && x.c == c && x.tipo == z.tipo && x) return true;
    else return false;
}*/

void attacca(player & att){
    char avv = (att.tipo == 'E') ? 'G' : 'E';
    ll best = LLONG_MAX; ll indVitt;

    for(ll i=0; i<4; i++){
        ll rN = att.r + spost[i].F, cN = att.c + spost[i].S;
        if(s[rN][cN] == avv){
            ll ind = indexPlayerAt(rN, cN);
            if(p[ind].vita < best){
                best = p[ind].vita;
                indVitt = ind;
            }
        }
    }

    p[indVitt].vita -= 3;

    if(p[indVitt].vita <= 0){
        s[p[indVitt].r][p[indVitt].c] = '.';
        (p[indVitt].tipo == 'E') ? E-- : G--;
    }
}

/*bool isThereTarget(){
    ll E = 0, G = 0;
    for(player & x : p){
        (x.tipo == 'E') ? E++ : G++;
    }
    return (E != 0 && G != 0);
}*/

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while(cin >> s[RR]) RR++;

    CC = ll(s[0].size());
    //for(ll i=0; i<N; i++) cout << s[i] << "\n";

    for(ll i=0; i<RR; i++){
        for(ll j=0; j<s[i].size(); j++){
            if(s[i][j] != '.' && s[i][j] != '#'){
                p.push_back({ s[i][j], i, j });
                (s[i][j] == 'E') ? E++ : G++;
            }
        }
    }

    //for(player & x : p) x.to_string();
    /*pii res = nextSquare(p[0]);
    cout << res.F << " " << res.S;*/

    ll nRounds = 0;
    ll V = 2;
    //stampa();
    bool noTarget = false;
    //while(V--){
    while(E != 0 && G != 0){
        for(player & x : p){
            if(x.vita <= 0) continue;

            char avv = (x.tipo == 'E') ? 'G' : 'E';

            if(isNear(avv, x.r, x.c))
                attacca(x);
            else{
                muovi(x);
                if(isNear(avv, x.r, x.c)) attacca(x);
            }
            if(G == 0 || E == 0 && (x.r != p[p.size()-1].r || x.c != p[p.size()-1].c)){ noTarget = true; break; }
        }
        //stampa();
        erase_players();
        sort(p.begin(), p.end());
        if(!noTarget)nRounds++;
    }

    //cout << "nRounds: " << nRounds << "\n\n"; for(player & x : p) x.to_string(); stampa(); cout << "\n";
    ll vitaRestante = 0;
    for(player & x : p) vitaRestante += x.vita;
    ll res = vitaRestante * nRounds;
    cout << res;

    return 0;
}

