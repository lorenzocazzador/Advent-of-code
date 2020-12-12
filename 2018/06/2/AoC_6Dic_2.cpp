#include <bits/stdc++.h>
using namespace std;

#define MAXN 100
#define MAX_SUM 10000
#define F first
#define S second
typedef pair<int, int> pii;

pii p[MAXN];
bool isInfinitive[MAXN];
int occ[MAXN];

int calcolaDist(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

int main(){
    freopen("input.txt", "r", stdin);

    int N = 0, maxR = 0, maxC = 0; char c;
    while(cin >> p[N].F >> c >> p[N].S){
        maxC = max(maxC, p[N].F+1);
        maxR = max(maxR, p[N].S+1);
        N++;
    }
    int grid[maxR][maxC];
    for(int i=0; i<N; i++) grid[p[i].S][p[i].F] = i;

    int res = 0;

    for(int i=0; i<maxR; i++){
        for(int j=0; j<maxC; j++){
            grid[i][j] = 0;
            int dist = INT_MAX;
            for(int x=0; x<N; x++){
                int dist_tmp = calcolaDist(i, j, p[x].S, p[x].F);
                grid[i][j] += dist_tmp;
            }
            if(grid[i][j] < MAX_SUM) res++;
            //if((i==0 || j==0 || i==maxR-1 || j==maxC-1) && grid[i][j] >= 0){ isInfinitive[grid[i][j]] = true; }
        }
    }

    /*for(int i=0; i<maxR; i++){
        for(int j=0; j<maxC; j++) if(grid[i][j] != -1) cout << grid[i][j]; else cout << ".";
        cout << "\n";
    }*/

    cout << res;

    return 0;
}
