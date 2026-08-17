# Range Frequent Element Query 

## 📌 Problem Description

Given an array $A$ of size $N$, an integer parameter $k$ ($1 \le k \le 3$), and $Q$ range queries $[L, R]$ (1-based index):

Find an element $x$ in $A[L \dots R]$ whose frequency satisfies:

$$ \text{Frequency}(x, L, R) \ge \left\lceil \frac{R - L + 1}{k} \right\rceil $$

This is mathematically equivalent to:

$$ \text{Frequency}(x, L, R) \times k \ge (R - L + 1) $$

### Output Rules & Constraints
* **Tie-Breaking Rule**: If multiple distinct elements satisfy the threshold, output the **minimum numeric value**.
* **None Found**: If no element meets the criteria, output `-1`.
* **Constraints**: $1 \le N, Q \le 2 \times 10^5$, $1 \le A[i] \le 10^9$, $1 \le k \le 3$.

---

## 💡 Key Mathematical Insights

### 1. Bounded Candidate Count (Pigeonhole Principle)
Since $k \le 3$, any qualifying element must occupy at least 33.3% of the queried range. By the Pigeonhole Principle, a strictly limited number of distinct elements can satisfy this threshold simultaneously:
* **$k = 1$**: At most **1** candidate (100% majority)
* **$k = 2$**: At most **2** candidates ($\ge$ 50%)
* **$k = 3$**: At most **3** candidates ($\ge$ 33.3%)

### 2. Fast Frequency Querying
By storing 0-based indices for each unique value $v$ in a sorted vector `pos[v]`, we can calculate the exact occurrence count of any element in a range $[L, R]$ in $O(\log N)$ time using binary search:

$$ \text{freq}(v, L, R) = \mathtt{upper\_bound}(pos[v], R) - \mathtt{lower\_bound}(pos[v], L) $$

*(Note: Coordinate compression is used internally to map $A[i] \le 10^9$ to $O(N)$ space).*

---

## 🚀 Included Algorithms

| Solution | Time Complexity | Space Complexity | Guarantee |
| :--- | :--- | :--- | :--- |
| **Deterministic Segment Tree** | $O((N + Q) \log^2 N)$ | $O(N \log N)$ | 100% Deterministic AC |
| **Monte Carlo Sampling** | $O(N \log N + Q \cdot M \log N)$ | $O(N)$ | Probabilistic ($P_{error} < 10^{-7}$) |

### Method 1: Segment Tree (Deterministic)
Builds a segment tree where each node maintains a list of up to 3 candidate elements that appear with $\ge$ 33.3% frequency in that specific segment. When querying a range, we extract $O(\log N)$ canonical segments, collect their candidates, and verify their exact frequencies in the total queried range.

### Method 2: Monte Carlo (Probabilistic)
Randomly samples $M$ elements uniformly from the queried range $[L, R]$. If an element satisfies the frequency threshold, there is at least a $1/k$ probability of picking it in a single draw. With $M = 50$ iterations, the probability of missing a valid candidate is infinitesimally small.

---
