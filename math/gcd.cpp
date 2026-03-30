#include <iostream>
#include <type_traits>
#include <bit> 
#include <utility>

template <typename T>
constexpr T hybrid_gcd(T a, T b) {
    static_assert(std::is_integral_v<T>, "gcd requires integer types");

    // 1. Safety & Normalization: Convert to unsigned to avoid negative issues
    using U = std::make_unsigned_t<T>;
    U u = a < 0 ? -static_cast<U>(a) : static_cast<U>(a);
    U v = b < 0 ? -static_cast<U>(b) : static_cast<U>(b);

    // Base cases
    if (u == 0) return v;
    if (v == 0) return u;

    // 2. The Euclidean Leap: If inputs are heavily skewed, use modulo
    // The multiplier (8) is a heuristic threshold. If one is 8x larger, 
    // the modulo division pays for itself in saved loop iterations.
    if (u >= v * 8) u %= v;
    else if (v >= u * 8) v %= u;

    // Check base cases again in case the modulo resulted in 0
    if (u == 0) return v;
    if (v == 0) return u;

    // 3. Binary GCD (Stein's Algorithm): Fast bitwise finish
    // std::countr_zero compiles down to blazing fast CPU instructions (like tzcnt)
    int shift = std::countr_zero(u | v); // Common power of 2
    
    u >>= std::countr_zero(u); // Strip 2s from u

    while (v != 0) {
        v >>= std::countr_zero(v); // Strip 2s from v
        
        if (u > v) {
            std::swap(u, v);
        }
        v -= u; // v is always the larger number, subtract the smaller
    }

    // Multiply the common power of 2 back in
    return static_cast<T>(u << shift); 
}
