#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out1.txt", "w", stdout);

    string s;
    cin >> s;
    bool actionPerformed = true;
    while(actionPerformed){
        actionPerformed = false;
        for(int i=0; i<(int)s.size()-1; i++){
            if(abs(s[i]-s[i+1]) == abs('a'-'A')){
                s.erase(i, 2);
                actionPerformed = true;
            }
        }
    }
    cout << s.size();
    return 0;
}
