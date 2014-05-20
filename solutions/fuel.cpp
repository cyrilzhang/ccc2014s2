// CCC 2014 Stage 2
// Day 2, Problem 1: Where's That Fuel?
// Brian Bi

// Idea: Sort planets in order of increasing travel cost, skip planets that
// require more fuel to travel to than they provide, and stop if we reach a
// planet too expensive to travel to. O(N log N)
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int N, P; scanf("%d %d", &N, &P);
    vector<pair<int, int> > planets;
    for (int i = 1; i <= N; i++) {
        int a, b; scanf("%d %d", &a, &b);
        if (i == P) {
            // no fuel required to "travel" to initial planet
            b = 0;
        }
        planets.push_back(make_pair(b, a));
    }
    sort(planets.begin(), planets.end());
    int fuel = 0;
    int vis = 0;
    for (int i = 0; i < planets.size(); i++) {
        if (planets[i].first > fuel) {
            break;
        }
        if (planets[i].first <= planets[i].second) {
            vis++;
            fuel += planets[i].second - planets[i].first;
        }
    }
    printf("%d\n%d\n", fuel, vis);
}
