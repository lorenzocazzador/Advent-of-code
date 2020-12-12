#include <bits/stdc++.h>
using namespace std;

#define MAXN
long long tree[1000000];

typedef pair<int, int> pii;
#define F first
#define S second

pii calcola(int a){
    int nChild = tree[a], nData = tree[++a], res = 0;
    a++;
    vector<int> valueChild (nChild);
    pii res_tmp = { a, 0 };
    for(int i=0; i<nChild; i++){
        res_tmp = calcola(res_tmp.F);
        valueChild[i] = res_tmp.S;
    }
    a = res_tmp.F;
    for(int i=0; i<nData; i++){
        int t = tree[a++];
        if(nChild == 0)res += t;
        else if(t <= nChild && t > 0) res += valueChild[t-1];
    }
    return { a, res };
}

int main(){
    freopen("input.txt", "r", stdin);

    int i=0;
    while(cin >> tree[i]){ i++; }

    //for(int j=0; j<i; j++)cout << tree[j] << " "; cout << "\n";

    cout << "res: " << calcola(0).S;

    return 0;
}
