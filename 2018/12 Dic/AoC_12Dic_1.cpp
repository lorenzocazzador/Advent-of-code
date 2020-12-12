#include <bits/stdc++.h>
using namespace std;

#define dbg_var(x) cout << #x << ": " << x << "\n";

unordered_map<string, char> m;
typedef long long ll;

/*string riduci(string s){
    ll i=0;
    while(s[i] == '.') i++;
    s = s.substr(i, s.size()-i);

    i = s.size() - 1;
    while(s[i] == '.') i--;
    s = s.substr(0, i+1);

    return s;
}*/

ll calcola(string s, ll first){
    ll res = 0;
    for(ll i=0; i<s.size(); i++) if(s[i] == '#') res += i - first;
    return res;
}

ll calcola2(ll ris124, ll x){
    return ris124 + (x - 124) * 88;
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string s, k, tmp; char v;
    cin >> s >> s >> s;

    s = "..." + s + "...";
    ll first = 3;

    while(cin >> k >> tmp >> v){
        m[k] = v;
    }

    ll ris, risPrec, delta, res124;
    for(ll g=0; g<126; g++){
        ris = calcola(s, first);
        if(g == 124) res124 = ris;
        if(g > 124){ delta = ris - risPrec; }//cout << g << ": " << delta << "\n"; }
        risPrec = ris;
        string actual = "";
        for(ll i=0; i<s.size(); i++){
            actual += s[i];
            if(i >= 4){
                ll middle = i-2;
                s[middle] = (m.count(actual) > 0)? m[actual] : '.';
                actual = actual.substr(1,4);
            }
        }
        for(ll k=s.size()-4; k<s.size(); k++) if(s[k] != '.') s += '.';
        for(ll k=0; k<4; k++) if(s[k] != '.'){ s = '.' + s; first++; }
    }

    ll res = 0;
    //for(ll i=0; i<s.size(); i++) if(s[i] == '#') res += i - first;

    //for(int i=125; i<=150; i++) cout << i << ": " << calcola2(res124, i) << "\n";
    ll querie = 50000000000;
    cout << "res: " << calcola2(res124, querie);
    //cout << "Rres: " << res << "\n" << s << "\nsize: " << s.size();
    //cout << riduci(s);
    return 0;
}
