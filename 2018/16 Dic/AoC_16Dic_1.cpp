#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

void dbg_arr(int a[], int N){
    for(int i=0; i<N; i++) cout << a[i] << " "; cout << "\n";
}

void print_vi( vi v){
    for(int & x : v) cout << x << " "; cout << "\n";
}

int bef[4], istr[4], aft[4];
#define A istr[1]
#define B istr[2]
#define C istr[3]

bool addr(){ return aft[C] == (bef[A] + bef[B]); }

bool addi(){ return aft[C] == (bef[A] + B); }

bool mulr(){ return aft[C] == (bef[A] * bef[B]); }

bool muli(){ return aft[C] == (bef[A] * B); }

bool banr(){ return aft[C] == (bef[A] & bef[B]); }

bool bani(){ return aft[C] == (bef[A] & B); }

bool borr(){ return aft[C] == (bef[A] | bef[B]); }

bool bori(){ return aft[C] == (bef[A] | B); }

bool setr(){ return aft[C] == bef[A]; }

bool seti(){ return aft[C] == A; }

bool gtir(){ return aft[C] == ((A > bef[B]) ? 1 : 0); }

bool gtri(){ return aft[C] == ((bef[A] > B) ? 1 : 0); }

bool gtrr(){ return aft[C] == ((bef[A] > bef[B]) ? 1 : 0); }

bool eqir(){ return aft[C] == ((A == bef[B]) ? 1 : 0); }

bool eqri(){ return aft[C] == ((bef[A] == B) ? 1 : 0); }

bool eqrr(){ return aft[C] == ((bef[A] == bef[B]) ? 1 : 0); }

vi common_subset(vi v1, vi v2){
    int freq[16]; memset(freq, 0, sizeof freq);
    //dbg_arr(freq, 16);
    for(int i=0; i< max(v1.size(), v2.size()); i++){
        if(i < v1.size()) freq[v1[i]]++;
        if(i < v2.size()) freq[v2[i]]++;
    }

    vi res;
    for(int i=0; i<16; i++){
        assert(freq[i] <= 2);
        if(freq[i] == 2) res.push_back(i);
    }
    return res;
}

typedef bool (*funzione) ();

vi fromOpcodeToOperation[16];

int contOpcode(){
    funzione opcodes[] = { addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };
    int cont = 0, nOp = istr[0];

    vi v;
    for(int i=0; i<16; i++) if(opcodes[i]()){ cont++; v.push_back(i); }

    fromOpcodeToOperation[nOp] = (fromOpcodeToOperation[nOp].empty()) ? v : common_subset(fromOpcodeToOperation[nOp], v);

    return cont;
}

void erase_vi(vi & v, int value){
    vi tmp;
    for(int & x : v){
        if(x != value) tmp.push_back(x);
    }
    v = tmp;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string s; char c; int res = 0;

    while(cin >> s >> c){
        for(int i=0; i<4; i++) cin >> bef[i] >> c;
        for(int i=0; i<4; i++) cin >> istr[i];
        cin >> s >> c;
        for(int i=0; i<4; i++) cin >> aft[i] >> c;

        /*dbg_arr(bef); dbg_arr(istr); dbg_arr(aft);
        cout << "\n";*/

        if(contOpcode() >= 3) res++;

    }

    //for(int i=0; i<16; i++){ cout << i << ": "; print_vi(fromOpcodeToOperation[i]); } cout << "\n";

    queue<int> daProcess;
    for(int i=0; i<16; i++) if(fromOpcodeToOperation[i].size() == 1) daProcess.push(fromOpcodeToOperation[i][0]);

    //cout << daProcess.front();
    while(!daProcess.empty()){
        int daElim = daProcess.front(); daProcess.pop();

        for(int i=0; i<16; i++){
            if(fromOpcodeToOperation[i].size() != 1){
                erase_vi(fromOpcodeToOperation[i], daElim);
                if(fromOpcodeToOperation[i].size() == 1) daProcess.push(fromOpcodeToOperation[i][0]);
            }
        }

    }

    for(int i=0; i<16; i++){ cout << i << ": "; print_vi(fromOpcodeToOperation[i]); }
}
