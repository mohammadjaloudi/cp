// #define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

// don't forget to include these
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// this using is necessary
using namespace __gnu_pbds;

using namespace std;

// ordered_set
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ordered_multiset
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    // we defined the type <here>
    ordered_set<int> st;

    // insertion
    st.insert(10);
    st.insert(20);
    st.insert(30);

    // find_by_order(k);
    // finds the element at index k in a zero-based index
    // returns an iterator (to use the real value we do *it)
    auto it = st.find_by_order(1);
    if(it != st.end()) cout << (*it) << endl;
    
    // order_of_key(k)
    // returns the number of elements strictly smaller than k
    // k doesn't need to exist in the set itself
    cout << st.order_of_key(25) << endl;
    
    // we can use standard set operations
    
    // insertion
    st.insert(5);
    // size
    cout << st.size() << endl;
    
    // erase
    // fast
    auto it2 = st.find_by_order(2);
    st.erase(it2);

    // slow
    st.erase(20);
    
    // is empty
    cout << st.empty() << endl;

    // lower and upper bound
    auto lb = st.lower_bound(10);
    if(lb != st.end()) cout << (*lb) << endl;
    
    auto ub = st.upper_bound(10);
    if(ub != st.end()) cout << (*ub) << endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int TESTCASES = 1;
    // cin >> TESTCASES;
    while (TESTCASES--) solve();
 
    return 0;
}
