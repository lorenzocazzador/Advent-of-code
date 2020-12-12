#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void stampa(list<ll> v, auto it){
    for(ll & x : v)
        if( x == *it) cout << "(" << x << ")" << " ";
        else cout << x << " ";
    cout << "\n";
}

#define MAXN 1000
ll score[MAXN];

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out2.txt", "w", stdout);

    ll P, N;
    cin >> P >> N;

    N *= 100;
    list<ll> v;
    v.push_back(0);
    auto current = v.begin();
    ll maxScore = 0, playerAtt = 1;
    //cout << "[-]  "; stampa(v, current);
    for(ll i=1; i<=N; i++){
        if( (i % 23) != 0){
            auto next_current = current;
            advance(next_current, 1);
            if(next_current == v.end()){ next_current = v.begin(); }
            advance(next_current, 1);
            //cout << "i: " << i << "\n";
            current = v.insert(next_current , i);
        }else{
            //cout << "\t";
            score[playerAtt] += i;
            for(ll i=0; i<7; i++){
                if(current == v.begin()){ current = v.end(); current--; }
                else current--;
            }
            score[playerAtt] += *current;
            //cout << "i: " << i << " marble: " << *current << "\n";
            current = v.erase(current);
            if(current == v.end()) current = v.begin();
            maxScore = max(maxScore, score[playerAtt]);
        }
        //cout << "[" << playerAtt << "]  "; stampa(v, current);
        if(++playerAtt > P) playerAtt = 1;
    }

    cout << maxScore;
    return 0;
}
