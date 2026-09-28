const int N = 1e6 + 5;
vector<int> spf(N);

void buildSPF() {
    for (int i = 0; i < N; i++)
        spf[i] = i;

    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}
