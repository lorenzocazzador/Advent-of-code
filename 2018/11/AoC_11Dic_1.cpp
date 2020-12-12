#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll serial;

#define dbg_var(x) cout << #x << ": " << x << "\n"

ll power(ll X, ll Y){
    ll id = X + 10;
    ll power = id * Y;
    power += serial;
    power *= id;
    power = (power % 1000) / 100;
    return power-5;
}


ll grid[300][300];

int main(){
    //freopen("input_ex.txt", "r", stdin);

    cin >> serial;

    /*int X, Y;
    while(cin >> X >> Y && (X || Y)) cout << power(X, Y) << "\n";*/

    for(int Y=0; Y<300; Y++){
        for(int X=0; X<300; X++) grid[Y][X] = power(X+1, Y+1);
    }

    /*ll maxSum = INT_MIN;
    int X, Y, S;
    //for(int i=0; i<3; i++) for(int j=0; j<3; j++) maxSum += grid[i][j];

    for(int i=0; i<300; i++){
        for(int j=0; j<300; j++){
            ll actualSum = grid[i][j];
            for(int s=2; s<=300 && (i+s-1)<300 && (j+s-1)<300; s++){
                for(int z=0; z<s; z++) actualSum += grid[i+z][j+s-1];
                for(int k=0; k<s-1; k++) actualSum += grid[i+s-1][j+k];
                if(actualSum > maxSum){
                    maxSum = actualSum;
                    X = j+1; Y = i+1; S = s;
                }
            }
        }
    }
    cout << X << "," <<  Y << "," << S; //dbg_var(maxSum); */

    /// Solution from subreddit
    int maxTot = -100;
	int maxX, maxY, maxsz;
	for(int sz = 1; sz <= 300; sz++) {
		for(int i = 0; i < 300 - sz + 1; i++) {
			for(int j = 0; j < 300 - sz + 1; j++) {
				int tot = 0;
				for(int k = 0; k < sz; k++) {
					for(int l = 0; l < sz; l++) {
						tot += grid[i+k][j+l];
					}
				}
				if(tot > maxTot) {
					maxTot = tot;
					maxX = i+1;
					maxY = j+1;
					maxsz = sz;
				}
			}
		}
	}
	cout << maxTot << " " << maxsz << " " << maxX << " " << maxY << endl;

    return 0;
}
