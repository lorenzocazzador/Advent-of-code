#include <bits/stdc++.h>
using namespace std;
#define dbg(x) cout << #x << ": " << x << "\n";

typedef long long ll;
typedef pair<int, int> pii;

ll find_substr(string s, string sub){
    ll j=0;
    for(ll i=0; i<s.size(); i++){
        if(j == sub.size()) return (i-ll(sub.size()));
        //59414cout << i << " " << j << "\n";
        if(s[i] == sub[j])j++;
        else if(s[i] == sub[0]) j = 1;
        else j=0;
    }
    //dbg(j);
    return (j == sub.size()) ? (ll(s.size())-ll(sub.size())) : -1;
}

int main(){
    //freopen("output.txt", "w", stdout);
    string N = "765071";
    //cout << find_substr("3710101245","01245");
    //cin >> N;

    string s = "37", last = "";
    ll posE1 = 0, posE2 = 1;

    /*ll V = 1000;
    set<pii> posElf;*/

    while(true){
        //cout << s << "\n";

        /*pii p = {posE1, posE2};
        if(posElf.count(p)) cout << "eccolo: " <<  "\n";
        else posElf.insert(p);*/

        ll somma = (s[posE1]-'0') + (s[posE2]-'0');
        s += to_string(somma);
        last += to_string(somma);
        int res = find_substr(last, N);
        if(res != -1){cout << s.size() - last.size() + res; return 0; }
        if(last.size() > N.size()) last = last.substr(ll(last.size())-ll(N.size()), N.size());
        posE1 = (posE1 + (s[posE1]-'0') + 1) % s.size();
        posE2 = (posE2 + (s[posE2]-'0') + 1) % s.size();
    }

    //cout << s;
    return 0;
}
