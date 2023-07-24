template<const int _mod_>
struct mod_int
{
    static const int mod = _mod_;
    int val;

    mod_int(long long v = 0)
    {
        if (v < 0) v = v % mod + mod;
        if (v >= mod) v %= mod;
        val = v;
    }

    static int mod_inv(int a, int m = mod)
    {
        int g = m, r = a, x = 0, y = 1;
        while (r != 0)
        {
            int q = g / r;
            g %= r;
            swap(g, r);
            x -= q * y;
            swap(x, y);
        }
        return x < 0 ? x + m : x;
    }

    explicit operator int() const{return val;}

    mod_int& operator+=(const mod_int &other)
    {
        val += other.val;
        if (val >= mod) val -= mod;
        return *this;
    }

    mod_int& operator-=(const mod_int &other)
    {
        val -= other.val;
        if (val < 0) val += mod;
        return *this;
    }

    static unsigned fast_mod(uint64_t x, unsigned m = mod)
    {
#if !defined(_WIN32) || defined(_WIN64)
        return x % m;
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in a 32-bit integer.
        unsigned x_high = x >> 32, x_low = (unsigned) x;
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }

    mod_int& operator*=(const mod_int &other)
    {
        val = fast_mod((uint64_t) val * other.val);
        return *this;
    }

    mod_int& operator/=(const mod_int &other){return *this *= other.inv();}

    friend mod_int operator+(const mod_int &a, const mod_int &b){return mod_int(a) += b;}
    friend mod_int operator-(const mod_int &a, const mod_int &b){return mod_int(a) -= b;}
    friend mod_int operator*(const mod_int &a, const mod_int &b){return mod_int(a) *= b;}
    friend mod_int operator/(const mod_int &a, const mod_int &b){return mod_int(a) /= b;}

    mod_int& operator++()
    {
        val = val == mod - 1 ? 0 : val + 1;
        return *this;
    }

    mod_int& operator--()
    {
        val = val == 0 ? mod - 1 : val - 1;
        return *this;
    }

    mod_int operator++(int)
    {
        mod_int a = *this;
        ++*this;
        return a;
    }
    mod_int operator--(int)
    {
        mod_int a = *this;
        --*this;
        return a;
    }
    mod_int operator-() const{return val == 0 ? 0 : mod - val;}
    mod_int inv() const{return mod_inv(val);}

    bool operator==(const mod_int &other) const{return val == other.val;}
    bool operator!=(const mod_int &other) const{return val != other.val;}
    bool operator<(const mod_int &other) const{return val < other.val;}
    bool operator>(const mod_int &other) const{return val > other.val;}

    template<typename T>
    bool operator<(const T &other) const{return val < other;}

    template<typename T>
    bool operator>(const T &other) const{return val > other;}

    friend string to_string(const mod_int &m){return to_string(m.val);}
    friend mod_int abs(const mod_int &m){return mod_int(m.val);}

    friend ostream& operator<<(ostream &stream, const mod_int &m){return stream << m.val; }
    friend istream& operator>>(istream &stream, mod_int &m){return stream >> m.val;}
};
