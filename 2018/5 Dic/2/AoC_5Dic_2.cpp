#include <bits/stdc++.h>
using namespace std;

int reazione(string s){
    bool actionPerformed = true;
    while(actionPerformed){
        actionPerformed = false;
        for(int i=0; i<s.size()-1; i++){
            if(abs(s[i]-s[i+1]) == abs('a'-'A')){
                s.erase(i, 2);
                actionPerformed = true;
            }
        }
    }
    return s.size();
}

string rimuovi(string s, char c){
    string res = "";
    char c_upper = c - abs('A' - 'a');
    for(int i=0; i<s.size(); i++){
        if(s[i] != c && s[i] != c_upper) res += s[i];
    }
    return res;
}

int main(){
    freopen("input.txt", "r", stdin);

    string s;
    cin >> s;
    int res = INT_MAX;
    for(int i=0; i<=25; i++){
        string s_mod = rimuovi(s, char('a'+i) );
        //cout << s_mod << "\n";
        int tmp = reazione(s_mod);
        if(tmp < res) res = tmp;
    }
    cout << res;
    return 0;
}
