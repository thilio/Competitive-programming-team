/*
	Title: Modular Int
	Description: Definitions and operations of type ModInt
	Complexity:
		Everything is O(1), except for the functions "/" and "pow",
		which are O(log (something)).

	Details: You may use it in the same way that you use "int" type.
*/

template<int mod>
struct modInt {
  	unsigned x;
  	modInt() : x(0) { }
	modInt(signed sig) : x((sig%mod + mod)%mod) {  }
	modInt(signed long long sig) : x((sig%mod + mod)%mod) { }
	int get() const { return (int)x; }
	modInt pow(ll p) { 
		modInt res = 1, a = *this; 
		while (p) { 
			if (p & 1) res *= a; 
			a *= a; p >>= 1; 
		} 
		return res; 
	}
	 
 	modInt &operator+=(modInt that) { if ((x += that.x) >= mod) x -= mod; return *this; }
	modInt &operator-=(modInt that) { if ((x += mod - that.x) >= mod) x -= mod; return *this; }
	modInt &operator*=(modInt that) { x = (__int128)x * that.x % mod; return *this; }
	modInt &operator/=(modInt that) { return (*this) *= that.pow(mod - 2); }
	 
	modInt operator+(modInt that) const { return modInt(*this) += that; }
	modInt operator-(modInt that) const { return modInt(*this) -= that; }
	modInt operator*(modInt that) const { return modInt(*this) *= that; }
	modInt operator/(modInt that) const { return modInt(*this) /= that; }
	bool operator<(modInt that) const { return x < that.x; }
	bool operator>(modInt that) const { return x > that.x; }
	friend ostream& operator<<(ostream &os, modInt a) { os << a.x; return os; }
	friend istream& operator>>(istream &is, modInt &a) { is >> a.x; return is; }
};
typedef modInt<1000000007> mint;
