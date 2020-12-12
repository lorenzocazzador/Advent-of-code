#include <bits/stdc++.h>
using namespace std;

#define MAXN 30
vector<char> adj[MAXN];
int canBeFirst[MAXN];
bool visited[MAXN];
int done[MAXN];
int needed[MAXN];

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out1.txt", "w", stdout);

    string s;
    while(getline(cin, s)){
        char p = s[5], a = s[36];
        adj[p-'A'].push_back(a);
        if(canBeFirst[p-'A'] == 0) canBeFirst[p-'A'] = 1;
        canBeFirst[a-'A'] = -1;
        needed[a-'A']++;
    }

    priority_queue<int, vector<int>, greater<int>> ready;
    for(int i=0; i<26; i++) if(canBeFirst[i] == 1) ready.push(i);

    string res = "";
    while(!ready.empty()){
        char c = ready.top()+'A'; ready.pop();
        visited[c-'A'] = true;
        res += c;
        for(char x : adj[c-'A'])
            if(!visited[x-'A']){
                done[x-'A']++;
                if(done[x-'A'] == needed[x-'A'])ready.push(x-'A');
            }

    }
    //cout << char(ready.top()+'A');
    cout << res;
    return 0;
}
