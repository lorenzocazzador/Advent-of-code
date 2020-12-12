#include <bits/stdc++.h>
using namespace std;

void stampa(vector<int> v){ for(int & x : v) cout << x << " "; cout << "\n"; }

#define MAXN 1000
int score[MAXN];

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out1.txt", "w", stdout);

    int P, N;
    cin >> P >> N;

    vector<int> v;
    v.push_back(0);
    auto current = v.begin();
    int maxScore = 0, playerAtt = 1;
    //cout << "[-]  "; stampa(v);
    for(int i=1; i<=N; i++){
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
            for(int i=0; i<7; i++){
                if(current == v.begin()) current = v.end()-1;
                else current--;
            }
            score[playerAtt] += *current;
            //cout << "i: " << i << " marble: " << *current << "\n";
            current = v.erase(current);
            if(current == v.end()) current = v.begin();
            maxScore = max(maxScore, score[playerAtt]);
        }
        //cout << "[" << playerAtt << "]  "; stampa(v);
        if(++playerAtt > P) playerAtt = 1;
    }

    cout << maxScore;
    return 0;
}
