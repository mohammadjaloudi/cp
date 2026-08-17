# Range Frequent Element Query ($k \le 3$)

A high-performance algorithmic solution for finding frequent elements in array subsegments, written in modern C++20.

---

## 📌 Problem Description

Given an array $A$ of size $N$, an integer parameter $k$ ($1 \le k \le 3$), and $Q$ range queries $[L, R]$ (1-based index):

Find an element $x$ in $A[L \dots R]$ whose frequency satisfies:
$$\text{Frequency}(x, L, R) \ge \left\lceil \frac{R - L + 1}{k} \right\rceil \iff \text{Frequency}(x, L, R) \times k \ge (R - L + 1)$$

### Output Rules & Constraints
* **Tie-Breaking Rule**: If multiple distinct elements satisfy the threshold, output the **minimum numeric value**.
* **None Found**: If no element meets the criteria, output `-1`.
* **Constraints**: $1 \le N, Q \le 2 \times 10^5$, $1 \le A[i] \le 10^9$, $1 \le k \le 3$.

---

## 💡 Key Mathematical Insights

### 1. Bounded Candidate Count (Pigeonhole Principle)
Since $k \le 3$, any qualifying element must occupy at least $33.3\%$ of the range. By the Pigeonhole Principle, **at most 3 distinct numbers** can satisfy this threshold in any range simultaneously:
* $k = 1$: At most $1$ candidate ($100\%$ majority)
* $k = 2$: At most $2$ candidates ($\ge 50\%$)
* $k = 3$: At most $3$ candidates ($\ge 33.3\%$)

### 2. $O(\log N)$ Frequency Query via Binary Search
By storing 0-based indices for each value $v$ in a sorted vector `pos[v]`, the exact count in range $[L, R]$ is calculated in $O(\log N)$:
$$\text{freq}(v, L, R) = \text{upper\_bound}(pos[v], R) - \text{lower\_bound}(pos[v], L)$$

---

## 🚀 Solutions Included

| Solution | Time Complexity | Space Complexity | Guarantee |
| :--- | :--- | :--- | :--- |
| **Deterministic Segment Tree** | $O((N + Q) \log^2 N)$ | $O(N \log N)$ | 100% Deterministic AC |
| **Monte Carlo Sampling** | $O(N \log N + Q \cdot M \log N)$ | $O(N)$ | Probabilistic ($P_{error} < 10^{-7}$) |

---

## 🛠️ Compilation & Execution

```bash
