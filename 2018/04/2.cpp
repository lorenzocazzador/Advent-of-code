#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

#define MAXN 10000

struct evento{
    int year, month, day, h, m, id;
    char a; /// B = begin, S=sleep, W=wake

    bool operator <(const evento& o) const{
        if(year != o.year) return year < o.year;
        else if(month != o.month) return month < o.month;
        else if(day != o.day) return day < o.day;
        else if(h != o.h) return h < o.h;
        else return m < o.m;
    }

    void toString(){
        cout << day << "-" << month << "-" << year << " " << h << ":" << m << " ";
        if(id != -1) cout << "#" << id << " ";
        cout << a << "\n";
    }

};

evento e[MAXN];

struct guardia{
    int ore[60];

    int calcolaOreTot(){ int r=0; return accumulate(ore, ore+60, r); }

    pii oraPiuFreq(){
        pii res = { 0 , 0 }; //ripetizioni, ora
        for(int i=0; i<60; i++) if(ore[i] > res.first){ res.first = ore[i]; res.second = i; }
        return res;
    }

    void tostring(){
        for(int i=0; i<60; i++) cout << ore[i];
        cout << "  " << calcolaOreTot() << "\n";
    }

};

guardia g[MAXN];
unordered_set<int> idguardie;

void tostring_guardie(){
    cout << "    ";
    for(int i=0; i<=5; i++) for(int j=0; j<10; j++) cout << i;
    cout << "\n    ";
    for(int i=0; i<=5; i++) for(int j=0; j<10; j++) cout << j;
    cout << "\n#10 "; g[10].tostring();
    cout << "#99 "; g[99].tostring();
}

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out2.txt", "w", stdout);

    char c; string s;
    int year, month, day, h, m, id, i=0, nA;
    while(cin >> c >> year >> c >> month >> c >> day >> h >> c >> m >> c >> s){
        if(s == "falls"){
            cin >> s;
            e[i++] = { year, month, day, h, m, -1, 'S'};
        }
        else if(s == "wakes"){
            cin >> s;
            e[i++] = { year, month, day, h, m, -1, 'W'};
        }
        else if(s == "Guard"){
            cin >> c >> id >> s >> s;
            e[i++] = { year, month, day, h, m, id, 'B'};
        }
    }
    nA = i;
    sort(e, e+nA);
    for(int i=0; i<nA; i++){
        if(e[i].id != -1){ id = e[i].id; idguardie.insert(id); continue; }
        if(e[i].a == 'S'){
            int in = e[i].m, f = e[++i].m;
            for(;in<f; in++){
                //cout << "entro\n";
                g[id].ore[in]++;
            }
        }

    }
    pii res = { 0 , 0 }; // { ripOra, oraRes }
    int guardiaRes = -1;
    for(int x : idguardie){
        pii att = g[x].oraPiuFreq();
        if(att.first > res.first){ res = att; guardiaRes = x; }
    }

    cout << "res: " << res.second * guardiaRes;

    return 0;
}
