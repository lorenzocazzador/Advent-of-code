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

bool addr(bool Part1){ return (Part1) ? (aft[C] == (bef[A] + bef[B])) : (aft[C] = (bef[A] + bef[B])); }

bool addi(bool Part1){ return (Part1) ? (aft[C] == (bef[A] + B)) : (aft[C] = (bef[A] + B)); }

bool mulr(bool Part1){ return (Part1) ? (aft[C] == (bef[A] * bef[B])) : (aft[C] = (bef[A] * bef[B])); }

bool muli(bool Part1){ return (Part1) ? (aft[C] == (bef[A] * B)) : (aft[C] = (bef[A] * B)); }

bool banr(bool Part1){ return (Part1) ? (aft[C] == (bef[A] & bef[B])) : (aft[C] = (bef[A] & bef[B])); }

bool bani(bool Part1){ return (Part1) ? (aft[C] == (bef[A] & B)) : (aft[C] = (bef[A] & B)); }

bool borr(bool Part1){ return (Part1) ? (aft[C] == (bef[A] | bef[B])) : (aft[C] = (bef[A] | bef[B])); }

bool bori(bool Part1){ return (Part1) ? (aft[C] == (bef[A] | B)) : (aft[C] = (bef[A] | B)); }

bool setr(bool Part1){ return (Part1) ? (aft[C] == bef[A]) : (aft[C] = bef[A]); }

bool seti(bool Part1){ return (Part1) ? (aft[C] == A) : (aft[C] = A); }

bool gtir(bool Part1){ return (Part1) ? (aft[C] == ((A > bef[B]) ? 1 : 0)) : (aft[C] = ((A > bef[B]) ? 1 : 0)); }

bool gtri(bool Part1){ return (Part1) ? (aft[C] == ((bef[A] > B) ? 1 : 0)) : (aft[C] = ((bef[A] > B) ? 1 : 0)); }

bool gtrr(bool Part1){ return (Part1) ? (aft[C] == ((bef[A] > bef[B]) ? 1 : 0)) : (aft[C] = ((bef[A] > bef[B]) ? 1 : 0)); }

bool eqir(bool Part1){ return (Part1) ? (aft[C] == ((A == bef[B]) ? 1 : 0)) : (aft[C] = ((A == bef[B]) ? 1 : 0)); }

bool eqri(bool Part1){ return (Part1) ? (aft[C] == ((bef[A] == B) ? 1 : 0)) : (aft[C] = ((bef[A] == B) ? 1 : 0)); }

bool eqrr(bool Part1){ return (Part1) ? (aft[C] == ((bef[A] == bef[B]) ? 1 : 0)) : (aft[C] = ((bef[A] == bef[B]) ? 1 : 0)); }

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

typedef bool (*funzione) (bool Part1);
funzione opcodes[] = { addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };

vi fromOpcodeToOperation[16];

void contOpcode(){
    int nOp = istr[0];

    vi v;
    for(int i=0; i<16; i++) if(opcodes[i](true)) v.push_back(i);

    fromOpcodeToOperation[nOp] = (fromOpcodeToOperation[nOp].empty()) ? v : common_subset(fromOpcodeToOperation[nOp], v);
}

void erase_vi(vi & v, int value){
    vi tmp;
    for(int & x : v){
        if(x != value) tmp.push_back(x);
    }
    v = tmp;
}

int main(){
    freopen("input/in.txt", "r", stdin);
    freopen("output/out2.txt", "w", stdout);

    string s; char c;

    int N_RIGHE = 773;
    while(N_RIGHE--){
        cin >> s >> c;
        for(int i=0; i<4; i++) cin >> bef[i] >> c;
        for(int i=0; i<4; i++) cin >> istr[i];
        cin >> s >> c;
        for(int i=0; i<4; i++) cin >> aft[i] >> c;

        /*dbg_arr(bef); dbg_arr(istr); dbg_arr(aft);
        cout << "\n";*/

        contOpcode();

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

    //for(int i=0; i<16; i++){ cout << i << ": "; print_vi(fromOpcodeToOperation[i]); }

    for(int i=0; i<4; i++) bef[i] = aft[i] = 0;

    while(cin >> istr[0] >> istr[1] >> istr[2] >> istr[3]){
        int opc = fromOpcodeToOperation[istr[0]][0];
        opcodes[opc](false);
        for(int i=0; i<4; i++) bef[i] = aft[i];
        //dbg_arr(aft, 4);
    }

    cout << aft[0];
}
