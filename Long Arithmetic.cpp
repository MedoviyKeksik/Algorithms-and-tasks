// Long Arithmetic BETA

struct BigInt {
    static const long long BASE = 1e9;
    static const long long SIZE = 100;

    long long digits[SIZE];

    BigInt() {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
    }

    BigInt(long long x) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
        int ind = 0;
        while (x) {
            digits[ind++] = x % BASE;
            x /= BASE;
        }
    }

    BigInt(const BigInt &other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }
    }

    BigInt& operator=(const BigInt &other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }

        return *this;
    }

    void operator+=(const BigInt &other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] += other.digits[i];
        }
        for (int i = 0; i < SIZE - 1; i++) {
            if (digits[i] > BASE ) {
                digits[i + 1] += digits[i] / BASE;
                digits[i] %= BASE;
            }
        }
    }

    BigInt operator+ (const BigInt &other) {
        BigInt n(*this);
        n += other;
        return n;
    }

    void operator-= (const BigInt &other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] -= other.digits[i];
        }
        for (int i = 0; i < SIZE - 1; i++) {
            if (digits[i] < 0) {
                digits[i] += BASE;
                digits[i + 1]--;
            }
        }
    }

    BigInt operator- (const BigInt &other) {
        BigInt n(*this);
        n -= other;
        return n;
    }

    bool operator== (const BigInt &other) {
        for (int i = 0; i < SIZE; i++) {
            if (digits[i] != other.digits[i]) return false;
        }
        return true;
    }

    bool operator> (const BigInt &other) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (digits[i] > other.digits[i]) return true;
            if (digits[i] < other.digits[i]) return false;
        }
        return false;
    }

    bool operator< (const BigInt &other) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (digits[i] < other.digits[i]) return true;
            if (digits[i] > other.digits[i]) return false;
        }
        return false;
    }

    void print() {
        long long cur_size = SIZE - 1;
        while (cur_size > 0 && digits[cur_size--] == 0);
        for (int i = cur_size; i >= 0; i--) {
            printf("%I64d", digits[i]);
        }
    }
};
