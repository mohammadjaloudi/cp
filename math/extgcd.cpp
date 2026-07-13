#include <iostream>
#include <cmath>

using namespace std;

// Extended Euclidean Algorithm
// Returns gcd(a, b) and sets x, y such that a*x + b*y = gcd(a, b)
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Finds a single solution to a*x + b*y = n
// Returns true if a solution exists, false otherwise
bool find_any_solution(long long a, long long b, long long n, long long &x, long long &y) {
    // Edge case: both coefficients are 0
    if (a == 0 && b == 0) {
        if (n == 0) {
            x = 0; y = 0; // Infinite solutions exist
            return true;
        }
        return false;
    }
    
    long long x0, y0;
    // Use absolute values to avoid negative modulo behavior in C++
    long long g = extGCD(abs(a), abs(b), x0, y0);
    
    // Solution exists iff gcd(a, b) divides n
    if (n % g != 0) {
        return false; 
    }
    
    // Scale the solution
    long long scale = n / g;
    x = x0 * scale;
    y = y0 * scale;
    
    // Adjust signs based on the original a and b
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    
    return true;
}

void solve() {
    long long a, b, n, x, y;
    // Example: 15x + 26y = 7
    a = 15; b = 26; n = 7;
    
    if (find_any_solution(a, b, n, x, y)) {
        cout << "Solution found: x = " << x << ", y = " << y << "\n";
    } else {
        cout << "No solution exists.\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}
