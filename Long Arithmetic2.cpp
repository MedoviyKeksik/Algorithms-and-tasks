
class BigInt {
public:
    static const int base = 1e9;
    static const int num_base = 9;
    vector<int> digits;
    bool is_neg;

    void remove_leading_zeros() {
        while (this->digits.size() > 1 && this->digits.back() == 0) this->digits.pop_back();
        if (this->digits.size() == 1 && this->digits.back() == 0) this->is_neg = false;
    }

    BigInt() {
        this->is_neg = false;
        this->digits.push_back(0);
    }

    BigInt(long long x) {
        if (x < 0) this->is_neg = true;
        this->digits.push_back(abs(x));
    }

    BigInt(const string &s) {
        if (s.size() == 0) {
            this->is_neg = false;
            this->digits.push_back(0);
        } else {
            this->is_neg = s[0] == '-';
            for (int i = s.size(); i > 0 + is_neg; i -= num_base) {
                if (i < num_base + is_neg) {
                    digits.push_back(atoi(s.substr(0 + is_neg, i).c_str()));
                } else {
                    digits.push_back(atoi(s.substr(i - num_base, num_base).c_str()));
                }
            }
            remove_leading_zeros();
        }
    }

    BigInt(const BigInt &other) {
        *this = other;
    }

    string to_string() {
        string res, tmp;
        if (this->is_neg) res += '-';
        for (vector<int>::reverse_iterator it = this->digits.rbegin(); it != this->digits.rend(); it++) {
            tmp = std::to_string(*it);
            if (it != this->digits.rbegin()) {
                for (int i = 0; i < num_base - (int) tmp.size(); i++) res += '0';
            }
            res += tmp;
        }
        return res;
    }

    const BigInt& operator+() {
        return *this;
    }

    const BigInt& operator-() {
        this->is_neg ^= 1;
        return *this;
    }

    bool operator== (const BigInt &other) {
        if (is_neg ^ other.is_neg) {
            return false;
        }
        if (digits.size() != other.digits.size()) return false;
        for (int i = 0; i < (int) digits.size(); i++) {
            if (digits[i] != other.digits[i]) return false;
        }
        return true;
    }


    bool operator<(const BigInt &other) {
        if (is_neg ^ other.is_neg) {
            if (is_neg) return true;
            else return false;
        }
        if (digits.size() < other.digits.size()) return true ^ (is_neg ^ other.is_neg);
        if (digits.size() > other.digits.size()) return false ^ (is_neg ^ other.is_neg);
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] < other.digits[i]) return true ^ (is_neg ^ other.is_neg);
            if (digits[i] > other.digits[i]) return false ^ (is_neg ^ other.is_neg);
        }
        return false;
    }

    bool operator>(BigInt &other) {
        return other < *this;
    }


    void operator+=(const BigInt &other) {
        long long carry = 0, tmp = 0;
        for (int i = 0; i < (int) max(digits.size(), other.digits.size()) || carry; i++) {
            if (i == (int) digits.size()) {
                digits.push_back(0);
            }
            tmp = digits[i] + carry + (i < (int) other.digits.size() ?  other.digits[i] : 0);
            digits[i] = tmp % base;
            carry = tmp / base;
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
            if (carry) digits[i] += base;
        }
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    }

    BigInt operator-(const BigInt &other) {
        BigInt n(*this);
        n -= other;
        return n;
    }

};

ostream& operator<<(ostream& os, BigInt &a) {
    os << a.to_string();
    return os;
}
