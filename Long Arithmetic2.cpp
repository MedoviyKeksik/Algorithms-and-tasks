struct BigInt {
    static const long long BASE = 1e9;
    static const long long num_base = 9;
    vector <long long> digits;

    BigInt() {
        digits.clear();
        digits.push_back(0);
    }

    BigInt(long long x) {
        digits.clear();
        while (x) {
            digits.push_back(x % BASE);
            x /= BASE;
        }
    }

    BigInt(const BigInt &other) {
        digits.assign(other.digits.begin(), other.digits.end());
    }

    BigInt(string s) {
        for (int i = s.size(); i > 0; i -= num_base) {
            if (i < num_base) {
                digits.push_back(atoi(s.substr(0, i).c_str()));
            } else {
                digits.push_back(atoi(s.substr(i - num_base, num_base).c_str()));
            }
        }
    }

    BigInt& operator=(const BigInt &other) {
        digits.assign(other.digits.begin(), other.digits.end());
        return *this;
    }

    void operator+=(const BigInt &other) {
        long long carry = 0;
        for (int i = 0; i < (int) max(digits.size(), other.digits.size()) || carry; i++) {
            if (i == (int) digits.size()) {
                digits.push_back(0);
            }
            digits[i] += carry + (i < (int) other.digits.size() ?  other.digits[i] : 0);
            carry = digits[i] / BASE; digits[i] %= BASE;
            // pr_v(digits);
        }
    }

    BigInt operator+(const BigInt &other) {
        BigInt n(*this);
        n += other;
        return n;
    }

    void operator-=(const BigInt &other) {
        long long carry = 0;
        for (int i = 0; i < (int) other.digits.size() || carry; i++) {
            digits[i] -= carry + (i < (int) other.digits.size() ? other.digits[i] : 0);
            carry = digits[i] < 0;
            if (carry) digits[i] += BASE;
        }
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    }

    BigInt operator-(const BigInt &other) {
        BigInt n(*this);
        n -= other;
        return n;
    }

    bool operator== (const BigInt &other) {
        if (digits.size() != other.digits.size()) return false;
        for (int i = 0; i < (int) digits.size(); i++) {
            if (digits[i] != other.digits[i]) return false;
        }
        return true;
    }

    bool operator>(const BigInt &other) {
        if (digits.size() > other.digits.size()) return true;
        if (digits.size() < other.digits.size()) return false;
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] > other.digits[i]) return true;
            if (digits[i] < other.digits[i]) return false;
        }
        return false;
    }

    bool operator<(const BigInt &other) {
        if (digits.size() < other.digits.size()) return true;
        if (digits.size() > other.digits.size()) return false;
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] < other.digits[i]) return true;
            if (digits[i] > other.digits[i]) return false;
        }
        return false;
    }

    void print() {
        printf("%I64d", digits.back());
        for (int i = (int) digits.size() - 2; i >= 0; i--) {
            printf("%09I64d", digits[i]);
        }
    }

};
