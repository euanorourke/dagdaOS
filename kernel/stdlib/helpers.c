unsigned long long __udivdi3(unsigned long long n, unsigned long long d) {
    unsigned long long q = 0;
    while (n >= d) {
        n -= d;
        q++;
    }
    return q;
}

unsigned long long __umoddi3(unsigned long long n, unsigned long long d) {
    while (n >= d) {
        n -= d;
    }
    return n;
}

unsigned long long __udivmoddi4(unsigned long long n, unsigned long long d, unsigned long long *rem) {
    unsigned long long q = 0;
    while (n >= d) {
        n -= d;
        q++;
    }
    if (rem) {
        *rem = n;
    }
    return q;
}