#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("input/in.txt","r",stdin);
    freopen("output/out1.txt", "w",stdout);

    int n, res = 0;
    while(cin >> n){ res += n; }

    cout << res;

    return 0;
}
