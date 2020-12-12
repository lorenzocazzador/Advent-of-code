#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("input/in.txt","r",stdin);
    freopen("output/out2.txt", "w",stdout);

    int n, res = 0, i = 0, M = 0;
    set<int> s; vector<int> v (2000);
    s.insert(res);
    while(cin >> n){
        res += n; M++;
        v[i++] = n;
        if(!s.count(res))s.insert(res);
        else{
            cout << res;
            return 0;
        }
    }
    i = 0;
    while(true){
        res += v[i++];
        if(i > M) i = 0;
        if(s.count(res)){
            cout << res;
            return 0;
        }
    }
    return 0;
}
