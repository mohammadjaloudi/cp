// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,lzcnt,popcnt,abm,mmx,avx,avx2,bmi,bmi2")

// typedef tree<int, null_type, less_equal<int>, rb_tree_tag, 
//              tree_order_statistics_node_update> ordered_multiset;

// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 rnd2(chrono::steady_clock::now().time_since_epoch().count());

#define int long long
#define int64 long long
#define endl "\n"
#define pb push_back
#define all(x) x.begin(), x.end()
#define print(x) for(auto i : x) cout << i << ' ';

// EPS (Epsilon) is our tiny tolerance value for floating-point comparisons
const double EPS = 1e-9;
long long MOD = 1e9 + 7;
long long INF = 1e18;
long long mod = 998244353;
int mx = 2e6;

// Structure to hold a 2D coordinate
struct point {
    double x, y;
};

// Standard Euclidean distance formula between two points
double distance(point p1, point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Calculates the radius of the circumcircle (the circle passing through p1, p2, p3)
double rad(point p1, point p2, point p3) {
    // Get side lengths of the triangle formed by the three points
    double a = distance(p1, p2);
    double b = distance(p1, p3);
    double c = distance(p2, p3);

    // Cross product to check if points are collinear (on a straight line)
    // If the cross product is ~0, they form a line, not a triangle, so no finite circle exists
    double cross_prod = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if(abs(cross_prod) < EPS) return -1.0; // Return invalid radius

    // Heron's Formula to find the area of the triangle
    double s = (a + b + c) / 2.0; // Semi-perimeter
    double area = sqrt(s * (s - a) * (s - b) * (s - c)); // Area (K)
    
    // Circumradius formula: R = (a * b * c) / (4 * Area)
    double r = a * b * c / (4.0 * area);
    return r;
}

// Calculates the exact (x, y) center of the circumcircle using Cartesian coordinates
point center(point p1, point p2, point p3) {
    // The common denominator 'D' (which is 4 times the signed area of the triangle)
    double D = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    
    // Calculate the square of the distance from the origin for each point
    double p1_sq = p1.x * p1.x + p1.y * p1.y;
    double p2_sq = p2.x * p2.x + p2.y * p2.y;
    double p3_sq = p3.x * p3.x + p3.y * p3.y;

    // Apply Cramer's rule to find the intersection of the perpendicular bisectors
    point center;
    center.x = (p1_sq * (p2.y - p3.y) + p2_sq * (p3.y - p1.y) + p3_sq * (p1.y - p2.y)) / D;
    center.y = (p1_sq * (p3.x - p2.x) + p2_sq * (p1.x - p3.x) + p3_sq * (p2.x - p1.x)) / D;
    
    return center;
}

void solve() {
    int n;
    cin >> n;
    vector<point> p(n);
    for(int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

    // A circle can always pass through at least 2 points (unless n < 2, but problem constraints usually say n >= 2)
    int ans = 2;
    
    // O(N^3) loops to fix three points to define a unique circle
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                
                // Get the radius of the circle formed by points i, j, k
                double r = rad(p[i], p[j], p[k]);
                
                // If r < 0, the 3 points are collinear (form a line), so we skip them
                if(r < 0) continue;
                
                // Find the specific center coordinate of this circle
                point c = center(p[i], p[j], p[k]);
                
                int curr = 0;
                // O(N) loop to check every point against the current circle
                for(int m = 0; m < n; m++) {
                    // Find the distance from the center to point m
                    double dist = distance(c, p[m]);
                    
                    // If the distance equals the radius (within our EPS margin of error),
                    // the point lies on the circumference of the circle!
                    if(abs(dist - r) <= EPS) curr++;
                }

                // Update the maximum points found on any valid circle so far
                ans = max(ans, curr);
            }
        }
    }

    cout << ans << endl;
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // cout << fixed << setprecision(7);

    int TESTCASES = 1;
    cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
