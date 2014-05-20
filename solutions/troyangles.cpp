// CCC 2014 Stage 2
// Day 1, Problem 1: Troyangles
// Aaron Voelker

#include <cstdio>

#define MIN(a, b) ((a)<(b) ? (a) : (b))
#define MAX_N 10001

using namespace std;

int main() {
    static char grid[MAX_N][MAX_N];
    static long long dp[MAX_N][MAX_N];
    
    int i, j, n;
    long long count=0;
    
    scanf("%d", &n);    
    for (i=0; i<n; i++) {
        scanf("%s", grid[i]);
    }
    
    for (i=n-1; i>=0; i--) {
        for (j=0; j<n; j++) {
            if (grid[i][j] != '#') {
                dp[i][j] = 0;
            } else if (j==0 || j==n-1 || i==n-1 || grid[i+1][j] != '#') {
                dp[i][j] = 1;
            } else {
                dp[i][j] = MIN(dp[i+1][j-1], dp[i+1][j+1]) + 1;
            }
            count += dp[i][j];
        }
    }

    printf("%lld\n", count);    
    return 0;   
}
