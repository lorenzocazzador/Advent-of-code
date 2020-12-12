#include <bits/stdc++.h>
using namespace std;

#define MAXN 30
#define W 5
#define TIME 60
vector<char> adj[MAXN];
int canBeFirst[MAXN];
bool visited[MAXN];
int done[MAXN];
int needed[MAXN];
bool isFree[W];

struct step{
    int f, w;
    char L;

    bool operator < (const step & s) const{
        return f > s.f;
    }
};

priority_queue<int, vector<int>, greater<int>> ready;
priority_queue<step> finishTimes;
int current_time;

void assegna(){
    for(int i=0; i<W && !ready.empty(); i++){
        if(isFree[i]){
            isFree[i] = false;
            char l = ready.top() + 'A';
            int f = TIME + ready.top() + current_time;
            ready.pop();
            finishTimes.push({ f, i, l});
        }
    }
}

int finisci(){
    step p = finishTimes.top();
    finishTimes.pop();
    char l = p.L; int t = p.f;
    isFree[p.w] = true;
    for(char x : adj[l-'A']){
        done[x-'A']++;
        if(done[x-'A'] == needed[x-'A'])ready.push(x-'A');
    }
    current_time = t+1;
    assegna();
    return t;
}

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out2.txt", "w", stdout);

    fill(isFree, isFree+W, true);

    string s;
    while(getline(cin, s)){
        char p = s[5], a = s[36];
        adj[p-'A'].push_back(a);
        if(canBeFirst[p-'A'] == 0) canBeFirst[p-'A'] = 1;
        canBeFirst[a-'A'] = -1;
        needed[a-'A']++;
    }

    for(int i=0; i<26; i++) if(canBeFirst[i] == 1) ready.push(i);

    assegna();

    while(!finishTimes.empty()) finisci();

    cout << current_time;
    return 0;
}
