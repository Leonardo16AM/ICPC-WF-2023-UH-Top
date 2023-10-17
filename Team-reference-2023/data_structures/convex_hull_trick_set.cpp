template<typename T>
T cross(complex<T> a, complex<T> b) { return imag(conj(a) * b); }
template<typename T> 
T dot(complex<T> a, complex<T> b) { return real(conj(a) * b); }
struct __Query { static bool query; };
bool __Query::query = false;
template<typename T>
struct Point{
	complex<T> p;
	mutable function<const complex<T>*()> succ;
	bool operator<(const Point &rhs) const{
		const complex<T> &q = rhs.p;
		if (!__Query::query){
			if (real(p) != real(q))
				return real(p) < real(q);
			return imag(p) < imag(q);
		}
		const complex<T> *s = succ();
		if (!s) return false;
		return dot(p - *s, q) < 0;
	}
};
template<typename T, int turn>
struct half_hull : public set<Point<T>>{
	using set<Point<T>>::begin;
	using set<Point<T>>::insert;
	using set<Point<T>>::end;
	using set<Point<T>>::lower_bound;
	using set<Point<T>>::empty;
	using set<Point<T>>::erase;
	using typename set<Point<T>>::iterator;
	complex<T> extreme(const complex<T> &p) const{
		assert(!empty() && turn * imag(p) >= 0);
		__Query::query = true;
		auto pos = lower_bound(Point<T>{p});
		__Query::query = false;
		assert(pos != end());
		return pos->p;
	}
	void insert(const complex<T> &p){
		auto y = insert(Point<T>{p}).first;
		if (y == end()) return;
		y->succ = [=] { return next(y) == end() ? nullptr : &next(y)->p; };
		if (bad(y)) { erase(y); return; }
		while (y != begin() && bad(prev(y))) erase(prev(y));
		while (next(y) != end() && bad(next(y))) erase(next(y));
	}
private:
	bool bad(iterator y){
		if (y == begin() || y == end())
			return false;
		auto x = prev(y), z = next(y);
		if (z == end())
			return false;
		return cross(y->p - x->p, z->p - x->p) * turn >= 0;
	}
};
template<typename T>
struct convex_hull_trick{
	void insert(const complex<T> &p){
		lower_hull.insert(p);
		upper_hull.insert(p);
	}
	complex<T> extreme(const complex<T> &p) const{
		if (std::imag(p) < 0)
			return lower_hull.extreme(p);
		return upper_hull.extreme(p);
	}
private:
	half_hull<T, +1> upper_hull;
	half_hull<T, -1> lower_hull;
};
