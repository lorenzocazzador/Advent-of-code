#include <bits/stdc++.h>
using namespace std;

#define MAXN
long long res, tree[1000000], N;

int calcola(int a){
    int nChild = tree[a], nData = tree[++a];
    a++;
    for(int i=0; i<nChild; i++){
        a = calcola(a);
    }
    for(int i=0; i<nData; i++){
        res += tree[a++];
    }
    return a;
}

int main(){
    freopen("input.txt", "r", stdin);

    int i=0;
    while(cin >> tree[i]){ i++; }
    //i--;

    //for(int j=0; j<i; j++)cout << tree[j] << " "; cout << "\n";
    N = i;
    calcola(0);
    cout << "\nres: " << res;

    return 0;
}
